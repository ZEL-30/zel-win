#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <iostream>

using namespace spdlog;

void basic_logfile_example() {
    try {
        auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

        logger->error("测试错误");
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}

int main() {
    error("fmt error");

    basic_logfile_example();

    return 0;
}