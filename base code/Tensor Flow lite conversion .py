# Convert the model to TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_saved_model('emotion_model.h5')
tflite_model = converter.convert()

# Save the TensorFlow Lite model
with open('emotion_model.tflite', 'wb') as f:
    f.write(tflite_model)
