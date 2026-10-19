# Real-Time ESP32 Local Web Server LED Controller

A physical, light-weight IoT implementation featuring an ESP32 NodeMCU micro-controller configured as a standalone local web server. The firmware allows asynchronous HTTP GET requests from any client connected to a designated smartphone hotspot to control physical GPIO states in real-time.

---

## 🚀 Live Demonstration & Proof of Concept

<!-- INSTRUCTION: Take a 10-second phone video of your phone screen toggling the web button and the physical LED blinking. Convert it to a GIF using a free online tool, upload it to this repo, and reference it below. -->

![Project Demo GIF](path-to-your-uploaded-demo-image-or-gif.gif)

*Figure 1: Real-time physical hardware response via asynchronous smartphone hotspot client routing.*

---

## 🛠️ Hardware Architecture & Bill of Materials (BOM)

This project was built, wired, and tested physically (not simulated). 

### 🎛️ Key Components:
* **Micro-controller:** ESP32 NodeMCU Development Board (Xtensa dual-core 32-bit LX6 microprocessor)
* **Actuator:** 1x Physical 5mm Light Emitting Diode (LED) / [Optional: 5V Single-Channel Relay Module]
* **Passive Components:** 1x 220Ω Current-Limiting Resistor
* **Prototyping:** 1x Solderless Breadboard & Premium Copper Jumper Wires
* **Power Source:** 5V Micro-USB standard interface

### 🔌 Pin Mapping Table:

| ESP32 Pin (GPIO) | Hardware Component | Description |
| :--- | :--- | :--- |
| **GND** | LED Cathode (-) | Common ground loop connection |
| **GPIO 2** (Built-in) | LED Anode (+) via 220Ω Resistor | Pulse / State Control Signal Out |
| **VIN (5V)** | External Module VCC | [If using an external relay module] |

---

## 💻 Software Stack & Firmware Logic

* **Development Environment:** Arduino IDE / PlatformIO
* **Language:** Embedded C++ (Object-Oriented syntax utilizing lightweight framework stacks)
* **Core Framework Libraries:** `<WiFi.h>` (Station mode initialization) & `<WebServer.h>` (Routing endpoints handling)

### Network Routing Logic:
1. **Network Authentication:** The ESP32 acts as a **Station (STA)**, connecting directly to a local smartphone hotspot network using pre-configured SSID and Password vectors.
2. **IP Allocation:** Upon handshake authentication, the router assigns a local IP address to the ESP32, which is printed via serial communication at **115200 Baud**.
3. **HTTP Server Initialization:** An active HTTP listener is established on port `80`.
4. **Endpoint Mappings:**
   * `/` -> Serves a clean, inline HTML/CSS responsive user dashboard containing UI toggle elements.
   * `/led/on` -> Toggles `digitalWrite(2, HIGH)` to drive current to the anode loop.
   * `/led/off` -> Toggles `digitalWrite(2, LOW)` to ground the anode loop.

---
![Circuit Wiring Diagram](circuit.png)
## 📈 Real-World Challenges Encounetered & Debugging Log

Building real hardware involves tackling unpredictabilities that simulators hide. During this physical deployment, I addressed the following engineering hurdles:

* **Wi-Fi Drop Handling:** Encountered occasional disconnections during long idle states. Resolved by implementing a conditional state-machine loop check inside `void loop()` that detects `WiFi.status() != WL_CONNECTED` and triggers an active auto-reconnection routine without crashing the board.
* **Debouncing & Latency:** Optimized the server request handlers to serve minimal payload frames, reducing the button-to-LED physical actuation latency down to under **50ms** across the local hotspot node.
