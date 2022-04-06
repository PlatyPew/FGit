#include "diff.hpp"
#include "defaults.hpp"
#include "filehandler.hpp"
#include "status.hpp"

Diff::Diff(std::string path, bool deleted, bool binary) {
    this->path = path;

    if (binary) {
        this->contents = "File is Binary";
        return;
    }

    string cache = Defaults::fgitCaches + path;

    if (deleted) {
        this->contents = Diff::diff(Filehandler::read(cache), "");
        return;
    }

    // Spaghettii woooooohoohohoo
    if (!Filehandler::exists(cache))
        this->contents = Diff::diff("", Filehandler::read(path)); // File was created
    else
        this->contents =
            Diff::diff(Filehandler::read(cache), Filehandler::read(path)); // File was modified
}

void Diff::print() {
    cout << "Diff: " << this->path << endl;
    cout << this->contents << endl;
}

void Diff::diff() {
    map<string, pair<bool, bool>> files = status::checkThrough();
    for (auto const& [key, value] : files) {
        Diff d(key, value.first, value.second);
        d.print();
    }
}
