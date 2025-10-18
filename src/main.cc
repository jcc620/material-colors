#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "material-color-utilities/cpp/utils/utils.h"
#include "material-color-utilities/cpp/cam/hct.h"

int parseRGBArgs(char* argv[], material_color_utilities::Argb& argb) {
    int red, green, blue;
    try {
        red = std::stoi(argv[2]);
        if (red < 0 || red > 255) {
            std::cerr << "Error: red value must be an integer from 0-255.\n";
            return EXIT_FAILURE;
        }
    }   catch (const std::exception& e) {
        std::cerr << "Error: red value must be an integer from 0-255.\n";
        return EXIT_FAILURE;
    }
    try {
        green = std::stoi(argv[3]);
        if (green < 0 || green > 255) {
            std::cerr << "Error: green value must be an integer from 0-255.\n";
            return EXIT_FAILURE;
        }
    }   catch (const std::exception& e) {
        std::cerr << "Error: green value must be an integer from 0-255.\n";
        return EXIT_FAILURE;
    }
    try {
        blue = std::stoi(argv[4]);
        if (blue < 0 || blue > 255) {
            std::cerr << "Error: blue value must be an integer from 0-255.\n";
            return EXIT_FAILURE;
        }
    }   catch (const std::exception& e) {
        std::cerr << "Error: blue value must be an integer from 0-255.\n";
        return EXIT_FAILURE;
    }
    argb = material_color_utilities::ArgbFromRgb(red, green, blue);
    return 0;
}

void print_usage(char* prog_name) {
    printf("Usage: %s (primary|secondary) <red> <green> <blue>\n", prog_name);
    printf(
        "For a given RGB-encoded color, find the frame and active tab color used by\n"
        "the Omarchy micro-fork of Chromium when that color is set as the theme color.\n\n"
        "RGB values should be integers in the range 0-255.\n"
    );
}

int main(int argc, char* argv[]) {
    material_color_utilities::Argb sourceColorARGB;
    double tone;

    // Parse command line arguments
    if (argc == 5) {
        int err = parseRGBArgs(argv, sourceColorARGB);
        if (err) {
            return err;
        }
        if (std::strcmp(argv[1], "primary") == 0) {
            tone = 12;
        } else if (std::strcmp(argv[1], "secondary") == 0) {
            tone = 25;
        } else {
            std::cerr << "Error: mode must be primary or secondary.\n";
            return EXIT_FAILURE;
        }
    } else if (argc == 2 && (std::strcmp(argv[1], "-h") == 0 || std::strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        return 0;
    }else {
        std::cerr << "Error: invalid usage.\n";
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const double hue = material_color_utilities::Hct(sourceColorARGB).get_hue();

    material_color_utilities::Hct hct = 
        material_color_utilities::Hct(hue, 16, tone);
    material_color_utilities::Hct secondaryColorHCT = 
        material_color_utilities::Hct(hue, 16, 25);

    material_color_utilities::Argb argb = hct.ToInt();
    material_color_utilities::Argb secondaryColorARGB = 
        secondaryColorHCT.ToInt();

    int sourceColorRGB = sourceColorARGB & 0xFFFFFF;
    int rgb = argb & 0xFFFFFF;
    int secondaryColorRGB = secondaryColorARGB & 0xFFFFFF;

    printf("%06x\n", rgb);
    
    return 0;
}

