/**
 * Active Belt Tensioner
 *
 * Developed by George Wilkins
 *
 * This main Sketch file contains the telemetry reading logic, along with hard-coded configuration values (those not
 * provided by SimHub as part of its telemetry payload).
 *
 * The included file(s) contain supporting functions and lower-level communications protocol logic for the integrated
 * servo motors.
 */
#include "Servos.h"

/**
 * These values represent the current state of the tensioner and are populated from the SimHub telemetry.
 */
float leftTorque = 0.0;
float rightTorque = 0.0;
float restingTorque = 0.04;

/**
 * In situations where no telemetry is received for some time, we go into an idle state, applying the idle torque
 * to simulate 'sprung' belts (meaning the they always self-wind onto the pulleys).
 */
long unsigned int telemetryTimeout = 1000;
elapsedMillis telemetryLastReceived;

/**
 * The `Servos` struct uses a command that supports four motors; but we're only using two. Therefore we set the first
 * two to opposite directions and leave the latter two disabled. Our two motors are expected to be configured with the
 * identifiers `1` and `2` (achieved using their physical DIP-switches or through the LKTech configurator application).
 */
Servos servos = Servos(600, -1, 1, 0, 0);

/**
 * Not much setup to do here; just enable the motors.
 */
void setup() {

  delay(5000);

  servos.powerOn();

}

/**
 * The main loop is responsible for parsing incoming torque targets from SimHub; which come in at 60Hz. We watch for
 * the prefix character (`|`) in the serial buffer, then use standard serial parsing functions to read the given values.
 * These automatically wait for a suitable value to become available in the buffer, so we don't need to wait for
 * additional incoming data using a loop.
 *
 * The 'Custom Serial Device' in SimHub must be created and configured to send the following output:
 * https://github.com/SHWotever/SimHub/wiki/Custom-serial-devices
 *
 * return '|' + [
 *   500, // Your Left Motor Target Torque 0-1000
 *   500, // Your Right Motor Target Torque 0-1000
 *   50 // Your Idle Target Torque 0-1000
 * ].join(',');
 *
 * Since the calculations for target torque on each motor are relatively simple, we do them in JavaScript within
 * SimHub and send only the final torque values to this controller. That keeps the microcontroller code simple and
 * allows full control over the way tensioner effects are applied without needing to reflash the Sketch each time.
 *
 * A fully implemented JS script is included with this codebase, along with an importable SimHub device file.
 */
void loop() {

  // Wait For Telemetry
  while (Serial.available()) {

    if (Serial.read() != '|') {
      continue;
    }

    // Parse Telemetry
    leftTorque = Serial.parseInt() * 0.001;
    rightTorque = Serial.parseInt() * 0.001;
    restingTorque = Serial.parseInt() * 0.001;

    telemetryLastReceived = 0;

    servos.setProportionalTorques(leftTorque, rightTorque);

  }

  // Apply Retraction Spring (Where Idle)
  if (telemetryLastReceived >= telemetryTimeout) {

    servos.setProportionalTorques(restingTorque, restingTorque);

    delay(500);

  }
}
