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

TEST_CASE("Creating the store", "[store]") {
    Store store("store.txt");
}

TEST_CASE("Displaying the inventory", "[display]") {

    Store store("store.txt");

    SECTION("Displaying an empty inventory") {

    }
    SECTION("Displaying a non-empty inventory") {

    }
}

TEST_CASE("Adding an item to the cart", "[adding]") {

    SECTION("Adding to an empty cart") {

    }
    SECTION("Adding to a cart with items already in it") {

    }
    SECTION("Adding to when there are no items left") {

    }
}

TEST_CASE("Removing an item from the cart", "[removing]") {

    SECTION("Removing an item from cart") {

    }
    SECTION("Removing an item from cart with no items") {

    }
}

TEST_CASE("Displaying the contents of the cart", "[displaying]") {

    SECTION("Displaying an empty cart") {

    }
    SECTION("Displaying a non-empty cart") {

    }
}

TEST_CASE("Checking out a cart", "[checking]") {

    SECTION("Checking out an empty cart") {

    }
    SECTION("Checking out a non-empty cart") {

    }
}

TEST_CASE("Clearing a cart", "[clearing]") {

    SECTION("Clearing an empty cart") {

    }
    SECTION("Clearing a non-empty cart") {

    }
}














