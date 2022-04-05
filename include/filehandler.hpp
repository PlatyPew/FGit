#include <string>

class Filehandler {
  public:
    static std::string read(std::string filename) {
        std::ifstream in(filename);
        std::stringstream data;
        if (!in)
            throw "Cannot open file!";

        data << in.rdbuf();
        in.close();

        return data.str();
    }

    static void write(std::string filename, std::string contents) {
        std::ofstream out;
        if (!out)
            throw "Cannot open file!";
        out.open(filename);
        out << contents;
        out.close();
    }
};
