#ifndef READER_SEMAPHORE_H
#define READER_SEMAPHORE_H

#include <condition_variable>
#include <cstdint>
#include <mutex>

class Semaphore final {
public:
    explicit Semaphore(const std::int32_t count);
    void Release();
    void Acquire();

private:
    std::int32_t count_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

#endif  // READER_SEMAPHORE_H
