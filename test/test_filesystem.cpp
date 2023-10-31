#include <iostream>

#include <filesystem/directory.h>
#include <filesystem/file.h>
using namespace zel::filesystem;

int main() {

    std::string path = "../test/a/b/哈哈/测试.txt";

    File file(path);
    std::cout << "文件路径: " << file.path() << "\n文件名：" << file.name() << "\n文件所在目录" << file.dir()
              << std::endl;

    // 文件是否存在
    if (file.exists()) {
        std::cout << "文件存在" << std::endl;
    } else {
        // 创建空文件
        std::cout << "文件不存在" << std::endl;
        if (file.create()) {
            std::cout << "创建文件成功" << std::endl;
        } else {
            std::cout << "创建文件失败" << std::endl;
        }
    }

    // 写入文件
    file.write("勇士总冠军\n");

    // 复制文件
    file.copy("./../test/a/b/c/2.txt");

    File file2("./../test/a/b/c/2.txt");
    std::cout << file2.read() << std::endl;

    // 删除文件
    file2.remove();

    // 重命名文件
    std::string name = "勇士队.txt";
    if (!file.rename("勇士队.txt")) {
        std::cout << "重命名失败" << std::endl;
    }

    Directory dir("../test/a/b/c");
    std::cout << "目录路径: " << dir.path() << std::endl;
    dir.cd("..");
    std::cout << "目录路径: " << dir.path() << std::endl;
    dir.cd("./c/测试");
    std::cout << "目录路径: " << dir.path() << std::endl;

    std::string dir2 = "./../test/a/b/c/测试/";
    for (int i = 0; i < 10; i++) {
        std::string path = dir2 + std::to_string(i) + ".txt";
        File        file(path);
        file.create();
        file.write("勇士总冠军\n");
    }

    auto files = dir.files();
    for (auto file : files) {
        std::cout << file.name() << std::endl;
    }

    if (!dir.copy("D:/Workspaces/C++/Visual Studio Code/zel-win/test/a/b/")) {
        std::cout << "复制失败" << std::endl;
    }

    return 0;
}