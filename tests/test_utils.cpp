//
// Created by mitt on 25/11/2019.
//

#include <catch/catch.hpp>
#include <fstream>
#include "../src/utils.hpp"

TEST_CASE("Throws when file doesn't exist", "[utils][error]") {
    std::ifstream gStream;
    REQUIRE_THROWS_WITH(Utils::loadFile(gStream, "../.doesntexist"), "Could not open file \"../.doesntexist\".");
}