# To use it you'll need python and the lib pillow (pip install pillow)
# I've only tested with bmp files, I haven't tested any other format
from PIL import Image
import sys


def bmp_to_map(input_bmp, output_txt):
    img = Image.open(input_bmp).convert("RGB")

    width, height = img.size
    pixels = img.load()
    BLUE = (0, 0, 255)
    WHITE = (255, 255, 255)
    blue_positions = []

    output_lines = []
    for y in range(height):
        row = ""
        for x in range(width):
            pixel = pixels[x, y]
            if pixel == BLUE:
                blue_positions.append((x + 1, y + 1))
                row += "0"
            elif pixel == WHITE:
                row += "1"
            else:
                row += "0"
        output_lines.append(row)
    if len(blue_positions) == 0:
        raise ValueError("Error: No blue pixel (#0000FF) found.")
    if len(blue_positions) > 1:
        raise ValueError(
            f"Error: Only a single blue pixel (#0000FF) can be in the image."
        )
    blue_x, blue_y = blue_positions[0]

    with open(output_txt, "w") as f:
        f.write(f"{width} {height}\n")
        f.write(f"{blue_x} {blue_y}\n")
        for line in output_lines:
            f.write(line + "\n")
    print(f"Map saved to {output_txt}")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage:")
        print("python bmp_map_converter.py input.bmp output")
        sys.exit(1)

    bmp_to_map(sys.argv[1], sys.argv[2])