#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <sstream> // stringstream
#include "Item.h"
#include "Store.h"
#include "TextUI.h"

TEST_CASE("Adding an item", "[AddItem]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.00, 1); //item used in test1 and test2
	Item item2(1, "item2", 3.00, 1); //item used in test2
	
    SECTION("Adding an item to an empty cart") {
		std::vector<Item *> test = cart.get_items(); //Get items in the cart
        REQUIRE(test.size() == 0); //Cart should be empty
        cart.AddItem(&item1); //Add item to cart
        test = cart.get_items();
        REQUIRE(test.size() == 1); //Check if item1 was added correctly
    }
    SECTION("Adding an item to a cart where there are items") {
		cart.AddItem(&item1);
        std::vector<Item *> test = cart.get_items();
        REQUIRE(test.size() == 1);
        cart.AddItem(&item2);
        test = cart.get_items();
        REQUIRE(test.size() == 2); //Check if item2 was added correctly
    }
    SECTION("Adding a repeated item") {
		cart.AddItem(&item1);
        std::vector<Item *> test = cart.get_items();
        REQUIRE(test.size() == 1);
        cart.AddItem(&item2);
        test = cart.get_items();
        REQUIRE(test.size() == 2);
        cart.AddItem(&item2);
        REQUIRE(test.size() == 2);
        REQUIRE(test[0]->get_quantity() == 1);
        REQUIRE(test[1]->get_quantity() == 2);
    }
}

TEST_CASE("Removing an item", "[RemoveItem]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.00, 1);
	Item item2(1, "item2", 3.00, 1); 
	
    SECTION("Removing an item from an empty cart") {
		std::vector<Item *> test = cart.get_items(); //Get items in the cart
		REQUIRE(test.size() == 0); //Cart should be empty
        cart.RemoveItem(&item1);
        test = cart.get_items();
        REQUIRE(test.size() == 0); //Cart should be empty
    }
    SECTION("Removing an item from a cart that isn't empty") {
		cart.AddItem(&item1);
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test[0]->get_quantity()==1);
		cart.RemoveItem(&item1);
		test = cart.get_items();
		REQUIRE(test.size()==0);
		cart.AddItem(&item1);
		cart.AddItem(&item2);
		test = cart.get_items();
		REQUIRE(test.size()==2);
		cart.RemoveItem(&item2);
		test = cart.get_items();
		REQUIRE(test.size()==1);
    }
    SECTION("Removing a repeated item") {
		cart.AddItem(&item1);
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test[0]->get_quantity()==1);
		cart.RemoveItem(&item1);
		test = cart.get_items();
		REQUIRE(test.size()==0);
		cart.AddItem(&item1);
		cart.AddItem(&item2);
		test = cart.get_items();
		REQUIRE(test.size()==2);
		cart.RemoveItem(&item2);
		test = cart.get_items();
		REQUIRE(test.size()==1);
		cart.AddItem(&item1);
		cart.AddItem(&item2);
		test = cart.get_items();
		REQUIRE(test.size()==2);
		REQUIRE(test[0]->get_quantity()==2);
		cart.RemoveItem(&item1);
		REQUIRE(test.size()==2);
		REQUIRE(test[0]->get_quantity()==1);
    }
}


TEST_CASE("Displaying the contents of the cart", "[DisplayCart]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.000, 1); 
	Item item2(1, "item2", 3.000, 1); 
	
    SECTION("Displaying the cart with items in it") {
        cart.AddItem(&item1); //Add item to cart
        cart.AddItem(&item2); //Add item to cart
        std::vector<Item *> test = cart.get_items();
        std::string str = "";
        std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << test[0]->get_cost();
		std::string s = stream.str();
        str.append(test[0]->get_type()+": "+s+" - "+std::to_string(test[0]->get_quantity())+"\n");
        std::stringstream stream2;
        stream2 << std::fixed << std::setprecision(2) << test[1]->get_cost();
		s = stream2.str();
        str.append(test[1]->get_type()+": "+s+" - "+std::to_string(test[1]->get_quantity())+"\n");
        REQUIRE(cart.DisplayCart() == str); //Check if item1 was added correctly
    }
    SECTION("Displaying an empty cart") {
    }
}

TEST_CASE("Clearing the cart", "[ClearCart]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.000, 1); 
	Item item2(1, "item2", 3.000, 1); 
	
    SECTION("Clearing a cart with items in it") {
		cart.AddItem(&item1); //Add item to cart
        cart.AddItem(&item2); //Add item to cart
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 2);
		cart.ClearCart();
		test = cart.get_items();
		REQUIRE(test.size() == 0);
    }
    SECTION("Clearing an empty cart") {
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 0);
		cart.ClearCart();
		test = cart.get_items();
		REQUIRE(test.size() == 0);
    }
}

TEST_CASE("Getting the items from the cart", "[GetItems]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.000, 1); 
	Item item2(1, "item2", 3.000, 1); 
	
    SECTION("Getting the items from a cart with items") {
		cart.AddItem(&item1); //Add item to cart
        cart.AddItem(&item2); //Add item to cart
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 2);
    }
    SECTION("Getting items from an empty cart") {
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 0);
    }
}

TEST_CASE("Constructing an item object", "[Item]") {
	Item item1(0, "item1", 2.000, 10);
	
    SECTION("Checking if the id is correctly stored") {
		REQUIRE(item1.get_id() == 0);
    }
    SECTION("Checking if the quantity is correctly stored") {
		REQUIRE(item1.get_quantity() == 10);
    }
    SECTION("Checking if the cost is correctly stored") {
		REQUIRE(item1.get_cost() == 2.000);
    }
    SECTION("Checking if the type is correctly stored") {
		REQUIRE(item1.get_type() == "item1");
    }
}

TEST_CASE("Increasing or decreasing a quantity", "[Increasing/Decreasing]") {
	Item item1(0, "item1", 2.000, 10);
	Item item2(1, "item2", 2.000, 0);
	
    SECTION("Increasing a quantity of an item") {
		item1.IncreaseQuantity(1);
		REQUIRE(item1.get_quantity() == 11);
    }
    SECTION("Decreasing a quantity of an item") {
		item1.DecreaseQuantity(1);
		REQUIRE(item1.get_quantity() == 9);
    }
    SECTION("Increasing a quantity by more than one item") {
		item1.IncreaseQuantity(3);
		REQUIRE(item1.get_quantity() == 13);
    }
    SECTION("Decreasing a quantity by more than one item") {
		item1.DecreaseQuantity(3);
		REQUIRE(item1.get_quantity() == 7);
    }
    SECTION("Decreasing a quantity when quantity is 0") {
		item2.DecreaseQuantity(1);
		REQUIRE(item2.get_quantity() == 0);
    }
    SECTION("Increasing a quantity when quantity is 0") {
		item2.IncreaseQuantity(1);
		REQUIRE(item2.get_quantity() == 1);
    }
}

TEST_CASE("Cloning", "[Clone]") {
	Item item1(0, "item1", 2.000, 10);
	
    SECTION("Checking if the clone has the same private variables") {
		Item* test = item1.Clone();
		REQUIRE(item1.get_id() == test->get_id());
		REQUIRE(item1.get_type() == test->get_type());
		REQUIRE(item1.get_cost() == test->get_cost());
		REQUIRE(test->get_quantity() == 1);
		REQUIRE(item1.get_quantity() == 10);
    }
}

TEST_CASE("Testing the stringify", "[toString]") {
	Item item1(0, "item1", 2.000, 10);
	
    SECTION("Print item info") {
		std::string str = "";
        std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << item1.get_cost();
		std::string s = stream.str();
        str.append(item1.get_type()+": "+s+" - "+std::to_string(item1.get_quantity()));
		REQUIRE(item1.ToString() == str);
    }
}
