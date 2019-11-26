#include "catch.hpp"
#include <iostream>


TEST_CASE("hello world") {
    SECTION("hello world") {
        REQUIRE(pow(1, 1) == 1);
    }
}
