#include "task/write_num.hpp"

#include <thread/task_dispatcher.h>
using namespace zel::thread;

#include <utility/singleton.hpp>
using namespace zel::utility;

int main() {

    // 日志初始化
    auto logger = Logger::instance();
    logger->open("../log/thread.log");

    int thread_count = 8;      // 线程数
    int task_count   = 100000; // 任务数

    // 多线程任务分发器初始化
    auto task_dispatcher = Singleton<TaskDispatcher>::instance();
    task_dispatcher->init(thread_count);

    // 创建线程任务
    for (int i = 0; i < task_count; i++) {
        Task *task = new WriteNum(i);
        task_dispatcher->assign(task);
    }

    // 计时开始
    auto start = std::chrono::system_clock::now();

    // 等待任务完成
    task_dispatcher->wait();

    // 计时结束
    auto end = std::chrono::system_clock::now();

    printf("all task done, use time: %ld ms\n",
           std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}