#include "string.h"

#include <codecvt>

namespace zel {

namespace utility {

String::String() {}
String::~String() {}

std::wstring String::string2wstring(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string String::wstring2string(const std::wstring &wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

} // namespace utility

} // namespace zel