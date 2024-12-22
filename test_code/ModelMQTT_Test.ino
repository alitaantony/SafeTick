#include <WiFi.h>
#include <PubSubClient.h>
#include <Seeed_Arduino_SSCMA.h>

// WiFi credentials
const char* ssid = "OPPO F19 Pro+";           // Replace with your WiFi SSID
const char* password = "ashishjoy10";   // Replace with your WiFi password

// MQTT broker details
const char* mqtt_server = "192.168.180.22";  // Replace with your Raspberry Pi's IP address
const int mqtt_port = 1883;
const char* mqtt_topic = "ai/detections";   // Topic to publish messages

WiFiClient espClient;
PubSubClient client(espClient);
SSCMA AI;

void setup()
{
    // Initialize Serial and AI
    Serial.begin(9600);
    AI.begin();

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Set up MQTT client
    client.setServer(mqtt_server, mqtt_port);
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP32_AI_Client")) // Replace with a unique client ID
        {
            Serial.println("Connected to MQTT broker");
        }
        else
        {
            Serial.print("Failed to connect, state: ");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void loop()
{
    if (!AI.invoke())
    {
        for (int i = 0; i < AI.boxes().size(); i++)
        {
            int target = AI.boxes()[i].target;
            float score = AI.boxes()[i].score;

            // Send MQTT message if confidence exceeds 50% for "elephant"
            if (score > 50.0 && target == 0) // Ensure target '0' corresponds to "elephant"
            {
                String message = "Elephant detected with confidence: " + String(score);
                client.publish(mqtt_topic, message.c_str());
                Serial.println(message);
                delay(1000); // Add delay to avoid sending multiple messages too quickly
                return;
            }
        }
    }
    delay(100); // Prevent excessive looping
}
