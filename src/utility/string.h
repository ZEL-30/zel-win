#pragma once

#include <string>

namespace zel {

namespace utility {

class String {

  public:
    String();
    ~String();

    static std::wstring string2wstring(const std::string &wstr);

    static std::string wstring2string(const std::wstring &str);

  private:
};

} // namespace utility

} // namespace zel