#include <FlexCAN_T4.h>

/**
 * An implementation of the communication protocol used by LKTech LF-series CAN bus integrated servo motors:
 * http://en.lkmotor.cn/Product.aspx?TypeID=17
 *
 * This is makes use of the only available multi-motor command (closed loop torque control) for greater efficiency
 * than sending individual commands; though it still must use individual commands for powering on/off each motor.
 *
 * Pass `0` as the direction of a motor to disable it.
 */
struct Servos
{
  FlexCAN_T4<CAN1, RX_SIZE_1024, TX_SIZE_16> canBus;

  uint16_t identifiers[4] = {0x141, 0x142, 0x143, 0x144};
  int8_t directions[4];
  bool poweredOn = true;
  uint16_t currentLimit = 2048;

  Servos(uint16_t _currentLimit, int _direction1, int _direction2 = 0, int _direction3 = 0, int _direction4 = 0)
  {
    currentLimit = min(2048, max(1, _currentLimit));
    directions[0] = _direction1;
    directions[1] = _direction2;
    directions[2] = _direction3;
    directions[3] = _direction4;

    canBus.begin();
    canBus.setBaudRate(1000000);

    powerOff();
  }

  /**
   * Powers on each motor, where not currently powered. Motors with `0` as their configured direction are ignored.
   */
  void powerOn()
  {
    if (!poweredOn) {
      for (uint8_t m = 0; m < 4; m++) {
        if (directions[m] != 0) {
          sendMessage(identifiers[m], 0x88);
        }
      }
      poweredOn = true;
    }
  }

  /**
   * Powers off each motor, where currently powered. Motors with `0` as their configured direction are ignored.
   */
  void powerOff() 
  {
    if (poweredOn) {
      for (uint8_t m = 0; m < 4; m++) {
        if (directions[m] != 0) {
          sendMessage(identifiers[m], 0x80);
        }
      }
      poweredOn = false;
    }
  }

  /**
   * Sets the motor torque to absolute values for motors with identifiers 1-4.
   * 
   * @param torque1 The torque to set motor 1 to, clamped to the current limit
   * @param torque2 The torque to set motor 2 to, clamped to the current limit
   * @param torque3 The torque to set motor 3 to, clamped to the current limit
   * @param torque4 The torque to set motor 4 to, clamped to the current limit
   */
  void setTorques(int16_t torque1, int16_t torque2 = 0, int16_t torque3 = 0, int16_t torque4 = 0)
  {
    int negativeCurrentLimit = currentLimit * -1;

    torque1 = max(negativeCurrentLimit, min(currentLimit, torque1)) * directions[0];
    torque2 = max(negativeCurrentLimit, min(currentLimit, torque2)) * directions[1];
    torque3 = max(negativeCurrentLimit, min(currentLimit, torque3)) * directions[2];
    torque4 = max(negativeCurrentLimit, min(currentLimit, torque4)) * directions[3];

    sendMessage(
      0x280,
      getByte(torque1, 0), getByte(torque1, 1),
      getByte(torque2, 0), getByte(torque2, 1),
      getByte(torque3, 0), getByte(torque3, 1),
      getByte(torque4, 0), getByte(torque4, 1)
    );
  }

  /**
   * Sets the motor torque proportionally to the maximum available for motors with identifiers 1-4. Where no
   * load is applied, this will result in the motor spinning freely at an indeterminate speed. Direction is
   * determined by the sign of the value (which is later affected by each motor's configured direction).
   * 
   * @param proportion1 The proportion of the maximum torque to apply to motor 1, in the range of -1.0 ~ 1.0
   * @param proportion2 The proportion of the maximum torque to apply to motor 2, in the range of -1.0 ~ 1.0
   * @param proportion3 The proportion of the maximum torque to apply to motor 3, in the range of -1.0 ~ 1.0
   * @param proportion4 The proportion of the maximum torque to apply to motor 4, in the range of -1.0 ~ 1.0
   */
  void setProportionalTorques(float proportion1 = 0.0, float proportion2 = 0.0, float proportion3 = 0.0, float proportion4 = 0.0)
  {
    proportion1 = max(-1.0, min(1.0, proportion1));
    proportion2 = max(-1.0, min(1.0, proportion2));
    proportion3 = max(-1.0, min(1.0, proportion3));
    proportion4 = max(-1.0, min(1.0, proportion4));

    setTorques(proportion1 * currentLimit, proportion2 * currentLimit, proportion3 * currentLimit, proportion4 * currentLimit);
  }

  /**
   * Constucts and sends the given bytes to the motor controller(s). Messages are fixed-length, so substitute
   * NULL where a byte is unpopulated.
   * 
   * @param identifier The numeric identifier of the motor (0x280 for multi-motor commands)
   * @param byte0 The first byte of the message (the 'command' byte indicating the type of command)
   * @param byte1 The second byte of the message
   * @param byte2 The third byte of the message
   * @param byte3 The fourth byte of the message
   * @param byte4 The fifth byte of the message
   * @param byte5 The sixth byte of the message
   * @param byte6 The seventh byte of the message
   * @param byte7 The eighth byte of the message
   * 
   * @return Whether the message was successfully sent (though not necessarily received)
   */
  bool sendMessage(
    uint32_t identifier,
    uint8_t byte0,
    uint8_t byte1 = 0x00,
    uint8_t byte2 = 0x00,
    uint8_t byte3 = 0x00,
    uint8_t byte4 = 0x00,
    uint8_t byte5 = 0x00,
    uint8_t byte6 = 0x00,
    uint8_t byte7 = 0x00
  ) {
    CAN_message_t message;

    message.id = identifier;
    message.len = 8;
    message.flags.remote = 0;
    message.buf[0] = byte0;
    message.buf[1] = byte1;
    message.buf[2] = byte2;
    message.buf[3] = byte3;
    message.buf[4] = byte4;
    message.buf[5] = byte5;
    message.buf[6] = byte6;
    message.buf[7] = byte7;

    return (canBus.write(MB11, message) == 1);
  }

  uint8_t getByte(int32_t value, uint8_t index)
  {
    if (index >= sizeof(value)) {
      return 0x00;
    }

    return *((uint8_t *)(&value) + index);
  }

};
