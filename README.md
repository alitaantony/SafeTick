# SafeTick : PPE Detection System

## Overview
This project utilizes a MobileNetV2-based deep learning model to detect Personal Protective Equipment (PPE) compliance in real-time. It is designed for deployment on edge devices, such as Raspberry Pi, using TensorFlow Lite for efficient inference. The system integrates hardware and software components to provide a complete solution for worker safety monitoring.

## Features
- **Lightweight Model**: MobileNetV2 architecture optimized for edge devices.
- **Real-time Detection**: Fast inference using TensorFlow Lite on resource-constrained devices.
- **Integrated Hardware**: Utilizes a Raspberry Pi camera and Grove Vision AI module for image capture and processing.
- **Feedback System**: Alerts and compliance ticks displayed in real-time on the Raspberry Pi screen.

## Architecture
### Network Architecture
- **Base Model**: MobileNetV2 pre-trained on the ImageNet dataset.
- **Input Layer**: Expects RGB images of size (224, 224, 3).
- **Global Average Pooling**: Reduces spatial dimensions and prepares the feature vector.
- **Dense Layers**: Includes ReLU and sigmoid activation for multi-label classification.
- **Output Layer**: Provides predictions for PPE compliance.

### Hardware Integration
1. **Image Capture**: The Raspberry Pi Rev 3 camera captures worker images.
2. **AI Processing**: Images are sent to the Grove Vision AI module for PPE detection.
3. **Decision Making**:
   - **If PPE is detected**:
     - A compliance tick is generated and displayed on the Raspberry Pi.
   - **If PPE is not detected**:
     - A non-compliance alert is displayed.

### Workflow
1. **Image Capture**:
   - Captures worker image via Raspberry Pi camera.
2. **AI Processing**:
   - Images are analyzed using the MobileNetV2 model (converted to TensorFlow Lite).
3. **Communication**:
   - Uses MQTT to transmit compliance status between devices.
4. **Real-Time Feedback**:
   - Displays compliance or alerts on the Raspberry Pi screen.

## Tools and Libraries Used
### Model Training
- **TensorFlow**: Framework for building and training the model.
- **Keras**: High-level API for defining the model architecture.
- **Keras Applications**: MobileNetV2 pre-trained model for transfer learning.

### Data Preparation
- **ImageDataGenerator**: Real-time data augmentation, including scaling and random transformations.

### Deployment
- **TensorFlow Lite**: Optimizes the trained model for inference on edge devices.
- **TF Lite Interpreter**: Executes the TensorFlow Lite model.

### Visualization and Evaluation
- **Matplotlib/Seaborn**: For visualizing training accuracy and loss.
- **Scikit-learn**: Computes additional evaluation metrics (F1-score, precision, recall).

### Hardware
- **Raspberry Pi**: Central hub for data processing and feedback.
- **Grove Vision AI Module**: Performs AI inference for PPE detection.
- **Xiao ESP32S3**: Handles communication between modules using I2C and MQTT.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/your-repo-name/ppe-detection.git
   ```
2. Install the required Python libraries:
   ```bash
   pip install tensorflow matplotlib scikit-learn
   ```
3. Deploy the TensorFlow Lite model to the Raspberry Pi.
4. Connect hardware components as described in the architecture section.

## Usage
1. Start the Raspberry Pi application to capture images.
2. Run the TensorFlow Lite inference script:
   ```bash
   python run_inference.py
   ```
3. Monitor compliance ticks and alerts on the Raspberry Pi screen.

## Results
The system provides real-time PPE compliance monitoring with:
- High accuracy using MobileNetV2.
- Optimized inference for edge devices.
- Instant feedback for workers.

## Future Enhancements
- Add support for additional safety measures.
- Extend compatibility to other hardware setups.
- Implement a cloud-based dashboard for compliance tracking.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Contributions are welcome! Feel free to submit a pull request or open an issue for suggestions and improvements.

