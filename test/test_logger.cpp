#include "utility/logger.h"
using namespace zel::utility;

int main() {

    Logger::instance()->open("../log/test.log");
    Logger::instance()->setMax(10000);

    log_debug("勇士总冠军");
    log_warn("warn message");
    log_info("info message");
    log_fatal("fatal message");

    return 0;
}