import os
import matplotlib.pyplot as plt

def plot_delta_sequences_100(folder_path, name, hundredMil):
        all_delta_sequences = []
        filename = folder_path + "\delta_sequence-" + name + "-"

        for i in range((hundredMil*100)-99, (hundredMil*100)+1):
            print("Currently computing: " + str(i) + " million")
            input_file_path = os.path.join(folder_path, filename + str(i) + "mil.txt")
            with open(input_file_path, 'r') as file:
                delta_sequence = [float(line.strip()) for line in file]
                all_delta_sequences.extend(delta_sequence)

        plt.plot(all_delta_sequences, label=r'$\frac{S_{10}(n) - 4.5n}{\sqrt{2 \cdot 8.25n \log(\log(n))}}$')
        plt.axhline(y=1, color='red', linestyle='--', label='Upper Bound (+1)')
        plt.axhline(y=0, color='grey', linestyle='--', label='Middle Bound (0)')
        plt.axhline(y=-1, color='red', linestyle='--', label='Lower Bound (-1)')

        plt.xlabel('n-th digit in the sequence')
        plt.ylabel(r'$\frac{S_{10}(n) - 4.5n}{\sqrt{2 \cdot 8.25n \log(\log(n))}}$')
        plt.title('10^7')
        plt.legend()

        plt.legend().set_visible(False)

        output_file = os.path.join('path\Delta Sequences', f'delta_sequence_e_10mil.png')
        plt.savefig(output_file)

        plt.close()


def main():
    name = 'pi'
    output_file_path = 'path\Delta Sequences'

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
