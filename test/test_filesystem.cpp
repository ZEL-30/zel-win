#include <iostream>

#include <filesystem/file.h>
#include <filesystem/directory.h>
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

    Directory dir("../test/a/b/哈哈");
    std::vector<File> files = dir.files();
    for (auto file: files) {
        printf("file: %s\n", file.name().c_str());
    }

    return 0;
}