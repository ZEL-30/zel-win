#include "thread_pool.h"

#include "worker_thread.h"

namespace zel {

namespace thread {

ThreadPool::ThreadPool()
    : threads_(0) {}
ThreadPool::~ThreadPool() {}

void ThreadPool::create(int threads) {
    threads_ = threads;
    for (int i = 0; i < threads_; i++) {
        Thread *thread = new WorkerThread();
        list_idle_.insert(thread);
        thread->start();
    }
}

Thread *ThreadPool::getIdleThread() {
    std::unique_lock<std::mutex> lock(mutex_idle_);
    while (list_idle_.empty()) {
        cond_idle_.wait(lock);
    }
    return *list_idle_.begin();
}

void ThreadPool::moveToIdleList(Thread *thread) {
    mutex_idle_.lock();
    list_idle_.insert(thread);
    cond_idle_.notify_one();
    mutex_idle_.unlock();

    mutex_busy_.lock();
    std::set<Thread *>::iterator it = list_busy_.find(thread);
    if (it != list_busy_.end()) {
        list_busy_.erase(it);
    }
    cond_busy_.notify_one();
    mutex_busy_.unlock();
}

// 将线程移动到忙碌线程列表
void ThreadPool::moveToBusyList(Thread *thread) {
    std::unique_lock<std::mutex> lock_busy(mutex_busy_);
    while (list_busy_.size() >= threads_) {
        cond_busy_.wait(lock_busy);
    }
    list_busy_.insert(thread);

    mutex_idle_.lock();
    std::set<Thread *>::iterator it = list_idle_.find(thread);
    if (it != list_idle_.end()) {
        list_idle_.erase(it);
    }
    mutex_idle_.unlock();
}

int ThreadPool::getThreadNumbers() { return threads_; }

int ThreadPool::getIdleThreadNumbers() {
    std::unique_lock<std::mutex> lock(mutex_idle_);
    return list_idle_.size();
}

int ThreadPool::getBusyThreadNumbers() {
    std::unique_lock<std::mutex> lock(mutex_busy_);
    return list_busy_.size();
}

void ThreadPool::assign(Task *task) {

    if (task == NULL) {
        // log_error("assign a null task to thread pool");
        return;
    }
    // log_debug("assign a new task: %x to thread pool", task);

    Thread *thread = getIdleThread();
    if (thread != NULL) {
        moveToBusyList(thread);
        thread->setTask(task);
    } else {
        // log_error("thread is null, assign a task failed");
    }
}

} // namespace thread

} // namespace zel