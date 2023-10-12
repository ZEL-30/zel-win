#pragma once

#include <mutex>
#include <windows.h>

namespace zel {
namespace thread {

// 任务类
class Task {
  public:
    Task();
    Task(void *data);
    virtual ~Task();

    void *data();
    void  data(void *data);

    // 执行任务的方法
    virtual void run() = 0;

    // 销毁任务的方法
    virtual void destroy() = 0;

  protected:
    void      *data_;
    std::mutex mutex_;
};

} // namespace thread
} // namespace zel