![Tensioner](https://github.com/user-attachments/assets/6d587ca9-4f6c-4fff-9fca-a998e93d5bd5)
![Belts](https://github.com/user-attachments/assets/22cb0579-bec0-4348-a225-a12360df4b75)
![Roller](https://github.com/user-attachments/assets/f8426194-8992-4687-9eb4-959cdfdd55db)
![Motors](https://github.com/user-attachments/assets/e4d272a8-f83f-47a7-8f84-d64874970974)

[Watch A Video](https://www.youtube.com/watch?v=mdPK2OQolQc)

# Active-Belt-Tensioner
A dual-channel sim racing belt tensioner using BLDC integrated servo motors.

Active belt tensioners are a form of haptic feedback device that simulate the forces experienced by a driver within a
moving vehicle. They achieve this by tightening and loosening the shoulder belts of a 5-point racing harness attached to
the seat, based on in-game telemetry (`surge`, `sway` and `heave`).

The application these forces contributes towards tricking the brain into thinking it is moving; tyipcally in conjunction
with other haptic feedback devices (tactile transducers, active seat bolsters, etc).

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
- **Arduino C++ Code:** The low-level
  motor control code is written in C++ and located on the microcontroller. It should not need to be amended in most cases

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

## Notable Parts & Pricing
The total BOM cost for this project is approximately **£350** at the time of writing, including the laser-cut acrylic
parts. This does not include the cost of the seat, harness or other prerequisite equipment.

Where provided, links are to the suppliers used by this author; but not necessarily recommended.

| Component | Quantity | Name | Description | Unit Price* | Total |
| --- | --- | --- | --- | --- | --- |
| Microcontroller | 1 | [Teensy 4.0](https://shop.pimoroni.com/products/teensy-4-0-development-board?variant=29443577217107) | A powerful microcontroller with built-in CanBus controller (but not transciever) | £22 | £22 |
| CanBus Transciever | 1 | [SN65HVD230](https://www.aliexpress.com/item/1005006408102971.html) | A CanBus transciever to convert the Teensy CanBus commands into a signal compatible with motor controller | £1 | £1 |
| Motor | 2 | [LKTech MF9015v2 35T-CAN-18BIT](http://en.lkmotor.cn/ProDetail.aspx?ProId=246) | A high-torque BLDC gimbal motor with FOC control and integrated driver | £100 | £200 |
| Braking Resistor | 2 | [100W 6 Ohm](https://www.amazon.co.uk/gp/product/B0BTHJRVF1) | Resistors to dissipate the energy generated by the motors when back-driven | £4 | £8 |
| Pulley Wire | ~2 metre | PVC-Coated Wire | Ideally steel wire with a total external diameter of 2mm | £1 | £2 |
| Aluminium Spacer | 11 | [40mm M4 Spacers](https://www.aliexpress.com/item/1005002348335932.html?spm=a2g0o.order_detail.order_detail_item.7.551ef19cEfX17t) | Attach the front and rear acylic plates together, while ensuring the wires do not unravel in problematic ways when the motors are unpowered | £1 | £11 |
| Bolt | 8 | M5x16mm Hex-Head Bolt | Attach the wire pulleys to the motors | £0 | £0 |
| Bolt | 22 | M4x10mm Hex-Head Bolt | Attach the acrylic plates to the aulminium spacers | £0 | £0 |
| TBC | TBC | TBC | TBC | TBC | TBC |
| TBC | TBC | TBC | TBC | TBC | TBC |
| TBC | TBC | TBC | TBC | TBC | TBC |
| | | | | | **£250** |

\* These prices are approximate/pessimistic at the time of writing. They're intened to give you a rough idea of the cost of the
project, but may not be accurate at the time of your purchase.

### Protoboard PCB


The current board I'm running was made specifically for experimentation and been modified a number of times to solve issues, so it includes extraneous components.

The design included in this repository is a simplified version of the same board that includes only the necessary components and traces.

> **Note:** I am currently designing a simple custom PCB that will make this much neater and replace the acrylic tray the protoboard sits ine (by integrating the mounting lugs).

#### Power Supply & Diodes
I've used a dual-PSU design in an effort to reduce issues with back-emf triggering the power supply overvoltage protection. This issue appears to have since been resolved through the addition of braking resistors.

You could probably get away with a single-PSU and eliminate the second power input connectors.

I'm also not sure if the diodes are actually necessary. I added them while debugging some CANBUS issues, but haven't made a new board without them yet. I'll update this documentation after some experimentation.



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
