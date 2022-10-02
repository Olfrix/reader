#ifndef READER_UNIQUEWORDSCOUNTER_H
#define READER_UNIQUEWORDSCOUNTER_H

#include <cstdint>
#include <filesystem>
#include <mutex>
#include <string>
#include <unordered_set>

#include "Reader.h"
#include "ThreadPool.h"

class UniqueWordsCounter final {
public:
    UniqueWordsCounter(const std::filesystem::path& filename, const char delimiter);

    UniqueWordsCounter(const UniqueWordsCounter& other) = delete;
    UniqueWordsCounter& operator=(const UniqueWordsCounter& other) = delete;
    UniqueWordsCounter(UniqueWordsCounter&& other) = delete;
    UniqueWordsCounter& operator=(UniqueWordsCounter&& other) = delete;

    std::size_t CountUniqueWords();

private:
    void Process(std::string&& contents);
    void Merge(std::unordered_set<std::string>&& new_words);

private:
    Reader reader_;
    ThreadPool thread_pool_;
    const char delimiter_;

    std::unordered_set<std::string> result_;
    mutable std::mutex mutex_;
};

#endif  // READER_UNIQUEWORDSCOUNTER_H
