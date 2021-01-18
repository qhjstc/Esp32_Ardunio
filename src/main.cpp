#include <Arduino.h>
#include <WiFi.h>
#define LED 2
const IPAddress serverIP(192,168,50,44); //Óû·ÃÎÊµÄµØÖ·
uint16_t serverPort = 8086;         //Server ip port
WiFiClient client; //Declare a client object to connect to the server

void ESP32_WiFiInit();

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.print("Hello! This is Esp32!\r\n");
    pinMode(LED, OUTPUT);
    ESP32_WiFiInit();
}

int LEDState = 0;
void loop() {
    delay(1000);
    LEDState = 1 - LEDState;
    digitalWrite(LED,LEDState); //LED power toggle
    client.write("Hello!\r\n");
}

void ESP32_WiFiInit(){
    WiFi.begin("KC114", "kc114kc114");   //the esp connects to the network as a station
    delay(1000);
    while (WiFi.status() != WL_CONNECTED)              //waiting for connection
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("The esp has connected to the network");
    WiFi.setAutoConnect(true);
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    Serial.println("Trying to connect to server");
    while(!client.connect(serverIP, serverPort)){
        Serial.println("Trying connect");
    }
    Serial.println("The esp has connect to the server");
    client.write("Hello this is esp32!\r\n");
    String WifiLine = client.readStringUntil('\n');
    Serial.print(WifiLine);
}

