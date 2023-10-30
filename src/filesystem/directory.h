#pragma once

#include <string>
#include <vector>

#include "file.h"

namespace zel {
namespace filesystem {

class Directory {

  public:
    Directory(const std::string &path);
    ~Directory();

    /// @brief 创建一个空目录(含子目录)
    bool create();

    /// @brief 删除目录(含子目录)
    void remove();

    /// @brief 复制目录(含子目录)
    /// @param dest 目标目录路径
    bool copy(const std::string &dest) const;

    /// @brief 重命名目录(含子目录)
    /// @param dest 目标目录路径
    bool rename(const std::string &dest);

    /// @brief 移动目录(含子目录)
    /// @param dest 目标目录路径
    bool move(const std::string &dest);

    /// @brief 判断目录是否存在
    bool exists() const;

    /// @brief 清空目录(含子目录)
    void clear();

    /// @brief 获取目录的路径
    std::string path() const;

    /// @brief 获取目录(包含子目录)下全部文件
    /// @param recursive 是否递归
    /// @param full_path 是否返回全路径
    std::vector<zel::filesystem::File> files(bool recursive = false, bool full_path = false) const;

    /// @brief 获取目录(包含子目录)下包含多少个文件
    /// @param recursive 是否递归
    int count(bool recursive = false) const;

    /// @brief 获取目录(包含子目录)下全部文件的行数
    /// @param recursive 是否递归
    int line(bool recursive = false) const;

    /// @brief 获取目录(包含子目录)下全部文件的大小
    /// @param recursive 是否递归
    int size(bool recursive = false) const;

  private:
    std::string                        path_;  // 目录路径
    std::wstring                       wpath_; // 目录路径
    std::vector<zel::filesystem::File> files_; // 目录下全部文件
    int                                count_; // 目录下文件数量
    int                                line_;  // 目录下文件行数
    int                                size_;  // 目录下文件大小
};

} // namespace filesystem
} // namespace zel