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
        REQUIRE(test[1]->get_quantity() == 2); //Check if repeated item was added correctly
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
		cart.RemoveItem(&item2); //remove item
		test = cart.get_items();
		REQUIRE(test.size()==1); //Check if an item was removed
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
		REQUIRE(test[0]->get_quantity()==2); //Repeated item
		cart.RemoveItem(&item1); //Remove item
		REQUIRE(test.size()==2);
		REQUIRE(test[0]->get_quantity()==1); //Check if repeated item was removed
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
		stream << std::fixed << std::setprecision(2) << test[0]->get_cost(); //float precision
		std::string s = stream.str();
        str.append(test[0]->get_type()+": "+s+" - "+std::to_string(test[0]->get_quantity())+"\n");//get item1 info
        std::stringstream stream2;
        stream2 << std::fixed << std::setprecision(2) << test[1]->get_cost();
		s = stream2.str();
        str.append(test[1]->get_type()+": "+s+" - "+std::to_string(test[1]->get_quantity())+"\n"); //get get item2 and added to what we had
        REQUIRE(cart.DisplayCart() == str); //Check if DisplayCart() returns te correct string
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
		cart.ClearCart(); //clear cart
		test = cart.get_items();
		REQUIRE(test.size() == 0); //cart should be empty
    }
    SECTION("Clearing an empty cart") {
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 0);  //cart should be empty
		cart.ClearCart();
		test = cart.get_items();
		REQUIRE(test.size() == 0);  //cart should be empty
    }
}

TEST_CASE("Getting the items from the cart", "[GetItems]") {
	ShoppingCart cart;
	Item item1(0, "item1", 2.000, 1); 
	Item item2(1, "item2", 3.000, 1); 
	
    SECTION("Getting the items from a cart with items") {
		cart.AddItem(&item1); //Add item to cart
        cart.AddItem(&item2); //Add item to cart
		std::vector<Item *> test = cart.get_items(); //Get item
		REQUIRE(test.size() == 2);  //Check if get items returns all the items
    }
    SECTION("Getting items from an empty cart") {
		std::vector<Item *> test = cart.get_items();
		REQUIRE(test.size() == 0); //Cart should be empty
    }
}

TEST_CASE("Constructing an item object", "[Item]") {
	Item item1(0, "item1", 2.000, 10); //Create item
	
    SECTION("Checking if the id is correctly stored") {
		REQUIRE(item1.get_id() == 0); //Check if id was correctly stored
    }
    SECTION("Checking if the quantity is correctly stored") {
		REQUIRE(item1.get_quantity() == 10); //Check if quantity was correctly stored
    }
    SECTION("Checking if the cost is correctly stored") {
		REQUIRE(item1.get_cost() == 2.000); //Check if cost was correctly stored
    }
    SECTION("Checking if the type is correctly stored") {
		REQUIRE(item1.get_type() == "item1"); //Check if type was correctly stored
    }
}

TEST_CASE("Increasing or decreasing a quantity", "[Increasing/Decreasing]") {
	Item item1(0, "item1", 2.000, 10);
	Item item2(1, "item2", 2.000, 0);
	
    SECTION("Increasing a quantity of an item") {
		item1.IncreaseQuantity(1); //increase quantity by 1
		REQUIRE(item1.get_quantity() == 11); //Check if quatity was increased correctly
    }
    SECTION("Decreasing a quantity of an item") {
		item1.DecreaseQuantity(1); //decrease quantity by 1
		REQUIRE(item1.get_quantity() == 9); //Check if quatity was decreased correctly
    }
    SECTION("Increasing a quantity by more than one item") {
		item1.IncreaseQuantity(3); //increase quantity by 3
		REQUIRE(item1.get_quantity() == 13);
    }
    SECTION("Decreasing a quantity by more than one item") {
		item1.DecreaseQuantity(3); //decrease quantity by 3
		REQUIRE(item1.get_quantity() == 7);
    }
    SECTION("Decreasing a quantity when quantity is 0") {
		item2.DecreaseQuantity(1);
		REQUIRE(item2.get_quantity() == 0); //Check if quantity can be negative
    }
    SECTION("Increasing a quantity when quantity is 0") {
		item2.IncreaseQuantity(1);
		REQUIRE(item2.get_quantity() == 1);
    }
}

TEST_CASE("Cloning", "[Clone]") {
	Item item1(0, "item1", 2.000, 10);
	
    SECTION("Checking if the clone has the same private variables") {
		Item* test = item1.Clone(); //clone an item
		REQUIRE(item1.get_id() == test->get_id()); //Check if id was cloned correctly
		REQUIRE(item1.get_type() == test->get_type()); //Check if type was cloned correctly
		REQUIRE(item1.get_cost() == test->get_cost()); //Check if cost was cloned correctly
		REQUIRE(test->get_quantity() == 1); //Check if the quantity of cloned item is 1
		REQUIRE(item1.get_quantity() == 10); //Check if original item did not change its quatity
    }
}

TEST_CASE("Testing the stringify", "[toString]") {
	Item item1(0, "item1", 2.000, 10);
	
    SECTION("Print item info") {
		std::string str = "";
        std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << item1.get_cost(); //float precision
		std::string s = stream.str();
        str.append(item1.get_type()+": "+s+" - "+std::to_string(item1.get_quantity())); //Get item info into string
		REQUIRE(item1.ToString() == str); //check if ToString returns correct string
    }
}
