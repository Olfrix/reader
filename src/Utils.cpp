#include "Utils.h"

namespace utils {
std::unordered_set<std::string_view> TokenizeStringIntoUniqueWords(std::string_view contents,
                                                                   const char delimiter) {
    if (contents.empty()) {
        return {};
    }

    std::unordered_set<std::string_view> unique_words;
    const auto size = static_cast<int>(contents.size());
    // Ignore possible leading delimiters
    int start = 0;
    while (contents[start] == delimiter) {
        ++start;
    }
    int index_left = start;
    int index_right = start - 1;
    bool is_consequent_delimiter = false;
    for (int i = start; i < size; ++i) {
        if (contents[i] == delimiter && is_consequent_delimiter) {
            ++index_right;
        } else if (contents[i] == delimiter) {
            index_left = index_right;
            index_right = i;
            int offset = index_left + 1;
            int length = index_right - offset;

            std::string_view word(contents.data() + offset, length);
            unique_words.insert(word);
            is_consequent_delimiter = true;
        } else {
            is_consequent_delimiter = false;
        }
    }
    const std::string_view final_word(contents.data() + index_right + 1,
                                      contents.size() - index_right - 1);
    // Case when input contains only delimiters
    if (!final_word.empty()) {
        unique_words.insert(final_word);
    }
    return unique_words;
}
}  // namespace utils