# ESP32 Hotspot LED Controller 🚀

A lightweight, high-performance **ESP32 Web Server** application written in C++ using the Arduino framework. This project allows you to connect your ESP32 board directly to a mobile phone hotspot and serve an interactive, modern dark-themed web interface to control structural GPIO pins (configured to Pin D4) in real-time.

---

## ✨ Features
* **Standalone Web Server:** Hosts a direct local HTTP server on port 80.
* **Responsive Dark UI:** Designed with modern CSS tailored perfectly for mobile browsers.
* **Optimized Memory Management:** Features instant header flushing to eliminate common ESP32 memory leaks during background browser refreshes.
* **PC & Mobile Flash Ready:** Fully tested and compatible with desktop Arduino IDE and mobile deployment tools like ArduinoDroid via OTG.

---

## 🛠️ Hardware Requirements
* **ESP32 Development Board** (NodeMCU-32S, ESP32 DevKit, etc.)
* **USB Data Cable** (High-quality data sync cable is highly recommended to avoid `Write timeout` errors)
* **A Smartphone** (To host the Wi-Fi hotspot and access the interface)

---

## 💻 Quick Start & Configuration

1. **Clone this repository:**
   ```bash
   git clone https://github.com
   ```

2. **Open the sketch:**
   Open the codebase in the **Arduino IDE** or **ArduinoDroid**.

3. **Configure your Network Credentials:**
   Locate lines 4 and 5 in the sketch file and replace the placeholder text with your phone's specific hotspot name and password:
   ```cpp
   const char* ssid     = "YOUR_HOTSPOT_NAME";
   const char* password = "YOUR_HOTSPOT_PASSWORD";
   ```

4. **Upload to Hardware:**
   * **PC Settings:** Set your Board to `ESP32 Dev Module`, select your active `COM Port`, lower the **Upload Speed** to `115200` for stability, and click **Upload**.
   * *Note: If the terminal halts at `Connecting...`, press and hold the physical **BOOT (IO0)** button on your ESP32 board until the progress percentage begins.*

5. **Access the Controller:**
   * Open your serial monitor at **115200 Baud**.
   * Copy the generated IP address printed by the ESP32 (e.g., `192.168.X.X`).
   * Connect your controlling phone or device to the same hotspot network, open a web browser, and type that IP address into the URL bar to launch the interface.

---

## 📸 Web Interface Preview
The hosted page serves a dark-mode control console featuring two touch-optimized buttons:
* 🟢 **TURN ON:** Sends a `GET /led/on` request to set Pin D4 `HIGH`.
* 🔴 **TURN OFF:** Sends a `GET /led/off` request to set Pin D4 `LOW`.

---

## ⚙️ How it Works under the Hood
The firmware initializes a basic `WiFiServer` listener. When an incoming browser connection hits the IP address, the ESP32 parses the incoming HTTP network headers chunk by chunk. To prevent system crashes, the system instantly processes the `GET` parameters, flushes the raw string buffer to keep RAM usage safe, and prints out standard HTML/CSS code directly down the active client data pipe.
