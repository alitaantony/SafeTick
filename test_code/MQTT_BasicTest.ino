#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "Your_SSID";          // Replace with your WiFi SSID
const char* password = "Your_PASSWORD";  // Replace with your WiFi password

// MQTT broker details
const char* mqtt_server = "192.168.1.100"; // Replace with your Raspberry Pi's IP address
const int mqtt_port = 1883;
const char* mqtt_topic = "test/topic";     // MQTT topic for testing

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT Broker
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32_Test_Client")) { // Replace with a unique client ID
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect, state: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Publish a test message
  client.publish(mqtt_topic, "Hello from ESP32!");
  Serial.println("Test message sent to MQTT broker");
}

void loop() {
  // Keep the MQTT connection alive
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void reconnect() {
  // Attempt to reconnect to MQTT broker
  while (!client.connected()) {
    Serial.println("Reconnecting to MQTT...");
    if (client.connect("ESP32_Test_Client")) {
      Serial.println("Reconnected to MQTT broker");
    } else {
      Serial.print("Failed to reconnect, state: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}
