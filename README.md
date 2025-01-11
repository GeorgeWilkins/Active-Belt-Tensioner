# Active-Belt-Tensioner
A dual-channel sim racing belt tensioner using BLDC integrated servo motors.

Active belt tensioners are a form of haptic feedback device that simulate the forces experienced by a driver within a
moving vehicle. They achieve this by tightening and loosening the shoulder belts of a 5-point racing harness attached to
the seat, based on in-game telemetry (`surge`, `sway` and `heave`).

The application these forces contributes towards tricking the brain into thinking it is moving; tyipcally in conjunction
with other haptic feedback devices (tactile transducers, active seat bolsters, etc).

![Tensioner](https://github.com/user-attachments/assets/6d587ca9-4f6c-4fff-9fca-a998e93d5bd5)
![Belts](https://github.com/user-attachments/assets/22cb0579-bec0-4348-a225-a12360df4b75)
![Roller](https://github.com/user-attachments/assets/f8426194-8992-4687-9eb4-959cdfdd55db)
![Motors](https://github.com/user-attachments/assets/e4d272a8-f83f-47a7-8f84-d64874970974)

### Video Demonstration
This shows the tensioner running from a SimHub telemetry replay. All other output on the rig (such as game audio and tactile
transducers) has been disabled, so the sound you hear is the servo motors. This is not normally audible during gameplay.

[![Watch A Video](https://github.com/user-attachments/assets/6d32fb89-c11b-46d1-a0b9-402ca5471bf7)](https://www.youtube.com/watch?v=mdPK2OQolQc)

## Important
⚠ This project involves potentially dangerous _electrical_ and _mechanical_ components. There are various _electrocution_,
_burning_, _fire_ and _crushing_ hazards associated with its construction and use. This documentation is provided not as
a guide, but as a record of the author's work. If you choose to replicate this project, you do so **entirely at your own
risk**.

Similarly, no warranty or support is provided for this project. The author is not responsible for any damage, injury or
expenses incurred by those who choose to replicate this project.

The device described in this documentation is a **prototype** and has in no way been tested for long-term reliability or
safety.

## Features
The included [sample code](#) offers the following features:
- **Idle Spring:** While not in a game session, the belts apply a small self-winding torque (as if spring-loaded), meaning
  any slack is always automatically wound up into the motor pulleys
- **Breaking:** Under _deceleration_, the belts will tighten proportionally, simulating your body being pushed against
  the belts as it wants to continue moving forward at the same velocity
- **Acceleration:** Under _acceleration_, the belts will loosen proportionally, simulating your body being pulled back
  into the seat as it resists the change in velocity
- **Cornering:** Under _lateral cornering forces_, the belts will indepenently tighten proportionally, simulating your
  body being pushed against either side of the vehicle

### Further Customisation
You can modify the behaviour of this device in a few ways:
- **Device Settings (SimHub):** The _Custom Serial Device_ UI in SimHub offers a number of sliders that allow you to
  easily adjust the strength of pre-defined effects without needing to touch the code
- **JavaScript Code (SimHub):** All of the telemetry-based effects are written in JavaScript and can be edited within
  SimHub, allowing relatively easy customisation of the effects to any degree you desire; simply by sending torque values
  (`-1.0`-`1.0`) to the controller for the left and right belts (in addition to an idle spring torque)
- **Teensy C++ Code:** The low-level motor control code is written in C++ and located on the microcontroller. It should
  not need to be amended in most cases, but can be edited and re-flashed to the Teensy using the Arduino IDE if desired

## Reccomendation
This device is intended to be attached to a dedicated sim racing rig; a tubular steel or aluminium profile frame with a
racing-style seat (with appropriate belt holes and fixing points).

Before considering adding a belt tensioner, you will _ideally_ already have:
- A direct-drive wheel and load-cell pedals
- Multiple tactile transducers (bass shakers)
- Positional audio

These items are generally simpler to implement and will have a _significant_ positive impact on your immersion. A belt
tensioner absolutely adds to the experience, but should not be your top priority.

## Prerequisites
- You **must** have a 5 or 6-point harness for this to work effectively, as the absence of a crotch strap will cause the
  belts to simply move _upwards_, rather than pin you into the seat. It may be possible to use a 4-point harness if you
  have all four belts attached to the tensioner pulleys, but this is not a configuration I have tested
- A **licensed** copy of [SimHub](https://www.simhubdash.com/get-a-license/) is required to communicate game telemetry
  data to the controller at the desired frequency

## Parts, Materials & Pricing
The total BOM cost for this project is approximately **£350** at the time of writing, including the laser-cut acrylic
parts. This does not include the cost of the seat, harness or other prerequisite equipment.

Where provided, links are simply for reference and not recommendations. Many of the parts are not available individually,
so must be bought in bulk. The total given should be enough to cover the required quantity; likely with plenty of spares.

If you're prepared to change the design yourself to fit what you already have, you can probably eliminate a few of these
components.

![Assembled Prototype](https://github.com/user-attachments/assets/20adceba-4a37-4b92-ac0b-1307ab532011)

| Component | Quantity | Name | Description | Notes | Total |
| --- | --- | --- | --- | --- | --- |
| Microcontroller | 1 | [Teensy 4.0](https://shop.pimoroni.com/products/teensy-4-0-development-board?variant=29443577217107) | A powerful microcontroller with built-in CanBus controller (but not transciever). Provides the connection between the host computer and motors | | £22 |
| CanBus Transciever | 1 | [SN65HVD230](https://www.aliexpress.com/item/1005006408102971.html) | A CanBus transciever to convert the Teensy CanBus commands into a signal compatible with motor controller | | £1 | £1 |
| Servo Motor | 2 | [LKTech MF9015v2 35T-CAN-18BIT](http://en.lkmotor.cn/ProDetail.aspx?ProId=246) | A high-torque BLDC gimbal motor with FOC control and integrated driver | Modified to add (supported but unpopulated) braking resistors | £200 |
| Braking Resistor | 2 | [100W 6 Ohm Power Resistor](https://www.amazon.co.uk/gp/product/B0BTHJRVF1) | Large aluminium-sinked resitors to dissipate the energy generated by the motors when back-driven | Modified with drilled and tapped mounting holes (or use thermal adhesive) | £8 |
| Protection Diode | 2 | >5A > 30V Diode (SR5100, 20SQ045?) | Theoretically helps to protect the power supply from back-EMF generated by the motors | May not be neccessary; need to test further | £4 |
| Pulley Wire | ~2 metre | [2mm PVC-Coated Wire](https://www.amazon.co.uk/Aoktorkit-Coated-Stainless-Strand-Climbing/dp/B0D86VZGFL) | Steel core coated wire to connect the pulleys to the belts | Around 1 metre for each belt; will depend on your rig | £9 |
| Silicone Wire | ~1 metre | [22AWG Silicone Wire](https://www.amazon.co.uk/gp/product/B0CG2SCCPB) | Connects the braking resistors to the motor pads | Silicone sleeving preferred for heat resistance | £10 |
| Aluminium Spacer | 11 | [40mm ⌀7mm M4 Aluminium Spacers](https://www.aliexpress.com/item/1005002348335932.html) | Round threaded spacers to attach the front and rear acylic plates together, creating a cage around the motors and pulleys | | £8 |
| Aluminium Spacer | 4 | [12mm ⌀7mm M4 Aluminium Spacers](https://www.aliexpress.com/item/1005002348335932.html) | Round threaded spacers to attach the protoboard tray to the cooling plates | | £4 |
| Grub | 4 | M4x20mm Grub Screw | Attach the motors and the protoboard tray to the cooling plates | | £0 |
| Grub | 6 | M4x5mm Grub Screw | Secures the steel wire into the belt loops | I've used sprung-bearing pointed grubs, but any type will do | £0 |
| Bolt | 4 | M4x16mm Hex-Head Bolt | Attach the cooling plates to motors | | £0 |
| Bolt | 30 | M4x12mm Hex-Head Bolt | Attach the acrylic plates to the aulminium spacers and motors to the acrylic plates | | £0 |
| Bolt | 8 | M5x16mm Hex-Head Bolt | Attach the wire pulleys to the motors | | £0 |
| Bolt | 4 | M4x5~10mm Hex-Head + Countersunk Bolt | Attaches the braking resistors to the cooling plates | Could use thermal adhesive instead; depends on the resistors you get | £5 |
| Protoboard | 1 | [40x60mm 2.54mm Pitch Protoboard](https://www.amazon.co.uk/Prototype-Universal-Connectors-Terminals-Electronic/dp/B09N28GWSV) | A prototyping PCB to mount the electronics to | | £1 |
| Aluminium Bar | 2 | [0.5x1x6.5" Aluminium Bar](https://www.amazon.co.uk/sourcing-map-Square-Aluminum-Thickness/dp/B0CKPMNJCL) | Cooling plates to attach the motors, braking resistors and protoboard tray together | | £10 |
| Connector | 2 | [2x3 2.54mm Pitch Header Connector](https://www.amazon.co.uk/gp/product/B07MNKWXSB) | For terminating the motor power wires | | - |
| Connector | 2 | [2x1 2.54mm Pitch Header Connector](https://www.amazon.co.uk/gp/product/B07MNKWXSB) | For terminating the motor CANBUS wires | | - |
| Connector | 2 | [1x14 2.54mm Header Socket](https://www.ebay.co.uk/itm/232533145324?var=533695806584) | For the Teensy socket on the protoboard | You can also take longer ones and cut them down | - |
| Connector | 1 | [1x6 2.54mm Header Socket](https://www.ebay.co.uk/itm/232533145324?var=533695806584) | For the CANBUS transceiver socket on the protoboard | You can also take longer ones and cut them down | - |
| Connector | - | [2.54mm Header Pins](https://www.amazon.co.uk/gp/product/B0CSJQJFPK) | For the protoboard connections | I prefer the colour-coded ones, but standard black ones will do | - |
| | | | | | **£250** |

### Tools & Consumables
- **Soldering Iron & Solder:** For attaching wires to the protoboard and motor controller
- **Heat-Shrink Tubing:** Suggested for covering the braking resistor legs
- **M4 Thread Tap:** For tapping the holes in the braking resistors and belt loops
- **Countersink Bit:** For countersinking the holes for mounting the braking resistors to the cooling plates (optional)
- **Multimeter:** For checking continuity and precise voltages
- **Wire Strippers / Pilers:** For trimming and removing insulation from wires
- **Allen Key Set:** For attaching the motors to the cooling plates

### Protoboard PCB
![Protoboard](https://github.com/user-attachments/assets/559f9396-00fb-4162-9be7-d4e1d673a4f3)
![Protoboard (Labelled)](https://github.com/user-attachments/assets/a9f5eaf1-314e-4c38-9d52-74c1a6559baf)
![Protoboard (Traces)](https://github.com/user-attachments/assets/fd9bbda2-4b83-4505-9658-52a0d47150eb)

The actual board I'm running was made specifically for experimentation and been modified a number of times to solve issues, so it includes unnecessary components.

The design shown above is a simplified version that includes only the necessary components and traces.

I am currently designing a custom PCB that will make this much neater and remove the need for the acrylic mounting tray (by integrating the mounting lugs into the PCB itself). Once this has been manufactured and tested, I'll make the design available.

#### Power Supply, Connectors & Diodes
I've used a dual-PSU design in an effort to reduce issues with back-EMF triggering the power supply overvoltage protection. These concerns appear to have been mitigated through the addition of motor braking resistors; though I haven't re-tested with a single supply since adding them.

You could probably get away with a single-PSU and eliminate the second power input connectors.

While the protoboard design shows spade terminals, I'm not sure I'd recommended them. Better alternatives exist, such as screw terminal blocks; and there is space for other types. Which you choose will likely depend on your power supply choice.

I'm also not sure if the protection diodes are actually necessary. I added them while debugging some CANBUS issues, but haven't made a new board without them yet. I'll update this documentation after some experimentation.

### Laser-Cut Parts
Unfortunately unless you happen to have a laser cutter, you will need to outsource the cutting of the [various plates](#) that
make up the chassis of the tensioner. While this is difficult to estimate, these should around £50-£100 in total.

These plates can be glued together using a dedicated acrylic bonding agent, or simple Cyanoacrylate (super glue).

## Source Files
TBC

## Assmebly
TBC

## Setup & Usage
TBC

### Installation
TBC

### Configuration
TBC

### Usage
TBC

## Known Issues & Troublehsooting
- Some games (e.g. _Test Drive Unlimited: Solare Crown_) seem to send erratic telemetry data, causing the belts to sharply
  tighten unexpectedly. This is likely due to the game's telemetry data being poorly implemented, but could also be due to
  a bug in the control code. This needs further investigation
- If the motor controller braking voltage is not set appropriately for the power supply used (or not updated when the power
  supply is changed), the following may happen:
  - The motors cut-out due to over-voltage protection kicking in (the braking ressitors are not activated)
  - The motor controller continuously dumps power into the braking resistors, causing them to overheat and **potentially
    catch fire**
