import librosa
import numpy as np

# Load audio file
audio_file = 'audio_sample.wav'
y, sr = librosa.load(audio_file)

# Extract features
mfccs = librosa.feature.mfcc(y=y, sr=sr, n_mfcc=13)
chroma = librosa.feature.chroma_stft(y=y, sr=sr)
spectral_contrast = librosa.feature.spectral_contrast(y=y, sr=sr)

# Combine features for model input
features = np.hstack([np.mean(mfccs, axis=1), np.mean(chroma, axis=1), np.mean(spectral_contrast, axis=1)])
print("Extracted Features:", features)
