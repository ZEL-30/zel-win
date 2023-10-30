#include "directory.h"
#include "utility/string.h"

#include <iostream>
#include <locale>
#include <string>
#include <windows.h>

namespace zel {
namespace filesystem {

Directory::Directory(const std::string &path)
    : path_(path) {
    wpath_ = utility::String::string2wstring(path_).c_str();
}

Directory::~Directory() {}

std::string Directory::path() const { return path_; }

bool Directory::create() {
    if (exists()) {
        return true;
    }

    std::string::size_type pos = path_.find_last_of('/');
    if (pos == std::string::npos) {
        return false;
    }
    std::string dir = path_.substr(0, pos);

    if (dir.empty()) {
        return false;
    }
    Directory d(dir);
    d.create();
    if (CreateDirectoryW(wpath_.c_str(), NULL) != 0) {
        return true;
    } else {
        return false;
    }
}

void Directory::remove() {
    if (!exists()) {
        return;
    }

    std::vector<File> files = this->files(true);

    for (auto &file : files) {
        printf("file: %s\n", file.name().c_str());
        file.remove();
    }
    RemoveDirectoryW(wpath_.c_str());
}

bool Directory::copy(const std::string &dest) const {
    if (!exists()) {
        return false;
    }
    Directory d(dest);
    d.create();
    std::vector<File> files = this->files(true);
    for (auto &file : files) {
        std::string            path = file.path();
        std::string            dest = path;
        std::string::size_type pos  = dest.find(path_);
        if (pos != std::string::npos) {
            dest.replace(pos, path_.size(), dest);
        }
        file.copy(dest);
    }
    return true;
}

bool Directory::rename(const std::string &dest) {
    if (!exists()) {
        return false;
    }
    Directory d(dest);
    d.create();
    std::vector<File> files = this->files(true);
    for (auto &file : files) {
        std::string            path = file.path();
        std::string            dest = path;
        std::string::size_type pos  = dest.find(path_);
        if (pos != std::string::npos) {
            dest.replace(pos, path_.size(), dest);
        }
        file.rename(dest);
    }
    return true;
}

bool Directory::move(const std::string &dest) {
    if (!exists()) {
        return false;
    }
    Directory d(dest);
    d.create();
    std::vector<File> files = this->files(true);
    for (auto &file : files) {
        std::string            path = file.path();
        std::string            dest = path;
        std::string::size_type pos  = dest.find(path_);
        if (pos != std::string::npos) {
            dest.replace(pos, path_.size(), dest);
        }
        file.move(dest);
    }
    return true;
}

bool Directory::exists() const {

    DWORD dwAttrib = GetFileAttributes(path_.c_str());

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void Directory::clear() {
    if (!exists()) {
        return;
    }
    std::vector<File> files = this->files(true);
    for (auto &file : files) {
        file.clear();
    }
}

std::vector<File> Directory::files(bool recursive, bool full_path) const {
    std::vector<File> files;
    if (!exists()) {
        return files;
    }
    std::string path = path_;
    if (path[path.size() - 1] != '/') {
        path += '/';
    }
    std::string     search_path = path + "*.*";
    WIN32_FIND_DATA fd;
    HANDLE          hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                std::string file_path = path + fd.cFileName;
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    if (recursive) {
                        Directory         d(file_path);
                        std::vector<File> sub_files = d.files(true);
                        files.insert(files.end(), sub_files.begin(), sub_files.end());
                    }
                } else {
                    if (full_path) {
                        files.push_back(File(file_path));
                    } else {
                        files.push_back(File(fd.cFileName));
                    }
                }
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return files;
}

int Directory::count(bool recursive) const {
    int count = 0;
    if (!exists()) {
        return count;
    }
    std::string path = path_;
    if (path[path.size() - 1] != '/') {
        path += '/';
    }
    std::string     search_path = path + "*.*";
    WIN32_FIND_DATA fd;
    HANDLE          hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                std::string file_path = path + fd.cFileName;
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    if (recursive) {
                        Directory d(file_path);
                        count += d.count(true);
                    }
                } else {
                    count++;
                }
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return count;
}

int Directory::line(bool recursive) const {
    int line = 0;
    if (!exists()) {
        return line;
    }
    std::string path = path_;
    if (path[path.size() - 1] != '/') {
        path += '/';
    }
    std::string     search_path = path + "*.*";
    WIN32_FIND_DATA fd;
    HANDLE          hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                std::string file_path = path + fd.cFileName;
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    if (recursive) {
                        Directory d(file_path);
                        line += d.line(true);
                    }
                } else {
                    File file(file_path);
                    line += file.line();
                }
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return line;
}

int Directory::size(bool recursive) const {
    int size = 0;
    if (!exists()) {
        return size;
    }
    std::string path = path_;
    if (path[path.size() - 1] != '/') {
        path += '/';
    }
    std::string     search_path = path + "*.*";
    WIN32_FIND_DATA fd;
    HANDLE          hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(fd.cFileName, ".") != 0 && strcmp(fd.cFileName, "..") != 0) {
                std::string file_path = path + fd.cFileName;
                if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    if (recursive) {
                        Directory d(file_path);
                        size += d.size(true);
                    }
                } else {
                    File file(file_path);
                    size += file.size();
                }
            }
        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return size;
}

} // namespace filesystem
} // namespace zel
