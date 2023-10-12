#pragma once

#include <string>
#include <thread/task.h>
#include <utility/logger.h>

class WriteNum : public zel::thread::Task {
  public:
    WriteNum(int num)
        : num_(num) {}
    ~WriteNum() {}

    void run() override { log_info("num: %d thread_id: %d", num_, std::this_thread::get_id()); }

    void destroy() override { delete this; }

  private:
    int num_;
};