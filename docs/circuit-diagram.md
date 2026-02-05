# Circuit Diagram and Connections

## Overview

This document provides detailed circuit connection information for the Automatic Irrigation System.

## System Architecture

```
┌─────────────┐
│   Power     │
│   Supply    │──────┬─────────────────────────────┐
│   12V/5V    │      │                             │
└─────────────┘      │                             │
                     ▼                             ▼
              ┌─────────────┐              ┌─────────────┐
              │   Arduino   │              │   Relay     │
              │     Uno     │──────────────│   Module    │
              └─────────────┘              └─────────────┘
                     │                             │
        ┌────────────┼────────────┐               │
        ▼            ▼            ▼               ▼
    ┌───────┐  ┌─────────┐  ┌─────────┐    ┌──────────┐
    │Sensor │  │Sensor   │  │ Sensor  │    │   Pump/  │
    │  A0   │  │   A3    │  │   A5    │    │  Valve   │
    └───────┘  └─────────┘  └─────────┘    └──────────┘
    Reservoir   Soil Moist.  Overhead
```

## Detailed Pin Connections

### Arduino Uno Pin Configuration

#### Digital Pins

| Arduino Pin | Component | Function | Notes |
|-------------|-----------|----------|-------|
| Pin 1 | Buzzer/Alarm | Low water alert | Active HIGH |
| Pin 5 | LCD D7 | Data line 7 | |
| Pin 6 | LCD D6 | Data line 6 | |
| Pin 7 | LCD D5 | Data line 5 | |
| Pin 8 | LCD D4 | Data line 4 | |
| Pin 10 | LCD E | Enable signal | |
| Pin 11 | LCD RS | Register Select | |
| Pin 12 | Relay IN2 | Valve control | Via transistor/relay |
| Pin 13 | Relay IN1 | Pump control | Via transistor/relay |

#### Analog Pins

| Arduino Pin | Component | Function | Voltage Range |
|-------------|-----------|----------|---------------|
| A0 | Reservoir Sensor | Water level detection | 0-5V |
| A3 | Soil Moisture Sensor | Soil moisture detection | 0-5V |
| A5 | Overhead Tank Sensor | Water level detection | 0-5V |

#### Power Pins

| Pin | Connection |
|-----|------------|
| 5V | Sensors VCC, LCD VCC |
| GND | Common ground for all components |
| VIN | 12V input (optional, if powered via barrel jack) |

## Component Connections

### 1. LCD Display (16x2)

```
LCD Pin  │ Arduino Pin │ Function
─────────┼─────────────┼──────────
VSS (1)  │ GND         │ Ground
VDD (2)  │ 5V          │ Power (+5V)
V0 (3)   │ Potentiometer│ Contrast adjustment
RS (4)   │ Pin 11      │ Register Select
RW (5)   │ GND         │ Read/Write (Write mode)
E (6)    │ Pin 10      │ Enable
D0 (7)   │ -           │ Not connected (4-bit mode)
D1 (8)   │ -           │ Not connected (4-bit mode)
D2 (9)   │ -           │ Not connected (4-bit mode)
D3 (10)  │ -           │ Not connected (4-bit mode)
D4 (11)  │ Pin 8       │ Data bit 4
D5 (12)  │ Pin 7       │ Data bit 5
D6 (13)  │ Pin 6       │ Data bit 6
D7 (14)  │ Pin 5       │ Data bit 7
A (15)   │ 5V via 220Ω │ Backlight anode
K (16)   │ GND         │ Backlight cathode
```

**Contrast Control:**
- Connect 10kΩ potentiometer:
  - Terminal 1 → 5V
  - Terminal 2 → LCD V0 (Pin 3)
  - Terminal 3 → GND

### 2. Moisture Sensors (x3)

All sensors use identical connection pattern:

```
Sensor Pin │ Arduino Connection
───────────┼────────────────────
VCC        │ 5V
GND        │ GND
A0 (OUT)   │ A0/A3/A5 (respective sensor)
```

**Sensor Locations:**
- **A0**: Reservoir water level sensor
- **A3**: Soil moisture sensor (main)
- **A5**: Overhead tank water level sensor

### 3. Relay Module (2-Channel)

```
Relay Pin │ Connection      │ Purpose
──────────┼─────────────────┼─────────────────
VCC       │ 5V              │ Relay logic power
GND       │ GND             │ Common ground
IN1       │ Arduino Pin 13  │ Pump control signal
IN2       │ Arduino Pin 12  │ Valve control signal
```

**Relay 1 (Pump):**
```
Common (COM) → 12V Power Supply (+)
Normally Open (NO) → Water Pump (+)
Pump (-) → Power Supply GND
```

**Relay 2 (Valve):**
```
Common (COM) → 12V Power Supply (+)
Normally Open (NO) → Solenoid Valve (+)
Valve (-) → Power Supply GND
```

### 4. Transistor Driver Circuit (Optional, if not using relay module)

If you're building custom relay drivers:

```
Arduino Pin → 1kΩ Resistor → Base (BC547/2N2222)
                              Collector → Relay Coil (+)
                              Emitter → GND
Relay Coil (-) → 12V Supply
1N4007 Diode across relay coil (cathode to +12V)
```

### 5. Buzzer/Alarm

```
Component │ Connection
──────────┼────────────
Buzzer (+) │ Arduino Pin 1 (via 220Ω resistor)
Buzzer (-) │ GND
```

For active buzzer: Direct connection
For passive buzzer: May need transistor driver

### 6. LED Indicators (Optional)

```
LED Purpose     │ Arduino Pin │ LED (+) via Resistor
────────────────┼─────────────┼─────────────────────
Power Indicator │ -           │ 5V via 220Ω → GND
Pump Status     │ Pin 13      │ Via 220Ω → GND
Valve Status    │ Pin 12      │ Via 220Ω → GND
```

## Power Supply Configuration

### Option 1: Dual Power Supply (Recommended)

```
12V Power Supply:
├── To Relay Module VCC (+)
├── To Water Pump (via relay)
├── To Solenoid Valve (via relay)
└── GND → Common Ground

5V Power Supply (via Arduino):
├── USB Power → Arduino
└── Arduino 5V → LCD, Sensors, Relay logic
```

### Option 2: Single 12V Supply with Regulator

```
12V Input
├── To Relay Module (12V devices)
└── To 7805 Voltage Regulator
    ├── Output (5V) → Arduino VIN
    └── GND → Common Ground

Capacitors:
- 0.33µF ceramic: 7805 input
- 0.1µF ceramic: 7805 output
```

## Complete Circuit Schematic

### Main Circuit

```
                    +12V
                     │
                 ┌───┴───┐
                 │ 7805  │
                 │  Reg  │
                 └───┬───┘
                     │ +5V
    ┌────────────────┼────────────────────┐
    │                │                    │
    │           ┌────▼─────┐              │
    │           │ Arduino  │              │
    │           │   Uno    │              │
    │           │          │              │
    │           │ A0  A3  A5│             │
    │           │  │   │   │ │            │
    │           │ Pin  Pin Pin│           │
    │           │ 12   13  1  │           │
    │           └──┬───┬───┬──┘           │
    │              │   │   │              │
    │         Valve Pump Alarm            │
    │              │   │   │              │
    ▼              ▼   ▼   ▼              ▼
┌────────┐    ┌─────────────────┐    ┌────────┐
│Sensors │    │  Relay Module   │    │  LCD   │
│ (x3)   │    │  (2-Channel)    │    │ 16x2   │
└────────┘    └─────────────────┘    └────────┘
    │                  │                   │
    └──────────────────┴───────────────────┘
                       │
                      GND
```

## Safety Considerations

### Protection Diodes

Add 1N4007 diodes across inductive loads:

```
Across Relay Coil:
Cathode (stripe) → +12V
Anode → Coil -

Across Water Pump:
Cathode → Pump +
Anode → Pump -

Across Solenoid Valve:
Cathode → Valve +
Anode → Valve -
```

### Current Limiting Resistors

| Component | Resistor Value | Purpose |
|-----------|----------------|---------|
| LCD Backlight | 220Ω | Limit current to ~20mA |
| LED Indicators | 220Ω - 330Ω | Limit current to ~15-20mA |
| Buzzer | 100Ω - 220Ω | Prevent overcurrent |
| Transistor Base | 1kΩ | Limit base current |

## Testing Points

When debugging, measure voltage at these points:

| Test Point | Expected Voltage | Condition |
|------------|------------------|-----------|
| Arduino 5V | 4.8V - 5.2V | Powered |
| Sensor VCC | 4.8V - 5.2V | Powered |
| Sensor OUT | 0V - 5V | Variable (based on moisture) |
| Relay VCC | 4.8V - 5.2V | Powered |
| Relay COM | 12V | When relay OFF |
| Relay NO | 12V | When relay ON |
| Pin 13 | 5V / 0V | Pump ON / OFF |
| Pin 12 | 5V / 0V | Valve ON / OFF |

## Troubleshooting Connection Issues

### LCD Not Displaying
- Check contrast potentiometer (try rotating fully)
- Verify 5V and GND connections
- Check data pin connections (D4-D7)
- Verify RS and E pin connections

### Sensors Reading Constant Values
- Check VCC and GND connections
- Verify analog pin connections (A0, A3, A5)
- Test sensor with multimeter (should vary 0-5V)

### Relays Not Switching
- Check relay module VCC (should be 5V)
- Verify control signal pins (12, 13)
- Test with LED instead of relay
- Check for adequate power supply current

### Pump/Valve Not Working
- Check 12V supply to relay COM
- Verify relay switching (listen for click)
- Test pump/valve directly with 12V
- Check wiring polarity

## Recommended Wire Gauges

| Connection Type | Wire Gauge | Notes |
|----------------|------------|-------|
| Sensor signals | 22-24 AWG | Keep under 1 meter |
| Logic signals | 22-24 AWG | Arduino to components |
| Power (5V) | 20-22 AWG | Up to 1A |
| Power (12V pump) | 18-20 AWG | Depends on pump current |

## PCB Design Tips (Future)

For permanent installation:
- Minimum trace width: 0.5mm for signals, 1mm for power
- Keep sensor traces away from high-current traces
- Add test points for all critical signals
- Include mounting holes for enclosure
- Add connectors for easy sensor replacement

---

**Safety Warning**: Always disconnect power before making any connections or modifications to the circuit.
