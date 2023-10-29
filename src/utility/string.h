#pragma once

#include <string>

namespace zel {

namespace utility {

class String {

  public:
    String();
    ~String();

    static char *wchar2char(const wchar_t *wchar);

    static wchar_t *char2wchar(const char* str);


  private:
};

} // namespace utility

} // namespace zel