#include "Reader.h"

#include <cmath>
#include <iostream>

namespace {
const std::streamoff SEEK_STEP = 1;
const char NEWLINE = '\n';
// Magic number was found experimentally. Works good enough for both small
// and large files. Lowering the size of chunk leads to smaller program
// memory footprint, but slower runtime and vice-versa.
const double SIZE_DIVISOR = 7000.0;
}  // namespace

Reader::Reader(const std::filesystem::path& filename, const char delimiter)
    : filestream_{filename}, delimiter_{delimiter} {
    if (!filestream_) {
        throw std::invalid_argument("Filestream is invalid, cannot proceed reading");
    }

    const auto file_size_in_bytes = std::filesystem::file_size(filename);
    std::cout << "File size: " << file_size_in_bytes << "b, " << file_size_in_bytes / 1024 << "kB"
              << std::endl;
    chunk_size_ = std::ceil(file_size_in_bytes / SIZE_DIVISOR);
    std::cout << "Chunk size: " << chunk_size_ << "b, " << chunk_size_ / 1024 << "kB" << std::endl;
}

std::string Reader::Read() {
    if (!Good()) {
        throw std::invalid_argument("Filestream is invalid, cannot proceed reading");
    }

    auto current_pos = filestream_.tellg();
    if (current_pos == -1) {
        throw std::runtime_error("Cannot determine current position in filestream buffer");
    }

    const std::streamoff stream_size_remainder = CalculateStreamSize(current_pos);

    // Nothing left to Read
    if (filestream_.peek() == EOF) {
        filestream_.ignore();
        throw std::runtime_error("Reached the end of filestream buffer, nothing left to read");
    }

    std::string contents;
    // If there is fewer data available than requested to be Read
    if (stream_size_remainder < chunk_size_) {
        ReadFromFilestream(stream_size_remainder, contents);
        return contents;
    }

    filestream_.seekg(chunk_size_, std::istream::cur);

    // Make sure words are not divided during extraction
    int peek_next = 0;
    char next_char = 0;
    do {
        filestream_.seekg(SEEK_STEP, std::istream::cur);
        peek_next = filestream_.peek();
        if (peek_next == EOF) {
            filestream_.seekg(0, std::istream::end);
            break;
        }
        next_char = static_cast<char>(peek_next);
    } while (next_char != delimiter_);
    auto pos_with_no_divided_words = filestream_.tellg();
    filestream_.seekg(current_pos);
    const std::streamoff chunk_size_with_no_divided_words = pos_with_no_divided_words - current_pos;
    ReadFromFilestream(chunk_size_with_no_divided_words, contents);

    return contents;
}

bool Reader::Good() const { return filestream_.good(); }

std::streamoff Reader::CalculateStreamSize(const std::streampos current_pos) {
    filestream_.seekg(0, std::istream::end);
    auto end_pos = filestream_.tellg();
    filestream_.seekg(current_pos);
    return end_pos - current_pos;
}

void Reader::ReadFromFilestream(const std::streamoff stream_size, std::string& contents) {
    contents.resize(stream_size);
    filestream_.read(&contents[0], stream_size);
    StripNewline(contents);
}

void Reader::StripNewline(std::string& contents) {
    if (!contents.empty() && contents.back() == NEWLINE) {
        contents.pop_back();
    }
}