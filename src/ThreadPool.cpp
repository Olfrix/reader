#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(const std::int32_t thread_count) : queue_semaphore_{thread_count} {
    std::cout << "Number of threads in a pool: " << thread_count << std::endl;
    try {
        for (std::int32_t i = 0; i < thread_count; ++i) {
            threads_.emplace_back(&ThreadPool::WorkerThread, this);
        }
    } catch (...) {
        stop_ = true;
        JoinThreads();
        throw;
    }
}

ThreadPool::~ThreadPool() {
    std::unique_lock guard(queue_mutex_);
    stop_ = true;
    cv_task_submitted_.notify_all();
    guard.unlock();
    JoinThreads();
}

void ThreadPool::WaitForAllTasksFinished() const {
    std::unique_lock guard(queue_mutex_);
    cv_task_finished_.wait(guard, [this]() { return work_queue_.empty() && (busy_ == 0); });
}

void ThreadPool::WorkerThread() {
    while (true) {
        std::unique_lock guard(queue_mutex_);
        cv_task_submitted_.wait(guard, [this]() { return stop_ || !work_queue_.empty(); });

        if (!work_queue_.empty()) {
            auto task = std::move(work_queue_.front());
            work_queue_.pop_front();
            busy_++;
            guard.unlock();

            task();
            queue_semaphore_.Release();

            guard.lock();
            busy_--;
            cv_task_finished_.notify_one();
        } else if (stop_) {
            break;
        }
    }
}

void ThreadPool::JoinThreads() {
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}