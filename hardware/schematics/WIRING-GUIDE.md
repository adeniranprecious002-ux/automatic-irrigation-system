# Simplified Connection Diagram

## Quick Reference Wiring Guide

This is a simplified, easy-to-follow wiring guide for the Automatic Irrigation System.

---

## System Overview

```
┌─────────────┐
│   12V PSU   │
└──────┬──────┘
       │
       ├──────→ Pump & Valve (via Relays)
       │
       ├──────→ 7805 Regulator
       │              │
       │              ↓
       │         ┌─────────┐
       │         │   5V    │
       │         └────┬────┘
       │              │
       │              ├──→ Arduino
       │              ├──→ LCD
       │              ├──→ Sensors
       │              └──→ Relays Logic
       │
      GND (Common Ground - Very Important!)
```

---

## 1. ARDUINO UNO CONNECTIONS

### Power Connections

```
Arduino 5V Pin  ──→  +5V Rail (powers sensors & LCD)
Arduino GND Pin ──→  Common Ground
Arduino VIN     ──→  Optional: 7-12V input
```

### Sensor Inputs (Analog)

```
Arduino A0 ──→ Reservoir Sensor Module (A0 pin)
Arduino A3 ──→ Soil Moisture Sensor Module (A0 pin)
Arduino A5 ──→ Overhead Tank Sensor Module (A0 pin)
```

### LCD Display (Digital)

```
Arduino Pin 5  ──→ LCD D7
Arduino Pin 6  ──→ LCD D6
Arduino Pin 7  ──→ LCD D5
Arduino Pin 8  ──→ LCD D4
Arduino Pin 10 ──→ LCD E (Enable)
Arduino Pin 11 ──→ LCD RS (Register Select)
```

### Control Outputs (Digital)

```
Arduino Pin 1  ──→ Buzzer (+) via 220Ω resistor
Arduino Pin 12 ──→ Transistor Q1 Base (Valve Control)
Arduino Pin 13 ──→ Transistor Q2 Base (Pump Control)
```

---

## 2. MOISTURE SENSOR MODULES (×3)

### Each sensor module has 4 pins

```
Sensor Module Pinout:
┌─────────────────┐
│ [1] [2] [3] [4] │
│ VCC GND A0  D0  │
└─────────────────┘

Connection for EACH sensor:
Pin 1 (VCC) ──→ +5V
Pin 2 (GND) ──→ Ground
Pin 3 (A0)  ──→ Arduino Analog Pin (A0, A3, or A5)
Pin 4 (D0)  ──→ Leave UNCONNECTED (not used)
```

### Sensor Assignment

```
Sensor #1: Connect A0 to Arduino A0 (Reservoir Level)
Sensor #2: Connect A0 to Arduino A3 (Soil Moisture)
Sensor #3: Connect A0 to Arduino A5 (Overhead Tank)
```

---

## 3. LCD DISPLAY (16×2)

### LCD has 16 pins

```
Full LCD Pinout (back view):
┌────────────────────────────────────────────────┐
│ 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16│
│VSS VDD V0 RS RW E D0 D1 D2 D3 D4 D5 D6 D7 A  K│
└────────────────────────────────────────────────┘

Connections:
Pin  1 (VSS) ──→ GND
Pin  2 (VDD) ──→ +5V
Pin  3 (V0)  ──→ Potentiometer wiper (contrast)
Pin  4 (RS)  ──→ Arduino Pin 11
Pin  5 (RW)  ──→ GND (write mode only)
Pin  6 (E)   ──→ Arduino Pin 10
Pin  7 (D0)  ──→ Not connected
Pin  8 (D1)  ──→ Not connected
Pin  9 (D2)  ──→ Not connected
Pin 10 (D3)  ──→ Not connected
Pin 11 (D4)  ──→ Arduino Pin 8
Pin 12 (D5)  ──→ Arduino Pin 7
Pin 13 (D6)  ──→ Arduino Pin 6
Pin 14 (D7)  ──→ Arduino Pin 5
Pin 15 (A)   ──→ +5V via 220Ω resistor (backlight)
Pin 16 (K)   ──→ GND (backlight)
```

### Contrast Potentiometer (10kΩ)

```
Terminal 1 ──→ +5V
Wiper      ──→ LCD Pin 3 (V0)
Terminal 3 ──→ GND

Adjust this to make text visible!
```

---

## 4. RELAY DRIVER CIRCUITS (×2)

### Circuit for EACH relay (identical)

```
RELAY 1 - VALVE CONTROL (Pin 12)
───────────────────────────────────

Arduino Pin 12
      │
      ├──→ 1kΩ Resistor
      │
      └──→ BC547 Transistor BASE
           │
           │  BC547 Pinout (flat side facing you):
           │  ┌───────┐
           │  │ C B E │
           │  │ │ │ │ │
           └──┴─┴─┴───┘
              │ │ │
              │ │ └──→ GND
              │ └────→ To 1kΩ resistor from Arduino
              │
              └──→ Relay Coil Pin 1
                        │
                   +5V ─┴─→ Relay Coil Pin 2
                        │
                   1N4007 Diode across coil
                   (Cathode to +5V, Anode to Collector)

Relay Contacts:
  COM ──→ +12V
  NO  ──→ Solenoid Valve (+)
  NC  ──→ Not connected
  
Valve (−) ──→ GND


RELAY 2 - PUMP CONTROL (Pin 13)
─────────────────────────────────

Arduino Pin 13
      │
      ├──→ 1kΩ Resistor
      │
      └──→ BC547 Transistor BASE
           │
           │  (Same pinout as above)
           │
           └──→ BC547 COLLECTOR
                     │
                     └──→ Relay Coil Pin 1
                               │
                          +5V ─┴─→ Relay Coil Pin 2
                               │
                          1N4007 Diode across coil

Relay Contacts:
  COM ──→ +12V
  NO  ──→ Water Pump (+)
  NC  ──→ Not connected
  
Pump (−) ──→ GND
```

### Important: Diode Orientation

```
1N4007 Diode must be placed ACROSS the relay coil:

     Relay Coil
        │ │
        │ │
   ┌────┘ └────┐
   │           │
   │  ┌─────┐  │
   └──┤►│───├──┘
      └─────┘
      1N4007
   Anode  Cathode
          (stripe)

Cathode (stripe) → +5V
Anode           → Collector
```

---

## 5. BUZZER/ALARM

### Simple Connection

```
Arduino Pin 1
      │
      ├──→ 220Ω Resistor
      │
      └──→ Buzzer (+) Terminal
                │
               GND ←─── Buzzer (−) Terminal

Note: Use ACTIVE buzzer (has built-in oscillator)
```

---

## 6. POWER SUPPLY

### Option A: Dual Supply (Recommended)

```
12V Power Adapter (2A minimum):
  (+) ──→ Relay COM terminals (both relays)
  (−) ──→ Common GND

5V USB Power:
  USB ──→ Arduino USB port
        Arduino 5V pin ──→ Sensors, LCD, Relay logic
```

### Option B: Single 12V Supply with Regulator

```
12V Input
   │
   ├──→ Relay COM terminals (12V loads)
   │
   └──→ 7805 Voltage Regulator
         │
         │  7805 Pinout (front view):
         │  ┌───────┐
         │  │  TAB  │
         │  │ ┌───┐ │
         │  └─┴─┬─┴─┘
         │   │ │ │
         │  IN G OUT
         │  12V  5V
         │   │  │
         │   │  ├──→ Arduino VIN
         │   │  └──→ +5V Rail
         │   │
         │  GND ←───┴─── Common Ground
         │
    Add Capacitors:
    - 100µF between IN and GND
    - 0.1µF between OUT and GND
```

---

## 7. COMPLETE WIRING CHECKLIST

### Step-by-step Assembly

#### Step 1: Power Rails

```
☐ Set up +5V power rail
☐ Set up +12V power rail  
☐ Set up common GND rail
☐ Connect all grounds together (CRITICAL!)
```

#### Step 2: Arduino Connections

```
☐ Connect Arduino 5V to +5V rail
☐ Connect Arduino GND to GND rail
☐ Verify power on Arduino (LED should light)
```

#### Step 3: LCD Display

```
☐ Connect LCD power (VSS, VDD)
☐ Connect contrast pot (10kΩ)
☐ Connect LCD control pins (RS, RW, E)
☐ Connect LCD data pins (D4-D7)
☐ Connect LCD backlight (A, K with 220Ω)
☐ Test: Upload LCD test code
```

#### Step 4: Sensors

```
☐ Connect Sensor 1 (VCC, GND, A0 to Arduino A0)
☐ Connect Sensor 2 (VCC, GND, A0 to Arduino A3)
☐ Connect Sensor 3 (VCC, GND, A0 to Arduino A5)
☐ Test: Upload sensor test code
```

#### Step 5: Relay Drivers

```
☐ Build Relay 1 circuit (transistor, resistor, diode)
☐ Build Relay 2 circuit (transistor, resistor, diode)
☐ Connect Arduino Pin 12 to Relay 1
☐ Connect Arduino Pin 13 to Relay 2
☐ Test: Manually trigger pins, listen for clicking
```

#### Step 6: Loads

```
☐ Connect +12V to both Relay COM terminals
☐ Connect Valve to Relay 1 NO terminal
☐ Connect Pump to Relay 2 NO terminal
☐ Connect Valve and Pump (−) to GND
☐ Test: Upload full code, test operation
```

#### Step 7: Buzzer

```
☐ Connect Arduino Pin 1 to 220Ω resistor
☐ Connect resistor to Buzzer (+)
☐ Connect Buzzer (−) to GND
☐ Test: Trigger alarm condition
```

#### Step 8: Final Checks

```
☐ Double-check all power connections
☐ Verify no short circuits
☐ Check diode polarity
☐ Verify transistor pinout
☐ Test complete system operation
```

---

## 8. QUICK TROUBLESHOOTING

### Power Issues

```
Problem: Nothing works
Check:
  ☐ 12V power supply connected?
  ☐ 5V present at Arduino 5V pin?
  ☐ All grounds connected?
  ☐ Fuse not blown?
```

### LCD Issues

```
Problem: LCD blank
Check:
  ☐ Power (VDD = 5V, VSS = GND)?
  ☐ Contrast pot adjusted?
  ☐ Backlight connected?
  
Problem: LCD shows blocks
Check:
  ☐ Contrast too high?
  ☐ Connections D4-D7 correct?
  ☐ RS and E pins correct?
```

### Sensor Issues

```
Problem: Sensor reads constant value
Check:
  ☐ VCC connected to 5V?
  ☐ GND connected?
  ☐ A0 pin to correct Arduino pin?
  ☐ Sensor working? (test with multimeter)
```

### Relay Issues

```
Problem: Relay doesn't click
Check:
  ☐ Transistor oriented correctly?
  ☐ 1kΩ resistor present?
  ☐ Relay coil connected to 5V?
  ☐ Diode present and correct polarity?
  
Problem: Relay clicks but load doesn't work
Check:
  ☐ 12V connected to COM?
  ☐ Load connected to NO?
  ☐ Load ground connected?
  ☐ Load functioning? (test directly)
```

---

## 9. SAFETY WARNINGS

### ⚠️ CRITICAL SAFETY POINTS

```
☐ NEVER mix up +5V and +12V connections
☐ ALWAYS connect all grounds together
☐ NEVER reverse transistor pins (will destroy it)
☐ NEVER reverse diode polarity (no protection)
☐ ALWAYS disconnect power before wiring
☐ ALWAYS double-check before powering on
☐ NEVER touch circuits while powered
☐ ALWAYS use proper gauge wire for 12V loads
☐ NEVER exceed relay current rating
☐ ALWAYS use insulated tools
```

---

## 10. COMPONENT SUMMARY

### Shopping List with Quantities

```
Arduino & Display:
  1× Arduino Uno
  1× LCD 16×2
  1× 10kΩ Potentiometer

Sensors:
  3× Moisture Sensor Modules (YL-69 / FC-28)

Switching:
  2× 5V SPDT Relay
  2× BC547 NPN Transistor
  2× 1N4007 Diode

Resistors:
  2× 1kΩ (transistor base)
  2× 220Ω (buzzer & LCD backlight)

Other:
  1× 5V Active Buzzer
  1× 12V DC Water Pump
  1× 12V Solenoid Valve
  1× 12V 2A Power Supply
  1× 7805 Voltage Regulator (if using single supply)
  2× 100µF Capacitor (power filtering)
  2× 0.1µF Capacitor (decoupling)
  
Wiring:
  Jumper wires (M-M, M-F, F-F)
  Solid core wire (22 AWG for breadboard)
  Stranded wire (18-20 AWG for 12V loads)
```

---

**Congratulations!** You now have a complete wiring guide. Take your time, double-check each connection, and test incrementally.

**Good luck with your build! 🌱💧**
