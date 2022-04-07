#include "diff.hpp"
#include "defaults.hpp"
#include "filehandler.hpp"
#include "status2.hpp"

using std::string, std::cout, std::endl, std::set;

Diff::Diff(std::string path) : Status(path) {
    if (binary) {
        this->contents = "File is Binary";
        return;
    }

    string cache = Defaults::fgitCaches + path;
    switch (flagStatus) {
    case 1:
        this->contents = Diff::diff("", Filehandler::read(path));
        break;

    case 2:
        this->contents = Diff::diff(Filehandler::read(cache), "");
        break;

    case 3:
        this->contents = Diff::diff(Filehandler::read(cache), Filehandler::read(path));
        break;
    }
}

void Diff::print() {
    cout << "Diff: " << this->path << endl;
    cout << this->contents << endl;
}

void Diff::diff() {
    set<string> files = getAllFiles();
    for (auto const& f : files) {
        Diff d(f);
        if (d.getStatusFlag())
            d.print();
    }
}
