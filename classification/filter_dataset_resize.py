from PIL import Image
import os

# Paths to the input directories and output directories
input_image_dir = r"C:\Users\Alita\Downloads\Constructionsite\filtered_dataset\images"
input_label_dir = r"C:\Users\Alita\Downloads\Constructionsite\filtered_dataset\labels"
output_image_dir = r"C:\Users\Alita\Downloads\Constructionsite\filtered_dataset_resized\images"
output_label_dir = r"C:\Users\Alita\Downloads\Constructionsite\filtered_dataset_resized\labels"

# Create output directories if they don't exist
os.makedirs(output_image_dir, exist_ok=True)
os.makedirs(output_label_dir, exist_ok=True)

# Resize images and adjust corresponding labels
for filename in os.listdir(input_image_dir):
    if filename.endswith(".jpg") or filename.endswith(".png"):  # Check image file format
        # Paths for image and label files
        image_path = os.path.join(input_image_dir, filename)
        label_filename = filename.replace(".jpg", ".txt").replace(".png", ".txt")  # Assuming label file is .txt
        label_path = os.path.join(input_label_dir, label_filename)
        
        # Open and resize the image
        img = Image.open(image_path)
        original_width, original_height = img.size
        img_resized = img.resize((320, 320))  # Resize image to 320x320
        img_resized.save(os.path.join(output_image_dir, filename))  # Save resized image

        # Open and adjust the label file
        with open(label_path, 'r') as label_file:
            lines = label_file.readlines()

        # Adjust label coordinates based on the new image size
        with open(os.path.join(output_label_dir, label_filename), 'w') as new_label_file:
            for line in lines:
                parts = line.split()
                class_id = parts[0]
                x_center, y_center, width, height = map(float, parts[1:])
                
                # Scale the bounding box coordinates to the new image size
                new_x_center = x_center * 320  # Scale to 320x320
                new_y_center = y_center * 320
                new_width = width * 320
                new_height = height * 320
                
                # Write the adjusted label to the new file
                new_label_file.write(f"{class_id} {new_x_center} {new_y_center} {new_width} {new_height}\n")

print("Resizing and label adjustment complete!")
