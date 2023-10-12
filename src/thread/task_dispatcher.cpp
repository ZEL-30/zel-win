#include "task_dispatcher.h"

namespace zel {
namespace thread {

TaskDispatcher::TaskDispatcher() {}
TaskDispatcher::~TaskDispatcher() {}

void TaskDispatcher::init(int threads) {
    zel::utility::Singleton<ThreadPool>::instance()->create(threads);
    start();
}

void TaskDispatcher::assign(Task *task) {
    // log_debug("task dispatcher assign task");
    mutex_.lock();
    tasks_.push_back(task);
    mutex_.unlock();

    cond_.notify_one();
}

void TaskDispatcher::handle(Task *task) {
    // log_debug("task dispatcher handle task");
    ThreadPool *threadpool = zel::utility::Singleton<ThreadPool>::instance();

    if (threadpool->getIdleThreadNumbers() > 0) {
        threadpool->assign(task);
    } else {
        // mutex_.lock();
        tasks_.push_front(task);
        // mutex_.unlock();
        // log_debug("all threads are busy!");
    }
}

void TaskDispatcher::wait() {
    ThreadPool *threadpool = zel::utility::Singleton<ThreadPool>::instance();
    while (true) {
        if (tasks_.size() == 0 && threadpool->getBusyThreadNumbers() == 0 &&
            threadpool->getIdleThreadNumbers() == threadpool->getThreadNumbers()) {
            if (tasks_.size() == 0 && threadpool->getBusyThreadNumbers() == 0 &&
                threadpool->getIdleThreadNumbers() == threadpool->getThreadNumbers()) {
                if (tasks_.size() == 0 && threadpool->getBusyThreadNumbers() == 0 &&
                    threadpool->getIdleThreadNumbers() == threadpool->getThreadNumbers()) {
                    break;
                }
            }
        }
    }

    // threadpool->destroy();
    // stop();
}

void TaskDispatcher::run() {

    // sigset_t mask;
    // if (0 != sigfillset(&mask)) {
    //     // log_error("thread manager sigfillset failed!");
    //     return;
    // }
    // if (0 != pthread_sigmask(SIG_SETMASK, &mask, NULL)) {
    //     // log_error("thread manager pthread_sigmask failed!");
    //     return;
    // }
    while (true) {
        // log_debug("task list: %d", m_actions.size());
        std::unique_lock<std::mutex> lock(mutex_);
        while (tasks_.empty())
            cond_.wait(lock);

        Task *task = tasks_.front();
        tasks_.pop_front();

        handle(task);
    }
}

} // namespace thread
} // namespace zel