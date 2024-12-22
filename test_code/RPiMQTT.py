import paho.mqtt.client as mqtt

# MQTT broker details
mqtt_broker = "192.168.180.22"  # Replace with your Raspberry Pi's IP address
mqtt_port = 1883
mqtt_topic = "ai/detections"

# Flags to track if both helmet and vest are detected
helmet_detected = False
vest_detected = False

# MQTT callback when a message is received
def on_message(client, userdata, msg):
    global helmet_detected, vest_detected
    
    message = msg.payload.decode("utf-8")
    print(f"Message received: {message}")
    
    # Check if the message indicates helmet or vest detection
    if "Helmet detected" in message:
        helmet_detected = True
    elif "Vest detected" in message:
        vest_detected = True
    
    # If both helmet and vest are detected, allow entry
    if helmet_detected and vest_detected:
        print("Entry allowed")
    else:
        print("Entry not allowed")

# MQTT callback when connected to broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected to MQTT broker with result code {rc}")
    client.subscribe(mqtt_topic)

# Set up the MQTT client
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# Connect to the MQTT broker
client.connect(mqtt_broker, mqtt_port, 60)

# Loop forever to listen for messages
client.loop_forever()
