import os

# Get the current working directory
folder_path = os.getcwd()

# Loop through all files in the current folder
for file_name in os.listdir(folder_path):
    # Check if the file has an extension that ends with 'x'
    if file_name.lower().endswith('x'):
        file_path = os.path.join(folder_path, file_name)
        
        # Construct the command as a string, assuming unlzs.exe is in the same folder
        command = f'unlzs.exe --no-header-test -d "{file_path}" final'
        
        # Run the command using os.system
        os.system(command)

print('Command executed for all files ending with "x"')
