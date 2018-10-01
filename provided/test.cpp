#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Item.h"
#include "Store.h"
#include "TextUI.h"

TEST_CASE("Sample", "[test]") {
    SECTION("wow") {
        REQUIRE(1 == 1);
    }
}
