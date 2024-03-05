#include <WiFi.h>
#include <Servo.h>
#include <ThingSpeak.h>

const char *ssid = "YourWiFiSSID";
const char *password = "YourWiFiPassword";
const unsigned long channelID = YourChannelID;
const char *apiKey = "YourAPIKey";

Servo horizontalServo;
Servo verticalServo;

int horizontalPin = 9; // Digital pin for horizontal servo
int verticalPin = 10;  // Digital pin for vertical servo

int horizontalAngle = 90; // Initial horizontal angle
int verticalAngle = 90;   // Initial vertical angle

void setup() {
  horizontalServo.attach(horizontalPin);
  verticalServo.attach(verticalPin);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop() {
  // Read light intensity from sensor
  int lightIntensity = analogRead(A0);

  // Calculate servo angles based on light intensity
  horizontalAngle = map(lightIntensity, 0, 1023, 0, 180);
  verticalAngle = map(lightIntensity, 0, 1023, 0, 180);

  // Move servos to track the sun
  horizontalServo.write(horizontalAngle);
  verticalServo.write(verticalAngle);

  // Send data to ThingSpeak
  ThingSpeak.writeField(channelID, 1, lightIntensity, apiKey);

  delay(1000); // Delay for smoother movement and data transmission
}