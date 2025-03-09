#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3pmeRZyuy"
#define BLYNK_TEMPLATE_NAME "Smart Home Automation"
#define BLYNK_DEVICE_NAME "My Device"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xo7IEOLpFdiU9LzMrBPM2GgnjAeyz81I"; // Auth code from Blynk email

// Define multiple Wi-Fi credentials
const char* ssid[] = {"ANNAPURNA J 314", "ANNAPURNA J 317","HemantG"}; // List of SSIDs
const char* pass[] = {"00004455", "00004455","sarika321"}; // Corresponding passwords

void connectWiFi() {
  int networkCount = sizeof(ssid) / sizeof(ssid[0]);
  for (int i = 0; i < networkCount; i++) {
    Serial.print("Connecting to ");
    Serial.println(ssid[i]);
    WiFi.begin(ssid[i], pass[i]);
    
    // Wait until connected or timeout (10 seconds)
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 100) {
      delay(100);
      retries++;
      Serial.print(".");
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.print("Connected to ");
      Serial.println(ssid[i]);
      break;
    } else {
      Serial.println();
      Serial.println("Failed to connect, trying next network...");
    }
  }

  // If still not connected, display error
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to any network.");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set D1 as an output pin and initialize it to HIGH (OFF state for relay)
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);

  // Connect to Wi-Fi
  connectWiFi();

  // Connect to Blynk
  Blynk.config(auth);
  while (WiFi.status() == WL_CONNECTED && !Blynk.connect()) {
    delay(100);
  }
}

// This function will be called every time a new value is received on Virtual Pin V1
BLYNK_WRITE(V1)
{
  int value = param.asInt(); // Get value as an integer (0 or 1)
  
  if (value == 1) {
    digitalWrite(D1, LOW); // Turn relay ON
    Serial.println("Relay ON");
  } else {
    digitalWrite(D1, HIGH); // Turn relay OFF
    Serial.println("Relay OFF");
  }
}

void loop()
{
  Blynk.run();
}
