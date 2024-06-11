#include <iostream>
#include <fstream>
#include <map>
#include "pixelart.hpp"
#include <cstdlib>
int main(int argc, char const *argv[]) {
    // Check if terminal is compatible with 24 bit colors
    // const char *colorterm = std::getenv("COLORTERM");
    // if (colorterm == nullptr || (std::string(colorterm) != "truecolor" && std::string(colorterm) != "24bit")) {
    //     std::cerr << "Terminal is not compatible with 24 bit colors" << std::endl;
    //     return 1;
    // }

    // Check if the user has provided a file name
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <pixel art file>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];

    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file " << filename << std::endl;
        return 1;
    }

    // Read the file for each line
    std::map<char, std::string> palette;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            // Skip to the next section
            break;
        }
        if (line.size() < 3 || line[1] != '=') {
            std::cerr << "Invalid line: " << line << std::endl;
            return 1;
        }
        char key = line[0];
        if (palette.find(key) != palette.end()) {
            std::cerr << "Duplicate key: " << key << std::endl;
            return 1;
        }
        palette[key] = line.substr(2);
    }

    // Print the pixel art
    while (std::getline(file, line)) {
        for (char c : line) {
            if (c == ' ') {
                printTransparentDot();
            } else {
                auto it = palette.find(c);
                if (it == palette.end()) {
                    std::cerr << "Unknown character: " << c << std::endl;
                    return 1;
                }
                const std::string &rgb = it->second;
                printRgbDot(rgb);
            }
        }
        std::cout << std::endl;
    }


    return 0;
}