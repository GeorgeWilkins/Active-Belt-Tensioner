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
| Connector | 4 | [1/4" Male 5.08mm Pitch Spade Terminal](https://www.amazon.co.uk/gp/product/B01KYCC7GS) | For the power supply connections | I'd suggest replacing these with screw terminals or similar | £7 |
| Clamp | 2 | [2" Truss Clamps](https://www.amazon.co.uk/sourcing-map-Aluminum-Lighting-1-89-2-01inch/dp/B0DGLFSM6K) | For mounting the tensioner to a 2" tubular rig frame | For other types of rig frame, you'll need to come up with a different mount | £20 |
| Power Supply | 2 | 24V >4A DC Power Supply | I'm using a pair of GS120A24-P1M supplies; high quality but with aggressive overvoltage protection. There may be better-suited supplies available | A single >7A supply should also work | £40 |
| | | | | | **~£380** |

### Laser-Cut Parts
The structure of the tensioner is comprised of stacked [3mm black cast acrylic sheet](https://kitronik.co.uk/products/value-acrylic-sheet-cast-3mm-x-400mm-x-300mm?variant=39715481124927), because I always have a huge stock of the stuff and it cuts beautifully on my diode laser. It is more than strong enough for the task.

Unless you happen to have a laser cutter, you will need to outsource the cutting of these layered sheets, or come up with your own version of the design. The required files have been provided in both [SVG](/Parts/Acrylic/SVG) and [DXF](/Parts/Acrylic/DXF) formats, as these tend to be the supported formats for online quotation systems.

As a rough guide I obtained a quotation from [RazorLab](https://razorlab.online/) of approximately £125 for the parts to be cut, which is more than I expected. I estimate cutting it on my own machine cost around £15, excluding my time. Make of that what you will. Loads of laser cutting providers are available.

If using acrylic, these plates can be glued together using a dedicated acrylic bonding agent, or simple Cyanoacrylate (super glue). You could also cut them out of plywood or engineering plastics (where safe to do so).

![3D Model](https://github.com/user-attachments/assets/98aa0188-43af-408b-a2b8-425b154f2767)
![3D Model (Rear)](https://github.com/user-attachments/assets/49c8676e-2fd1-4ed2-837d-c35ee4c1bfd2)
![3D Model (Exploded)](https://github.com/user-attachments/assets/b7757561-fb88-4138-bf5a-786923bcc3ef)


### Protoboard PCB
The current prototype uses a standard 40x60mm protoboard and can be assembled by anyone familiar with a soldering iron. The designs below are a simplified version; the one I'm running has unnecessary components and traces for development and testing purposes.

This design still leaves room for the remaining pins on the Teensy to be utilised where desired, such as adding I2C/SPI/Serial displays, sensors and input devices.

I am planning to design a custom PCB that will make this much neater and remove the need for the acrylic mounting tray (by integrating the mounting lugs into the PCB itself). Once this has been manufactured and tested, I'll make the design available here. I've used [Aisler](https://aisler.net/) before for other projects and intend to use them again.

![Protoboard](https://github.com/user-attachments/assets/f8910af4-9150-47cc-9a3b-50a3e95b057e)

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
- **Metal File:** For rounding off the aluminium bar ends and modifying the motor housings
- **JST Crimping Tool:** For attaching the JST connectors to the unterminated motor leads

## Source Files
- [Sketchup Design](Design.skp)
- [Arduino / Teensy Code](/Teensy)
- [SimHub JS Code](/SimHub/Device.js)
- [SimHub Importable Device](/SimHub/Device.shsds)
- [Parts SVGs (Laser-Cut Acrylic)](/Parts)

## Assembly
Between the previously shown protoboard diagrams and the exploded view of the acrylic plates, the process of physically putting together the tensioner unit should be fairly obvious. Notes on which fasteners are used where are included in the [list of parts](#parts-materials--pricing) above.

### Protoboard
1. Attach the various headers to the board
2. Attach the spade terminals and diodes (where using these)
3. Attach the zero-ohm links (or equivalent insulated wire)
4. Cut and bend solid-core wire to match and solder to the board as traces
5. Check continuity with a multimeter (good connections, no shorts, etc)
6. Attach the header pins to the Teensy and Transceiver (if absent)

![Protoboard (Unpopulated)](https://github.com/user-attachments/assets/c33e2eca-f029-4987-a51a-924a5413cab1)
![Protoboard (Traces)](https://github.com/user-attachments/assets/73255be8-d9b6-42a1-8278-645d099a3edd)

### Motors
1. Terminate the bare negative and positive (black and red) wires of the motors with the 2x3 header connectors
2. Terminate the bare CANBUS (yellow and blue) wires of the motors to the 2x1 header connectors
3. Remove the motor back covers and locate the `BRAKE-RES` pads; soldering lengths of silicone wire to them
4. Use a metal file to remove some of the rear cover material, allowing the wires you've soldered through
5. Reattach the motor covers, being sure not to pinch the new wires

![Soldering Brake Leads](https://github.com/user-attachments/assets/b346bfd5-93a2-400f-adeb-af165df15806)
![Modified Cover](https://github.com/user-attachments/assets/42279f81-b85d-4a73-8861-626f2d3d671a)
![Reattached Cover](https://github.com/user-attachments/assets/c67a7f42-6b03-4f35-b11b-db235ba6a57d)

### Main Unit
1. Glue the 'Front Panel' plates together
2. Glue the 'Rear Panel' plates together
3. Assemble the 'Pulley' plates (no need to glue these together), not forgetting to insert the steel wire into the curved recess as you do
4. Bolt the assembled pulleys onto the motors using the M5x16mm screws (ensuring one side is 'flipped' so the wire winds from the outside edge on both sides)
5. Attach the motors to the assembled 'Rear Panel' part using the 12mm M4 bolts
6. Using the 40mm spacers and 12mm M4 bolts, attach the 'Front Panel' to the 'Rear Panel' (ensuring the steel wires exit between the indicated spacers)
7. Attach the resistors to the aluminium cooling plates using the countersunk screws _or_ thermal adhesive
8. Attach the cooling plates to the motors using the M4x20mm grubs, spacers and M4x16mm bolts
9. Solder the resistor wires previously attached to the motors to the resistor terminals (heat-shrinking the connections to prevent shorts)
10. Attach the protoboard tray to the spacers using the M4x12mm bolts, feeding the data and power wires up from underneath
11. Attach the 2" truss clamps to the large holes at the base of the tensioner assembly

![Steel Wire Routing](https://github.com/user-attachments/assets/c5c52d2c-5a03-436f-8659-b8882eed2940)
![Pulley Orientation & Wire Path](https://github.com/user-attachments/assets/b41c111c-2ab0-4dd9-a13c-a804b3a04f8e)
![Fitted Resistors](https://github.com/user-attachments/assets/39eae1f8-831f-4aee-8333-7afe27eb3378)
![Grub Screw & Spacer](https://github.com/user-attachments/assets/fc0af8f1-f449-495e-a08f-32494312bba5)
![Fitted Plates](https://github.com/user-attachments/assets/38b1229f-6ad7-4f11-90d1-b5f4ad3873da)
![Fitted Tray](https://github.com/user-attachments/assets/20adceba-4a37-4b92-ac0b-1307ab532011)

### Belt Loops
1. Pre-tap the 'Belt Loop' plate holes with M4 threads (you won't be able to do this once the plates are glued)
2. Glue the 'Belt Loop' plates together, such that the 'slotted' plate is in the middle and the threaded plates are on the outside
3. Fit the M4 grub screws into the threaded holes, leaving a gap for the wire
4. Feed the steel wire into the slot (which now forms a hole in the assmebled part) and tighten the grub screws to retain the wire

![Fitted Loop](https://github.com/user-attachments/assets/f9eeb6c1-c851-4e07-9f8d-e53c890dafc2)

## Initial Setup
### Installation
For tubular steel racing rigs, simply attach the two truss clamps to the back of your frame. For other types, you'll need to come up with your own fixture.

The exact configuration of your belts will depend on your rig, but the wires coming out of the tensioner should roughly line up with the centers of your seat's belt holes; or at least close enough not to be a problem.

Don't hook anything else up until you've completed the other steps below.

![Attached To Frame](https://github.com/user-attachments/assets/0a940c39-5a37-4c69-91cc-d7bfce869a2b)

### Motor Identifiers & Termination Resistor
Each motor on the CANBUS needs to have a unique identifier set. We also need to enable the built-in 120Ohm termination resistor on the specific motor that sits at the end of the bus (with our transceiver already providing one at the start of the bus).

In my configuration, the  _right_ motor should have identifier `1` and the _left_ motor should be `2` (when looking at the tensioner from the rear of your rig). The _right_ motor is also the terminating motor, so we need to enable its resistor and disable the _left_ motor's resistor.

We do all of this by setting the DIP switches on the back of each motor:

| Motor | Identifier | SW1 | SW2 | SW3 | SW4 (R) |
| ----- | ---------- | --- | --- | --- | ------- |
| Left  | 1          | ON  | OFF | OFF | OFF     |
| Right | 2          | OFF | OFF | OFF | ON      |

See the [motor manual](http://en.lkmotor.cn/Download.aspx?ClassID=21) for more information or for setting different configurations.

### Braking Resistor Tuning
In order for the braking resistors to work, we need to tell each motor controller at what voltage threshold it should dump energy into the resistor.

This voltage must be _above_ the output voltage of the '24V' power supply (`23.9V`, `24.05V`, `24.15V`, etc) but below the threshold at which your specific power supply triggers its internal overvoltage protection.

Get this _too high_, and the braking resistor won't activat before the OVP does, and your power supply will likely go into protection mode regularly. Get this _too low_ and the motor controller will be dumping energy into the resistors continuously, resulting in the resistors getting _very_ hot and the motors not running properly. Both scenarios should be pretty obvious during testing.

In practice, with my Meanwell supplies (with their aggressive overvoltage protection), this meant I had to be no more than `0.1V` above their typical output voltage for this all to work.

I'd suggest the following approach:
1. Measure the _exact_ unloaded output voltage of your chosen power supply with a multimeter
2. Launch the [LK Motor Tool](http://en.lkmotor.cn/Download.aspx?ClassID=45) and connect to the motor using the serial cable and USB adapter provided with the motor
3. Set the `Brake Resistor Control` to `Yes` and the `Brake Resistor Voltage` to be _just above_ the measured PSU voltage (roughly +0.10V). You might want to start with slightly higher values to see where your PSU OVP kicks in
4. Click `Save Setting`, reboot the motor, then click `Motor On` and measure the voltage across the resistor, to confirm it is _zero_ while the motor is idle. If you've set the `Brake Resistor Voltage` value _too low_, this will be something like `12V` and the resistor will be rapidly heating up (that's bad). If so, go back and adjust raise the value; otherwise continue
5. With the tensioner held firm, assertively pull the steel wire attached to the motor pulley to back-drive the motor (while monitoring the voltage across the resistor). The motor should heavily resist rotation and a voltage should be seen across the resistor while you pull (importantly, the PSU should also not cut-out due to the motor being backdriven)

I queried _LKTech_ for assistance in setting up this seemingly undocumented feature. They were less than helpful; giving me _bad_ information that I thankfully double-checked before applying. There may be better ways to configure this or otherwise handle the back-EMF issue. If anyone better informed on this has any input, please let me know.

### Flashing The Teensy
There is a [good tutorial](https://www.pjrc.com/teensy/tutorial.html) available if you've never used a Teensy before. It's basically the same as an Arduino, but there are a couple extra steps to take when first getting it set up.

The required Arduino 'Sketch' is [included in this repository](/Teensy), so download it and open it in the Arduino IDE. Follow the flashing process as shown by the tutorial.

After flashing, _Windows Device Manager_ should see a new `USB Serial Device` under `Ports (COM & LPT)`, along with a numbered `COM` port. That's the one we'll be selecting in SimHub.

### Configuring SimHub
Now that the Teensy is plugged in and flashed, we can tell SimHub to use it.

We're going to make use of a SiumHub feature called [Custom Serial Devices](https://github.com/SHWotever/SimHub/wiki/Custom-serial-devices), which allows us to tell SimHub to send formatted telemetry to any device that enumerates as a serial port on the computer.

The link above covers how to access this feature. If you'd like this to be configured for you, download the [Device.shsds](/SimHub/Device.shsds) file and import it under `Export And Import` > `Import Settings`. This will do everything for you, except for select the correct `Serial Port` (which which there is likely only going to be one anyway).

If you make changes you can also use `Export Settings` to create a new version of this file for future use.

With this done you should be clear to power up the motors.

## Usage
While powered, the tensioner will always apply the given _idle torque_ whenever no telemetry is being received (between games and while in menus).

This is useful when getting in/out of the seat and fitting/releasing the harness, as it automatically takes up any slack. Ideally the _idle torque_ value you set will be not quite enough to overcome the weight of your belts, but enough to reel them in when you're taking their weight by holding them.

If you wish to have control over the belts, put their power supply/supplies on a separate switched mains cable and just turn them on/off as needed. They'll automatically reconnect and function once power is restored.

## Known Issues & Troubleshooting
- Some games (e.g. _Test Drive Unlimited: Solar Crown_) occaisionally send erratic telemetry data, which can cause the belts to sharply
  tighten and release unexpectedly. This could be due to the game's telemetry being borked, or due to a bug in the control code. This
  needs further investigation
- Incorrect configuration of the motor braking resistors will cause significant issues with operation; either regular drop-outs of the
  power supply or overheating of the resitors. At the moment mine works reliably with the current configuration; but it's likely to
  depend very much on the power supply you use
- The _LKTech_ CANBUS protocol documentation isn't clear about how the torque commands scale with different motor sizes. I've experimentally found that either:
  - Torque values are extremely _non-linear_, with most higher values in the allowed `-2048`~`2048` range being clamped to 100% of the motor's available torque
  - Torque values are treated as _absolute_; meaning if `30A` is the maximum current represented by value of `2048`, a motor with a `3A` maximum can only use values up to `204`. I'm not sure about this though; needs further investigation
- Possibly due to the above, the torque can occaisionally feel a little lumpy; not as smooth as it could be. This is almost certainly improvable with software tweaks

## Questions & Answers
- **How can I contact you?**
  - For technical queries, corrections and submissions, please [create an issue](/issues)
  - For other enquiries, best to [message me via Reddit](https://www.reddit.com/user/XG3OX/)
- **Can I sell this design (or a derivative)?**
  - Yes. I've used the MIT license to permit this, subject to some kind of attribution being included
  - This includes being permitted to make kits available (e.g. the laser cut parts, fittings, etc)
- **Will you supply me with the laser-cut parts?**
  - Maybe. I'm not equipped to run a laser cutting service, but may do acrylic kits for small numbers of people in the UK
- **How do I mount this to my aluminium profile rig?**
  - This has been designed to clamp onto 2" tubing rigs (such as the [GT Omega Titan](https://www.gtomega.co.uk/products/titan-cockpit)) using a pair of truss clamps, not aluminium profile
  - If you want to do this, you'll need to come up with your own mounting solution
  - If there is enough intereest I'll have a look at making the design support universal fitting
- **Where are the files for the belt rollers?**
  - I considered adding them, but since they're so specific to my rig and chosen seat, they are almost certainly going to be useless to you
  - The design is available inside the [Sketchup File](Design.skp) if you want it
  - Whether these are actually needed or not will depend on your seat's design. You may be better off just sticking some nylon/acetal rods in the belt holes for the belts to run over
- **Why use 1/4x1" aluminium bars for the cooling plates?**
  - It's cheaper than having a full plate laser or water-jet cut and can be trimmed/drilled with basic tools
  - You could come up with a custom cut plate if you like
- **Is active cooling needed?**
  - Not as far as I've observed; the motors and their controllers barely get warm
  - The load we're putting these motors under is actually pretty light and not continuous-duty
  - If you don't tune the braking resistor voltage properly, then you _will_ have overheating (and other) problems
- **How much noise does it make?**
  - That will actually depend on how well you tune the FOC parameters in the motor configuration software
  - I have a number of these motors now in different sizes/windings and some are virtually silent, while others are whiney (indicating the tuning needs improvement)
  - The motors come with a crude 'factory tune' that can be improved, but that is beyond the scope of this documentation
