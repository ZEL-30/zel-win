#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <windows.h>

int main() {
    std::string path = "../test/a/b/哈哈/勇士队.txt"; // 使用std::string路径

    // 将std::string转换为std::wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring                                           wpath = converter.from_bytes(path);

    if (CreateDirectoryW(wpath.c_str(), NULL) != 0) {
        std::wcout << L"创建成功" << std::endl;
    } else {
        std::wcerr << L"创建失败，错误码: " << GetLastError() << std::endl;
    }

    std::ofstream out;
    out.open(path);
    out.close();

    return 0;
}
