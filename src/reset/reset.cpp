#include "reset.hpp"
#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "diff.hpp"

#include <map>
#include <stack>
#include <string>

using std::map, std::stack, std::string, std::pair;

Reset::Reset(string path, stack<Blob> blobs) {
    this->path = path;
    this->patchContents(blobs);
}

void Reset::patchContents(stack<Blob> blobs) {
    while (!blobs.empty()) {
        Blob b = blobs.top();
        blobs.pop();

        if (b.getDeletion()) { // Checks if file has been deleted
            this->contents = "";
        } else if (b.getBinary()) { // Handles file if it's binary or not
            Bin* bi = (Bin*)(&b);
            this->contents = bi->getContents();
        } else { // Patch if it's normal text file
            this->contents = b.getContents(this->contents);
        }
    }
}

string Reset::getPath() {
    return this->path;
}

string Reset::getContents() {
    return this->contents;
}

void Reset::reset(string id) {
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

    for (auto const& [path, blobby] : commits) { // I have completely given up on variable names
        Reset r(path, blobby);
    }
}
