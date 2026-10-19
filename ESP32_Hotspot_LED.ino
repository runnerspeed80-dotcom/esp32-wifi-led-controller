
#include <WiFi.h>

// 1. PUT YOUR PHONE'S HOTSPOT DETAILS HERE
const char* ssid     = "12345678";
const char* password = "12345678";

// Configured to Pin D4 as requested
const int ledPin = 4;

WiFiServer server(80);
String header;

void setup() {
  Serial.begin(115200);
  
  // Initialize Pin D4 as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 

  Serial.print("Connecting to Hotspot: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected to phone hotspot!");
  Serial.println("Type this IP address into your phone's browser:");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  if (client) {                             
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Check if phone clicked ON or OFF
            if (header.indexOf("GET /led/on") >= 0) {
              digitalWrite(ledPin, HIGH); // Turns D4 High (On)
            } else if (header.indexOf("GET /led/off") >= 0) {
              digitalWrite(ledPin, LOW);  // Turns D4 Low (Off)
            }
            
            // Clear header immediately after checking commands to prevent memory crash
            header = ""; 

            // Simple Interface Webpage
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<style>html { font-family: Arial; text-align: center; background-color: #121212; color: white;}");
            client.println(".btn { display: inline-block; padding: 20px 40px; font-size: 24px; font-weight: bold;");
            client.println("text-decoration: none; margin: 15px; border-radius: 10px; color: white; border: none; cursor: pointer;}");
            client.println(".on-btn { background-color: #2ecc71; } .off-btn { background-color: #e74c3c; }</style></head>");
            
            client.println("<body><h1>ESP32 Hotspot Control</h1>");
            client.println("<p>Control Pin D4 LED:</p>");
            client.println("<p><a href='/led/on'><button class='btn on-btn'>TURN ON</button></a></p>");
            client.println("<p><a href='/led/off'><button class='btn off-btn'>TURN OFF</button></a></p>");
            client.println("</body></html>");
            
            client.println();
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
    client.stop();
  }
}
