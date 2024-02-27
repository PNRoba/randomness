import numpy as np
from datetime import datetime

def calculate_delta(s_10_n, n):
    mean_value = 4.5
    variance = 8.25
    delta_n = (s_10_n - (mean_value * (n))) / np.sqrt(2 * variance * (n) * np.log(np.log(n)))
    return delta_n

def write_file(input_file, output_file, startTime):
    sakums=0
    dot_encountered = False

    with open(input_file, 'r') as file:
        content = file.read()
        digit_index = 0
        digitSum = 0
        string=""
        failasaturs=""

        file = open(output_file  + "-1mil.txt", 'w')
        for char in content:
            if not dot_encountered:
                # Ignore characters until '.'
                if char == '.':
                    dot_encountered = True
            elif char.isdigit():
                # Calculate delta for each digit separately
                # print(char)

                if digit_index % 1000000 == 0:
                    print("Currently starting: " + str(datetime.now() - startTime) + " | Digit index: " + str(digit_index) + " | Digit Sum: " + str(digitSum))
                    if digit_index > sakums:
                        file.write(failasaturs)
                        failasaturs = ""
                        string = str(int(digit_index / 1000000)+1)
                        file = open(output_file + "-" + string + "mil.txt", 'w')
                digit_index += 1
                digitSum += int(char)
                if digit_index > sakums:
                    delta = calculate_delta(digitSum, digit_index)
                    print(delta)
                    failasaturs = failasaturs + "{}\n".format(delta)
        file.write(failasaturs)


def main():
    startTime = datetime.now()

    input_file_path = 'digitString.txt'
    output_file_path = 'deltaDigitString' # ".txt is added later"
    write_file(input_file_path, output_file_path, startTime)
    print("done")


if __name__ == "__main__":
    main()
