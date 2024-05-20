# Programme: Counter
# Description:
# Counts digits of constant strings after '.'

def count_digits_after_dot(file_path):
    # Read file
    with open(file_path, 'r') as file:
        content = file.read()
        
    # Initialise digit counts starting 0
    counts = {'0': 0, '1': 0, '2': 0, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0, '8': 0, '9': 0}

    dot_encountered = False

    # After '.' is encounered
    # Iterate through the file content char by char
    # Add +1 each time the respective digit occurs
    for char in content:
        if char == '.':
            dot_encountered = True
        elif dot_encountered and char.isdigit():
            counts[char] += 1

    # Print the file name
    print(f'File: {file_path}')

    # Print the counts
    for digit, count in counts.items():
        print(f'Mentions of {digit} after \'.\': {count}')

# Folder containing constant digit string text files
output_file_path = 'path\konstantes'

count_digits_after_dot(output_file_path+'\gr-const.txt')
count_digits_after_dot(output_file_path+'\cat-const.txt')
count_digits_after_dot(output_file_path+'\sqrt3-const.txt')
count_digits_after_dot(output_file_path+'\zeta3-const.txt')

count_digits_after_dot(output_file_path+'\lemn-const.txt')
count_digits_after_dot(output_file_path+'\log3-const.txt')
count_digits_after_dot(output_file_path+'\log2-const.txt')
count_digits_after_dot(output_file_path+'\log10-const.txt')

count_digits_after_dot(output_file_path+'\euler-const.txt')
count_digits_after_dot(output_file_path+'\e-const.txt')
count_digits_after_dot(output_file_path+'\sqrt2-const.txt')
