cmake_minimum_required (VERSION 3.2)
project (CEntropyScript)
set (CMAKE_CXX_STANDARD 23)

file (GLOB FILES
    "main.cpp"
    "include/*.h"
    "src/*.cpp"
)

add_executable(CEntropyScript ${FILES})


find_package(Catch2 2 REQUIRED)
file (GLOB TEST_FILES
    "test.cpp"
    "include/*.h"
    "src/*.cpp"
)

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests ${TEST_FILES})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
