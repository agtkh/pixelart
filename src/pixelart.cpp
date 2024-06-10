#include "pixelart.hpp"

#include <iostream>
#define ESC "\033"
#define DOUBLE_SPACE "  "
void printRgbDot(std::string colorStr) { std::cout << ESC "[48;2;" << colorStr << "m" DOUBLE_SPACE ESC "[0m"; }
void printTransparentDot() { std::cout << (ESC "[49m" DOUBLE_SPACE ESC "[0m"); }