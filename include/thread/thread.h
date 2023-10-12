#pragma once

#include <condition_variable>
#include <mutex>

#include "task.h"

namespace zel {
namespace thread {

// 线程类
class Thread {
  public:
    Thread();
    virtual ~Thread();

    // 启动线程
    void start();

    // 等待线程结束
    void join();

    int getThreadId() const { return thread_id_; }

    // 设置线程要执行的任务
    void setTask(Task *task);

    // 获取线程要执行的任务
    Task *getTask();

  protected:
    // 线程运行的方法
    virtual void run() = 0;

    // 线程的入口函数
    static DWORD WINAPI threadFunc(LPVOID lpParameter);

  protected:
    HANDLE                  handle_;
    DWORD                   thread_id_;
    Task                   *task_;
    std::mutex              mutex_;
    std::condition_variable cond_;
};

} // namespace thread

} // namespace zel