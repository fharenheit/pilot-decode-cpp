#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "base64.h"
#include "snappy.h"
#include "decode.h"

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
    /// Array Unnest
    /////////////////////////////

    string unnest_string = "a`b`c`d`e`f`a|b|c|d|e|f`1|2|3|4|5|6`g|h|i|j|k|l`0|9|8|7|6|5";
    vector <string> r = split(unnest_string, '`');

    for (int i = 0; i < r.size(); i++) {
        string column1 = r[0];
        string column2 = r[1];
        string column3 = r[2];
        string column4 = r[3];
        string column5 = r[4];
        string column6 = r[5];

        vector <string> column7 = split(r[6], '|');
        vector <string> column8 = split(r[7], '|');
        vector <string> column9 = split(r[8], '|');
        vector <string> column10 = split(r[9], '|');

        int array_count = column7.size();
        column1.append(",")
                .append(column2).append(",")
                .append(column3).append(",")
                .append(column4).append(",")
                .append(column5).append(",")
                .append(column6);
        for (int i = 0; i < array_count; i++) {
            string row;
            row.append(column1).append(",").append(column7[i]).append(",")
                    .append(column8[i]).append(",")
                    .append(column9[i]).append(",")
                    .append(column10[i]);
            cout << row << endl;
        }
    }

    /////////////////////////////
    /// Base64
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
    /// Snappy
    /////////////////////////////

    string input = "Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)";
    string output;
    for (int i = 0; i < 5; ++i) {
        input += input;
    }

    snappy::Compress(input.data(), input.size(), &output);
    cout << "input size :" << input.size() << " output size :" << output.size() << endl;
    cout << output << endl;

    string output_uncom;
    snappy::Uncompress(output.data(), output.size(), &output_uncom);
    if (input == output_uncom) {
        cout << "Equal " << endl;
    } else {
        cout << "ERROR : not equal" << endl;
    }

    return 0;
}
