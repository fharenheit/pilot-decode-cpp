#include <iostream>
#include "string"
#include "base64.h"

std::string decode(const std::string &encoded, const std::string &write_path) {
    std::string decoded = base64_decode(encoded);
    std::cout << decoded << std::endl;
    std::cout << write_path << std::endl;

    return std::string();
}
