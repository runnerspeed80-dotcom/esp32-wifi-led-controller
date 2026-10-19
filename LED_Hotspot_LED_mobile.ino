
#include <WiFi.h>

// 1. CHOOSE YOUR PHONE HOTSPOT DETAILS HERE
const char* ssid     = "12345678";
const char* password = "12345678";

const int ledPin = 4;

WiFiServer server(80);
String header;

void setup() {
  Serial.begin(115200);
  
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
  Serial.println("Connected successfully!");
  Serial.print("IP Address: ");
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
            
            // Check web buttons
            if (header.indexOf("GET /led/on") >= 0) {
              digitalWrite(ledPin, HIGH); 
            } else if (header.indexOf("GET /led/off") >= 0) {
              digitalWrite(ledPin, LOW);  
            }
            
            // Send response header using write instead of print
            const char* responseHeader = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\nConnection: close\r\n\r\n";
            client.write((const uint8_t*)responseHeader, strlen(responseHeader));
            
            // Single plain string for the webpage layout
            String htmlPage = "<!DOCTYPE html><html>"
                              "<head><meta name='viewport' content='width=device-width, initial-scale=1'>"
                              "<style>html { font-family: Arial; text-align: center; background-color: #121212; color: white;}"
                              ".btn { display: inline-block; padding: 25px 50px; font-size: 26px; font-weight: bold;"
                              "text-decoration: none; margin: 20px; border-radius: 12px; color: white; border: none; cursor: pointer;}"
                              ".on-btn { background-color: #2ecc71; } .off-btn { background-color: #e74c3c; }</style></head>"
                              "<body><h1>ESP32 Phone Switch</h1>"
                              "<p>Tap a button to toggle your LED:</p>"
                              "<p><a href='/led/on'><button class='btn on-btn'>TURN ON</button></a></p>"
                              "<p><a href='/led/off'><button class='btn off-btn'>TURN OFF</button></a></p>"
                              "</body></html>\r\n";
                              
            // Send the page using a direct byte buffer write
            client.write((const uint8_t*)htmlPage.c_str(), htmlPage.length());
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
  }
}
