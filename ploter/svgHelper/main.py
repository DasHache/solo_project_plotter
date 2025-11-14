import re
import matplotlib.pyplot as plt

# Paste your C array here as a raw string
c_array = r"""
int link_path[][2] = {
{0, 27},
       {21, 60},
       {37, 95},
       {52, 135},
       {64, 172},
       {75, 205},
       {87, 227},
       {99, 240},
       {113, 237},
       {120, 215},
       {119, 182},
       {110, 140},
       {97, 97},
       {80, 57},
       {60, 27},
       {90, 72},
       {108, 50},
       {114, 5},
       {111, -52},
       {101, -107},
       {88, -152},
       {73, -175},
       {60, -165},
       {54, -125},
       {61, -80},
       {79, -40},
       {101, 0},
       {123, 30},
       {140, 50},
       {147, 57}
};
"""


def parse_c_array(text):
    """Extracts (x, y) integer tuples from a C-style array string."""
    pattern = r'\{\s*([+-]?\d+)\s*,\s*([+-]?\d+)\s*\}'
    pairs = re.findall(pattern, text)
    return [(int(x), int(y)) for x, y in pairs]

def plot_array(coords):
    """Plots the array of coordinate pairs."""
    x = [p[0] for p in coords]
    y = [p[1] for p in coords]

    plt.figure()
    plt.plot(x, y, marker='o')
    plt.xlabel('X value')
    plt.ylabel('Y value')
    plt.title('Plot from C-style array')
    plt.grid(True)
    plt.show()


def print_inverted_array(coords, var_name="link_path_inverted"):
    """Prints the reversed array in C format."""
    print(f"int {var_name}[{len(coords)}][2] = {{")
    for x, y in reversed(coords):
        print(f"    {{{x}, {y}}},")
    print("};")

def print_doubled_array(coords):
    for x, y in coords:
        print(f"    {{{x}, {y }}},")


if __name__ == "__main__":
    coords = parse_c_array(c_array)
    coords = [(int(x * 4), -y) for x, y in coords]

    #print_inverted_array(coords)
    print_doubled_array(coords)
    #plot_array(coords)

    # Call this line to print the inverted array

