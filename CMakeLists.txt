cmake_minimum_required (VERSION 3.2)
project (CEntropyScript)
set (CMAKE_CXX_STANDARD 23)

file (GLOB FILES
    "*.cpp"
    "include/*.h"
    "CES/*.cpp"
    "Test/*.cpp"
    "Test/*.h"
)

add_executable(CEntropyScript ${FILES})