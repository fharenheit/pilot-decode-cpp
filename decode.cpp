#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "base64.h"
#include "snappy.h"
#include <fstream>
#include "java.h"

using namespace std;

JNIEXPORT jstring JNICALL Java_com_samsung_ds_tracemon_worker_util_Decoder_decode(JNIEnv *env, jobject obj, jstring string) {
    std::string encoded = env->GetStringUTFChars(string, NULL);
    std::string decoded = base64_decode(encoded);
    std::string result;
    snappy::Uncompress(decoded.data(), decoded.size(), &result);
    std::cout << result << std::endl;
    return env->NewStringUTF(result.data());
}

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

vector<string> split_by_delimiter(string data, char delimiter) {
    istringstream iss(data);
    string buffer;
    vector<string> result;
    while (getline(iss, buffer, delimiter)) {
        result.push_back(buffer);
    }
    return result;
}
