# Programme: Diagrams
# Description:
# From millions of float data points generates
# diagrams (each containing 100 million data points)
# that show the values in relation to the limits

import os
import matplotlib.pyplot as plt

def plot_delta_sequences_100(folder_path, name, hundredMil):
        all_delta_sequences = []
        filename = folder_path + "\delta_sequence-" + name + "-"

        # extract and format data from delta sequence files
        # up tp 100 million data points, to be visualised
        for i in range((hundredMil*100)-99, (hundredMil*100)+1):
            print("Currently computing: " + str(i) + " million")
            input_file_path = os.path.join(folder_path, filename + str(i) + "mil.txt")
            with open(input_file_path, 'r') as file:
                delta_sequence = [float(line.strip()) for line in file]
                all_delta_sequences.extend(delta_sequence)

        # Diagram settings
        plt.plot(all_delta_sequences, label=r'$\frac{S_{10}(n) - 4.5n}{\sqrt{2 \cdot 8.25n \log(\log(n))}}$')
        plt.axhline(y=1, color='red', linestyle='--', label='Upper Bound (+1)')
        plt.axhline(y=0, color='grey', linestyle='--', label='Middle Bound (0)')
        plt.axhline(y=-1, color='red', linestyle='--', label='Lower Bound (-1)')

        plt.xlabel('n-th digit in the sequence')
        plt.ylabel(r'$\frac{S_{10}(n) - 4.5n}{\sqrt{2 \cdot 8.25n \log(\log(n))}}$')
        plt.title('10^7')
        plt.legend()

        plt.legend().set_visible(False)

        # Save diagram
        output_file = os.path.join('path\Delta Sequences', f'delta_sequence_e_10mil.png')
        plt.savefig(output_file)

        plt.close()


def main():
    # Name of constant to generate the diagrams for
    name = 'sqrt2'
    # Name of folder (used for locating data for diagram generation, and for storing generated diagrams)
    output_file_path = 'path\Delta Sequences'

    # Give:
    # - Folder path (containing data + for storing diagrams)
    # - Name of the constant (included in the pattern of delta sequence text file titles)
    # - index describing which 100 million data to visualise 
    #   (1 -> from 1 to 100 million, 2 -> from 101 to 200 million, etc.)
    # For 1 billion - 10 diagrams, for 10 billion - 100 diagrams
    plot_delta_sequences_100(output_file_path, name, 1)
    # plot_delta_sequences_100(output_file_path, name, 2)
    # plot_delta_sequences_100(output_file_path, name, 3)
    # plot_delta_sequences_100(output_file_path, name, 4)
    # plot_delta_sequences_100(output_file_path, name, 5)
    # plot_delta_sequences_100(output_file_path, name, 6)
    # plot_delta_sequences_100(output_file_path, name, 7)
    # plot_delta_sequences_100(output_file_path, name, 8)
    # plot_delta_sequences_100(output_file_path, name, 9)
    # plot_delta_sequences_100(output_file_path, name, 10)


if __name__ == "__main__":
    main()
