def count_digits_after_dot(file_path, counts):
    with open(file_path, 'r') as file:
        content = file.read()

    for char in content:
        if char.isdigit():
            counts[char] += 1

    # Print the file name
    print(f'File: {file_path}')

    # Print the counts
    for digit, count in counts.items():
        print(f'Mentions of {digit} after \'.\': {count}')

# Example usage
output_file_path = 'path\Pi-chunks'

counts = {'0': 0, '1': 0, '2': 0, '3': 0, '4': 0, '5': 0, '6': 0, '7': 0, '8': 0, '9': 0}

count_digits_after_dot(output_file_path+'\chunk_1.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_2.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_3.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_4.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_5.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_6.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_7.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_8.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_9.txt', counts)
count_digits_after_dot(output_file_path+'\chunk_10.txt', counts)


