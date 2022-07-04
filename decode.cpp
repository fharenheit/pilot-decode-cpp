#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "base64.h"
#include "snappy.h"
#include <fstream>

using namespace std;

string decode(const string &encoded, const string &write_path) {
    ofstream encoded_csv_file(write_path);
    string decoded = base64_decode(encoded);
    string result;
    snappy::Uncompress(decoded.data(), decoded.size(), &result);
    cout << result << endl;
    encoded_csv_file << result << endl;
    encoded_csv_file.close();
    return result;
}

vector <string> split_by_delimiter(string data, char delimiter) {
    istringstream iss(data);
    string buffer;
    vector <string> result;
    while (getline(iss, buffer, delimiter)) {
        result.push_back(buffer);
    }
    return result;
}
