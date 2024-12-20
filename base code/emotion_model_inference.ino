#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "emotion_model_data.h"  // Include converted TFLite model

const int tensor_arena_size = 2 * 1024;
uint8_t tensor_arena[tensor_arena_size];

void setup() {
  Serial.begin(115200);

  // Load the TFLite model
  const tflite::Model* model = tflite::GetModel(emotion_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model version mismatch!");
    while (1);
  }

  // Initialize interpreter
  static tflite::MicroMutableOpResolver<10> resolver;
  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, tensor_arena_size, nullptr);

  Serial.println("Model Loaded!");
}

void loop() {
  // Perform inference and handle results
}
