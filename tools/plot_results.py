# import csv
# import matplotlib.pyplot as plt
# import sys

# def plot_csv(files, title, output):
#     for file in files:
#         sizes = []
#         times = []
#         label = file.split("/")[-1].replace(".csv", "")

#         with open(file) as f:
#             reader = csv.DictReader(f)
#             for row in reader:
#                 sizes.append(int(row["matrix_size"]))
#                 times.append(float(row["time_seconds"]))

#         plt.plot(sizes, times, marker='o', label=label)

#     plt.xlabel("Matrix Size (N x N)")
#     plt.ylabel("Time (seconds)")
#     plt.title(title)
#     plt.legend()
#     plt.grid(True)
#     plt.savefig(output)
#     plt.close()

# if __name__ == "__main__":
#     plot_csv(
#         sys.argv[1:-2],
#         sys.argv[-2],
#         sys.argv[-1]
#     )


import csv
import matplotlib.pyplot as plt
import sys
import imageio
import os


def plot_csv(files, title, output_png, output_gif=None):
    all_data = []

    # ----------------------------
    # Read all CSVs
    # ----------------------------
    for file in files:
        sizes = []
        times = []
        label = os.path.basename(file).replace(".csv", "")

        with open(file) as f:
            reader = csv.DictReader(f)
            for row in reader:
                sizes.append(int(row["matrix_size"]))
                times.append(float(row["time_seconds"]))

        all_data.append((label, sizes, times))

    # ----------------------------
    # Compute global limits
    # ----------------------------
    all_sizes = []
    all_times = []

    for _, s, t in all_data:
        all_sizes.extend(s)
        all_times.extend(t)

    xmin, xmax = min(all_sizes), max(all_sizes)
    ymin, ymax = min(all_times), max(all_times)

    # Add padding
    ymin *= 0.9
    ymax *= 1.1

    # ----------------------------
    # Static PNG plot
    # ----------------------------
    plt.figure(figsize=(8, 5))

    for label, sizes, times in all_data:
        plt.plot(sizes, times, marker='o', label=label)

    plt.xlabel("Matrix Size (N x N)")
    plt.ylabel("Time (seconds)")
    plt.title(title)
    plt.legend()
    plt.grid(True)

    plt.xlim(xmin, xmax)
    plt.ylim(ymin, ymax)

    plt.tight_layout()
    plt.savefig(output_png, dpi=120)
    plt.close()

    print(f"[OK] Saved plot -> {output_png}")

    # ----------------------------
    # GIF generation (optional)
    # ----------------------------
    if output_gif:
        frames = []
        unique_sizes = sorted(set(all_data[0][1]))

        for upto in range(1, len(unique_sizes) + 1):
            plt.figure(figsize=(8, 5))

            for label, sizes, times in all_data:
                plt.plot(
                    sizes[:upto],
                    times[:upto],
                    marker='o',
                    label=label
                )

            plt.xlabel("Matrix Size (N x N)")
            plt.ylabel("Time (seconds)")
            plt.title(title + f" (up to {unique_sizes[upto-1]})")
            plt.legend()
            plt.grid(True)

            plt.xlim(xmin, xmax)
            plt.ylim(ymin, ymax)

            plt.tight_layout()

            fname = f"_frame_{upto}.png"
            plt.savefig(fname, dpi=120)
            plt.close()

            frames.append(imageio.imread(fname))
            os.remove(fname)

        imageio.mimsave(output_gif, frames, fps=1)
        print(f"[OK] Saved GIF -> {output_gif}")



if __name__ == "__main__":
    """
    Usage:
    python plot_results.py file1.csv file2.csv ... "Title" out.png [out.gif]
    """

    if len(sys.argv) < 5:
        print("Usage: python plot_results.py f1.csv f2.csv ... \"Title\" out.png [out.gif]")
        sys.exit(1)

    # If GIF present
    if sys.argv[-1].endswith(".gif"):
        out_gif = sys.argv[-1]
        out_png = sys.argv[-2]
        title = sys.argv[-3]
        files = sys.argv[1:-3]
    else:
        out_gif = None
        out_png = sys.argv[-1]
        title = sys.argv[-2]
        files = sys.argv[1:-2]

    plot_csv(files, title, out_png, out_gif)

