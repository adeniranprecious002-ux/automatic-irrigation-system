# Hardware Design Files

This folder contains hardware design files for the Automatic Irrigation System.

## Folder Structure

```
hardware/
├── schematics/          # Circuit schematics and diagrams
├── pcb/                 # PCB design files (optional)
└── 3d-models/          # 3D printable enclosure designs (optional)
```

## Schematics

### Available Formats

Circuit schematics can be provided in multiple formats:

1. **Fritzing** (.fzz)
   - Beginner-friendly
   - Visual breadboard, schematic, and PCB views
   - Free download: <http://fritzing.org/>

2. **KiCad** (.kicad_pro, .kicad_sch, .kicad_pcb)
   - Professional-grade
   - Open-source
   - Free download: <https://www.kicad.org/>

3. **EasyEDA** (web-based)
   - Online circuit design
   - Easy sharing and collaboration
   - Access: <https://easyeda.com/>

4. **Eagle** (.sch, .brd)
   - Industry standard
   - Autodesk product
   - Free for hobbyists (limited)

5. **PDF** (.pdf)
   - Universal format
   - View and print
   - No special software required

### Creating Schematics

**For Contributors:**

If you create improved schematics:

1. Include all components with values
2. Label all connections clearly
3. Add notes for critical connections
4. Export to multiple formats:
   - Native format (KiCad, Fritzing, etc.)
   - PDF for easy viewing
   - PNG/SVG for documentation

## PCB Design (Optional)

### PCB Design Files

Custom PCB designs can be created for:

- **Single-layer PCB**: Simpler, lower cost
- **Double-layer PCB**: More routing flexibility
- **Arduino Shield**: Plugs directly onto Arduino

### PCB Specifications

**Recommended specs for manufacturing:**

- Board size: 100mm × 80mm (or smaller)
- Layers: 2 (top and bottom)
- Copper weight: 1oz
- Finish: HASL or ENIG
- Solder mask: Green (or any color)
- Silkscreen: White
- Minimum track width: 0.3mm
- Minimum spacing: 0.3mm

### PCB Manufacturers

**Popular options:**

- JLCPCB: Low cost, fast shipping
- PCBWay: Good quality, options
- OSH Park: USA-based, purple PCBs
- Seeed Studio: Fusion PCB service
- AllPCB: Competitive pricing

**Cost estimation:**

- 10 boards (100×80mm): ~$10-20 USD + shipping
- Assembly service available (extra cost)

### Design Tools

1. **KiCad** (Recommended)
   - Free, open-source
   - Full PCB design suite
   - Large component library
   - Active community

2. **EasyEDA**
   - Web-based
   - Integrated with JLCPCB
   - Large component library
   - Free for basic use

3. **Fritzing**
   - Good for beginners
   - Limited PCB features
   - Requires donation for PCB export

4. **Eagle**
   - Professional grade
   - Free for hobbyists (limited)
   - Large user base

## 3D Models

### Enclosure Design

3D printable enclosure for the system:

**Features to include:**

- Mounting for Arduino
- LCD viewing window
- Cable entry points
- Ventilation holes
- Weatherproof sealing
- Mounting brackets

**Recommended dimensions:**

- Internal: 150mm × 100mm × 75mm
- Wall thickness: 2-3mm
- Screw posts: M3 or M4

### 3D Modeling Software

1. **Fusion 360** (Recommended)
   - Powerful parametric design
   - Free for hobbyists/students
   - Easy to learn

2. **FreeCAD**
   - Open-source
   - Parametric modeling
   - Free

3. **Tinkercad**
   - Web-based
   - Very beginner-friendly
   - Free
   - Limited features

4. **OpenSCAD**
   - Code-based design
   - Great for parametric models
   - Free, open-source

### 3D Printing

**File formats:**

- STL (most common)
- OBJ (with textures)
- 3MF (newer standard)

**Print settings (PLA):**

- Layer height: 0.2mm
- Infill: 20-30%
- Supports: As needed
- Print speed: 50-60mm/s

**Materials:**

- **PLA**: Easy, indoor use
- **PETG**: Better durability, weather-resistant
- **ABS**: Strong, requires heated bed
- **TPU**: Flexible, for gaskets

### Mounting Options

**DIN Rail Mount:**

- Standard 35mm DIN rail
- Professional appearance
- Easy installation

**Wall Mount:**

- Screw holes for direct mounting
- Include template for drilling

**Pole Mount:**

- U-bolt friendly design
- For garden stakes/posts

## Bill of Materials (BOM)

### Hardware BOM Format

When creating BOMs, include:

| Item | Qty | Description | Specs | Part Number | Supplier |
|------|-----|-------------|-------|-------------|----------|
| R1 | 1 | Resistor | 220Ω 1/4W | - | Generic |
| C1 | 1 | Capacitor | 100µF 16V | - | Generic |

Export formats:

- CSV (Excel-compatible)
- XML (for automated tools)
- PDF (for documentation)

## Mechanical Parts

### Required Hardware

**Fasteners:**

- M3 screws × 10 (PCB/Arduino mounting)
- M3 nuts × 10
- M3 standoffs × 4 (height: 10mm)
- M4 screws × 4 (enclosure mounting)

**Cable Management:**

- Cable ties (zip ties) × 20
- Cable glands (PG7 or PG9) × 3
- Heat shrink tubing (assorted)
- Rubber grommets (for wire pass-through)

**Sealing:**

- Silicone sealant
- Rubber gasket (for enclosure lid)
- O-rings (for cable glands)

## Assembly Instructions

### PCB Assembly Order

1. **Lowest profile first:**
   - Resistors
   - Diodes
   - IC sockets

2. **Medium height:**
   - Capacitors (ceramic)
   - Small transistors

3. **Tallest last:**
   - Electrolytic capacitors
   - Connectors
   - Terminal blocks
   - Relays

### Soldering Tips

- Use 60/40 or 63/37 tin/lead solder
- Temperature: 350-400°C
- Clean tip frequently
- Use flux for better joints
- Check for bridges between pads
- Verify all connections with multimeter

## Testing

### PCB Testing Procedure

1. **Visual inspection:**
   - Check all solder joints
   - Look for bridges
   - Verify component orientation

2. **Continuity test:**
   - Check power traces
   - Verify no shorts to ground
   - Test all connections

3. **Power-on test:**
   - Apply power (5V/12V)
   - Check voltages at test points
   - Monitor current draw
   - Look/smell for problems

4. **Functional test:**
   - Upload test sketch
   - Verify all pins working
   - Test sensors
   - Check relay operation

## Contributing

### How to Contribute Hardware Designs

1. Fork the repository
2. Add your design files to appropriate folder
3. Include:
   - Source files (editable format)
   - Exported files (PDF, Gerber, STL)
   - BOM (Bill of Materials)
   - Assembly instructions
   - Photos of finished product
4. Update this README
5. Submit pull request

### Design Guidelines

- Use standard component footprints
- Label all connections clearly
- Include test points
- Document design decisions
- Follow good PCB design practices
- Make designs beginner-friendly

## Licensing

All hardware designs are licensed under:

- **Open Source Hardware (OSHW)**
- **MIT License** (consistent with software)

You are free to:

- Use designs commercially
- Modify and improve
- Share with others

Requirements:

- Give appropriate credit
- Indicate changes made
- Share improvements (encouraged, not required)

## Resources

### Learning Resources

**PCB Design:**

- "KiCad Like a Pro" course
- Contextual Electronics YouTube channel
- Phil's Lab (advanced PCB design)

**3D Modeling:**

- Fusion 360 tutorials (Autodesk)
- FreeCAD tutorials (MangoJelly Solutions)
- Makers Muse (3D printing)

**Electronics:**

- EEVblog (general electronics)
- GreatScott! (projects and tutorials)
- Andreas Spiess (sensors and IoT)

## Future Hardware Enhancements

Planned improvements:

- [ ] Custom PCB shield for Arduino Uno
- [ ] Compact all-in-one PCB
- [ ] Professional enclosure design
- [ ] DIN rail mounting option
- [ ] Solar charge controller PCB
- [ ] Sensor extension boards
- [ ] Multi-zone expansion boards

---

**Note**: This folder is a work in progress. Hardware design files will be added as they are created and tested.

Contributions are welcome!
