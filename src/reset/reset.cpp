#include "reset.hpp"
#include "bin.hpp"
#include "blob.hpp"
#include "commit.hpp"
#include "diff.hpp"

#include <map>
#include <stack>
#include <string>

using std::stack, std::string;

Reset::Reset(string path, stack<Blob> blobs) {
    this->path = path;
    this->patchContents(blobs);
}

void Reset::patchContents(stack<Blob> blobs) {
    while (!blobs.empty()) {
        Blob b = blobs.top();
        blobs.pop();

        // Handles file if it's binary or not
        if (b.getBinary()) {
            Bin* bi = (Bin*)(&b);
            this->contents = bi->getContents();
        } else {
            // Patch if it's normal text file
            this->contents = b.getContents(this->contents);
        }
    }
}
