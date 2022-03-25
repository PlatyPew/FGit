# Fake Git

A crappier version of git

### Building

``` sh
# Configure CMake
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++

# Build Cmake
cmake --build build --config Debug # You can add -j <num of cores> to speed up compilation

# Cleanup
cmake --build build --config Debug --target clean
```
