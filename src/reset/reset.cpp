#include "reset.hpp"
#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "defaults.hpp"
#include "diff.hpp"

#include <filesystem>
#include <fstream>
#include <map>
#include <stack>
#include <string>

using std::map, std::stack, std::string, std::pair, std::vector, std::ofstream, std::cout,
    std::endl;
namespace fs = std::filesystem;

Reset::Reset(string path, stack<Blob> blobs) : path(path) {
    this->patchContents(blobs);
}

/**
 * @brief patches contents
 *
 * @param blobs: a stack of blobs in commit order
 */
void Reset::patchContents(stack<Blob> blobs) {
    while (!blobs.empty()) {
        Blob b = blobs.top();
        blobs.pop();

        if (b.getDeletion()) { // Checks if file has been deleted
            this->contents = "";
            this->deletion = true;
        } else if (b.getBinary()) { // Handles file if it's binary or not
            Bin* bi = static_cast<Bin*>(&b);
            this->contents = bi->getContents();
            this->deletion = false;
        } else { // Patch if it's normal text file
            this->contents = b.getContents(this->contents);
            this->deletion = false;
        }
    }
}

/**
 * @brief write to cache and working directory
 *
 */
void Reset::writeFiles() {
    if (this->deletion)
        return;

    ofstream out;
    out.open(Defaults::fgitCaches + this->path);
    if (!out)
        return;

    out << this->contents;
    out.close();

    fs::copy(Defaults::fgitCaches + this->path, this->path, fs::copy_options::update_existing);
}

/**
 * @brief delete files from cache and working directory
 *
 */
void Reset::clearFiles() {
    vector<string> filesClear;
    for (const auto& entry : fs::directory_iterator(Defaults::fgitCaches)) {
        string f = entry.path();
        f = f.substr(Defaults::fgitCaches.size());
        filesClear.push_back(f);
    }

    for (string f : filesClear) {
        fs::remove(Defaults::fgitCaches + f);
        fs::remove(f);
    }
}

/**
 * @brief getter for paths
 *
 * @return path of blob
 */
string Reset::getPath() {
    return this->path;
}

/**
 * @brief getter for contents
 *
 * @return patched contents
 */
string Reset::getContents() {
    return this->contents;
}

void Reset::reset() {
    reset(Commit::getHeadCommit());
}

/**
 * @brief reset the contents
 *
 * @param id: reset by id
 */
void Reset::reset(string id) {
    // Clear all files in working directory and cache
    Reset::clearFiles();

    // Update HEAD file
    ofstream out;
    out.open(Defaults::fgitHead);
    out << id;
    out.close();

    string resetId = id;

    // Calculate patches
    map<string, stack<Blob>> commits;
    Commit c;
    do {
        c.readCommit(id);
        map<string, Blob> commitBlobs = c.getBlobs();

        for (auto const& [path, blob] : commitBlobs) { // Loop through all blobs in each commit
            auto check = commits.find(path);
            if (check == commits.end()) { // If path does not exist in the map
                // Create a new stack and push current blob inside
                stack<Blob> blobStack;
                blobStack.push(blob);
                commits.insert(pair<string, stack<Blob>>(path, blobStack));
            } else {
                // Push new blob to the stack
                check->second.push(blob);
            }
        }
    } while ((id = c.getPrevId()) != "");

    // Patch contents and output to file
    for (auto const& [path, blobby] : commits) { // I have completely given up on variable names
        Reset r(path, blobby);
        r.writeFiles();
    }

    cout << "Resetted to commit " << resetId << endl;
}
