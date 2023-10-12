#pragma once

#include <fstream>
#include <mutex>
#include <string>

namespace zel {
namespace utility {

#define log_debug(format, ...)                                                                                         \
    zel::utility::Logger::instance()->log(zel::utility::Logger::LOG_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_info(format, ...)                                                                                          \
    zel::utility::Logger::instance()->log(zel::utility::Logger::LOG_INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_warn(format, ...)                                                                                          \
    zel::utility::Logger::instance()->log(zel::utility::Logger::LOG_WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_error(format, ...)                                                                                         \
    zel::utility::Logger::instance()->log(zel::utility::Logger::LOG_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define log_fatal(format, ...)                                                                                         \
    zel::utility::Logger::instance()->log(zel::utility::Logger::LOG_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

class Logger {

  public:
    // 定义日志级别
    enum Level { LOG_DEBUG = 0, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL, LOG_COUNT };

    static Logger *instance();

    /// @brief 打开日志文件
    /// @param filename 日志文件名
    void open(const std::string &filename);

    /// @brief 判断日志文件是否打开
    bool isOpen();

    /// @brief 关闭日志文件
    void close();

    /// @brief 记录日志
    /// @param level 日志级别
    /// @param file 当前文件名
    /// @param line 当前文件行数
    /// @param format 类似于 printf
    /// @param ...
    void log(Level level, const char *file, int line, const char *format, ...);

    /// @brief 设置日志文件最大长度
    /// @param bytes 日志文件最大长度
    void setMax(int bytes);

    /// @brief 设置日志级别
    /// @param level 日志级别
    void setLevel(Level level);

  private:
    Logger();
    Logger(const Logger &);
    ~Logger();

    /// @brief 日志翻转
    void rotate();

  private:
    std::string        filename_; // 日志文件名
    std::ofstream      fout_;     // 文件输入流
    int                max_;      // 日志文件的最大长度
    int                len_;      // 当前文件长度
    Level              level_;    // 日志文件级别
    static const char *s_level_[LOG_COUNT];
    static Logger     *instance_;
    mutable std::mutex mutex_; // 添加互斥锁
};

} // namespace utility
} // namespace zel