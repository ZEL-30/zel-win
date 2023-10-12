#pragma once

#include "../utility/singleton.hpp"
#include "task.h"
#include "thread.h"
#include "thread_pool.h"

#include <list>

namespace zel {
namespace thread {

// 任务调度器类
class TaskDispatcher : Thread {
  public:
    TaskDispatcher();
    virtual ~TaskDispatcher();

    void init(int threads);

    void assign(Task *task);

    void wait();

  protected:
    void handle(Task *task);

    void run();

  protected:
    std::list<Task *> tasks_;

    std::mutex              mutex_;
    std::condition_variable cond_;
};

} // namespace thread

} // namespace zel