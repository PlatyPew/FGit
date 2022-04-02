cmake_minimum_required(VERSION 3.21)
set(PROJECT "fgit")

project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)
set(DMP "${PROJECT_SOURCE_DIR}/lib/dmp")
set(SHA1 "${PROJECT_SOURCE_DIR}/lib/sha1" )
set(CEREAL "${PROJECT_SOURCE_DIR}/lib/cereal/include")
set(GZIP "${PROJECT_SOURCE_DIR}/lib/gzip/include")

include_directories(${DMP} ${SHA1} ${CEREAL} ${GZIP})

add_link_options("-lz")

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(${PROJECT} src/main.cpp src/init.cpp src/commit/blob.cpp src/commit/commit.cpp src/commit/blob.cpp src/logging/log.cpp src/commit/bin.cpp src/add/add.cpp src/reset/reset.cpp)

target_precompile_headers(${PROJECT} PRIVATE "${DMP}/diff_match_patch.h" "${SHA1}/sha1.hpp")
