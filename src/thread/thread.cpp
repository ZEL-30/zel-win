#include "thread.h"

#include <windows.h>

namespace zel {
namespace thread {

Thread::Thread()
    : thread_id_(0)
    , handle_(0)
    , task_(nullptr) {}

Thread::~Thread() {
    if (handle_ != 0) {
        CloseHandle(handle_);
        handle_ = 0;
    }
}

void Thread::start() {
    handle_ = CreateThread(nullptr, 0, &Thread::threadFunc, this, 0, &thread_id_);
    if (handle_ == nullptr) {
        throw std::runtime_error("Failed to create thread.");
    }
}

void Thread::join() {
    if (handle_ != 0) {
        WaitForSingleObject(handle_, INFINITE);
        CloseHandle(handle_);
        handle_ = 0;
    }
}

void Thread::setTask(Task *task) {
    mutex_.lock();
    task_ = task;
    cond_.notify_one();
    mutex_.unlock();
}

Task *Thread::getTask() {
    std::unique_lock<std::mutex> lock(mutex_);
    return task_;
}

DWORD WINAPI Thread::threadFunc(LPVOID lpParameter) {
    Thread *thread = (Thread *) lpParameter;
    thread->run();
    return 0;
}

} // namespace thread

} // namespace zel