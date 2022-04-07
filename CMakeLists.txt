cmake_minimum_required(VERSION 3.21)
set(PROJECT "fgit")

project(${PROJECT})

set(CMAKE_CXX_STANDARD 20)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(ZLIB REQUIRED)

set(DMP "${PROJECT_SOURCE_DIR}/lib/dmp")
set(SHA1 "${PROJECT_SOURCE_DIR}/lib/sha1" )
set(CEREAL "${PROJECT_SOURCE_DIR}/lib/cereal/include")
set(GZIP "${PROJECT_SOURCE_DIR}/lib/gzip/include")

include_directories(${DMP} ${SHA1} ${CEREAL} ${GZIP})

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(${PROJECT} src/main.cpp src/init.cpp src/commit/blob.cpp src/commit/commit.cpp src/commit/blob.cpp src/logging/log.cpp  src/status/status.cpp src/commit/bin.cpp src/reset/reset.cpp src/diff/diff.cpp)

target_link_libraries(${PROJECT} ZLIB::ZLIB)
