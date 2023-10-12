#include "worker_thread.h"

#include "../utility/singleton.hpp"
#include "thread_pool.h"

namespace zel {
namespace thread {

WorkerThread::WorkerThread() {}

WorkerThread::~WorkerThread() {}

void WorkerThread::run() {
    while (true) {
        // start wait for task
        std::unique_lock<std::mutex> lock(mutex_);
        while (task_ == nullptr) {
            cond_.wait(lock);
        }

        // end wait for task
        task_->run();
        task_->destroy();
        task_ = nullptr;

        zel::utility::Singleton<ThreadPool>::instance()->moveToIdleList(this);
    }
}

void WorkerThread::cleanup(void* ptr) { printf("worker thread cleanup handler: %x", ptr); }
} // namespace thread

} // namespace zel