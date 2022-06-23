//
// Created by 김병곤 on 2022/06/23.
//

#ifndef TRACE_DECODE_DECODE_H
#define TRACE_DECODE_DECODE_H

#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string decode(string const &encoded, string const &write_path);

vector <string> split_by_delimiter(string data, char delimiter);

#endif //TRACE_DECODE_DECODE_H
