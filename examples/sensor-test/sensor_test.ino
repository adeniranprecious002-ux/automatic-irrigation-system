/*
 * Sensor Test Sketch
 * 
 * This sketch is used to test and calibrate the moisture sensors
 * before deploying the full irrigation system.
 * 
 * Upload this sketch to test:
 * - Sensor connectivity
 * - Reading ranges
 * - Sensor responsiveness
 * 
 * Open Serial Monitor at 9600 baud to view readings
 */

// Sensor pins (same as main project)
const int reserviorPin = A0;
const int moisturePin = A3;
const int overheadPin = A5;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Print header
  Serial.println("===================================");
  Serial.println("  Moisture Sensor Test Program    ");
  Serial.println("===================================");
  Serial.println();
  delay(2000);
}

void loop() {
  // Read raw analog values (0-1023)
  int reserviorRaw = analogRead(reserviorPin);
  int moistureRaw = analogRead(moisturePin);
  int overheadRaw = analogRead(overheadPin);
  
  // Convert to voltage (0-5V)
  float reserviorVolt = reserviorRaw * (5.0 / 1023.0);
  float moistureVolt = moistureRaw * (5.0 / 1023.0);
  float overheadVolt = overheadRaw * (5.0 / 1023.0);
  
  // Convert to percentage (using default scale)
  float reserviorPercent = (300.0 * reserviorRaw) / 1024.0;
  float moisturePercent = (300.0 * moistureRaw) / 1024.0;
  float overheadPercent = (300.0 * overheadRaw) / 1024.0;
  
  // Display readings
  Serial.println("--------------------------------");
  Serial.print("Time: ");
  Serial.print(millis() / 1000);
  Serial.println(" seconds");
  Serial.println();
  
  // Reservoir sensor
  Serial.println("RESERVOIR SENSOR (A0):");
  Serial.print("  Raw Value: ");
  Serial.println(reserviorRaw);
  Serial.print("  Voltage: ");
  Serial.print(reserviorVolt, 2);
  Serial.println(" V");
  Serial.print("  Percentage: ");
  Serial.print(reserviorPercent, 1);
  Serial.println(" %");
  Serial.println();
  
  // Soil moisture sensor
  Serial.println("SOIL MOISTURE SENSOR (A3):");
  Serial.print("  Raw Value: ");
  Serial.println(moistureRaw);
  Serial.print("  Voltage: ");
  Serial.print(moistureVolt, 2);
  Serial.println(" V");
  Serial.print("  Percentage: ");
  Serial.print(moisturePercent, 1);
  Serial.println(" %");
  
  // Provide interpretation
  if (moisturePercent < 20) {
    Serial.println("  Status: DRY - Needs water!");
  } else if (moisturePercent < 60) {
    Serial.println("  Status: MOIST - Optimal");
  } else {
    Serial.println("  Status: WET - Too much water");
  }
  Serial.println();
  
  // Overhead tank sensor
  Serial.println("OVERHEAD TANK SENSOR (A5):");
  Serial.print("  Raw Value: ");
  Serial.println(overheadRaw);
  Serial.print("  Voltage: ");
  Serial.print(overheadVolt, 2);
  Serial.println(" V");
  Serial.print("  Percentage: ");
  Serial.print(overheadPercent, 1);
  Serial.println(" %");
  Serial.println();
  
  // Wait 2 seconds before next reading
  delay(2000);
}

/*
 * CALIBRATION INSTRUCTIONS:
 * 
 * 1. Dry Reading Test:
 *    - Remove sensor from any material
 *    - Note the "Raw Value" (should be high, ~900-1023)
 *    - This is your DRY_READING
 * 
 * 2. Wet Reading Test:
 *    - Fully submerge sensor in water
 *    - Note the "Raw Value" (should be low, ~200-400)
 *    - This is your WET_READING
 * 
 * 3. Update Main Code:
 *    Replace the conversion formula with:
 *    float moistureLevel = map(moisture, WET_READING, DRY_READING, 100, 0);
 *    
 * 4. Test Each Sensor:
 *    - Repeat for all three sensors
 *    - Each sensor may have slightly different values
 *    - Record values in a notebook
 * 
 * 5. Threshold Determination:
 *    - Test sensor in actual soil conditions
 *    - Note values at different moisture levels
 *    - Adjust DRY_SOIL_THRESHOLD and other values accordingly
 */
