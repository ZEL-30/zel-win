#pragma once

#include "thread.h"

namespace zel {
namespace thread {

// 工作线程类
class WorkerThread : public Thread {
  public:
    WorkerThread();
    virtual ~WorkerThread();

    // 重写线程运行的方法
    virtual void run();

    void cleanup(void *ptr);
};

} // namespace thread
} // namespace zel