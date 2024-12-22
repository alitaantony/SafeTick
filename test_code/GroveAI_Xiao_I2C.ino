#include <Wire.h>
#include <Grove_Vision_AI.h>  // Include the Grove Vision AI library

#define I2C_ADDRESS 0x62  // I2C address for Grove Vision AI module

GroveVisionAI vision;  // Create an instance of the GroveVisionAI class

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Initialize Grove Vision AI module using I2C
  if (!vision.begin(&Wire, I2C_ADDRESS)) {
    Serial.println("Grove Vision AI initialization failed!");
    while (1);  // Halt if initialization fails
  }

  Serial.println("Grove Vision AI initialized successfully.");
  
  // Invoke the model (you can adjust the number of invocations and parameters as needed)
  if (vision.invoke(1)) {
    Serial.println("Model invocation successful.");
  } else {
    Serial.println("Model invocation failed.");
  }
}

void loop() {
  // Check how many bytes are available to read from the Grove Vision AI
  int availableBytes = vision.available();
  
  if (availableBytes > 0) {
    // Prepare a buffer to read the data from the Grove Vision AI
    char data[availableBytes];
    
    // Read the available data
    int bytesRead = vision.read(data, availableBytes);
    
    // Check if the data was read successfully
    if (bytesRead > 0) {
      // Print the received data to the serial monitor
      Serial.print("Received data: ");
      for (int i = 0; i < bytesRead; i++) {
        Serial.print(data[i], HEX);  // Print in hexadecimal format
        Serial.print(" ");
      }
      Serial.println();
      
      // Optionally, you can parse or process the data here
    } else {
      Serial.println("Failed to read data from Grove Vision AI.");
    }
  }
  
  delay(500);  // Small delay to allow for continuous reading
}
