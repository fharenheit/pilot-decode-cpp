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

/// Base64 Encoding + Snappy Compression된 문자열을 디코딩한다.
/// \param encoded
/// \param write_path
/// \return
string decode(string const &encoded, string const &write_path);

/// 지정한 delimiter로 CSV 구조의 토큰 배열로 구성한다.
/// \param data
/// \param delimiter
/// \return
vector <string> split_by_delimiter(string data, char delimiter);

#endif //TRACE_DECODE_DECODE_H
