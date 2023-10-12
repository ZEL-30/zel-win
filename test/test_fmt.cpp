#include <fmt/core.h>
#include <fmt/ranges.h>
using namespace fmt;

#include <map>

int main() {
    std::map<std::string, std::string> m = {{"name", "zel"}, {"age", "34"}};

    print("{}", m);

    return 0;
}