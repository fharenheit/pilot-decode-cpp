#include <string>
#include <iostream>
#include "base64.h"
#include "snappy.h"
#include "decode.h"

int main() {

    /////////////////////////////
    // Base64
    /////////////////////////////

    const std::string orig =
            "René Nyffenegger\n"
            "http://www.renenyffenegger.ch\n"
            "passion for data\n";

    const std::string write_path = "/home/data/A0000/dir.txt";

    std::string encoded = base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length());

    std::string result = decode(encoded, write_path);
    std::cout << result << std::endl;

    std::string decoded = base64_decode(encoded);

    std::cout << encoded << std::endl;
    std::cout << decoded << std::endl;

    /////////////////////////////
    // Snappy
    /////////////////////////////

    std::string input = "This is snappy example.";
    std::string output;
    for (int i = 0; i < 5; ++i)                        //loop to increase the length of input string
    {
        input += input;
    }

    std::cout << input << std::endl;

    //snappy::Compress(input.data(), input.size(), &output);

    /*
    std::string input = "This is snappy example.";
    std::string output;
    for (int i = 0; i < 5; ++i)                        //loop to increase the length of input string
    {
        input += input;
    }
    snappy::Compress(input.data(), input.size(), &output);        //compress input string by snappy
    std::cout << "input size :" << input.size() << " output size :" << output.size() << std::endl;
    std::string output_uncom;                        //define uncompressed output string variable
    snappy::Uncompress(output.data(), output.size(), &output_uncom);    //uncompress the compressed string
    if (input == output_uncom)                    //compare the string before compression and uncompressed string
    {
        std::cout << "Equal " << std::endl;
    } else {
        std::cout << "ERROR : not equal" << std::endl;
    }

*/
    return 0;
}
