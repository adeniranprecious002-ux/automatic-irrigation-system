/*
 * Automatic Irrigation System
 * 
 * Description:
 * An Arduino-based irrigation control system that monitors soil moisture
 * and water levels to automatically control irrigation valves and pumps.
 * 
 * Features:
 * - Monitors soil moisture, reservoir, and overhead tank levels
 * - Automatic valve control for irrigation
 * - Automatic pump control for water circulation
 * - LCD display for real-time status
 * - Low water alarm system
 * 
 * Hardware:
 * - Arduino Uno (ATmega328P)
 * - 3x Analog Moisture Sensors
 * - 16x2 LCD Display
 * - 2-Channel Relay Module
 * - Water Pump (12V)
 * - Solenoid Valve (12V)
 * - Buzzer/Alarm
 * 
 * Author: Onuche Carney Enyo-Ojo
 * University: University of Abuja
 * Department: Electrical/Electronics Engineering
 * Date: January 2024
 * 
 * License: MIT
 */

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// ==================== PIN DEFINITIONS ====================

// LCD Connections (RS, E, D4, D5, D6, D7)
// RW and D0-D3 connected to GND
LiquidCrystal lcd(11, 10, 8, 7, 6, 5);

// Output Control Pins
const int PUMP = 13;    // Water pump control (via relay)
const int VALVE = 12;   // Irrigation valve control (via relay)
int alarm = 1;          // Low water alarm

// Analog Sensor Input Pins
const int reserviorPin = A0;   // Reservoir water level sensor
const int moisturePin = A3;    // Soil moisture sensor
const int overheadPin = A5;    // Overhead tank level sensor

// ==================== CONFIGURATION ====================

// Moisture thresholds (adjustable based on soil type)
const int DRY_SOIL_THRESHOLD = 20;      // Below this: activate valve
const int WET_SOIL_THRESHOLD = 100;     // Above this: deactivate valve

// Water level thresholds
const int LOW_OVERHEAD_THRESHOLD = 20;   // Below this: activate pump
const int FULL_OVERHEAD_THRESHOLD = 100; // Above this: deactivate pump
const int LOW_RESERVOIR_THRESHOLD = 30;  // Below this: activate alarm
const int SAFE_RESERVOIR_THRESHOLD = 50; // Above this: deactivate alarm

// Display update interval (milliseconds)
const int DISPLAY_DELAY = 1000;

// ==================== SETUP ====================

void setup() {
  // Initialize output pins
  pinMode(alarm, OUTPUT);
  pinMode(VALVE, OUTPUT);
  pinMode(PUMP, OUTPUT);
  
  // Set all outputs to LOW (off) initially
  digitalWrite(alarm, LOW);
  digitalWrite(VALVE, LOW);
  digitalWrite(PUMP, LOW);
  
  // Initialize LCD display
  lcd.begin(16, 2);      // 16x2 LCD type
  lcd.clear();           // Clear all LCD content
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Auto Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();
  
  // Optional: Initialize serial communication for debugging
  // Serial.begin(9600);
  // Serial.println("Automatic Irrigation System Initialized");
}

// ==================== MAIN LOOP ====================

void loop() {
  // Read analog sensor values (0-1023)
  float moisture = analogRead(moisturePin);
  float overhead = analogRead(overheadPin);
  float reservior = analogRead(reserviorPin);
  
  // Convert to percentage (0-300% scale as per original design)
  // Note: Scale can be adjusted based on sensor calibration
  float moistureLevel = (300 * moisture) / 1024;
  float overheadLevel = (300 * overhead) / 1024;
  float reserviorLevel = (300 * reservior) / 1024;
  
  // ==================== DISPLAY STATUS ====================
  
  // Clear display and show current readings
  lcd.clear();
  
  // Line 1: Soil moisture
  lcd.setCursor(0, 0);
  lcd.print("Moist.=");
  lcd.print(moistureLevel, 0);  // Display without decimal places
  lcd.print("% ");
  
  // Line 2: Reservoir and overhead tank levels
  lcd.setCursor(0, 1);
  lcd.print("Res=");
  lcd.print(reserviorLevel, 0);
  lcd.print("% ");
  lcd.print("Tnk=");
  lcd.print(overheadLevel, 0);
  lcd.print("% ");
  
  delay(DISPLAY_DELAY);
  
  // ==================== IRRIGATION CONTROL ====================
  
  // Condition 1: Low soil moisture AND adequate overhead tank water
  // Action: Open valve to irrigate the soil
  if (moistureLevel <= DRY_SOIL_THRESHOLD && overheadLevel >= 30) {
    digitalWrite(VALVE, HIGH);  // Open valve
    delay(10);
    
    // Display irrigation status
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Low Moisture");
    lcd.setCursor(0, 1);
    lcd.print("VALVE is ON");
    delay(DISPLAY_DELAY);
  }
  
  // Condition 2: Soil is sufficiently wet
  // Action: Close valve to stop irrigation
  if (moistureLevel >= WET_SOIL_THRESHOLD) {
    digitalWrite(VALVE, LOW);   // Close valve
    delay(50);
  }
  
  // ==================== WATER CIRCULATION CONTROL ====================
  
  // Condition 3: Adequate reservoir AND low overhead tank
  // Action: Activate pump to fill overhead tank
  if (reserviorLevel >= 30 && overheadLevel <= LOW_OVERHEAD_THRESHOLD) {
    digitalWrite(PUMP, HIGH);   // Turn on pump
    delay(10);
    
    // Display pump status
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Low Overhead");
    lcd.setCursor(0, 1);
    lcd.print("PUMP is ON");
    delay(DISPLAY_DELAY);
  }
  
  // ==================== LOW WATER ALARM ====================
  
  // Condition 4: Low reservoir AND low overhead tank
  // Action: Activate alarm, keep pump off (safety)
  if (reserviorLevel <= LOW_RESERVOIR_THRESHOLD && overheadLevel <= LOW_OVERHEAD_THRESHOLD) {
    digitalWrite(PUMP, LOW);    // Ensure pump is off
    digitalWrite(alarm, HIGH);  // Activate alarm
    delay(10);
    
    // Display alarm status
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Low Reservior");
    lcd.setCursor(0, 1);
    lcd.print("Alarm is ON");
    delay(500);
    
    // Create beeping pattern
    digitalWrite(alarm, LOW);
    delay(500);
  }
  
  // ==================== AUTOMATIC SHUTOFF ====================
  
  // Condition 5: Overhead tank is full
  // Action: Turn off pump
  if (overheadLevel >= FULL_OVERHEAD_THRESHOLD) {
    digitalWrite(PUMP, LOW);
    delay(50);
  }
  
  // Condition 6: Reservoir refilled to safe level
  // Action: Deactivate alarm
  if (reserviorLevel >= SAFE_RESERVOIR_THRESHOLD) {
    digitalWrite(alarm, LOW);
    delay(50);
  }
}

// ==================== HELPER FUNCTIONS ====================
// (Can be added for future enhancements)

/*
 * Future enhancements could include:
 * - void calibrateSensors() - Calibrate sensor readings
 * - void logData() - Log data to SD card or cloud
 * - void checkWiFi() - Monitor WiFi connection status
 * - float getAverageReading(int pin) - Get averaged sensor reading
 * - void displayError(String message) - Show error messages
 */
