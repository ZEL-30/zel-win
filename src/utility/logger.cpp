/// @file logger.cpp
/// @author ZEL (zel1362848545@gmail.com)
/// @brief
/// @version 0.1
/// @date 2023-02-01
/// @copyright Copyright (c) 2023 ZEL

#include "logger.h"

#include <cstddef>
#include <errno.h>
#include <iostream>
#include <stdarg.h>
#include <stdexcept>
#include <string.h>
#include <time.h>

namespace zel {
namespace utility {

const char *Logger::s_level_[LOG_COUNT] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

Logger *Logger::instance_ = nullptr;

Logger::Logger()
    : level_(LOG_DEBUG)
    , max_(0)
    , len_(0) {}

Logger::Logger(const Logger &) {}

Logger::~Logger() { close(); }

Logger *Logger::instance() {
    if (instance_ == nullptr) {
        instance_ = new Logger();
        return instance_;
    }

    return instance_;
}

void Logger::open(const std::string &filename) {

    filename_ = filename;

    // 打开文件
    fout_.open(filename, std::ios::app);

    if (fout_.fail()) {
        throw std::logic_error("open file failed " + filename);
    }

    // 获取当前文件的长度
    fout_.seekp(0, std::ios::end);
    len_ = fout_.tellp();
}

bool Logger::isOpen() { return fout_.is_open(); }

void Logger::close() { fout_.close(); }

void Logger::log(Level level, const char *file, int line, const char *format, ...) {
    std::lock_guard<std::mutex> lock(mutex_); // 加锁

    if (level_ > level) return;

    if (fout_.fail()) {
        throw std::logic_error("open file failed " + filename_);
    }

    time_t     ticks = time(NULL);
    struct tm *ptm   = localtime(&ticks);
    char       timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);

    const char *fmt = "%s %s %s:%d ";
    int         len = snprintf(NULL, 0, fmt, timestamp, s_level_[level], file, line);
    if (len > 0) {
        char *buffer = new char[len + 1];
        snprintf(buffer, len + 1, fmt, timestamp, s_level_[level], file, line);
        buffer[len] = '\0';

        fout_ << buffer;

        delete[] buffer;
        len_ += len;
    }

    va_list arg_ptr;
    va_start(arg_ptr, format);
    len = vsnprintf(NULL, 0, format, arg_ptr);
    va_end(arg_ptr);
    if (len > 0) {
        char *content = new char[len + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, len + 1, format, arg_ptr);
        va_end(arg_ptr);
        content[len] = '\0';

        fout_ << content;

        delete[] content;
        len_ += len;
    }

    fout_ << "\n";
    fout_.flush();

    if (max_ > 0 && len_ >= max_) rotate();
}

void Logger::setMax(int bytes) { max_ = bytes; }

void Logger::setLevel(Level level) { level_ = level; }

void Logger::rotate() {
    close();

    time_t     ticks = time(NULL);
    struct tm *ptm   = localtime(&ticks);
    char       timestamp[32];
    memset(timestamp, 0, sizeof(timestamp));
    strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", ptm);

    std::string filename = filename_ + timestamp;
    if (rename(filename_.c_str(), filename.c_str()) != 0) {
        throw std::logic_error("rename log file failed: " + std::string(strerror(errno)));
    }

    open(filename_);
}

} // namespace utility
} // namespace zel