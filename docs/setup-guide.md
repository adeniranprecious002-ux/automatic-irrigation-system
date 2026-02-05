# Setup Guide

Complete step-by-step guide for setting up the Automatic Irrigation System.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Hardware Assembly](#hardware-assembly)
3. [Software Installation](#software-installation)
4. [Sensor Calibration](#sensor-calibration)
5. [System Testing](#system-testing)
6. [Deployment](#deployment)
7. [Maintenance](#maintenance)

---

## Prerequisites

### Tools Required

- [ ] Screwdriver set (Phillips and flathead)
- [ ] Wire strippers
- [ ] Wire cutters
- [ ] Multimeter (for testing)
- [ ] Soldering iron and solder (for permanent assembly)
- [ ] Heat shrink tubing or electrical tape
- [ ] Small pliers
- [ ] USB cable (Type A to Type B)

### Materials Checklist

- [ ] Arduino Uno board
- [ ] 3× Soil moisture sensors
- [ ] 16×2 LCD display
- [ ] 2-channel relay module
- [ ] 12V water pump
- [ ] 12V solenoid valve
- [ ] 12V 2A power supply
- [ ] Buzzer/alarm
- [ ] Jumper wires (M-M, M-F, F-F)
- [ ] Breadboard (for prototyping)
- [ ] Resistors (220Ω, 1kΩ, 10kΩ)
- [ ] Capacitors (0.1µF, 100µF)
- [ ] Diodes (1N4007)
- [ ] 10kΩ potentiometer
- [ ] Enclosure (weatherproof for outdoor use)
- [ ] Water tubing and connectors
- [ ] Cable ties and mounting hardware

### Software Requirements

- [ ] Computer (Windows, Mac, or Linux)
- [ ] Arduino IDE (1.8.x or higher)
- [ ] USB drivers (usually auto-install)
- [ ] LiquidCrystal library (included in Arduino IDE)

---

## Hardware Assembly

### Phase 1: Breadboard Prototype

#### Step 1: Prepare the Workspace

1. Clear a clean, dry workspace
2. Organize all components by type
3. Keep the circuit diagram handy
4. Ensure good lighting

#### Step 2: Mount Arduino on Breadboard

1. Place breadboard on stable surface
2. Position Arduino Uno next to breadboard
3. Do NOT insert Arduino into breadboard (it won't fit properly)
4. Use jumpers to connect Arduino to breadboard

#### Step 3: LCD Display Connection

**Important:** Test LCD with simple sketch first!

```
Connection sequence:
1. Connect power rails:
   - Breadboard + rail → Arduino 5V
   - Breadboard - rail → Arduino GND

2. LCD Power:
   - LCD VSS (Pin 1) → GND
   - LCD VDD (Pin 2) → 5V
   
3. LCD Contrast (Potentiometer):
   - 10kΩ pot terminal 1 → 5V
   - 10kΩ pot wiper (middle) → LCD V0 (Pin 3)
   - 10kΩ pot terminal 3 → GND
   
4. LCD Control:
   - LCD RS (Pin 4) → Arduino Pin 11
   - LCD RW (Pin 5) → GND (write mode)
   - LCD E (Pin 6) → Arduino Pin 10
   
5. LCD Data (4-bit mode):
   - LCD D4 (Pin 11) → Arduino Pin 8
   - LCD D5 (Pin 12) → Arduino Pin 7
   - LCD D6 (Pin 13) → Arduino Pin 6
   - LCD D7 (Pin 14) → Arduino Pin 5
   
6. LCD Backlight:
   - LCD A (Pin 15) → 5V via 220Ω resistor
   - LCD K (Pin 16) → GND
```

**Testing LCD:**

1. Upload the LCD test sketch (see examples folder)
2. Adjust potentiometer to see characters clearly
3. You should see "Hello World" or test message

#### Step 4: Connect Sensors

**All three sensors use same connection pattern:**

```
Sensor 1 (Reservoir - A0):
- Sensor VCC → 5V
- Sensor GND → GND
- Sensor A0 → Arduino A0

Sensor 2 (Soil Moisture - A3):
- Sensor VCC → 5V
- Sensor GND → GND
- Sensor A0 → Arduino A3

Sensor 3 (Overhead Tank - A5):
- Sensor VCC → 5V
- Sensor GND → GND
- Sensor A0 → Arduino A5
```

**Testing Sensors:**

1. Upload sensor test sketch
2. Open Serial Monitor (9600 baud)
3. Dry sensor should read ~1000
4. Wet sensor should read ~200-400
5. Verify all three sensors work independently

#### Step 5: Relay Module Connection

**Warning:** Do not connect high voltage (230V AC) during breadboard testing!

```
Relay Module Control:
- Relay VCC → 5V
- Relay GND → GND
- Relay IN1 → Arduino Pin 13 (Pump control)
- Relay IN2 → Arduino Pin 12 (Valve control)

For testing (use LEDs instead of pump/valve):
- Relay 1 COM → 5V
- Relay 1 NO → LED (+) via 220Ω resistor → GND
- Relay 2 COM → 5V
- Relay 2 NO → LED (+) via 220Ω resistor → GND
```

**Testing Relays:**

1. Listen for clicking sound when relay activates
2. LED should light up when relay is ON
3. Test both channels independently

#### Step 6: Buzzer/Alarm Connection

```
Active Buzzer:
- Buzzer (+) → Arduino Pin 1 via 220Ω resistor
- Buzzer (-) → GND

OR (for louder sound):
- Buzzer (+) → 5V via transistor
- Transistor base → Arduino Pin 1 via 1kΩ resistor
- Transistor collector → Buzzer (+)
- Transistor emitter → GND
- Buzzer (-) → GND
```

#### Step 7: Power Supply Setup

**For breadboard testing, use Arduino USB power:**

1. Connect Arduino to computer via USB
2. Arduino provides 5V to all components
3. Total current should be < 500mA

**For standalone testing with 12V pump/valve:**

```
Option 1: Separate power supplies
- 12V adapter → Relay module (VCC for loads only)
- USB power → Arduino

Option 2: Regulated 12V supply
- 12V input → 7805 regulator
- 7805 output → Arduino VIN
- 12V direct → Relay loads
- Common ground for all!
```

### Phase 2: Permanent Assembly

#### Step 1: PCB Planning (Optional)

For permanent installation, consider:

- Custom PCB design using KiCad or EasyEDA
- Perfboard (veroboard) with point-to-point soldering
- Arduino shield design

#### Step 2: Enclosure Selection

**Requirements:**

- Size: Accommodate all components
- Material: ABS plastic or metal for outdoor use
- IP Rating: IP65 or higher for weather resistance
- Ventilation: Holes for heat dissipation
- Cable glands: For sensor and power cables

**Recommended:**

- Weatherproof junction box (150mm × 100mm × 75mm)
- Transparent cover for viewing LCD
- Wall or pole mounting brackets

#### Step 3: Component Mounting

```
Layout inside enclosure:
┌─────────────────────────────┐
│  [Power Supply]             │
│                [Arduino]    │
│  [Relay Module]             │
│                [LCD Display]│
│  [Terminal Blocks]          │
└─────────────────────────────┘

Mounting tips:
- Use standoffs for Arduino
- Hot glue or double-sided tape for LCD
- Secure relay module with screws
- Use terminal blocks for external connections
```

#### Step 4: Wiring

**Best practices:**

1. Use color-coded wires:
   - Red: +5V / +12V
   - Black: GND
   - Yellow: Analog signals
   - Green: Control signals

2. Keep wires organized:
   - Bundle related wires together
   - Use cable ties
   - Label all connections

3. Strain relief:
   - Use cable glands
   - Tie down wires inside enclosure
   - Leave service loops

#### Step 5: Soldering (if using perfboard)

**Soldering tips:**

1. Heat the pad and component lead together (2-3 seconds)
2. Apply solder to the heated joint
3. Remove iron and let cool without moving
4. Inspect for good solder joints (shiny, cone-shaped)
5. Check for cold solder joints (dull, cracked)
6. Look for solder bridges between pads

**Component placement:**

- Start with lowest profile components (resistors, diodes)
- Then medium height (capacitors, IC sockets)
- Finally tall components (connectors, relays)

---

## Software Installation

### Step 1: Install Arduino IDE

**Windows:**

1. Download from: <https://www.arduino.cc/en/software>
2. Run installer (arduino-ide-windows.exe)
3. Follow installation wizard
4. Install drivers when prompted

**Mac:**

1. Download .dmg file
2. Drag Arduino to Applications folder
3. Open from Applications

**Linux:**

1. Download .tar.xz file
2. Extract: `tar -xf arduino-*.tar.xz`
3. Run: `sudo ./install.sh`

### Step 2: Configure Arduino IDE

1. Connect Arduino via USB
2. Open Arduino IDE
3. Select board: `Tools > Board > Arduino Uno`
4. Select port: `Tools > Port > COM# (Arduino Uno)` or `/dev/ttyUSB0`
5. Test: Upload "Blink" example

### Step 3: Install Libraries

**LiquidCrystal library** (usually pre-installed):

1. `Sketch > Include Library > Manage Libraries`
2. Search "LiquidCrystal"
3. Click Install (if not already installed)

**SoftwareSerial library** (pre-installed):

- No action needed, included with Arduino IDE

### Step 4: Download Project Code

**Option A: From GitHub**

```bash
git clone https://github.com/adeniranprecious002-ux/automatic-irrigation-system.git
cd automatic-irrigation-system
```

**Option B: Manual Download**

1. Download ZIP from GitHub
2. Extract to your Arduino folder
3. Open `src/irrigation_system/irrigation_system.ino`

### Step 5: Upload Code to Arduino

1. Open `irrigation_system.ino` in Arduino IDE
2. Verify code: Click ✓ (Verify) button
3. Check for compilation errors
4. Upload: Click → (Upload) button
5. Wait for "Done uploading" message

**Troubleshooting upload issues:**

- Check USB cable (try a different one)
- Verify correct COM port selected
- Close Serial Monitor if open
- Try resetting Arduino before upload
- Check for USB driver issues

---

## Sensor Calibration

### Why Calibrate?

Sensors vary in sensitivity. Calibration ensures:

- Accurate moisture readings
- Proper threshold triggering
- Reliable system operation

### Calibration Procedure

#### Step 1: Prepare Test Materials

- Completely dry soil/sand
- Container of water
- Spray bottle with water
- Towels
- Notebook for recording values

#### Step 2: Calibrate Soil Moisture Sensor

```
1. Dry Reading (Air):
   - Remove sensor from any material
   - Note reading: Should be ~1000-1023
   
2. Saturated Reading (Water):
   - Fully submerge sensor in water
   - Note reading: Should be ~200-400
   
3. Create Reference Points:
   - Dry soil: Record value
   - Slightly moist: Record value
   - Medium moist: Record value
   - Very wet: Record value
   
4. Calculate Percentage:
   moistureLevel = map(reading, WET_VALUE, DRY_VALUE, 100, 0);
```

#### Step 3: Calibrate Water Level Sensors

For each sensor:

```
1. Empty: Note reading
2. 25% full: Note reading
3. 50% full: Note reading
4. 75% full: Note reading
5. 100% full: Note reading

Create a calibration curve or use linear mapping.
```

#### Step 4: Update Code with Calibration Values

```cpp
// Replace default values with your calibration data
#define DRY_READING 900    // Your dry air reading
#define WET_READING 300    // Your water reading

// In loop():
float moisturePercent = map(moisture, WET_READING, DRY_READING, 100, 0);
moisturePercent = constrain(moisturePercent, 0, 100);
```

#### Step 5: Test Calibration

1. Test with real soil at different moisture levels
2. Compare LCD display with actual conditions
3. Adjust threshold values if needed

---

## System Testing

### Test Sequence

#### Test 1: Power-On Test

**Expected behavior:**

- [ ] LCD backlight illuminates
- [ ] Startup message displays
- [ ] All sensors show readings
- [ ] No smoke or burning smell
- [ ] No unusual sounds

**If fails:**

- Check power connections
- Verify polarity
- Inspect for shorts

#### Test 2: LCD Display Test

**Test procedure:**

1. LCD should show: "Moist.=X% Res=X% Tnk=X%"
2. Values should update every second
3. Adjust potentiometer for best contrast

**If fails:**

- Check all 16 LCD connections
- Verify 4-bit mode connections (D4-D7)
- Test with simple LCD sketch

#### Test 3: Sensor Reading Test

**For each sensor:**

1. Dry condition: Should read low percentage (~0-20%)
2. Wet condition: Should read high percentage (~80-100%)
3. Values should change smoothly, not erratically

**If fails:**

- Check sensor power connections
- Verify analog pin connections (A0, A3, A5)
- Test sensor with multimeter (should vary 0-5V)
- Replace faulty sensor

#### Test 4: Valve Control Test

**Test procedure:**

1. Simulate dry soil (low moisture reading)
2. Ensure overhead tank has water (>30%)
3. Valve should activate
4. LCD should show "VALVE is ON"
5. Relay should click

**If fails:**

- Check relay control signal (Pin 12)
- Verify relay power
- Test relay with LED first
- Check code logic

#### Test 5: Pump Control Test

**Test procedure:**

1. Simulate low overhead tank (<20%)
2. Ensure reservoir has water (>30%)
3. Pump should activate
4. LCD should show "PUMP is ON"
5. Relay should click

**If fails:**

- Check relay control signal (Pin 13)
- Same debugging as valve test

#### Test 6: Alarm Test

**Test procedure:**

1. Simulate low reservoir (<30%)
2. Simulate low overhead tank (<20%)
3. Alarm should beep intermittently
4. LCD should show "Alarm is ON"
5. Pump should remain OFF (safety)

**If fails:**

- Check buzzer connections (Pin 1)
- Test buzzer directly with 5V
- Verify alarm logic in code

#### Test 7: Integration Test

**Full system test:**

1. Start with all tanks full, soil dry
2. System should irrigate soil
3. Monitor for several cycles
4. Check for:
   - Proper valve operation
   - Water flow
   - Automatic shutoff when wet
   - No leaks
   - Stable operation

---

## Deployment

### Site Preparation

#### Step 1: Choose Installation Location

**Considerations:**

- [ ] Proximity to water source
- [ ] Access to electrical power
- [ ] Protection from weather
- [ ] Easy maintenance access
- [ ] Sensor placement in soil

#### Step 2: Install Water System

**Components to install:**

1. **Reservoir/Water tank**
   - Ensure adequate capacity
   - Install water level sensor
   - Filter inlet water

2. **Overhead tank** (if using gravity feed)
   - Mount above plant level
   - Install level sensor
   - Connect pump input

3. **Water pump**
   - Submersible: Place in reservoir
   - Connect output to overhead tank
   - Ensure proper sealing

4. **Solenoid valve**
   - Install in irrigation line
   - Arrow pointing in flow direction
   - Test for leaks

5. **Distribution system**
   - Drip lines or sprinklers
   - Ensure even coverage
   - Check for blockages

#### Step 3: Install Sensors

**Soil moisture sensor:**

1. Insert into soil at root depth (5-15cm)
2. Ensure good soil contact
3. Weatherproof connections
4. Run cable to control box

**Water level sensors:**

1. Install at appropriate depths
2. Secure to tank wall/bottom
3. Weatherproof all connections
4. Calibrate for tank size

#### Step 4: Power Installation

**Safety first!**

**12V DC system (recommended):**

1. Install 12V power adapter indoors
2. Run low-voltage cable to control box
3. Use proper cable glands
4. Add fuse for overcurrent protection

**Solar option:**

1. Mount solar panel facing sun
2. Connect to charge controller
3. Connect battery
4. Add battery disconnect switch

#### Step 5: Final Assembly

1. Mount control box securely
2. Make all connections
3. Seal all cable entries
4. Label all wires
5. Add weatherproofing
6. Test all functions

### Initial Operation

**Day 1-3: Observation Period**

Monitor system continuously:

- Check valve operation
- Verify pump cycles
- Monitor soil moisture trends
- Look for leaks or issues
- Adjust thresholds if needed

**Week 1: Fine-tuning**

Adjust parameters:

- Moisture thresholds
- Watering duration
- Tank levels
- Sensor positions

---

## Maintenance

### Daily Checks (First Week)

- [ ] Verify system is running
- [ ] Check LCD display for errors
- [ ] Inspect for water leaks
- [ ] Monitor soil moisture manually

### Weekly Maintenance

- [ ] Clean sensors (gently wipe)
- [ ] Check water levels
- [ ] Inspect all connections
- [ ] Test alarm function

### Monthly Maintenance

- [ ] Deep clean all sensors
- [ ] Check pump filter
- [ ] Inspect tubing for wear
- [ ] Verify valve operation
- [ ] Check power supply
- [ ] Update threshold values if needed

### Seasonal Maintenance

- [ ] Full system inspection
- [ ] Replace worn components
- [ ] Clean entire system
- [ ] Test all sensors thoroughly
- [ ] Update firmware if available
- [ ] Check weatherproofing

### Troubleshooting Guide

**Sensor reads constant value:**

- Clean sensor surface
- Check connections
- Test with multimeter
- Replace if faulty

**Valve not opening:**

- Check relay operation
- Verify 12V supply
- Check valve for blockage
- Replace valve solenoid

**Pump not running:**

- Check relay
- Verify power supply
- Ensure pump not jammed
- Check for dry run

**LCD not displaying:**

- Adjust contrast
- Check power (5V)
- Verify connections
- Replace LCD if needed

**System acting erratically:**

- Check power supply stability
- Look for loose connections
- Inspect for water damage
- Check code logic

---

## Safety Guidelines

### Electrical Safety

⚠️ **CRITICAL SAFETY RULES:**

1. **Never mix water and electricity**
   - Keep control box dry
   - Weatherproof all outdoor connections
   - Use IP65+ rated enclosures

2. **Low voltage recommended**
   - Use 12V DC for pump/valve
   - Avoid 230V AC if possible
   - If using AC, hire qualified electrician

3. **Proper grounding**
   - Ground all metal enclosures
   - Use GFI/RCD protection
   - Never bypass safety features

4. **Power disconnection**
   - Install emergency cutoff switch
   - Disconnect before maintenance
   - Label all power sources

### Water Safety

1. **Prevent flooding:**
   - Test overflow scenarios
   - Install manual shutoff valves
   - Monitor system regularly

2. **Clean water only:**
   - Filter water inputs
   - Avoid contaminated sources
   - Clean system periodically

3. **Winterization** (cold climates):
   - Drain all water
   - Remove sensors
   - Store indoors
   - Protect from freezing

---

## Next Steps

After successful setup:

1. ✅ Monitor system for 1-2 weeks
2. ✅ Fine-tune threshold values
3. ✅ Document your specific settings
4. ✅ Consider adding features:
   - WiFi connectivity
   - Mobile app
   - Data logging
   - Multiple zones

---

**Congratulations!** Your automatic irrigation system is now ready for operation.

For support, visit: [GitHub Issues](https://github.com/adeniranprecious002-ux/automatic-irrigation-system/issues)
