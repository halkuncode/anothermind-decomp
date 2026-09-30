import os

# Get the current working directory
folder_path = os.getcwd()

# Loop through all files in the current folder
for file_name in os.listdir(folder_path):
    if file_name.lower().endswith('.anx.dec'):
        new_file_name = file_name[:-8] + '.ans'  # Remove .tix.dec and add .tim
        os.rename(file_name, new_file_name)

print('file rename complete')
