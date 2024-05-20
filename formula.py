# Programme: Formula
# Description:
# From digit strings calculates delta for each
# digit as the string grows

import numpy as np
from datetime import datetime

# Delta calculation formula based on digit sum and digit index
def calculate_delta(s_10_n, n):
    mean_value = 4.5
    variance = 8.25
    delta_n = (s_10_n - (mean_value * (n))) / np.sqrt(2 * variance * (n) * np.log(np.log(n)))
    return delta_n

def write_file(input_file, output_file, startTime):
    sakums=0 # beginning index, used in case generation stopped before reached the end of constant digit string file
    dot_encountered = False # change to true if constant digit string file starts after '.' and therefore doesnt contain '.'

    with open(input_file, 'r') as file:
        content = file.read()
        digit_index = 0
        digitSum = 0
        string=""
        failasaturs=""

        # Open first file
        file = open(output_file  + "-1mil.txt", 'w')
        for char in content:
            if not dot_encountered:
                # Ignore characters until '.'
                if char == '.':
                    dot_encountered = True
            elif char.isdigit():
                # Calculate delta for each digit separately

                # After million data points are processed
                if digit_index % 1000000 == 0:
                    # Print current passed time, digit index and digit sum
                    print("Currently starting: " + str(datetime.now() - startTime) + " | Digit index: " + str(digit_index) + " | Digit Sum: " + str(digitSum))

                    # Store the million data points and open new file for next million float data points
                    if digit_index > sakums:
                        file.write(failasaturs)
                        failasaturs = ""
                        string = str(int(digit_index / 1000000)+1)
                        file = open(output_file + "-" + string + "mil.txt", 'w')
                # Digit index
                digit_index += 1
                # Digit sum
                digitSum += int(char)
                if digit_index > sakums:
                    # calculates delta for current digit
                    delta = calculate_delta(digitSum, digit_index)
                    # print(delta)
                    failasaturs = failasaturs + "{}\n".format(delta)
                    
        # Save last million data points
        file.write(failasaturs)


def main():
    # Start time for printing time used to calculate
    startTime = datetime.now()

    input_file_path = 'digitString.txt' # change to respective digit string to be processed
    output_file_path = 'deltaDigitString' # ".txt is added later"
    write_file(input_file_path, output_file_path, startTime)
    print("done")


if __name__ == "__main__":
    main()
