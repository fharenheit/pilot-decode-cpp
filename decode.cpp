#include <iostream>
#include "base64.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string decode(const string &encoded, const string &write_path) {
    string decoded = base64_decode(encoded);
    cout << decoded << endl;
    cout << write_path << endl;

    return string();
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
