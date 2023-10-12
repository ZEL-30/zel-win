#include "task.h"

#include "../utility/singleton.hpp"

namespace zel {
namespace thread {

Task::Task()
    : data_(nullptr) {}
Task::Task(void *data)
    : data_(data) {}
Task::~Task() {}

void *Task::data() {
    std::unique_lock<std::mutex> lock(mutex_);
    return data_;
}

void Task::data(void *data) {
    std::unique_lock<std::mutex> lock(mutex_);
    data_ = data;
}

} // namespace thread
} // namespace zel