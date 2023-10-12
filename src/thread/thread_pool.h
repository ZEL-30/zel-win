#pragma once

#include "task.h"
#include "thread.h"

#include <list>
#include <set>

namespace zel {
namespace thread {

// 线程池类
class ThreadPool {
  public:
    ThreadPool();
    ~ThreadPool();

    // 创建线程池
    void create(int threads);

    // 获取一个空闲线程
    Thread *getIdleThread();

    // 将线程移动到空闲线程列表
    void moveToIdleList(Thread *thread);

    // 将线程移动到忙碌线程列表
    void moveToBusyList(Thread *thread);

    // 获取线程数量
    int getThreadNumbers();

    // 获取空闲线程数量
    int getIdleThreadNumbers();

    // 获取忙碌线程数量
    int getBusyThreadNumbers();

    // 分配任务
    void assign(Task *task);

  private:
    int threads_; // 线程数量

    std::set<Thread *> list_idle_; // 空闲线程列表
    std::set<Thread *> list_busy_; // 忙碌线程列表

    std::mutex mutex_idle_;  // 空闲线程列表的互斥量
    std::mutex mutex_busy_;  // 忙碌线程列表的互斥量
    std::mutex mutex_tasks_; // 任务列表

    std::condition_variable cond_idle_; // 空闲线程列表的条件变量
    std::condition_variable cond_busy_; // 任务列表的条件变量
};

} // namespace thread
} // namespace zel