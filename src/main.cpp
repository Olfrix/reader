#include <filesystem>
#include <iostream>

#include "UniqueWordsCounter.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Specify path to the input file as a parameter to executable";
        return -1;
    }

    const std::filesystem::path filename(argv[1]);
    std::cout << "Looking for a file: " << filename << std::endl;
    if (!std::filesystem::exists(filename)) {
        std::cerr << "File could not be found" << std::endl;
        return -1;
    }

    const char delimiter = ' ';
    UniqueWordsCounter counter{filename, delimiter};
    const auto answer = counter.CountUniqueWords();
    std::cout << "Number of unique words: " << answer << std::endl;
    return 0;
}
