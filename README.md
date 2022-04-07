# Fake Git

A crappier version of git

## Sub-commands

-   `init`: initialises the fgit repo
-   `status`: list status of file (created, modified or deleted)
-   `log`: shows the commit graph
-   `diff`: shows the diff between current commit and workspace (binary files will be truncated)
-   `commit`: saves a snapshot of the current workspace by specifying what files to add
-   `reset`: reverts back to a commit and updating the contents in the workspace

## Building

You can download the binaries [here](https://github.com/PlatyPew/Fake-Git/releases) (macOS and Linux only)

```sh
# Cloning the repo
git clone --recurse-submodules https://github.com/PlatyPew/Fake-Git.git

# Configure CMake
cmake -B build -DCMAKE_CXX_COMPILER=clang++

# Build Cmake
cmake --build build # You can add -j <num of cores> to speed up compilation

# Cleanup
cmake --build build --target clean
```

## Running

```sh
# Init
fgit init
```

```sh
# Status
fgit status
```

```sh
# Log
fgit log [commit id]
```

```sh
# Diff
fgit diff
```

```sh
# Commit
fgit commit <author> <message> [files]
```

```sh
# Reset
fgit reset [commit hash]
```
