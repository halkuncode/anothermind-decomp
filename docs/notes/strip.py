import os

# Specify the input and output folder paths
input_folder = '.'
output_folder = 'snip'

# Create the output folder if it doesn't exist
os.makedirs(output_folder, exist_ok=True)

# Loop through all files in the input folder
for file_name in os.listdir(input_folder):
    # Check if the file has an extension that ends with 'z'
    if file_name.lower().endswith('z'):
        input_file_path = os.path.join(input_folder, file_name)
        new_file_name = file_name[:-1] + 'x'  # Change the extension from 'z' to 'x'
        output_file_path = os.path.join(output_folder, new_file_name)
        
        # Open the input file in binary mode and remove the first two bytes
        with open(input_file_path, 'rb') as input_file:
            data = input_file.read()[2:]
        
        # Write the modified data to a new file in the output folder
        with open(output_file_path, 'wb') as output_file:
            output_file.write(data)

print('Files processed and saved to', output_folder)
