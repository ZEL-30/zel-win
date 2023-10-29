#pragma once

#include <string>

namespace zel {
namespace filesystem {

class File {

  public:
    File(const std::string &path);
    ~File();

    /// @brief 创建文件
    void create();

    /// @brief 删除文件
    void remove();

    /// @brief 复制文件
    /// @param dest 目标文件路径
    bool copy(const std::string &dest) const;

    /// @brief 重命名文件
    /// @param dest 目标文件路径
    bool rename(const std::string &dest_filename);
    bool rename(const wchar_t *dest_filename);

    /// @brief 移动文件
    /// @param dest 目标文件路径
    bool move(const std::string &dest);

    /// @brief 判断文件是否存在
    bool exists() const;

    /// @brief 清空文件内容
    void clear();

    /// @brief 一次性读取文件所有内容
    std::string read() const;

    /// @brief 一次性写入文件
    /// @param content 写入内容
    void write(const std::string &content);

    /// @brief 获取文件名
    std::string name() const;

    /// @brief 获取文件路径
    std::string path() const;

    /// @brief 获取文件所在目录
    std::string dir() const;

    /// @brief 获取文件最后修改时间
    std::string time() const;

    /// @brief 获取文件行数
    int line() const;

    /// @brief 获取文件大小
    int size() const;

  private:
    std::string path_; // 文件路径
    std::string name_; // 文件名
    std::string dir_;  // 文件所在目录
    std::string time_; // 文件最后修改时间
    int         line_; // 文件行数
    int         size_; // 文件大小
};
} // namespace filesystem
} // namespace zel