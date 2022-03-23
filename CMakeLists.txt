cmake_minimum_required(VERSION 3.21)
project(fgit)

set(CMAKE_CXX_STANDARD 20)

include_directories("${PROJECT_SOURCE_DIR}/lib/dmp/")

include_directories("${PROJECT_SOURCE_DIR}/include/")
add_executable(fgit src/main.cpp src/init.cpp src/diff/diff.cpp src/commit/blob.cpp src/commit/commit.cpp)
