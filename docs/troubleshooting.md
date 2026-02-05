# Troubleshooting Guide

## Common Issues and Solutions

### Table of Contents

- [Power Issues](#power-issues)
- [LCD Display Problems](#lcd-display-problems)
- [Sensor Issues](#sensor-issues)
- [Relay/Control Problems](#relaycontrol-problems)
- [Water System Issues](#water-system-issues)
- [Software/Code Issues](#softwarecode-issues)

---

## Power Issues

### Arduino Not Powering On

**Symptoms:**

- No LED lights on Arduino
- LCD display blank
- No response when connected

**Possible Causes & Solutions:**

1. **No power supply**
   - ✓ Check USB cable connection
   - ✓ Try different USB cable
   - ✓ Test USB port with another device
   - ✓ Check 12V adapter if using VIN pin

2. **Damaged Arduino**
   - ✓ Look for physical damage
   - ✓ Check for burning smell
   - ✓ Test with multimeter: 5V pin should show ~5V
   - ✓ Try resetting Arduino (reset button)

3. **Short circuit**
   - ✓ Disconnect all components
   - ✓ Power on Arduino alone
   - ✓ Add components one by one to find culprit

### Power LED On, But Nothing Else Works

**Solutions:**

- Upload simple "Blink" sketch to test
- Check if bootloader is intact
- Verify TX/RX LEDs flash during upload
- Try different Arduino board

### System Resets Randomly

**Possible Causes:**

1. **Insufficient power**
   - Use adequate power supply (2A minimum)
   - Add capacitors across power rails (100µF)
   - Check voltage drop under load

2. **Brown-out reset**
   - Monitor 5V rail with multimeter
   - Should stay between 4.5V - 5.5V
   - Add voltage regulator if using VIN

3. **EMI interference**
   - Add decoupling capacitors (0.1µF near ICs)
   - Separate high-current lines from logic lines
   - Shield sensitive cables

---

## LCD Display Problems

### LCD Shows Nothing (Blank Screen)

**Step-by-step diagnosis:**

1. **Check power**

   ```
   Measure voltage:
   - Pin 2 (VDD): Should be ~5V
   - Pin 1 (VSS): Should be 0V (GND)
   ```

2. **Adjust contrast**
   - Rotate 10kΩ potentiometer fully
   - You should see contrast change
   - If no change, check potentiometer connection

3. **Verify connections**

   ```
   Critical pins:
   - RS → Pin 11
   - E  → Pin 10
   - D4-D7 → Pins 8,7,6,5
   - RW → GND
   ```

4. **Test with simple sketch**
   Upload basic "Hello World" LCD example

### LCD Shows Squares/Random Characters

**Causes:**

- Contrast set too high/low → Adjust potentiometer
- Poor connections → Check jumper wires
- Initialization error → Add delay in setup()
- Wrong pin configuration → Verify code matches wiring

**Solutions:**

```cpp
// Add this in setup() before lcd.begin():
delay(100);  // Wait for LCD to power up
lcd.begin(16, 2);
lcd.clear();
delay(100);
```

### LCD Backlight Not Working

**Check:**

- Pin 15 (A) connected to 5V via 220Ω resistor
- Pin 16 (K) connected to GND
- Resistor not too high (use 220Ω max)
- LED backlight not burned out

### LCD Shows Garbage or Flickering

**Causes:**

- Loose connections → Secure all wires
- Interference → Keep LCD cables short
- Insufficient power → Check 5V supply
- Timing issues → Add delays in code

---

## Sensor Issues

### Sensor Reads Constant Value (No Change)

**Diagnosis:**

1. **Check power**
   - Measure VCC: Should be ~5V
   - Measure GND: Should be 0V

2. **Check output**
   - Measure sensor output with multimeter
   - Should vary between 0-5V
   - Try wetting/drying sensor

3. **Verify analog pin**

   ```cpp
   // Test analog reading:
   int value = analogRead(A3);
   Serial.println(value);  // Should change when wet/dry
   ```

4. **Test sensor directly**
   - Connect sensor to 5V and GND
   - Measure output with multimeter
   - Should see voltage change

**Solutions:**

- Replace faulty sensor
- Clean sensor probes (corrosion)
- Check wiring to correct analog pin
- Verify sensor is genuine (not counterfeit)

### Sensor Reads Maximum (1023) Always

**Causes:**

- Sensor disconnected
- Analog pin not connected
- Sensor dead (open circuit)

**Fix:**

- Check all three connections (VCC, GND, OUT)
- Verify correct analog pin (A0, A3, or A5)
- Replace sensor

### Sensor Reads Minimum (0) Always

**Causes:**

- Output shorted to ground
- Sensor damaged
- Wrong wiring

**Fix:**

- Check for short circuits
- Verify wiring diagram
- Test sensor independently

### Erratic/Unstable Readings

**Causes:**

- Poor electrical contact
- EMI interference
- Faulty sensor

**Solutions:**

1. **Software filtering:**

   ```cpp
   // Add averaging:
   float getAverageMoisture() {
     long sum = 0;
     for (int i = 0; i < 10; i++) {
       sum += analogRead(moisturePin);
       delay(10);
     }
     return sum / 10.0;
   }
   ```

2. **Hardware fixes:**
   - Add 0.1µF capacitor across sensor VCC/GND
   - Use shielded cable for long runs
   - Keep sensor cables away from power lines

### Sensor Corroding Quickly

**Prevention:**

- Use capacitive sensors (longer lifespan)
- Only power sensor when reading
- Coat probes with protective lacquer
- Use stainless steel or gold-plated sensors

---

## Relay/Control Problems

### Relay Not Clicking

**Check:**

1. **Control signal**

   ```
   Measure Arduino pin (12 or 13):
   - Should be 5V when active
   - Should be 0V when inactive
   ```

2. **Relay module power**
   - Verify VCC = 5V
   - Check GND connection
   - Measure current draw (should be 15-20mA per relay)

3. **Test relay module**
   - Disconnect from Arduino
   - Apply 5V directly to IN pin
   - Should click and LED illuminate

**Solutions:**

- Replace relay module if defective
- Check control pin configuration in code
- Verify relay trigger mode (active HIGH/LOW)

### Relay Clicks But Load Doesn't Activate

**Diagnosis:**

1. **Check relay contacts**

   ```
   With relay OFF:
   - COM to NO: Should be open (infinite resistance)
   - COM to NC: Should be closed (near zero resistance)
   
   With relay ON:
   - COM to NO: Should be closed
   - COM to NC: Should be open
   ```

2. **Verify load wiring**
   - COM to power supply (+)
   - NO to pump/valve (+)
   - Load (-) to power supply (-)

3. **Check load power**
   - Measure voltage at relay output
   - Should be 12V when relay ON
   - Test pump/valve with direct 12V connection

**Solutions:**

- Rewire relay terminals correctly
- Replace blown relay contacts
- Check load for internal damage

### Relay Stays On Constantly

**Causes:**

- Pin stuck HIGH in code
- Relay module damaged
- Wrong trigger logic

**Solutions:**

```cpp
// Add explicit OFF states:
void setup() {
  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW);  // Ensure OFF
}

// Check logic:
if (condition) {
  digitalWrite(PUMP, HIGH);
} else {
  digitalWrite(PUMP, LOW);  // Explicit OFF
}
```

---

## Water System Issues

### Pump Not Running

**Step-by-step check:**

1. **Test pump directly**
   - Connect pump to 12V directly
   - Should run smoothly
   - Listen for unusual sounds

2. **Check relay**
   - Verify relay clicks
   - Measure voltage at relay output (should be 12V)

3. **Check connections**
   - Ensure proper polarity
   - Look for loose wires
   - Verify power supply capacity

4. **Check for blockage**
   - Remove pump from water
   - Check inlet filter
   - Spin impeller manually

**Solutions:**

- Replace clogged filter
- Clean pump impeller
- Verify 12V power supply provides enough current
- Replace pump if motor burned out

### Valve Not Opening

**Diagnosis:**

1. **Measure voltage**
   - Should be 12V across valve when activated
   - Check with multimeter

2. **Test valve manually**
   - Remove valve from system
   - Apply 12V directly
   - Should hear clicking and feel vibration

3. **Check pressure**
   - Solenoid valves need minimum pressure (~0.02 MPa)
   - May not work without water pressure

**Solutions:**

- Ensure adequate water pressure
- Check valve direction (arrow on body)
- Clean valve if clogged
- Replace if solenoid coil burned out

### Water Leaks

**Common leak points:**

- Tubing connections
- Valve seals
- Pump seals
- Sensor mounting points

**Solutions:**

- Use proper hose clamps
- Apply thread seal tape (PTFE)
- Replace worn O-rings
- Tighten connections (don't over-tighten)

### Insufficient Water Flow

**Causes:**

- Clogged filter
- Air in system
- Undersized tubing
- Weak pump

**Solutions:**

- Clean/replace filters
- Bleed air from system
- Use larger diameter tubing
- Upgrade pump if necessary

---

## Software/Code Issues

### Upload Failed

**Error messages and fixes:**

1. **"Port not found"**
   - Check USB connection
   - Select correct COM port (Tools → Port)
   - Install USB drivers

2. **"Not in sync"**
   - Press reset button before upload
   - Try uploading while holding reset
   - Disconnect all pins from 0 and 1

3. **"Programmer not responding"**
   - Check USB cable (try different one)
   - Verify board selection (Tools → Board → Arduino Uno)
   - Bootloader may be corrupted (need to re-flash)

### Code Compiles But Doesn't Work

**Debugging steps:**

1. **Add serial debugging:**

   ```cpp
   void setup() {
     Serial.begin(9600);
     Serial.println("System starting...");
   }
   
   void loop() {
     Serial.print("Moisture: ");
     Serial.println(moistureLevel);
     // ... rest of code
   }
   ```

2. **Check variable types:**
   - Ensure `float` for decimal calculations
   - Watch for integer division errors

3. **Verify pin numbers:**
   - Double-check all pin assignments
   - Match code to physical wiring

4. **Test step-by-step:**
   - Comment out code sections
   - Test each function individually
   - Add delay() to slow down execution

### LCD Not Updating

**Common issues:**

1. **Missing lcd.clear()**

   ```cpp
   lcd.clear();  // Add before updating display
   lcd.setCursor(0, 0);
   lcd.print("New data");
   ```

2. **Too fast updates**

   ```cpp
   delay(1000);  // Add delay between updates
   ```

3. **Text overlap**

   ```cpp
   lcd.print("       ");  // Clear with spaces first
   lcd.setCursor(0, 0);
   lcd.print("Value");
   ```

### System Behavior Incorrect

**Logic issues:**

1. **Check thresholds**
   - Verify threshold values match your sensors
   - Print values to serial monitor
   - Adjust as needed

2. **Verify conditions**

   ```cpp
   // Add debug output:
   Serial.print("Moisture: ");
   Serial.print(moistureLevel);
   Serial.print(" | Threshold: ");
   Serial.println(DRY_SOIL_THRESHOLD);
   
   if (moistureLevel <= DRY_SOIL_THRESHOLD) {
     Serial.println("Should activate valve");
     digitalWrite(VALVE, HIGH);
   }
   ```

3. **Check for conflicts**
   - Ensure conditions don't conflict
   - Verify state machine logic
   - Add proper else statements

---

## Advanced Troubleshooting

### Using Serial Monitor for Debugging

```cpp
void loop() {
  // Read sensors
  float moisture = analogRead(moisturePin);
  
  // Debug output
  Serial.print("Raw: ");
  Serial.print(moisture);
  Serial.print(" | Percent: ");
  Serial.print(moistureLevel);
  Serial.print(" | Valve: ");
  Serial.println(digitalRead(VALVE) ? "ON" : "OFF");
  
  delay(500);
}
```

### Using Multimeter

**Voltage checks:**

```
5V rail: Should be 4.75V - 5.25V
Sensor output: 0V - 5V (variable)
Relay output: 0V or 12V (depending on state)
Pin states: 0V or 5V
```

**Continuity checks:**

- GND connections: Should beep
- Power connections: Verify no shorts
- Signal traces: Check for breaks

### Component Replacement Order

If multiple components fail:

1. Replace cheapest first (jumper wires)
2. Then sensors (~$2-5 each)
3. Then relay module (~$3-5)
4. Then LCD (~$5)
5. Last: Arduino (~$20)

---

## Prevention Tips

### Regular Maintenance

- Clean sensors monthly
- Check connections quarterly
- Replace sensors yearly
- Update firmware as needed

### Best Practices

- Use quality components
- Proper weatherproofing
- Adequate power supply
- Good wiring practices
- Regular system checks

### Documentation

- Keep wiring diagrams
- Note calibration values
- Log any modifications
- Record issues and fixes

---

## Getting Help

### Before Asking for Help

1. Check this troubleshooting guide
2. Review circuit diagram
3. Verify all connections
4. Test with multimeter
5. Try simple test sketches

### When Asking for Help

Include:

- Detailed problem description
- What you've already tried
- Error messages (exact text)
- Photos of your setup
- Serial monitor output
- Code (if modified)

### Where to Get Help

- [GitHub Issues](https://github.com/yourusername/automatic-irrigation-system/issues)
- Arduino Forums
- Stack Overflow (tag: arduino)
- Reddit: r/arduino
- Local maker spaces

---

## Emergency Procedures

### Water Emergency

1. Cut power immediately
2. Close manual shutoff valve
3. Disconnect system
4. Dry all components
5. Inspect for damage before restarting

### Fire/Smoke

1. Disconnect power immediately
2. Use appropriate fire extinguisher (Class C)
3. Never use water on electrical fire
4. Ensure area is safe
5. Replace damaged components

### Electrical Shock

1. Don't touch person if still in contact
2. Cut power first
3. Call emergency services
4. Seek medical attention

---

**Safety First:** When in doubt, seek help from qualified professionals, especially for high-voltage installations.
