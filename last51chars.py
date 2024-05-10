import os

def print_last_chars_of_files(folder_path):
    if not os.path.isdir(folder_path):
        print("The specified path is not a directory.")
        return

    file_list = os.listdir(folder_path)

    for file_name in file_list:
        if file_name.endswith('.txt'):
            file_path = os.path.join(folder_path, file_name)
            with open(file_path, 'r') as file:
                file.seek(999999949)
                rest_of_file = file.read()
                print(f"Last 51 characters of {file_name}: {rest_of_file[-51:]}")

folder_path = 'konstantes\done'

print_last_chars_of_files(folder_path)
