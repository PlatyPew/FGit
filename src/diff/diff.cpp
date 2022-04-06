#include "diff.hpp"
#include "defaults.hpp"
#include "filehandler.hpp"
#include "status.hpp"

Diff::Diff(std::string path) {
    this->path = path;
    // Spaghettii woooooohoohohoo
    string cache = Defaults::fgitCaches + path;
    if (!Filehandler::exists(cache) && Filehandler::exists(path)) {
        // File was created
        if (status::checkIfBinary(path))
            this->contents = "File is Binary";
        else
            this->contents = Diff::diff("", Filehandler::read(path));
    } else if (Filehandler::exists(cache) && Filehandler::exists(path)) {
        // File was modified
        if (status::checkIfBinary(path))
            this->contents = "File is Binary";
        else
            this->contents = Diff::diff(Filehandler::read(cache), Filehandler::read(path));
    } else if (Filehandler::exists(cache) && !Filehandler::exists(path)) {
        // File was deleted
        if (status::checkIfBinary(cache))
            this->contents = "File is Binary";
        else
            this->contents = Diff::diff(Filehandler::read(cache), "");
    }
}

void Diff::print() {
    cout << "Diff: " << this->path << endl;
    cout << this->contents << endl;
}

void Diff::diff() {
    map<string, pair<bool, bool>> files = status::checkThrough();
    for (auto const& [key, value] : files) {
        Diff d(key);
        d.print();
    }
}
