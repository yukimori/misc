
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <utility>
#include <vector>


//   Char. number range  |        UTF-8 octet sequence
//      (hexadecimal)    |              (binary)
//   --------------------+---------------------------------------------
//   0000 0000-0000 007F | 0xxxxxxx
//   0000 0080-0000 07FF | 110xxxxx 10xxxxxx
//   0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
//   0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

bool decode_unicode_escape_to_utf8(const std::string& src, std::string& dst) {
    std::string result("");
    result.resize(src.size());

    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = '\0';
    }

    size_t result_index = 0;
    bool in_surrogate_pair = false;
    size_t surrogate_buffer = 0;
    for (size_t i = 0; i < src.size(); ++i) {
        if (i + 1 < src.size() && src[i] == '\\' && src[i+1] == 'u') {
            std::cout << "unicode" << std::endl;
            size_t octet = 0;
            {  // calculate octet
                const char* const hex = &src[i + 2];
                for (int j = 0; j < 4; ++j) {
                    octet *= 16;
                    if ('0' <= hex[j] && hex[j] <= '9') {
                        octet += static_cast<int>(hex[j] - '0');
                    } else if ('a' <= hex[j] && hex[j] <= 'f') {
                        octet += static_cast<int>(hex[j] - 'a' + 10);
                    } else if ('A' <= hex[j] && hex[j] <= 'F') {
                        octet += static_cast<int>(hex[j] - 'A' + 10);
                    } else {
                        return false;
                    }
                }
            }
            {  // fill up sequence
                char* const sequence = &result[result_index];
                if (in_surrogate_pair) {
                    if (0xdc00 <= octet && octet <= 0xdfff) {
                        // low surrogate pair
                        const size_t joined = surrogate_buffer + (octet & 0x03ff) + 0x10000;
                        sequence[0] = (static_cast<char>(joined >> 18)  &  0x3) | 0xf0;
                        sequence[1] = (static_cast<char>(joined >> 12)  & 0x3f) | 0x80;
                        sequence[2] = (static_cast<char>(joined >> 6)   & 0x3f) | 0x80;
                        sequence[3] = (static_cast<char>(joined & 0xff) & 0x3f) | 0x80;
                        result_index += 4;
                        in_surrogate_pair = false;
                    } else {
                        return false;
                    }
                } else if (octet < 0x7f) {
                    sequence[0] = static_cast<char>(octet) & 0x7f;
                    result_index += 1;
                } else if (octet < 0x7ff) {
                    sequence[0] = (static_cast<char>(octet >> 6) & 0xdf) | 0xc0;
                    sequence[1] = (static_cast<char>(octet)      & 0x3f) | 0x80;
                    result_index += 2;
                } else if (0xdbff) {
                    // high surrogate pair
                    in_surrogate_pair = true;
                    surrogate_buffer = (octet & 0x03ff) * 0x400;
                } else {
                    sequence[0] = (static_cast<char>(octet >> 12) & 0x0f) | 0xe0;
                    sequence[1] = (static_cast<char>(octet >> 6)  & 0x3f) | 0x80;
                    sequence[2] = (static_cast<char>(octet)       & 0x3f) | 0x80;
                    result_index += 3;
                }
            }
            i += 5;  // \\uXXXX is 6 bytes, so + 5 here, and + 1 in next loop
        } else {  // not unicode
            std::cout << "not unicode" << std::endl;
            if (in_surrogate_pair) {
                return false;
            }
            result[result_index] = src[i];
            result_index += 1;
        }
        // next char
    }
    result.resize(result_index);
    dst.swap(result);
    return true;
}

//
// convert utf-8 string to \uXXXX format.
// return actual length of the escaped string.
//
// size_t escapeUnicode(const char* fromStr, char* const toStr, const size_t& maxSize)
// {
//     // initialize iconv
//     iconv_t cd = iconv_open("UTF-16BE", "UTF-8");
//     // set iconv parameters
//     int arg = 1;
//     iconvctl(cd, ICONV_SET_TRANSLITERATE, &arg);
//     iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, &arg);
//     // get the size to be converted.
//     size_t fromLen = strlen(fromStr) + 1;
//     size_t afromLen = fromLen;
//     // set the size to contain the result as twice of utf-8 length
//     // (if there is all ascii, twice is needed.)
//     size_t toLen = fromLen << 1;
//     // prepare a buffer to contain the UTF-16 string.
//     char* buff = (char*)calloc(toLen, sizeof(char));
//     // because iconv() function will move the pointer, prepare a backup.
//     char* abuff = buff;
//     size_t size = iconv(cd, (const char**)&fromStr, &afromLen, &abuff, &toLen);
//     iconv_close(cd);

//     // buffer for escaped string
//     char* escBuff = (char*)calloc((fromLen << 1) + 1, sizeof(char));
//     // size of the escaped string.
//     size_t n = 0;
//     for (size_t i = 0; (buff[i] != 0 || buff[i+1] != 0); i += 2) {
//         const size_t UNI_ESC_SIZE = 6;
//         char uni[UNI_ESC_SIZE + 1] = {0};// \uXXXX
//         if (buff[i] != 0) {
//             // unicode escape format
//             sprintf(uni, "\\u%02X%02X", (unsigned char)buff[i], (unsigned char)buff[i+1]);
//             // concat escaped unicode
//             memcpy(escBuff + n, uni, UNI_ESC_SIZE);
//             n += UNI_ESC_SIZE;
//         } else {
//             // ascii
//             escBuff[n++] = buff[i + 1];
//         }
//     }
//     escBuff[n] = '\0';// terminate the string.

//     strncpy(toStr, escBuff, maxSize);

//     free(buff);
//     buff = 0;
//     free(escBuff);
//     escBuff = 0;
//     return n;
// }

std::string encode_utf8_to_unicodeescape(std::string& src) {
    std::stringstream ss;
    
    int i = 1;
    for (std::string::iterator iter = src.begin(); iter != src.end(); ++iter) {
        std::cout << "hex:" << std::hex << static_cast<uint32_t>(*iter) << std::endl;
        if (*iter <= 127) {
            ss << static_cast<char>(*iter);
            std::cout << std::hex << (static_cast<uint32_t>(*iter) & 0xff ) << std::endl;
        } else {
            ss << "\\u" << std::hex << std::setfill('0')
               << std::setw(4) << static_cast<int>(*iter);

            std::cout << /*"\\u" <<*/ std::hex << std::setw(4) << std::setfill('0')
                      << (static_cast<int>(*iter) & 0xff) << std::endl;

        }
        // std::cout << std::setw(4) << std::setfill('0') << std::endl;
        std::cout << std::dec << i << " : " << ss.str() << std::endl;
        i++;
    }

    return ss.str();
}
    
std::vector<std::pair<size_t, size_t> > make_pairs(int*xs) {
    std::vector<std::pair<size_t, size_t> > v;
    for (int* x  = xs; *x != -1; x += 2) {
        v.push_back(std::make_pair(x[0], x[1]));
    }
    return v;
}

int main() {
    int exp[] = {0, 6, 9, 6, -1};
    std::vector<std::pair<size_t, size_t> > vec = make_pairs(exp);
    for (std::vector<std::pair<size_t, size_t> >::iterator ite = vec.begin(); ite != vec.end(); ++ite) {
        std::cout << ite->first << ", " << ite->second << std::endl;
    }
    
    char *p = "\u3042\u3044\u3046\u3048\u304a";
    printf("char %s\n", p);
    
    std::string input("\u3042\u3044\u3046\u3048\u304a"), result;

    std::cout << input << std::endl;
    std::cout << input.c_str() << std::endl;
    printf("%s\n", input.c_str());
    
    bool complete = decode_unicode_escape_to_utf8(input, result);
    assert(complete);

    std::cout << result << std::endl;

    std::string test_str("あいうえお");
    std::string encoded = encode_utf8_to_unicodeescape(test_str);
    std::cout << encoded << std::endl;
}
