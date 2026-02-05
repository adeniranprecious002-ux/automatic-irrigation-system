# Circuit Schematic Diagram

## Complete System Schematic

This document provides the detailed circuit schematic for the Automatic Irrigation System using real moisture sensor modules.

---

## Main Circuit Diagram

```
                                    AUTOMATIC IRRIGATION SYSTEM
                                    ============================

POWER SUPPLY SECTION
====================
                    +12V DC INPUT
                         │
                         ├────────────────────────────────┐
                         │                                │
                    ┌────▼────┐                          │
                    │  7805   │                          │
                    │ VR REG  │                          │
                    │ IN  OUT │                          │
                    └────┬────┘                          │
                         │ +5V                           │
                    ┌────┴────┐                          │
                   ─┴─ 100µF  ─┴─                        │
                    C1 (16V)   │                         │
                         │     │                         │
                        GND   ─┴─ 0.1µF                  │
                              ─┬─ C2                     │
                               │                         │
                              GND                        │
                                                          │
MICROCONTROLLER SECTION                                  │
=======================                                  │
                         +5V                             │
                          │                              │
                    ┌─────┴──────────────────────┐       │
                    │                             │      │
                    │      ARDUINO UNO R3         │      │
                    │      (ATmega328P)           │      │
                    │                             │      │
    SENSORS         │   A0  A1  A2  A3  A4  A5   │      │
    =======         │   │                  │      │      │      │
                    │   │                  │      │      │      │
  ┌─────────┐       │   │                  │      │      │      │
  │ Sensor1 │       │   │                  │      │      │      │
  │Reservoir│───────┤   │                  │      │      │      │
  │ VCC GND │       │   │                  │      │      │      │
  │  │   │  │       │   │                  │      │      │      │
  └──┼───┼──┘       │   │                  │      │      │      │
     │   │          │   │                  │      │      │      │
    5V  GND         │   │                  │      │      │      │
                    │   │                  │      │      │      │
  ┌─────────┐       │   │   ┌──────────────┘      │      │      │
  │ Sensor2 │       │   │   │              │      │      │      │
  │  Soil   │───────┤   │   │              │      │      │      │
  │Moisture │       │   │   │              │      │      │      │
  │ VCC GND │       │   │   │              │      │      │      │
  │  │   │  │       │   │   │              │      │      │      │
  └──┼───┼──┘       │   │   │              │      │      │      │
     │   │          │   │   │              │      │      │      │
    5V  GND         │   │   │              │      │      │      │
                    │   │   │   ┌──────────┘      │      │      │
  ┌─────────┐       │   │   │   │          │      │      │      │
  │ Sensor3 │       │   │   │   │          │      │      │      │
  │Overhead │───────┤   │   │   │          │      │      │      │
  │  Tank   │       │   │   │   │          │      │      │      │
  │ VCC GND │       │   │   │   │          │      │      │      │
  │  │   │  │       │   │   │   │          │      │      │      │
  └──┼───┼──┘       │   │   │   │          │      │      │      │
     │   │          │   │   │   │          │      │      │      │
    5V  GND         │   │   │   │          │      │      │      │
                    │   │   │   │          │      │      │      │
    DIGITAL I/O     │                             │      │      │
    ===========     │  D1  D2  D3 ... D10 D11 D12 D13   │      │
                    │  │                  │   │   │   │  │      │
LCD DISPLAY         │  │                  │   │   │   │  │      │
===========         │  │                  │   │   │   │  │      │
                    │  │                  │   │   │   │  │      │
    16x2 LCD        │  │                  │   │   │   │  │      │
    ┌─────────┐     │  │                  │   │   │   │  │      │
    │1  2  3  │     │  │                  │   │   │   │  │      │
    │VSS VDD VO│     │  │                  │   │   │   │  │      │
    │ │  │   │ │     │  │                  │   │   │   │  │      │
    │GND 5V  ┌┴┐    │  │                  │   │   │   │  │      │
    │       POT │    │  │                  │   │   │   │  │      │
    │       10kΩ│    │  │                  │   │   │   │  │      │
    │        └┬┘    │  │                  │   │   │   │  │      │
    │        GND    │  │                  │   │   │   │  │      │
    │               │  │                  │   │   │   │  │      │
    │4  5  6  11-14│  │                  │   │   │   │  │      │
    │RS RW E  D4-7│  │                  │   │   │   │  │      │
    │ │ │  │   │││││ │                  │   │   │   │  │      │
    │ │GND │   │││││ │                  │   │   │   │  │      │
    └─┼────┼───┼┼┼┼─┘  │                  │   │   │   │  │      │
      │    │   ││││    │                  │   │   │   │  │      │
      11  10   8765 ───┘                  │   │   │   │  │      │
                    │                     │   │   │   │  │      │
    │15 16│         │                     │   │   │   │  │      │
    │A   K│         │                     │   │   │   │  │      │
    │ │  │ │         │                     │   │   │   │  │      │
   5V─┤  └GND       │                     │   │   │   │  │      │
      │             │                     │   │   │   │  │      │
     220Ω           │                     │   │   │   │  │      │
      │             │                     │   │   │   │  │      │
     GND            │                     │   │   │   │  │      │
                    │                     │   │   │   │  │      │
                    │   5V               GND           │  │      │
                    └─────┬───────────────┬────────────┘  │      │
                          │               │               │      │
                         ─┴─ 0.1µF       ─┴─             │      │
                         ─┬─ C3         ─┬─             │      │
                          │               │               │      │
                         GND             GND              │      │
                                                          │      │
ALARM CIRCUIT                                             │      │
=============                                             │      │
                                                          │      │
    D1 ────┬─────────────────────────┐                   │      │
           │                         │                   │      │
          220Ω                       │                   │      │
           │                         │                   │      │
           ├──→ BUZZER (+)           │                   │      │
           │       │                 │                   │      │
          GND ←────┘                 │                   │      │
                                     │                   │      │
                                     │                   │      │
RELAY CONTROL CIRCUITS               │                   │      │
======================               │                   │      │
                                     │                   │      │
VALVE CONTROL (Pin 12)               │                   │      │
──────────────────────               │                   │      │
                                     │                   │      │
    D12 ──────┬──────────────────────┘                   │      │
              │                                          │      │
             1kΩ R1                                      │      │
              │                                          │      │
              ├──→ BC547 (Q1)                           │      │
              │      B C E                               │      │
             GND     │ │                                 │      │
                     │ └──→ GND                          │      │
                     │                                   │      │
                     │    ┌─────────┐                   │      │
                     └────┤1        │                   │      │
                    5V────┤2  RLY1  │                   │      │
                          │         │                   │      │
                          │  1N4007 │                   │      │
                          │  ┌───┐  │                   │      │
                    5V────┤──┤│ │├──┤                   │      │
                          └──┴─┬─┴──┘                   │      │
                             COM NO NC                  │      │
                              │  │  │                   │      │
                             12V │ NC                   │      │
                                 │                      │      │
                                 └──→ SOLENOID VALVE (+)│      │
                                          │              │      │
                                         GND             │      │
                                                         │      │
PUMP CONTROL (Pin 13)                                    │      │
─────────────────────                                    │      │
                                                         │      │
    D13 ──────┬──────────────────────────────────────────┘      │
              │                                                 │
             1kΩ R2                                             │
              │                                                 │
              ├──→ BC547 (Q2)                                  │
              │      B C E                                      │
             GND     │ │                                        │
                     │ └──→ GND                                 │
                     │                                          │
                     │    ┌─────────┐                          │
                     └────┤1        │                          │
                    5V────┤2  RLY2  │                          │
                          │         │                          │
                          │  1N4007 │                          │
                          │  ┌───┐  │                          │
                    5V────┤──┤│ │├──┤                          │
                          └──┴─┬─┴──┘                          │
                             COM NO NC                         │
                              │  │  │                          │
                             12V │ NC                          │
                                 │                             │
                                 └──→ WATER PUMP (+) ──────────┘
                                          │
                                         GND


COMPONENT VALUES
================
Resistors:
  R1, R2: 1kΩ (Transistor base)
  R3: 220Ω (Buzzer)
  R4: 220Ω (LCD backlight)
  POT1: 10kΩ (LCD contrast)

Capacitors:
  C1: 100µF 16V (Power supply filter)
  C2: 0.1µF (Regulator output)
  C3: 0.1µF (Arduino decoupling)

Semiconductors:
  Q1, Q2: BC547 NPN Transistor
  D1, D2: 1N4007 Diode
  IC1: 7805 Voltage Regulator

Relays:
  RLY1, RLY2: 5V SPDT Relay (10A contacts)

Other:
  LCD: 16x2 Character LCD (HD44780)
  Sensors: YL-69/FC-28 Moisture Sensor Modules
  Buzzer: 5V Active Buzzer

POWER REQUIREMENTS
==================
Input: 12V DC, 2A minimum
Logic Supply: 5V (regulated)
Load Supply: 12V (direct)
Total Power: ~20-25W (peak)
```

---

## Pin Connection Table

### Arduino Uno Pin Assignments

| Pin | Type | Connection | Function |
|-----|------|------------|----------|
| **ANALOG INPUTS** |
| A0 | Analog Input | Reservoir Sensor A0 | Water level monitoring |
| A3 | Analog Input | Soil Moisture Sensor A0 | Soil moisture monitoring |
| A5 | Analog Input | Overhead Tank Sensor A0 | Tank level monitoring |
| **DIGITAL I/O** |
| D1 | Digital Output | Buzzer (+) via 220Ω | Low water alarm |
| D5 | Digital Output | LCD D7 | LCD data |
| D6 | Digital Output | LCD D6 | LCD data |
| D7 | Digital Output | LCD D5 | LCD data |
| D8 | Digital Output | LCD D4 | LCD data |
| D10 | Digital Output | LCD E (Enable) | LCD control |
| D11 | Digital Output | LCD RS (Register Select) | LCD control |
| D12 | Digital Output | Q1 Base via 1kΩ | Valve relay control |
| D13 | Digital Output | Q2 Base via 1kΩ | Pump relay control |
| **POWER PINS** |
| 5V | Power Output | Sensors VCC, LCD VDD | +5V supply |
| GND | Ground | Common ground | 0V reference |
| VIN | Power Input | 7805 Output (optional) | 7-12V input |

---

## Sensor Module Connections

### YL-69 / FC-28 Moisture Sensor Module

Each sensor module has identical connections:

```
┌─────────────────────────────────┐
│  Moisture Sensor Module         │
│                                 │
│  Pin 1: VCC  ──→  5V           │
│  Pin 2: GND  ──→  GND          │
│  Pin 3: A0   ──→  Arduino Ax   │
│  Pin 4: D0   ──→  Not Connected│
│                                 │
│  [Sensor Probe Connection]     │
│                                 │
└─────────────────────────────────┘

Where Ax = A0, A3, or A5 depending on sensor
```

**Sensor Placement:**
- **Sensor 1 (A0):** Reservoir water tank
- **Sensor 2 (A3):** Soil/plant area
- **Sensor 3 (A5):** Overhead water tank

---

## LCD Display Connections

### 16x2 LCD Module (HD44780 Compatible)

```
LCD Pin Layout (Looking at back of LCD)
┌─────────────────────────────────────┐
│ 1  2  3  4  5  6  7  8  9 10 11 ... │
│VSS VDD V0 RS RW E D0 D1 D2 D3 D4 ...│
└─────────────────────────────────────┘

Pin Connections:
┌──────┬─────────────┬──────────────────────┐
│ LCD  │ Arduino/    │ Description          │
│ Pin  │ Component   │                      │
├──────┼─────────────┼──────────────────────┤
│  1   │ GND         │ Ground (VSS)         │
│  2   │ 5V          │ Power (VDD)          │
│  3   │ POT Wiper   │ Contrast (V0)        │
│  4   │ Pin 11      │ Register Select (RS) │
│  5   │ GND         │ Read/Write (RW)      │
│  6   │ Pin 10      │ Enable (E)           │
│  7   │ ---         │ Not used (4-bit mode)│
│  8   │ ---         │ Not used (4-bit mode)│
│  9   │ ---         │ Not used (4-bit mode)│
│ 10   │ ---         │ Not used (4-bit mode)│
│ 11   │ Pin 8       │ Data 4 (D4)          │
│ 12   │ Pin 7       │ Data 5 (D5)          │
│ 13   │ Pin 6       │ Data 6 (D6)          │
│ 14   │ Pin 5       │ Data 7 (D7)          │
│ 15   │ 5V + 220Ω   │ Backlight + (A)      │
│ 16   │ GND         │ Backlight - (K)      │
└──────┴─────────────┴──────────────────────┘

Contrast Control (10kΩ Potentiometer):
  Terminal 1 → 5V
  Wiper      → LCD Pin 3 (V0)
  Terminal 3 → GND
```

---

## Relay Driver Circuits

### Transistor-Based Relay Driver (×2)

**Circuit per relay:**

```
Arduino Pin (D12 or D13)
        │
        ├── 1kΩ Resistor
        │
        └──→ BC547 Base (Pin 1)
             │
             ├──→ Collector (Pin 2) ──┬──→ Relay Coil Pin 1
             │                        │
             └──→ Emitter (Pin 3) ──→ GND
                                      │
                        5V ───────────┴──→ Relay Coil Pin 2
                                      │
                        1N4007 Diode  │
                        Cathode ──────┘
                        Anode ─────→ Collector

Relay Contact Configuration:
  COM (Common) ──→ 12V Supply
  NO (Normally Open) ──→ Load (+)
  NC (Normally Closed) ──→ Not connected
  
  Load (-) ──→ GND
```

**Component Details:**

**Transistor BC547 Pinout:**
```
    Flat side facing you
    ┌─────────┐
    │   ___   │
    │  /   \  │
    │  │ ○ │  │
    │  \___/  │
    │         │
    │ 1  2  3 │
    │ C  B  E │
    └─────────┘
    Collector Base Emitter
```

**1N4007 Diode:**
```
    ┌──────────┐
────┤          ├────
    │  ──►│    │
    │   Diode  │
    └──────────┘
    Anode  Cathode
           (stripe)
```

---

## Power Supply Section

### Voltage Regulation Circuit

```
12V Input ───┬─── To Relay COM Terminals
             │
             ├─── 7805 Regulator ─── 5V Output
             │        │
            C1       C2
           100µF    0.1µF
             │        │
            GND      GND

Component Layout:
┌────────────────────────────────┐
│  7805 Voltage Regulator        │
│  (TO-220 Package)              │
│                                │
│  Looking at front (flat side): │
│                                │
│  ┌───────────┐                 │
│  │    TAB    │                 │
│  │  ┌─────┐  │                 │
│  │  │     │  │                 │
│  │  │     │  │                 │
│  └──┴──┬──┴──┘                 │
│     │  │  │                    │
│    IN GND OUT                  │
│    12V     5V                  │
└────────────────────────────────┘

Input Filter: 100µF electrolytic capacitor
Output Filter: 0.1µF ceramic capacitor
Heat Sink: Recommended for currents >500mA
```

---

## Water System Components

### Solenoid Valve Connection

```
12V Relay Output (NO)
        │
        └──→ Solenoid Valve (+) Terminal
                    │
                   Coil
                    │
                   GND

Specifications:
- Operating Voltage: 12V DC
- Current: 300-500mA
- Type: Normally Closed (NC)
- Connection: 1/2" or 3/4" NPT/BSP
```

### Water Pump Connection

```
12V Relay Output (NO)
        │
        └──→ DC Pump (+) Terminal
                  │
                Motor
                  │
                 GND

Specifications:
- Operating Voltage: 12V DC
- Current: 500mA - 1.5A
- Type: Submersible
- Flow Rate: 2-5 L/min
```

---

## PCB Layout Considerations

### Recommended PCB Sections

```
┌─────────────────────────────────────────┐
│                                         │
│  ┌──────────┐         ┌─────────────┐  │
│  │  POWER   │         │   ARDUINO   │  │
│  │  SUPPLY  │         │   MOUNT     │  │
│  └──────────┘         └─────────────┘  │
│                                         │
│  ┌──────────┐         ┌─────────────┐  │
│  │  RELAY   │         │    LCD      │  │
│  │ DRIVERS  │         │  CONNECTOR  │  │
│  └──────────┘         └─────────────┘  │
│                                         │
│  ┌─────────────────────────────────┐   │
│  │   TERMINAL BLOCKS               │   │
│  │   (Sensors, Pump, Valve)        │   │
│  └─────────────────────────────────┘   │
│                                         │
└─────────────────────────────────────────┘
```

### Trace Width Recommendations

- **5V Power**: 1.0mm minimum
- **12V Power**: 1.5mm minimum
- **Signal traces**: 0.5mm minimum
- **Ground plane**: Fill all available space

---

## Wiring Color Code

### Recommended Wire Colors

| Circuit | Color | Purpose |
|---------|-------|---------|
| +12V | Red | Main power positive |
| +5V | Orange | Logic power |
| GND | Black | Common ground |
| Sensor Signal | Yellow | Analog inputs |
| Control Signal | Green | Digital outputs |
| Relay Outputs | Blue | High current loads |

---

## Safety Features

### Protection Components

1. **Flyback Diodes (1N4007)**
   - Protect transistors from relay back-EMF
   - One across each relay coil

2. **Current Limiting Resistors**
   - 220Ω for buzzer (limits to ~20mA)
   - 1kΩ for transistor base (limits base current)

3. **Decoupling Capacitors**
   - 0.1µF near Arduino (C3)
   - Reduces noise and voltage spikes

4. **Voltage Regulation**
   - 7805 regulator with filtering
   - Protects Arduino from voltage spikes

---

## Testing Points

### Voltage Test Points

Add test points at these locations for debugging:

| Test Point | Expected Voltage | When |
|------------|------------------|------|
| TP1 - 12V Input | 11-13V | Always |
| TP2 - 5V Regulated | 4.75-5.25V | Always |
| TP3 - Sensor A0 | 0-5V | Variable |
| TP4 - Sensor A3 | 0-5V | Variable |
| TP5 - Sensor A5 | 0-5V | Variable |
| TP6 - Pin 12 | 0V or 5V | Valve control |
| TP7 - Pin 13 | 0V or 5V | Pump control |
| TP8 - Relay 1 Output | 0V or 12V | When active |
| TP9 - Relay 2 Output | 0V or 12V | When active |

---

## Bill of Materials Reference

See `docs/component-specs.md` for complete specifications.

---

**Note:** This schematic represents the complete electrical design. Always double-check connections before applying power. Use proper safety precautions when working with electrical circuits.

**Revision:** 1.0  
**Date:** 2024  
**Author:** Automatic Irrigation System Project
