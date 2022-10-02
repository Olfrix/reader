#ifndef READER_READER_H
#define READER_READER_H

#include <filesystem>
#include <string>
#include <fstream>
#include <cstdint>

class Reader final {
public:
    Reader(const std::filesystem::path& filename, const char delimiter);

    Reader(const Reader& other) = delete;
    Reader& operator=(const Reader& other) = delete;
    Reader(Reader&& other) = delete;
    Reader& operator=(Reader&& other) = delete;

    std::string Read();
    bool Good() const;

private:
    std::streamoff CalculateStreamSize(const std::streampos current_pos);
    void ReadFromFilestream(const std::streamoff stream_size, std::string& contents);
    static void StripNewline(std::string& contents);

private:
    std::ifstream filestream_;
    const char delimiter_;
    std::int64_t chunk_size_;
};

#endif  // READER_READER_H
