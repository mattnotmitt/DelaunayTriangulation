//int
// Created by mitt on 25/11/2019.
//
#include <iterator>
#include <string>
#include <fstream>
#include <sstream>
#include "utils.hpp"

namespace utils {
    int lineLength(const std::string &line) {
        std::istringstream iss(line);
        return std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
    }
}