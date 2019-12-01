#include <string>
#include <stdexcept>
#include "Triangle.hpp"
/**
 * @file utils.hpp
 * Utility functions file
 */

/**
 * Namespace of utility functions
 */
namespace Utils {
    /**
     * Find number of parameters in file import lines
     * @param line
     * @return number of parameters in line
     */
    int lineLength(const std::string &line);
    /**
     * Opens a stream with the specified file and verifies it has been opened correctly
     * @tparam Stream Stream of type std::ifstream or std::ofstream
     * @param gStream Reference to stream to be opened
     * @param fileName Name of file for stream to be opened with
     * @throws std::runtime_error File cannot be opened
     */
    template <typename Stream>
    void loadFile(Stream &gStream, const std::string& fileName) {
        gStream.open(fileName.c_str(), std::ios::binary);
        if (not gStream.is_open()) {
            std::stringstream ss;
            ss << "Could not open file \"" << fileName << "\".";
            throw std::runtime_error(ss.str());
        }
    }
    template <typename T>
    double constantValueApprox(T func, const Triangle& triangle) {
        return triangle.area() * func(triangle.getCc().x, triangle.getCc().y);
    }
    template <typename T>
    double linearInterpolationApprox(T func, const Triangle& triangle) {
        return triangle.area() / 3;
    }
}