cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(emil)
add_executable(emil main.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample-01.in DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
find_package(Threads REQUIRED)

project(tests)
add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain Threads::Threads)