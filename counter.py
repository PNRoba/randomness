def count_digits_after_dot(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    counts = {'0': 0, '1': 0, '2': 0, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0, '8': 0, '9': 0}

    dot_encountered = False

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

output_file_path = 'path\konstantes'


count_digits_after_dot(output_file_path+'\gr-const.txt')
count_digits_after_dot(output_file_path+'\cat-const.txt')
count_digits_after_dot(output_file_path+'\sqrt3-const.txt')
count_digits_after_dot(output_file_path+'\zeta3-const.txt')

count_digits_after_dot(output_file_path+'\lemn-const.txt')
count_digits_after_dot(output_file_path+'\log3-const.txt')
count_digits_after_dot(output_file_path+'\log2-const.txt')
count_digits_after_dot(output_file_path+'\log10-const.txt')

