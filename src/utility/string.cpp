#include "string.h"

#include <windows.h>

namespace zel {

namespace utility {

String::String() {}
String::~String() {}

char *String::wchar2char(const wchar_t *wchar) {
    char *m_char;
    int   len = WideCharToMultiByte(CP_ACP, 0, wchar, -1, NULL, 0, NULL, NULL);
    m_char    = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wchar, -1, m_char, len, NULL, NULL);
    m_char[len] = '\0';
    return m_char;
}

// 将 单字节char* 转换为 宽字节 wchar*
wchar_t *String::char2wchar(const char *str) {
    int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, NULL, 0);
    if (nLen == 0) {
        return NULL;
    }
    wchar_t *result = new wchar_t[nLen];
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, result, nLen);
    return result;
}

} // namespace utility

} // namespace zel