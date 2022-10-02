#ifndef READER_THREADPOOL_H
#define READER_THREADPOOL_H

#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "Semaphore.h"

class ThreadPool final {
public:
    explicit ThreadPool(const std::int32_t thread_count = std::thread::hardware_concurrency());

    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;
    ThreadPool(ThreadPool&& other) = delete;
    ThreadPool& operator=(ThreadPool&& other) = delete;

    ~ThreadPool();

    template <typename FunctionType>
    void Submit(FunctionType&& f) {
        queue_semaphore_.Acquire();
        std::lock_guard guard(queue_mutex_);
        work_queue_.emplace_back(std::forward<FunctionType>(f));
        cv_task_submitted_.notify_one();
    }

    void WaitForAllTasksFinished() const;

private:
    void WorkerThread();
    void JoinThreads();

private:
    bool stop_{false};
    std::int32_t busy_{0};

    std::deque<std::function<void()>> work_queue_;
    std::vector<std::thread> threads_;

    Semaphore queue_semaphore_;
    mutable std::mutex queue_mutex_;
    mutable std::condition_variable cv_task_submitted_;
    mutable std::condition_variable cv_task_finished_;
};

#endif  // READER_THREADPOOL_H
