cmake_minimum_required(VERSION 3.21)

project(reader LANGUAGES CXX)

set(TARGET ${PROJECT_NAME})
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(${TARGET}
                src/main.cpp
                src/Semaphore.cpp
                src/Semaphore.h
                src/ThreadPool.cpp
                src/ThreadPool.h
                src/Reader.cpp
                src/Reader.h
                src/UniqueWordsCounter.cpp
                src/UniqueWordsCounter.h
                src/Utils.cpp
                src/Utils.h)

target_compile_options(${TARGET}
                        PRIVATE
                        -Wall -Wextra -Wpedantic
                        $<$<CONFIG:DEBUG>:-Og>)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(${TARGET} PRIVATE Threads::Threads)

enable_testing()

add_executable(
        UtilsTest
        src/Utils.cpp
        test/UtilsTest.cpp)
target_link_libraries(
        UtilsTest
        GTest::gtest_main
)
target_include_directories(UtilsTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(UtilsTest)