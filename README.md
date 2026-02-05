# Automatic Irrigation System

An Arduino-based automatic irrigation system that monitors soil moisture levels and controls water supply to optimize plant growth while conserving water resources.

![Project Status](https://img.shields.io/badge/status-completed-success)
![License](https://img.shields.io/badge/license-MIT-blue)
![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=Arduino&logoColor=white)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Components](#system-components)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Configuration](#configuration)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## 🌱 Overview

This project implements an automated irrigation control system designed to address inefficient manual watering practices in agriculture. The system uses soil moisture sensors to monitor moisture levels and automatically controls water pumps and valves to maintain optimal soil conditions for plant growth.

### Key Benefits

- **Water Conservation**: Prevents over-watering and optimizes water usage
- **Labor Reduction**: Eliminates manual watering tasks
- **Improved Crop Yield**: Maintains consistent optimal moisture levels
- **Cost Efficiency**: Reduces water waste and labor costs
- **Real-time Monitoring**: LCD display shows system status and moisture levels

## ✨ Features

- **Automatic Moisture Detection**: Three moisture sensors monitor soil, reservoir, and overhead tank levels
- **Smart Water Control**: Automated valve and pump control based on moisture thresholds
- **Visual Feedback**: 16x2 LCD display shows real-time moisture percentages
- **Low Water Alert**: Alarm system warns when reservoir water is low
- **Multi-level Monitoring**:
  - Soil moisture monitoring
  - Reservoir water level
  - Overhead tank water level
- **Energy Efficient**: Optimized power consumption with relay-based control
- **Scalable Design**: Can be expanded for larger agricultural applications

## 🔧 System Components

### Hardware

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| Arduino Uno | ATmega328P | 1 | Main controller |
| Soil Moisture Sensors | Analog | 3 | Moisture detection |
| Water Pump | 12V DC | 1 | Water circulation |
| Solenoid Valve | 12V | 1 | Water flow control |
| Relay Module | 5V, 2-Channel | 1 | Switching control |
| LCD Display | 16x2 with I2C | 1 | Status display |
| Transistor | NPN (BC547) | 2 | Switching |
| Diode | 1N4007 | 2 | Back EMF protection |
| Resistors | Various values | Multiple | Current limiting |
| Potentiometer | 10kΩ | 1 | LCD contrast |
| Capacitors | Ceramic & Electrolytic | Multiple | Filtering |
| LED Indicators | 5mm | 3 | Visual status |
| Buzzer/Alarm | 5V | 1 | Low water alert |
| Power Supply | 12V/5V | 1 | System power |
| Jumper Wires | Male-to-Male/Female | Multiple | Connections |

### Software

- **Programming Language**: Arduino C/C++
- **IDE**: Arduino IDE 1.8.x or higher
- **Libraries**:
  - LiquidCrystal.h (LCD control)
  - SoftwareSerial.h (Serial communication)

## 📐 Circuit Diagram

The system uses the following connections:

### Arduino Pin Configuration

```
LCD Connections:
- RS → Pin 11
- E  → Pin 10
- D4 → Pin 8
- D5 → Pin 7
- D6 → Pin 6
- D7 → Pin 5

Control Outputs:
- Water Pump  → Pin 13 (via Relay)
- Valve       → Pin 12 (via Relay)
- Alarm       → Pin 1

Sensor Inputs:
- Reservoir Sensor → A0
- Soil Moisture    → A3
- Overhead Tank    → A5
```

See the [Circuit Diagram](docs/circuit-diagram.md) for detailed schematics.

## 🚀 Installation

### Prerequisites

1. Arduino IDE installed on your computer
2. USB cable for Arduino programming
3. All hardware components listed above

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/automatic-irrigation-system.git
   cd automatic-irrigation-system
   ```

2. **Open the Arduino sketch**
   ```bash
   # Open Arduino IDE and load the sketch
   arduino-ide src/irrigation_system/irrigation_system.ino
   ```

3. **Install required libraries**
   - In Arduino IDE: Sketch → Include Library → Manage Libraries
   - Search and install: `LiquidCrystal`

4. **Connect your Arduino**
   - Connect Arduino Uno to your computer via USB
   - Select the correct board: Tools → Board → Arduino Uno
   - Select the correct port: Tools → Port → (your Arduino port)

5. **Upload the code**
   - Click the Upload button (→) in Arduino IDE
   - Wait for "Done uploading" message

6. **Assemble the hardware**
   - Follow the circuit diagram in `/docs/circuit-diagram.md`
   - Double-check all connections before powering on

## 💻 Usage

### First Time Setup

1. **Power on the system** with all sensors disconnected
2. **Verify LCD display** shows initialization message
3. **Connect sensors one by one** and verify readings on LCD
4. **Calibrate moisture thresholds** (default values in code):
   - Dry soil: < 20%
   - Optimal soil: 20-100%
   - Low overhead tank: < 20%
   - Low reservoir: < 30%

### Normal Operation

The system operates automatically:

1. **Monitoring Phase**: Continuously reads sensor values
2. **Decision Phase**: Compares readings with thresholds
3. **Action Phase**: Controls pump/valve based on conditions
4. **Display Phase**: Updates LCD with current status

### LCD Display Format

```
Line 1: Moist.=XX%
Line 2: Res=XX% Tnk=XX%
```

### System States

| Condition | Valve | Pump | Alarm | Display Message |
|-----------|-------|------|-------|-----------------|
| Low soil moisture & adequate overhead | ON | OFF | OFF | "Low Moisture" / "VALVE is ON" |
| Adequate reservoir & low overhead | OFF | ON | OFF | "Low Overhead" / "PUMP is ON" |
| Low reservoir & low overhead | OFF | OFF | ON | "Low Reservior" / "Alarm is ON" |
| All levels optimal | OFF | OFF | OFF | Normal readings |

## ⚙️ How It Works

### System Logic Flow

```
┌─────────────────────────────────────────┐
│         Read All Sensor Values          │
│  - Soil Moisture (A3)                   │
│  - Reservoir Level (A0)                 │
│  - Overhead Tank (A5)                   │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│     Convert to Percentage (0-300%)      │
│   moistureLevel = (300 × reading)/1024  │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│        Display on LCD Screen            │
│    "Moist.=XX% Res=XX% Tnk=XX%"        │
└──────────────┬──────────────────────────┘
               │
               ▼
┌─────────────────────────────────────────┐
│         Check Conditions                │
└──────────────┬──────────────────────────┘
               │
     ┌─────────┴─────────┐
     ▼                   ▼
┌─────────┐         ┌─────────┐
│ Valve   │         │  Pump   │
│ Control │         │ Control │
└─────────┘         └─────────┘
```

### Detailed Operation

1. **Soil Moisture Control**:
   - If moisture ≤ 20% AND overhead tank ≥ 30%:
     - Valve opens to irrigate soil
   - If moisture ≥ 100%:
     - Valve closes

2. **Water Circulation**:
   - If reservoir ≥ 30% AND overhead ≤ 20%:
     - Pump activates to fill overhead tank
   - If overhead ≥ 100%:
     - Pump deactivates

3. **Low Water Warning**:
   - If reservoir ≤ 30% AND overhead ≤ 20%:
     - Alarm activates (beeping pattern)
     - Pump remains off
   - If reservoir ≥ 50%:
     - Alarm deactivates

## 🔧 Configuration

### Adjusting Moisture Thresholds

Edit these values in the code (`src/irrigation_system/irrigation_system.ino`):

```cpp
// Soil moisture thresholds
#define DRY_SOIL_THRESHOLD 20      // Activate valve below this
#define WET_SOIL_THRESHOLD 100     // Deactivate valve above this

// Water level thresholds
#define LOW_OVERHEAD_THRESHOLD 20   // Activate pump below this
#define FULL_OVERHEAD_THRESHOLD 100 // Deactivate pump above this
#define LOW_RESERVOIR_THRESHOLD 30  // Activate alarm below this
#define SAFE_RESERVOIR_THRESHOLD 50 // Deactivate alarm above this
```

### Calibrating Sensors

1. Insert sensor in completely dry soil → note reading
2. Insert sensor in saturated soil → note reading
3. Adjust the conversion formula:
   ```cpp
   float moistureLevel = map(moisture, DRY_READING, WET_READING, 0, 100);
   ```

## 📁 Project Structure

```
automatic-irrigation-system/
│
├── README.md                 # This file
├── LICENSE                   # MIT License
├── .gitignore               # Git ignore rules
│
├── src/                     # Source code
│   └── irrigation_system/
│       └── irrigation_system.ino  # Main Arduino sketch
│
├── docs/                    # Documentation
│   ├── circuit-diagram.md   # Detailed circuit diagrams
│   ├── component-specs.md   # Component specifications
│   ├── setup-guide.md       # Detailed setup instructions
│   ├── troubleshooting.md   # Common issues and solutions
│   └── theory.md            # Theoretical background
│
├── hardware/                # Hardware design files
│   ├── pcb/                # PCB design (if available)
│   ├── schematics/         # Circuit schematics
│   └── 3d-models/          # 3D printable enclosure (optional)
│
├── images/                  # Project images
│   ├── system-overview.jpg
│   ├── circuit-board.jpg
│   └── lcd-display.jpg
│
├── research/               # Research documentation
│   └── project-report.pdf  # Original project report
│
└── examples/               # Additional examples
    └── sensor-test/        # Sensor testing sketches
        └── sensor_test.ino
```

## 🧪 Testing

### Component Testing

Before full system integration, test each component:

#### 1. LCD Display Test
```cpp
// Upload the test sketch from examples/lcd-test/
// Verify all characters display correctly
```

#### 2. Sensor Test
```cpp
// Upload examples/sensor-test/sensor_test.ino
// Monitor serial output for sensor readings
```

#### 3. Relay Test
```cpp
// Manually trigger relays
// Listen for clicking sound
// Verify pump/valve activation
```

### System Integration Test

1. **Dry Soil Test**: Use dry soil/sensor reading
   - Expected: Valve activates, LCD shows "Low Moisture"

2. **Wet Soil Test**: Immerse sensor in water
   - Expected: Valve deactivates

3. **Empty Tank Test**: Simulate low overhead tank
   - Expected: Pump activates, LCD shows "Low Overhead"

4. **Empty Reservoir Test**: Simulate low reservoir
   - Expected: Alarm activates, LCD shows "Low Reservior"

## 🚀 Future Enhancements

### Planned Features

- [ ] **IoT Integration**: WiFi module for remote monitoring
- [ ] **Mobile App**: Android/iOS app for system control
- [ ] **Weather Integration**: Adjust watering based on weather forecast
- [ ] **Multi-zone Support**: Control multiple irrigation zones
- [ ] **Data Logging**: SD card storage for historical data
- [ ] **Solar Power**: Solar panel power option
- [ ] **Advanced Sensors**: 
  - Temperature and humidity sensors
  - pH and EC sensors for soil quality
- [ ] **Machine Learning**: Predictive irrigation scheduling
- [ ] **Cloud Dashboard**: Web-based monitoring and analytics

### Potential Improvements

- Replace analog sensors with digital I2C sensors for better accuracy
- Add RTC module for scheduled irrigation times
- Implement PID control for precise moisture management
- Add water flow meter for consumption tracking
- Design custom PCB for more compact assembly

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please ensure:
- Code follows Arduino style guidelines
- Comments explain complex logic
- Testing has been performed
- Documentation is updated

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **Original Project**: Designed and implemented as a final year project at the University of Abuja
- **Supervisor**: Engr. Dr. I. Bebeji, for guidance and supervision
- **Department**: Electrical/Electronics Engineering, University of Abuja
- **Arduino Community**: For excellent libraries and support
- **Open Source Contributors**: For inspiration and code examples

## 📞 Contact & Support

- **Issues**: Please use the [GitHub Issues](https://github.com/yourusername/automatic-irrigation-system/issues) page
- **Discussions**: Join our [Discussions](https://github.com/yourusername/automatic-irrigation-system/discussions) for questions and ideas

## 📊 Project Statistics

- **Development Time**: Academic year 2023-2024
- **Programming Language**: Arduino C/C++
- **Total Components**: 20+
- **Code Lines**: ~100 lines
- **Sensors**: 3 analog moisture sensors
- **Power Consumption**: < 5W (idle), ~15W (active)

## Star ⭐ this repository if you find it helpful!

---

**Note**: This is an educational project. For commercial agricultural applications, consult with agricultural engineers and comply with local regulations.
