# Component Specifications

## Overview

This document provides detailed specifications for all components used in the Automatic Irrigation System.

## Table of Contents

- [Microcontroller](#microcontroller)
- [Sensors](#sensors)
- [Display](#display)
- [Power Components](#power-components)
- [Switching Components](#switching-components)
- [Water Control Components](#water-control-components)
- [Passive Components](#passive-components)
- [Miscellaneous](#miscellaneous)

---

## Microcontroller

### Arduino Uno (ATmega328P)

**General Specifications:**
- Microcontroller: ATmega328P
- Operating Voltage: 5V
- Input Voltage (recommended): 7-12V
- Input Voltage (limits): 6-20V
- Digital I/O Pins: 14 (6 provide PWM output)
- Analog Input Pins: 6
- DC Current per I/O Pin: 40 mA (max 20mA recommended)
- DC Current for 3.3V Pin: 50 mA
- Flash Memory: 32 KB (0.5 KB used by bootloader)
- SRAM: 2 KB
- EEPROM: 1 KB
- Clock Speed: 16 MHz

**Pin Configuration:**
- Digital pins 0-13 (0-1 used for serial communication)
- Analog pins A0-A5 (can also be used as digital I/O)
- Power pins: 5V, 3.3V, GND, VIN, IOREF
- Special pins: AREF, RESET

**Power Consumption:**
- Active mode: ~50mA @ 5V
- Idle mode: ~20mA @ 5V

**Interfaces:**
- USB (Type B)
- ICSP header
- Power jack (2.1mm center-positive)

**Purchase Information:**
- Approximate Cost: $20-25 USD
- Alternatives: Arduino Nano, Arduino Mega (for expansion)

---

## Sensors

### Soil Moisture Sensor (YL-69 or equivalent)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 3.3V - 5V DC |
| Output Voltage | 0V - 5V (analog) |
| Operating Current | 35 mA (typical) |
| Output Signal | Analog voltage |
| Probe Material | Nickel-plated |
| PCB Size | ~3cm x 1.5cm |
| Probe Length | ~6cm |

**Sensor Module Features:**
- Dual output mode: Analog (A0) and Digital (D0)
- Onboard LM393 comparator
- Adjustable sensitivity via potentiometer
- Power and output LED indicators
- Works with soil, sand, and various growing mediums

**Output Characteristics:**
- Dry soil: Higher resistance → Higher voltage (3-5V)
- Wet soil: Lower resistance → Lower voltage (0-2V)
- Typical range: 0-1023 (analog reading)

**Calibration Values (Typical):**
```
Air (completely dry): ~1023
Dry soil: 700-900
Humid soil: 400-600
Water: 200-400
Fully submerged: 0-200
```

**Limitations:**
- ⚠️ Corrosion: Nickel plating can corrode over time
- ⚠️ Not waterproof: Module PCB should stay dry
- ⚠️ Lifespan: ~1-2 years with continuous outdoor use
- Improvement: Consider capacitive sensors for longer life

**Purchase Information:**
- Cost: $2-5 USD per sensor
- Quantity needed: 3 sensors
- Better alternative: Capacitive soil moisture sensor v1.2

---

### Water Level Sensors (for Reservoir and Overhead Tank)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 3V - 5V DC |
| Operating Current | < 20 mA |
| Output Type | Analog |
| Sensor Type | Resistive |
| Detection Range | 0-40mm water depth |
| Operating Temperature | 10°C - 30°C |

**Alternative: Ultrasonic Sensor (HC-SR04)**

For non-contact water level measurement:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC |
| Operating Current | 15 mA |
| Operating Frequency | 40 kHz |
| Range | 2cm - 400cm |
| Accuracy | ±3mm |
| Measuring Angle | 15° |
| Trigger Input | 10µS TTL pulse |
| Echo Output | TTL signal (HIGH/LOW) |

**Recommended for This Project:**
- Use resistive sensors for simplicity
- Ultrasonic sensors better for large tanks
- Float switches for simple ON/OFF detection

---

## Display

### LCD Display (16x2 Character)

**Model:** HD44780 or compatible (1602A)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Display Type | STN Yellow-Green/Blue |
| Display Format | 16 characters × 2 lines |
| Operating Voltage | 5V DC |
| Operating Current | 2-3 mA (no backlight) |
| Backlight Current | 120-150 mA (LED backlight) |
| Controller | HD44780 or compatible |
| Interface | Parallel (4-bit or 8-bit) |
| Character Size | 5×8 dots |
| Module Size | ~80mm × 36mm × 12mm |

**Pin Configuration (16 pins):**

1. VSS - Ground
2. VDD - +5V power
3. V0 - Contrast adjustment (0-5V)
4. RS - Register select
5. RW - Read/Write (usually grounded)
6. E - Enable signal
7. D0 - Data bit 0 (not used in 4-bit mode)
8. D1 - Data bit 1 (not used in 4-bit mode)
9. D2 - Data bit 2 (not used in 4-bit mode)
10. D3 - Data bit 3 (not used in 4-bit mode)
11. D4 - Data bit 4
12. D5 - Data bit 5
13. D6 - Data bit 6
14. D7 - Data bit 7
15. A (Anode) - Backlight + (via resistor)
16. K (Cathode) - Backlight -

**Operating Modes:**
- 4-bit mode (uses D4-D7 only) ← Used in this project
- 8-bit mode (uses D0-D7)

**Backlight:**
- LED backlight: 120-150mA @ 4.2V
- Requires current limiting resistor (typically 220Ω)

**Alternative Options:**
- I2C LCD adapter (saves Arduino pins)
- OLED display (better contrast, no backlight needed)

**Purchase Information:**
- Cost: $3-6 USD
- With I2C module: $5-8 USD

---

## Power Components

### Voltage Regulator (7805)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Model | LM7805 / L7805CV |
| Output Voltage | 5V ±4% |
| Input Voltage | 7V - 35V |
| Output Current | 1A (with heatsink), 500mA (without) |
| Dropout Voltage | ~2V |
| Operating Temp | 0°C to 125°C |
| Package | TO-220 |

**Pin Configuration:**
1. Input (left)
2. Ground (middle)
3. Output (right)
(When facing the flat side with pins down)

**Recommended Circuit:**
```
Input: 0.33µF ceramic capacitor to GND
Output: 0.1µF ceramic capacitor to GND
Heatsink recommended for >500mA
```

**Power Dissipation:**
```
P = (Vin - Vout) × Iload
Example: (12V - 5V) × 0.5A = 3.5W
→ Heatsink required!
```

---

### Power Supply

**12V DC Power Adapter:**

| Specification | Recommended |
|--------------|-------------|
| Output Voltage | 12V DC |
| Output Current | 2A minimum (3A recommended) |
| Connector | 2.1mm barrel jack or screw terminals |
| Regulation | ±5% or better |
| Safety | Short circuit & overload protection |

**Load Calculation:**
```
Water Pump: ~1A @ 12V = 12W
Solenoid Valve: ~0.5A @ 12V = 6W
Arduino + Sensors + LCD: ~200mA @ 5V = 1W
Total Peak: ~19W → Use 24W (2A) or 36W (3A) supply
```

**Alternative: Solar Power**
- Solar panel: 20W minimum (12V)
- Battery: 12V 7Ah sealed lead-acid
- Charge controller: 10A PWM/MPPT

---

## Switching Components

### Relay Module (2-Channel)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Control Voltage | 5V DC |
| Relay Type | SRD-05VDC-SL-C or similar |
| Contact Rating | 10A @ 250VAC / 30VDC |
| Trigger Current | 15-20 mA |
| Number of Channels | 2 |
| Isolation | Optocoupler isolated |
| Indicator | LED per channel |
| Trigger Mode | Active LOW or HIGH (jumper selectable) |

**Terminal Connections:**
- COM (Common)
- NO (Normally Open)
- NC (Normally Closed)

**Control Pins:**
- VCC: 5V
- GND: Ground
- IN1, IN2: Control signals from Arduino

**Features:**
- Onboard optocouplers for isolation
- Freewheeling diodes for coil protection
- Screw terminals for easy connection
- LED indicators for relay status

**Purchase Information:**
- Cost: $3-5 USD for 2-channel
- Alternatives: 4-channel, 8-channel modules

---

### Transistor (NPN)

**Model:** BC547 or 2N2222

**BC547 Specifications:**

| Parameter | Value |
|-----------|-------|
| Type | NPN Bipolar Junction Transistor |
| Collector-Emitter Voltage (Vce) | 45V |
| Collector-Base Voltage (Vcb) | 50V |
| Emitter-Base Voltage (Veb) | 6V |
| Collector Current (Ic) | 100 mA |
| DC Current Gain (hFE) | 110-800 |
| Power Dissipation | 500 mW |
| Package | TO-92 |

**Pin Configuration (BC547):**
```
Flat face toward you:
Pin 1: Collector
Pin 2: Base
Pin 3: Emitter
```

**Typical Application:**
```
Arduino Pin → 1kΩ → Base
Collector → Relay coil (+)
Emitter → GND
```

**2N2222 (Alternative):**
- Higher current capability: 800mA
- Same pin configuration as BC547
- Better for driving larger relays

---

### Diode (1N4007)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Type | Rectifier diode |
| Forward Current | 1A continuous |
| Peak Reverse Voltage | 1000V |
| Forward Voltage Drop | 1.1V @ 1A |
| Reverse Recovery Time | 30µs |
| Package | DO-41 |

**Color Code:**
- Black body with silver/white stripe (cathode)

**Applications in This Project:**
- Flyback protection across relay coils
- Reverse polarity protection
- Freewheeling diodes for motors

---

## Water Control Components

### Water Pump (DC Submersible)

**Specifications:**

| Parameter | Typical Value |
|-----------|---------------|
| Operating Voltage | 12V DC |
| Current Draw | 0.5A - 1.5A |
| Maximum Flow Rate | 2-5 L/min |
| Maximum Head | 1-3 meters |
| Power | 6-18W |
| Inlet/Outlet | 6-8mm diameter |
| Waterproof Rating | IP68 |
| Noise Level | < 35 dB |

**Recommended Models:**
- Micro DC pump (RS-360SH)
- Mini submersible pump 12V
- Fountain pump (adjust flow rate)

**Important Notes:**
- ✓ Use submersible type for reservoir
- ✓ Check flow rate matches your needs
- ✓ Ensure waterproof rating for outdoor use
- ⚠️ Add filter at inlet to prevent clogging
- ⚠️ Never run dry (can damage pump)

---

### Solenoid Valve (12V DC)

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 12V DC |
| Current Draw | 300-500 mA |
| Working Pressure | 0-0.8 MPa (0-116 PSI) |
| Flow Coefficient (Cv) | 0.5-1.0 |
| Orifice Diameter | 6-13mm (1/4" to 1/2") |
| Connection Type | Threaded (NPT/BSP) or barbed |
| Material | Plastic body, rubber seal |
| Operating Mode | Normally Closed (NC) |

**Operating Principle:**
- Energized: Valve opens, water flows
- De-energized: Valve closes, water stops
- Requires minimum pressure (typically 0.02 MPa)

**Important Notes:**
- ✓ Choose normally closed (NC) for safety
- ✓ Match inlet size to water supply
- ✓ Check pressure rating
- ⚠️ Requires clean water (add filter)
- ⚠️ Install arrow in flow direction

**Purchase Information:**
- Cost: $5-15 USD
- Common sizes: 1/4", 1/2", 3/4"

---

## Passive Components

### Resistors

**Values Used in This Project:**

| Value | Quantity | Application |
|-------|----------|-------------|
| 220Ω | 3-5 | LED current limiting, LCD backlight |
| 330Ω | 2-3 | Alternative for LEDs |
| 1kΩ | 2 | Transistor base resistor |
| 10kΩ | 2-3 | Pull-up/pull-down resistors |

**Specifications:**
- Type: Carbon film or metal film
- Power rating: 1/4W (0.25W) minimum
- Tolerance: ±5% (gold band) or ±1% (brown band)
- Package: Through-hole, axial

**Color Code (for 220Ω):**
- Band 1: Red (2)
- Band 2: Red (2)
- Band 3: Brown (×10)
- Band 4: Gold (±5%)

---

### Potentiometer

**10kΩ Trimpot (for LCD contrast):**

| Parameter | Value |
|-----------|-------|
| Resistance | 10kΩ ±20% |
| Type | Single-turn trimmer |
| Power Rating | 0.1W - 0.5W |
| Adjustment | Screwdriver slot |
| Package | 3-pin through-hole |

**Connection:**
- Pin 1: 5V
- Pin 2 (wiper): LCD V0
- Pin 3: GND

---

### Capacitors

**Ceramic Capacitors:**

| Value | Quantity | Application |
|-------|----------|-------------|
| 0.1µF (100nF) | 4-6 | Decoupling, noise filtering |
| 0.33µF | 1 | Voltage regulator input |

**Electrolytic Capacitors:**

| Value | Voltage | Quantity | Application |
|-------|---------|----------|-------------|
| 100µF | 16V | 2 | Power supply filtering |
| 1000µF | 16V | 1 | Large reservoir (optional) |

**Important:**
- ⚠️ Observe polarity on electrolytic caps
- Longer lead = positive (anode)
- Stripe indicates negative (cathode)

---

## Miscellaneous

### Buzzer/Alarm

**Specifications:**

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 3V - 5V DC |
| Current Draw | 20-30 mA |
| Sound Output | 85-95 dB @ 10cm |
| Frequency | 2-4 kHz |
| Type | Active (built-in oscillator) |

**Types:**
- Active buzzer: Just apply voltage → beeps
- Passive buzzer: Needs PWM signal → tones

**This project uses:** Active buzzer

---

### Jumper Wires

**Specifications:**

| Type | Length | Quantity |
|------|--------|----------|
| Male-to-Male | 15-20cm | 20 pcs |
| Male-to-Female | 15-20cm | 15 pcs |
| Female-to-Female | 15-20cm | 10 pcs |

**Wire Gauge:** 22-24 AWG  
**Current Rating:** 1-2A per wire

---

### Breadboard (for Prototyping)

**Specifications:**
- Type: Solderless breadboard
- Size: 830 tie-points (full-size)
- Dimensions: ~165mm × 55mm
- Power rails: 2 (positive and negative)
- Terminal strips: 630 points

---

### PCB Board (for Permanent Assembly)

**Options:**

1. **Perfboard (Veroboard):**
   - Size: 9cm × 15cm
   - Hole spacing: 2.54mm (0.1")
   - Material: FR4

2. **Custom PCB:**
   - Design in: KiCad, EasyEDA, Eagle
   - Manufacture: JLCPCB, PCBWay, OSH Park
   - Layer: Single or double-sided

---

## Component Sourcing

### Recommended Suppliers

**International:**
- **Amazon** - Fast shipping, higher prices
- **AliExpress** - Low prices, slow shipping
- **Mouser** - Quality components, electronics specialist
- **DigiKey** - Large selection, reliable
- **SparkFun** - Arduino-focused, tutorials included
- **Adafruit** - Quality, educational resources

**Local:**
- Check local electronics stores
- Maker spaces and hackerspaces
- University electronics labs (surplus)

---

## Total Bill of Materials (BOM)

| Item | Quantity | Est. Cost (USD) |
|------|----------|-----------------|
| Arduino Uno | 1 | $20-25 |
| Moisture Sensors | 3 | $6-15 |
| LCD 16x2 | 1 | $3-6 |
| Relay Module (2-ch) | 1 | $3-5 |
| Water Pump 12V | 1 | $5-10 |
| Solenoid Valve 12V | 1 | $5-15 |
| Power Supply 12V 2A | 1 | $8-12 |
| Buzzer | 1 | $1-2 |
| Transistors (BC547) | 2 | $0.50 |
| Diodes (1N4007) | 3 | $0.30 |
| Resistors (assorted) | 10 | $1-2 |
| Capacitors (assorted) | 10 | $2-3 |
| Potentiometer 10kΩ | 1 | $0.50 |
| Jumper Wires | 50 pcs | $3-5 |
| Breadboard | 1 | $5-8 |
| Enclosure | 1 | $5-10 |
| **TOTAL** | | **$70-120** |

**Notes:**
- Prices vary by region and supplier
- Bulk purchases reduce cost
- Quality affects price and longevity
- Consider shipping costs

---

## Quality Considerations

### Component Selection Tips

1. **Arduino:**
   - Buy original or quality clones (CH340 chip okay)
   - Avoid ultra-cheap clones (poor build quality)

2. **Sensors:**
   - Nickel-plated vs. capacitive (capacitive lasts longer)
   - Check seller reviews for accuracy

3. **Relays:**
   - Ensure proper isolation (optocoupler)
   - Check contact rating for your load

4. **Power Supply:**
   - Buy certified (CE, UL, FCC)
   - Adequate current rating
   - Overload protection essential

5. **Water Components:**
   - Check material compatibility with water type
   - Verify pressure ratings
   - Food-safe materials if needed

---

**Last Updated:** 2024
