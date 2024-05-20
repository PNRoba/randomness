# Programme: Last 51 characters
# Description:
# Prints out last 51 characters from a text file
# that contains 1 billion characters
# (can be modified to print last 51 characters
# of a text file containing 10 billion)

import os

def print_last_chars_of_files(folder_path):
    if not os.path.isdir(folder_path):
        print("The specified path is not a directory.")
        return

    file_list = os.listdir(folder_path)

    # For each file print last 51 characters (last 51 digits of each constant)
    for file_name in file_list:
        if file_name.endswith('.txt'):
            file_path = os.path.join(folder_path, file_name)
            with open(file_path, 'r') as file:
                file.seek(999999949) # Add 9 in the front to print last 51 chars of 10 billion long char text file
                rest_of_file = file.read()
                print(f"Last 51 characters of {file_name}: {rest_of_file[-51:]}")

# Folder containing constant digit strings up to 1 billion length
folder_path = 'konstantes\done'

print_last_chars_of_files(folder_path)
