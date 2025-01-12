# Active Belt Tensioner
This is a dual-channel sim racing belt tensioner using BLDC integrated servo motors.

Active belt tensioners are a form of haptic feedback device that simulate the forces experienced by a driver within a
moving vehicle. They achieve this by tightening and loosening the shoulder belts of a 5-point racing harness attached to
the seat, based on in-game telemetry (`surge`, `sway` and `heave`).

This contributes towards tricking the brain into thinking the body it is moving; typically in conjunction with other haptic
feedback devices (tactile transducers, active seat bolsters, etc).

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

The device described in this documentation is a **prototype** and has in no way been tested for long-term reliability or
safety.

**It is _absolutely not safe_ for homes with young children and pets!**

## Features
The included [sample JS code](/SimHub/Device.js) offers the following features:
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
- **JS Code (SimHub):** All of the telemetry-based effects are written in JavaScript and can be edited within
  SimHub, allowing relatively easy customisation of the effects to any degree you desire; simply by sending torque values
  (`-1000` to `1000`) to the controller for the left and right belts (in addition to an idle spring torque)
- **Teensy C++ Code:** The low-level motor control code is written in C++ and located on the microcontroller. It should
  not need to be amended in most cases, but can be edited and re-flashed to the Teensy using the [Arduino IDE](https://www.arduino.cc/en/software)
  and [Teensyduino Addon](https://www.pjrc.com/teensy/td_download.html) if desired

## Recommendation
This device is intended to be attached to a dedicated sim racing rig with a racing-style seat (with appropriate belt holes
and fixing points).

Before considering adding a belt tensioner, you will _ideally_ already have:
- A direct-drive wheel and load-cell pedals
- Multiple tactile transducers (bass shakers)
- Positional audio

These items are generally simpler to implement and will have a _significant_ positive impact on your immersion. A belt
tensioner absolutely adds to the experience, but probably shouldn't be your top priority.

## Prerequisites
- You **must** have a five or six-point harness for this to work effectively, as the absence of an anchoring belt between
  the legs will cause the belts to simply move _upwards_, rather than pin you into the seat. It may be possible to use a
  four-point harness if you have all four belts attached to the tensioner pulleys, but this is not a setup I've tested
- A **licensed** copy of [SimHub](https://www.simhubdash.com/get-a-license/) is required to communicate game telemetry
  data to the controller at the desired frequency

## Parts, Materials & Pricing
Where provided, part links are simply for reference and not product or supplier recommendations. Many of the parts are not
available individually, so must be bought in bulk. The total cost indicated should be enough to cover the required quantity;
likely with plenty of spares.

If you're prepared to change the design yourself to fit parts and materials you already have, you can probably eliminate a
few of these components. Given enough interest, I may create a cost-optimised version of the design, and/or one that uses 3D
printed parts instead of stacked laser-cut sheets.

The vast majority of the cost is the motors.

![Assembled Prototype](https://github.com/user-attachments/assets/20adceba-4a37-4b92-ac0b-1307ab532011)

| Component | Quantity | Name | Description | Notes | Total |
| --- | --- | --- | --- | --- | --- |
| Microcontroller | 1 | [Teensy 4.0](https://shop.pimoroni.com/products/teensy-4-0-development-board?variant=29443577217107) | A powerful microcontroller with built-in CANBUS support (but still requires a transceiver). Provides the connection between the host computer and motors | Overkill for this application, but my preferred controller | £22 |
| CANBUS Transceiver | 1 | [SN65HVD230](https://www.aliexpress.com/item/1005006408102971.html) | A CANBUS transceiver to convert the Teensy CANBUS commands into a signal compatible with motor controller | There are _loads_ of variations of these available; most with the same pinout | £1 |
| Servo Motor | 2 | [LKTech MF9015v2 35T-CAN-18BIT](http://en.lkmotor.cn/ProDetail.aspx?ProId=246) | A high-torque BLDC gimbal motor with FOC control and integrated driver | Modified to add (supported but unpopulated) braking resistors | £200 |
| Braking Resistor | 2 | [100W 6 Ohm Power Resistor](https://www.amazon.co.uk/gp/product/B0BTHJRVF1) | Large aluminium-sinked resitors to dissipate the energy generated by the motors when back-driven (e.g. when pulling the belts to secure them into the cam) | Too much variation in these; you'll have to use thermal adhesive or drill your own holes for mounting | £8 |
| Protection Diode | 2 | >5A > 30V Diode (SR5100, 20SQ045?) | Theoretically helps to protect the power supply from back-EMF generated by the motors | May not be neccessary; need to test further | £4 |
| Pulley Wire | ~2 metre | [2mm PVC-Coated Wire](https://www.amazon.co.uk/Aoktorkit-Coated-Stainless-Strand-Climbing/dp/B0D86VZGFL) | Steel core plastic-coated wire to connect the pulleys to the belts | Around 1 metre for each belt; will depend on your rig | £9 |
| Silicone Wire | ~1 metre | [22AWG Silicone Wire](https://www.amazon.co.uk/gp/product/B0CG2SCCPB) | Connects the braking resistors to the motor pads | Silicone sleeving preferred for heat resistance | £10 |
| Aluminium Spacer | 11 | [40mm ⌀7mm M4 Aluminium Spacers](https://www.aliexpress.com/item/1005002348335932.html) | Round threaded spacers to attach the front and rear acylic plates together, creating a cage around the motors and pulleys | | £8 |
| Aluminium Spacer | 4 | [12mm ⌀7mm M4 Aluminium Spacers](https://www.aliexpress.com/item/1005002348335932.html) | Round threaded spacers to attach the protoboard tray to the cooling plates | | £4 |
| Grub | 4 | M4x20mm Grub Screw | Secures the motors and the protoboard tray to the cooling plates | | £3 |
| Grub | 6 | M4x5mm Grub Screw | Secures the steel wire into the belt loops | I've used sprung-bearing pointed grubs, but any type will do | £3 |
| Bolt | 4 | M4x16mm Hex-Head Bolt | Secures the cooling plates to motors | | £3 |
| Bolt | 30 | M4x12mm Hex-Head Bolt | Secures the acrylic plates to the aluminium spacers and motors to the acrylic plates | | £5 |
| Bolt | 8 | M5x16mm Hex-Head Bolt | Secures the wire pulleys to the motors | | £5 |
| Bolt | 4 | M4x5~10mm Hex-Head + Countersunk Bolt | Secures the braking resistors to the cooling plates (optional) | Could use thermal adhesive instead; depends on the resistors you get | £3 |
| Protoboard | 1 | [40x60mm 2.54mm Pitch Protoboard](https://www.amazon.co.uk/Prototype-Universal-Connectors-Terminals-Electronic/dp/B09N28GWSV) | A prototyping PCB to mount the electronics to | | £1 |
| Aluminium Bar | 2 | [0.5x1x6.5" Aluminium Bar](https://www.amazon.co.uk/sourcing-map-Square-Aluminum-Thickness/dp/B0CKPMNJCL) | Cooling plates to attach the motors, braking resistors and protoboard tray together | These need some manual drilling and shaping | £10 |
| Connector | 2 | [2x3 2.54mm Pitch Header Connector](https://www.amazon.co.uk/gp/product/B07MNKWXSB) | For terminating the motor power wires | | £3 |
| Connector | 2 | [2x1 2.54mm Pitch Header Connector](https://www.amazon.co.uk/gp/product/B07MNKWXSB) | For terminating the motor CANBUS wires | | £3 |
| Connector | 2 | [1x14 2.54mm Pitch Header Socket](https://www.ebay.co.uk/itm/232533145324?var=533695806584) | For the Teensy socket on the protoboard | You can also take longer ones and cut them down | £3 |
| Connector | 1 | [1x6 2.54mm Pitch Header Socket](https://www.ebay.co.uk/itm/232533145324?var=533695806584) | For the CANBUS transceiver socket on the protoboard | You can also take longer ones and cut them down | £3 |
| Connector | - | [2.54mm Pitch Header Pins](https://www.amazon.co.uk/gp/product/B0CSJQJFPK) | For the protoboard connections | I prefer the colour-coded ones, but standard black ones will do | £3 |
| Clamp | 2 | [2" Truss Clamps](https://www.amazon.co.uk/sourcing-map-Aluminum-Lighting-1-89-2-01inch/dp/B0DGLFSM6K) | For mounting the tensioner to a 2" tubular rig frame | For other types of rig frame, you'll need to come up with a different mount | £20 |
| Power Supply | 2 | 24V >4A DC Power Supply | I'm using a pair of GS120A24-P1M supplies; high quality but with aggressive overvoltage protection. There may be better-suited supplies available | A single >7A supply should also work | £40 |
| | | | | | **~£380** |

### Laser-Cut Parts
The structure of the tensioner is comprised of stacked [3mm black cast acrylic sheet](https://kitronik.co.uk/products/value-acrylic-sheet-cast-3mm-x-400mm-x-300mm?variant=39715481124927), because I always have a huge stock of the stuff and it cuts beautifully on my diode laser. It is more than strong enough for the task.

Unless you happen to have a laser cutter, you will need to outsource the cutting of these layered sheets, or come up with your own version of the design. The required files have been provided in both [SVG]() and [DXF]() formats, as these tend to be the supported formats for online quotation systems.

I've obtained a quotation from [RazorLab](https://razorlab.online/) of approximately £125 for the parts to be cut, which is quite a lot. I estimate cutting it on my own machine cost around £15, excluding my time. Make of that what you will.

If using acrylic, these plates can be glued together using a dedicated acrylic bonding agent, or simple Cyanoacrylate (super glue). You could also cut them out of plywood or engineering plastics (where safe to do so).

![Construction](https://github.com/user-attachments/assets/912797b4-8dd1-4cdb-b3e0-1440d6d163f4)

### Protoboard PCB
The current prototype uses a standard 40x60mm protoboard and can be assembled by anyone familiar with a soldering iron. The designs below are a simplified version; the one I'm running has unnecessary components and traces for development and testing purposes.

This design still leaves room for the remaining pins on the Teensy to be utilised where desired, such as adding I2C/SPI/Serial displays, sensors and input devices.

I am planning to design a custom PCB that will make this much neater and remove the need for the acrylic mounting tray (by integrating the mounting lugs into the PCB itself). Once this has been manufactured and tested, I'll make the design available here. I've used [Aisler](https://aisler.net/) before for other projects and intend to use them again.

#### Board Layout
![Protoboard](https://github.com/user-attachments/assets/f8910af4-9150-47cc-9a3b-50a3e95b057e)

#### ...Unpopulated
![Protoboard (Unpopulated)](https://github.com/user-attachments/assets/c33e2eca-f029-4987-a51a-924a5413cab1)

#### ...Traces
![Protoboard (Traces)](https://github.com/user-attachments/assets/73255be8-d9b6-42a1-8278-645d099a3edd)

#### Power Supply, Connectors & Diodes
I've used a dual-PSU design in an effort to reduce issues with back-EMF triggering the power supply overvoltage protection. These concerns appear to have been mitigated through the addition of motor braking resistors; though I haven't re-tested with a single supply since adding them.

You could probably get away with a single-PSU and eliminate the second power input connectors, diode and traces.

While the protoboard design shows spade terminals, I'm not sure I'd recommended them. Better alternatives exist, such as screw terminal blocks; and there is space for other types. Which you choose will likely depend on your power supply choice.

I'm also not sure if the protection diodes are actually necessary. I added them while debugging some CANBUS issues, but haven't made a new board without them yet. I'll update this documentation after some experimentation.

### Tools & Consumables
- **Soldering Iron & Solder:** For creating the protoboard and connecting the braking resistors to the motor drivers
- **Heat-Shrink Tubing:** For covering the braking resistor legs
- **M4 Thread Tap:** For tapping the holes in the braking resistors and belt loops
- **Countersink Bit:** For countersinking the holes for mounting the braking resistors to the cooling plates (optional)
- **Multimeter:** For checking continuity and precise voltages
- **Wire Strippers / Pilers:** For trimming and removing insulation from wires
- **Allen Key Set:** For attaching the motors to the cooling plates
- **Hacksaw / Jigsaw / Bandsaw:** For trimming the aluminium bars
- **JST Crimping Tool:** For attaching the JST connectors to the unterminated motor leads

## Source Files
- [Arduino / Teensy Code](/Teensy)
- [SimHub JS Code](/SimHub/Device.js)
- [SimHub Importable Device](/SimHub/Device.shsds)
- [Parts SVGs (Laser-Cut Acrylic)](/Parts)

## Assembly
Between the previously shown protoboard diagrams and the exploded view of the acrylic plates, the process of physically putting together the tensioner unit should be fairly obvious. Notes on which fasteners are used where are included in the [list of parts](#parts-materials--pricing) above.

Any notable details are included below.

### Protoboard
1. Attach the various headers to the board
2. Attach the spade terminals and diodes (where using these)
3. Attach the zero-ohm links (or equivalent insulated wire)
4. Referencing the [traces diagram](#traces), cut and bend solid-core wire to match and solder to the board
5. Check continuity with a multimeter (good connections, no shorts, etc)
6. Attach the pins to the Teensy and Transceiver, where not already done

### Motors
1. Terminate the bare negative and positive (black and red) wires of the motors with the 2x3 header connectors
2. Terminate the bare CANBUS (yellow and blue) wires of the motors to the 2x1 header connectors
3. Set the {MOTOR ID} + {CANBUS TERMINATION RESISTOR}

### Main Unit
1. Glue the 'Front Panel' plates together
2. Glue the 'Rear Panel' plates together
3. Glue the 'Pulley' plates together (remembering to keep each pulley in two parts so the 'S' plate that retains the steel wire is accessible)
4. Bolt the 'Pulley' parts and wires onto the motors (ensuring that one side if 'flipped' so the wire winds from the outside edge on both sides)
5. Attach the motors (and attached pulleys) to the assembled 'Rear Panel' part using the 12mm M4 bolts
6. Using the 40mm spacers and 12mm M4 bolts, attach the 'Front Panel' to the 'Rear Panel' (ensuring the previously attached wires exit between the appropriate spacers)
7. {ATTACH COOLING PLATES}
8. {ATTACH GRUBS + SPACERS}
9. {ATTACH PROTOBOARD TRAY}
10. {ATTACH PROTOBOARD}

### Belt Loops
1. Pre-tap the 'Belt Loop' plate holes with M4 threads (you won't be able to do this once the plates are glued)
2. Glue the 'Belt Loop' plates together
3. Fit the M4 grub screws
4. Feed the steel wire into the hole and tighten the grub screws to retain the wire (use a looser fit when first testing your setup)

## Setup & Usage
TBC

### Installation
TBC

### Configuration
TBC

#### Motor Identifiers
Each motor on the CANBUS needs to have a unique identifier set. There are two ways to do this:
- Adjust the DIP switches on the back of each motor to set the identifier physically (see the motor manual for details)
- Launch the [LK Motor Tool](http://en.lkmotor.cn/Download.aspx?ClassID=45), connect to the motor and set the `Driver ID` value

In either case the _TBC_ motor should be `1` and the _TBC_ motor should be `2` (when looking at the tensions from the rear of your rig).

#### CANBUS Termination
A CANBUS consists of two wires (`High` & `Low`) with any number of devices connected along its length. At each end of the wires we need a 120Ohm Termination Resistor for the CANBUS to function.

Our _Transciever_ board has one of these built in, so we just need to add another at the other end, which will be one of our motors. Thankfully these motors have these built-in, and we just need to use the DIP switches on the back to set this to _enabled_ for the terminating motor and _disabled_ for the non-terminating one.

In the configuration I've used, the _TBC_ motor is at the end of the BUS, so that's the one we want it enabled on (see the motor manual for details).

Alternatively you could solder your own 120Ohm resistor across the top of the blue CANBUS headers on the protoboard.

#### Resistor Tuning
1. Measure the _exact_ unloaded output voltage of your chosen power supply with a multimeter (for a '24V' supply this might actually be something like 24.15V)
2. Launch the [LK Motor Tool](http://en.lkmotor.cn/Download.aspx?ClassID=45) and connect to the motor using the serial cable and adapter provided with the motor
3. Set the `Brake Resistor Control` to `Yes` and the `Brake Resistor Voltage` to be just above the measured PSU voltage (roughly +0.10V). This should be _less_ than your PSU's _overvoltage threshold_
4. Click `Save Setting`, reboot the motor, then click `Motor On` and measure the voltage across the resistor, to confirm it is essentially zero while the motor is idle. If you've gotten the voltage value wrong, this will be non-zero and the resistor will be rapidly heating up (that's bad; go back and adjust raise the value)
5. With the motor held firm, assertively pull the wire attached to the motor drum to back-drive the motor while monitoring the voltage across the resistor. The motor should heavily resist rotation and a voltage should be seen across the resistorwhich should spike while you do so and return to zero afterwards (importantly, the PSU should also not cut-out due to the motor being backdriven)

> **Note:** If you're using a dual PSU setup like me, don't assume both supplies will have the exact same output voltage; measure both and then label the suplies so you don't mix them up later. The votlage tolerances are small make the braking resistors not function properly.

### Usage
TBC

## Known Issues & Troublehsooting
- Some games (e.g. _Test Drive Unlimited: Solare Crown_) seem to send erratic telemetry data, causing the belts to sharply
  tighten unexpectedly. This could be due to the game's telemetry being borked, or due to a bug in the control code. This
  needs further investigation
- If the motor controller braking voltage is not set appropriately for the power supply used (or not updated when the power
  supply is changed), the following may happen:
  - The motors cut-out repeatedly due to over-voltage protection kicking in (the braking ressitors are not activated)
  - The motor controller continuously dumps power into the braking resistors, causing them to overheat and **potentially
    catch fire**

## Questions & Answers
- **How can I contact you?**
  - Best to [message me via Reddit](https://www.reddit.com/user/XG3OX/)
- **Can I sell this design (or a derivative)?**
  - Yes. I've used the MIT license to permit this, subject to some kind of attribution being included
  - This includes being permitted to make kits available (e.g. the laser cut parts, fittings, etc)
- **Will you supply me with the laser-cut parts?**
  - Maybe. I'm not equipped to run a laser cutting service, but may do acrylic kits for people in the UK
- **How do I mount this to my aluminium profile rig?**
  - This has been designed to clamp onto 2" tubing rigs using a pair of truss clamps, not aluminium profile
  - If you want to do this, you'll need to come up with your own mounting solution
  - If there is enough intereest I'll have a look at making the design support universal fitting 
- **Where are the files for the belt rollers?**
  - I considered adding them, but since they're so specific to my rig and chosen seat, they are almost certainly going to be useless to you
  - Whether these are actually needed or not will depend on your seat's design. You may be better off just sticking some nylon/acetal rods in the belt holes for the belts to run over
- **Why use 1/4x1" aluminium bars for the cooling plates?**
  - It's cheaper than having a full plate laser or water-jet cut and can be trimmed/drilled with basic tools
  - You could come up with a custom cut plate if you like, but it didn't seem worth it
- **Is active cooling needed?**
  - Not as far as I've observed; the motors and their controllers barely get warm
  - The load we're putting these motors under is actually pretty light and not continuous-duty
  - If you don't tune the braking resistor voltage properly, then you _will_ have overheating (and other) problems
- **How much noise does it make?**
  - That will actually depend on how well you tune the FOC parameters in the motor configuration software
  - I have a number of these motors now in different sizes/windings and some are virtually silent, while others are whiney (indicating the tuning needs improvement)
  - The motors come with a crude 'factory tune' that can be improved, but that is beyond the scope of this documentation
