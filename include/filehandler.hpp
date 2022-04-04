#include <string>

class Filehandler {
  public:
    static std::string read(std::string filename) {
        std::ifstream in(filename);
        std::stringstream data;
        if (!in)
            return "";

        data << in.rdbuf();
        in.close();

        return data.str();
    }

    static void write(std::string filename, std::string contents) {
        std::ofstream out;
        out.open(filename);
        out << contents;
        out.close();
    }
};
