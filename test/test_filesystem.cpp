#include <iostream>

#include <filesystem/file.h>
using namespace zel::filesystem;

int main() {

    File file("./../test/a/b/哈哈/内盒.txt");
    std::cout << "文件路径: " << file.path() << "\n文件名：" << file.name() << "\n文件所在目录" << file.dir()
              << std::endl;

    // 文件是否存在
    if (file.exists()) {
        std::cout << "文件存在" << std::endl;
    } else {
        // 创建空文件
        file.create();
        std::cout << "文件不存在" << std::endl;
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
    if (!file.rename("勇士队.txt")) {
        std::cout << "重命名失败" << std::endl;
    }

    return 0;
}