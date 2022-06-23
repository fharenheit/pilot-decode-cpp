#include <string>
#include <iostream>
#include "base64.h"
#include "snappy.h"
#include "decode.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector <string> split(string data, char delimiter) {
    istringstream iss(data);
    string buffer;
    vector <string> result;
    while (getline(iss, buffer, delimiter)) {
        result.push_back(buffer);
    }
    return result;
}

int main() {

    /////////////////////////////
    // Array
    /////////////////////////////

    string str = "AAA,BBB,CCC,DDD,EEE,FFF,GGG";
    vector <string> r = split(str, ',');

    for (int i = 0; i < r.size(); i++) {
        cout << r[i] << "\n";
    }

    /////////////////////////////
    // Base64
    /////////////////////////////

    const string orig = "René Nyffenegger\n"
                        "http://www.renenyffenegger.ch\n"
                        "passion for data\n";

    const string write_path = "/home/data/A0000/dir.txt";

    string encoded = base64_encode(reinterpret_cast<const unsigned char *>(orig.c_str()), orig.length());

    string result = decode(encoded, write_path);
    cout << result << endl;

    string decoded = base64_decode(encoded);

    cout << encoded << endl;
    cout << decoded << endl;

    /////////////////////////////
    // Snappy
    /////////////////////////////

    string input = "This is snappy example.";
    string output;
    for (int i = 0; i < 5; ++i) {
        input += input;
    }

    snappy::Compress(input.data(), input.size(), &output);
    cout << "input size :" << input.size() << " output size :" << output.size() << endl;

    string output_uncom;
    snappy::Uncompress(output.data(), output.size(), &output_uncom);
    if (input == output_uncom) {
        cout << "Equal " << endl;
    } else {
        cout << "ERROR : not equal" << endl;
    }

    return 0;
}
