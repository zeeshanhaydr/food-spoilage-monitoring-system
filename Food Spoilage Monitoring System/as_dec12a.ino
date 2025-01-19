#include "arduino_secrets.h"

#include "thingProperties.h"
#include <Arduino_MKRIoTCarrier.h> // Include the MKR IoT Carrier library
#include <WiFiNINA.h>              // For Wi-Fi connection on MKR boards
#include <ArduinoHttpClient.h>
#include <Servo.h>
//HTTP client library

#define GAS_SENSOR_PIN A0

// Wi-Fi credentials
const char* ssid = "Zeeshan";        // Wi-Fi SSID
const char* password = "lab112233";       // Wi-Fi password


const char* host = "script.google.com";
const int port = 443;
const String path = "/macros/s/AKfycbxdpYBaUe3k1QQB_AJcFbURdU91VzsQXwbV4tmQ0S2eDUYeoRBY5uEZtGy3nbumNd99/exec"; // Google Apps Script URL path

WiFiSSLClient wifiClient;
HttpClient client(wifiClient, host, port);

MKRIoTCarrier carrier; // Instance of the carrier
Servo myServo; // Servo object to control the servo motor

// Thresholds
const float TEMP_THRESHOLD = 40.0; // Temperature threshold in Â°C
const float HUMID_THRESHOLD = 50.0; // Humidity threshold in %

void setup() {
  Serial.begin(9600);
  delay(1500);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to Wi-Fi!");

  initProperties(); // Initialize Cloud properties

  if (!carrier.begin()) {
    Serial.println("Failed to initialize MKR IoT Carrier!");
    while (1);
  }
  carrier.display.setRotation(0); // Adjust screen orientation

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2); // Debug info level
  ArduinoCloud.printDebugInfo();

  while (ArduinoCloud.connected() != 1) {
    ArduinoCloud.update();
    delay(500);
  }

  Serial.println("MQ4 Gas Sensor and MKR Carrier Initialized and Connected to IoT Cloud.");

  myServo.attach(4); // Connect servo to digital pin 9
  myServo.write(0);  // Set servo to initial position
}

void loop() {
  ArduinoCloud.update();  // Update the cloud state to sync the cloud variables

  // Read sensor values
    int gasValue = analogRead(GAS_SENSOR_PIN);
    float voltage = gasValue * (3.3 / 1023.0); // Convert to voltage
    gasLevel = (voltage / 3.3) * 100;   // Gas level as a percentage

     tempLevel = carrier.Env.readTemperature(); // In Â°C
     humidityLevel = carrier.Env.readHumidity(); // In %
    
  // Determine status based on thresholds
  String status = "Normal";
  if (gasLevel > 7 || tempLevel > TEMP_THRESHOLD || humidityLevel > HUMID_THRESHOLD) {
    status = "Risk"; // Status is at 'risk' - thresholds exceeded
  }

  // Display the readings on the MKR Carrier
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(1);

  carrier.display.setCursor(30, 50);
  carrier.display.print("Gas Level: ");
  carrier.display.print(gasLevel, 1);
  carrier.display.println(" %");

  carrier.display.setCursor(30, 60);
  carrier.display.print("Humidity Level: ");
  carrier.display.print(humidityLevel, 1);
  carrier.display.println(" %");

  carrier.display.setCursor(30, 80);
  carrier.display.print("Temperature Level: ");
  carrier.display.print(tempLevel, 1);
  carrier.display.println(" C");

  // Display the status
  carrier.display.setCursor(30, 100);
  carrier.display.print("Status: ");
  carrier.display.print(status);

  // Send data to Google Sheet via HTTP POST 
  
  String payload = "temp=" + String(tempLevel) + "&humidity=" + String(humidityLevel) + "&gasLevel=" + String(gasLevel) + "&status=" + status;

  Serial.println("Starting HTTP POST request...");
  client.beginRequest();
  client.post(path);
  client.sendHeader("Content-Type", "application/x-www-form-urlencoded");
  client.sendHeader("Content-Length", payload.length());
  client.print(payload);
  client.endRequest();
  
  bool alertTriggered = false; // Flag to track if an alert is active

  if (gasLevel > 3) {
    // carrier.Buzzer.sound(1000);
    carrier.leds.fill(255, 0, 0); // Red LED for gas alert
    alertTriggered = true;       // Set alert flag
    delay(500);                  // Sound duration
    carrier.Buzzer.noSound();
  }

  if (tempLevel > TEMP_THRESHOLD || humidityLevel > HUMID_THRESHOLD) {
    carrier.Buzzer.sound(1000);
    carrier.leds.fill(255, 0, 0); // Red LED for temperature/humidity alert
    carrier.leds.show();
    alertTriggered = true;       // Set alert flag
    delay(5000);                 // Keep the alert active for 5 seconds
    carrier.Buzzer.noSound();
  }

// If thresholds exceeded, rotate servo motor
if (alertTriggered) {
  Serial.println("Rotating servo motor due to alert!");
  
  // Rotate servo to 90 degrees
  for (int angle = 0; angle <= 90; angle += 5) {
    myServo.write(angle);   // Rotate servo
    delay(50);               // Small delay to allow servo to rotate smoothly
  }
  
  delay(2000);  // Hold the servo position for 2 seconds
  
  // Return servo to 0 degrees after delay
  for (int angle = 90; angle >= 0; angle -= 5) {
    myServo.write(angle);   // Rotate servo back
    delay(50);// Small delay

  }
}

  // If no alert is triggered, ensure LEDs are turned off
  if (!alertTriggered) {
    carrier.leds.fill(0, 0, 0); // Turn off LEDs
  }

  // Update LED states
  carrier.leds.show();
  
  // Delay before next iteration
  delay(5000);
}


void onGasLevelChange()  {
  // Add your code here to act upon GasLevel change
}

void onHumidityLevelChange()  {
  // Add your code here to act upon HumidityLevel change
}

void onTempLevelChange()  {
  // Add your code here to act upon TempLevel change
}
