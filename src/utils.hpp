#include <string>
#include <stdexcept>

namespace utils {
    int lineLength(const std::string &line);

    template <typename Stream>
    void loadFile(Stream &gStream, const std::string& fileName) {
        gStream.open(fileName.c_str(), std::ios::binary);
        if (not gStream.is_open()) {
            std::stringstream ss;
            ss << "Could not open file \"" << fileName << "\".";
            throw std::runtime_error(ss.str());
        }
    }
}