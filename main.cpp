#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "base64.h"
#include "snappy.h"
#include "decode.h"
#include "stopwatch.hpp"

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

void unnest_array() {
    cout << "======================================" << endl;
    cout << "Starting Array Unnest" << endl;
    cout << "======================================" << endl;

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
}

void loading_and_unnest_array(bool is_file_writing) {
    cout << "======================================" << endl;
    cout << "Starting Array Unnest From File" << endl;
    cout << "======================================" << endl;

    Stopwatch watch;
    watch.start();

    string line;
    ifstream csv_file("array.txt");
    long count = 0;
    if (csv_file.is_open()) {
        while (getline(csv_file, line)) {
            vector <string> r = split(line, '`');
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
                    // cout << row << endl;
                    count++;
                }
            }
        }
        csv_file.close();
        uint64_t elapsed_s = watch.elapsed<seconds>();

        cout << "Row Count : " << count << endl;
        cout << "Elapsed : " << elapsed_s << "s" << endl;
    }
}

void snappy_compress_and_base64_encoding() {
    cout << "========================================" << endl;
    cout << "Starting Snappy+Base64 and File Writing" << endl;
    cout << "========================================" << endl;

    Stopwatch watch;
    watch.start();

//    string input = "Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)";
    string input = "Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)";
    string string_to_encoding = "a`b`c`d`e`f`a|b|c|d|e|f`1|2|3|4|5|6`g|h|i|j|k|l`1|2|3|4|5|6";
    ofstream encoded_csv_file("array_plain_text.txt");
    for (int i = 0; i <= 200000; i++) {
        string output;
//        snappy::Compress(input.data(), input.size(), &output);
        //string encoded = base64_encode(reinterpret_cast<const unsigned char *>(output.c_str()), output.length());
        encoded_csv_file << input << endl;
    }
    encoded_csv_file.close();

    uint64_t elapsed_s = watch.elapsed<seconds>();

    cout << "Elapsed : " << elapsed_s << "s" << endl;
}

void snappy_compress_and_base64_decoding() {
    cout << "========================================" << endl;
    cout << "Starting File Reading and Snappy+Base64" << endl;
    cout << "========================================" << endl;

    Stopwatch watch;
    watch.start();

    ifstream encoded_csv_file("array_snappy_base64_encoded.txt");
    string output;
    while (encoded_csv_file.peek() != EOF) {
        string final_decoded;
        getline(encoded_csv_file, output);
        string decoded = base64_decode(output, output.length());
        snappy::Compress(decoded.data(), decoded.size(), &final_decoded);

        cout << final_decoded << endl;
    }

    encoded_csv_file.close();

    uint64_t elapsed_s = watch.elapsed<seconds>();

    cout << "Elapsed : " << elapsed_s << "s" << endl;
}

void base64_encoding_decoding() {
    cout << "======================================" << endl;
    cout << "Starting Base64" << endl;
    cout << "======================================" << endl;

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
}

void snappy_compress_decompress() {
    cout << "======================================" << endl;
    cout << "Starting Snappy " << endl;
    cout << "======================================" << endl;

    string input = "Snappy is a compression/decompression library. It does not aim for maximum compression, or compatibility with any other compression library; instead, it aims for very high speeds and reasonable compression. For instance, compared to the fastest mode of zlib, Snappy is an order of magnitude faster for most inputs, but the resulting compressed files are anywhere from 20% to 100% bigger. (For more information, see \"Performance\", below.)";
    string output;
    for (int i = 0; i < 5; ++i) {
        input += input;
    }

    cout << "original : " << input << endl;

    snappy::Compress(input.data(), input.size(), &output);
    cout << "input size :" << input.size() << " output size :" << output.size() << endl;
    cout << output << endl;

    cout << "compressed : " << output << endl;

    string output_uncom;
    snappy::Uncompress(output.data(), output.size(), &output_uncom);
    if (input == output_uncom) {
        cout << "Equal " << endl;
    } else {
        cout << "ERROR : not equal" << endl;
    }

    cout << "decompressed : " << output_uncom << endl;
}

int main() {

    /////////////////////////////
    /// Array Unnest
    /////////////////////////////

    // unnest_array();

    /////////////////////////////
    /// Array Unnest from File
    /////////////////////////////

    // loading_and_unnest_array();

    /////////////////////////////
    /// Snappy Compression
    /// Base64 Encode
    /// File Write
    /////////////////////////////

    // snappy_compress_and_base64_encoding();
    //snappy_compress_and_base64_decoding();

    /////////////////////////////
    /// Base64
    /////////////////////////////

    // base64_encoding_decoding();

    /////////////////////////////
    /// Snappy
    /////////////////////////////

    snappy_compress_decompress();

    return 0;
}
