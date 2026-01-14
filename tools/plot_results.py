import csv
import matplotlib.pyplot as plt
import sys

def plot_csv(files, title, output):
    for file in files:
        sizes = []
        times = []
        label = file.split("/")[-1].replace(".csv", "")

        with open(file) as f:
            reader = csv.DictReader(f)
            for row in reader:
                sizes.append(int(row["matrix_size"]))
                times.append(float(row["time_seconds"]))

        plt.plot(sizes, times, marker='o', label=label)

    plt.xlabel("Matrix Size (N x N)")
    plt.ylabel("Time (seconds)")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(output)
    plt.close()

if __name__ == "__main__":
    plot_csv(
        sys.argv[1:-2],
        sys.argv[-2],
        sys.argv[-1]
    )