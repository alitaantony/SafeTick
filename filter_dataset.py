import os
from shutil import copyfile

# Define paths
data_dir = r"C:\Users\Alita\Downloads\Constructionsite\css-data\train"
filtered_dir = r"C:\Users\Alita\Downloads\Constructionsite\filtered_dataset"

# Create filtered folders for images and labels
os.makedirs(os.path.join(filtered_dir, "images"), exist_ok=True)
os.makedirs(os.path.join(filtered_dir, "labels"), exist_ok=True)

# Classes to keep
target_classes = {0, 7}

# Loop through label files
label_dir = os.path.join(data_dir, "labels")  # Updated path to the correct 'labels' folder
image_dir = os.path.join(data_dir, "images")  # Updated path to the correct 'images' folder

for label_file in os.listdir(label_dir):
    label_path = os.path.join(label_dir, label_file)

    with open(label_path, "r") as file:
        lines = file.readlines()

    # Filter lines for target classes
    filtered_lines = [line for line in lines if int(line.split()[0]) in target_classes]

    # If there are valid lines, save them and copy the corresponding image
    if filtered_lines:
        # Save filtered label file
        new_label_path = os.path.join(filtered_dir, "labels", label_file)
        with open(new_label_path, "w") as new_file:
            new_file.writelines(filtered_lines)

        # Copy corresponding image
        image_file = label_file.replace(".txt", ".jpg")
        image_path = os.path.join(image_dir, image_file)
        new_image_path = os.path.join(filtered_dir, "images", image_file)

        if os.path.exists(image_path):  # Ensure the corresponding image exists
            copyfile(image_path, new_image_path)

print("Filtering completed. Filtered dataset is saved in:", filtered_dir)
