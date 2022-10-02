#include "UniqueWordsCounter.h"

#include <iostream>

#include "Utils.h"

UniqueWordsCounter::UniqueWordsCounter(const std::filesystem::path& filename, const char delimiter)
    : reader_{filename, delimiter}, delimiter_{delimiter} {}

std::int64_t UniqueWordsCounter::CountUniqueWords() {
    while (reader_.Good()) {
        try {
            std::string chunk = reader_.Read();
            thread_pool_.Submit(
                [this, chunk = std::move(chunk)]() mutable { Process(std::move(chunk)); });
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            break;
        }
    }
    thread_pool_.WaitForAllTasksFinished();

    return static_cast<std::int64_t>(result_.size());
}

void UniqueWordsCounter::Process(std::string&& contents) {
    auto tokens = utils::TokenizeStringIntoUniqueWords(contents, delimiter_);
    if (tokens.empty()) {
        return;
    }
    std::unordered_set<std::string> unique_words;
    unique_words.reserve(tokens.size());
    for (auto token : tokens) {
        unique_words.emplace(token);
    }
    Merge(std::move(unique_words));
}

void UniqueWordsCounter::Merge(std::unordered_set<std::string>&& new_words) {
    std::lock_guard guard(mutex_);
    result_.merge(std::move(new_words));
}
