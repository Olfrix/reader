#include "Semaphore.h"

Semaphore::Semaphore(const std::int32_t count) : count_{count} {}

void Semaphore::Release() {
    std::lock_guard guard(mutex_);
    ++count_;
    condition_.notify_one();
}

void Semaphore::Acquire() {
    std::unique_lock guard(mutex_);
    condition_.wait(guard, [this]() { return count_ > 0; });
    --count_;
}
