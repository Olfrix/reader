#ifndef READER_UTILS_H
#define READER_UTILS_H

#include <string_view>
#include <unordered_set>

namespace utils {
std::unordered_set<std::string_view> TokenizeStringIntoUniqueWords(std::string_view contents,
                                                                   const char delimiter);
}

#endif  // READER_UTILS_H
