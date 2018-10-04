#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <map>
#include <math.h>

#include "Item.h"
#include "Store.h"

/** 
  Provided code for CSCI 3010, HW 2, Fall 2018
*/

/**
	Returns a string with the items in the cart
    @param none
    @return string of cart contents
*/
std::string ShoppingCart::DisplayCart() {
  std::string inv = "";
  for (Item * i : in_cart_) {
    inv.append(i->ToString());
    inv.append("\n");
  }
  return inv;
}

/**
	Removes an item from the cart
    @param pointer to an item
    @return nothing
*/
void ShoppingCart::RemoveItem(Item * to_remove) {
  if (to_remove->get_quantity() > 1) {
    to_remove->DecreaseQuantity(1);
  } else {
    int target = -1;
    for (int i = 0; i < in_cart_.size(); i++) {
      if (in_cart_[i] == to_remove) {
        target = i;
        break;
      }
    }
    if (target >= 0) {
      in_cart_.erase(in_cart_.begin() + target);
    }
  }
}

/**
	Adds an item to the cart
    @param pointer to an item
    @return nothing
*/
void ShoppingCart::AddItem(Item * to_add) {
  bool added = false;
  for (int i = 0; i < in_cart_.size(); i++) {
    if (in_cart_[i]->get_id() == to_add->get_id()) {
      in_cart_[i]->IncreaseQuantity(1);
      added = true;
      break;
    }
  }
  if (!added) {
    in_cart_.push_back(to_add);
  }
}

/**
	Store contructor to initialize all private variables
    @param A filename string
    @return nothing
*/
Store::Store(std::string filename) {
  filename_ = filename;

  std::ifstream file;
  if (! file.is_open()) {
    // TODO: print a warning or something
    file.open(filename);
  }

  std::string line;
  std::string inv = "Inventory:";
  bool inventory = false;
  int id = 1;
  while (std::getline(file, line)) {
    // name is the first line
    if (name_.size() == 0) {
      name_ = line;
    }
    if (line.substr(0, inv.size()) == inv) {
      inventory = true;
    } else if (inventory) {
      std::vector<std::string> tokens;
      std::istringstream iss(line);
      std::string token;
      while(std::getline(iss, token, ',')) {
        tokens.push_back(token);
      }
      Item * i1 = new Item(id, tokens[0], std::stod(tokens[1]), std::stoi(tokens[2]));
      inventory_.push_back(i1);
      id++;
    }
  }
  file.close();

  std::cout << "Welcome to " << name_ << std::endl;

  cart_ = new ShoppingCart();
}

/**
	Create a map from int to items in inventory
    @param Nothing
    @return A map from in to items in inventory
*/
std::map<int, std::string> Store::Items() {
  std::map<int, std::string> items;
  for (Item * i : inventory_) {
    int id = i->get_id();
    std::string as_str = i->ToString();
    if (i->get_quantity() > 0) {
      items.insert({id, as_str});
    }
  }
  return items;
}

/**
	Create a map from int to items in cart
    @param Nothing
    @return A map from in to items in cart
*/
std::map<int, std::string> Store::CartItems() {
  std::map<int, std::string> items;
  for (Item * i : cart_->get_items()) {
    int id = i->get_id();
    std::string as_str = i->ToString();
    if (i->get_quantity() > 0) {
      items.insert({id, as_str});
    }
  }
  return items;
}

/**
	Add an item to cart
    @param int ID number of an item
    @return nothing
*/
void Store::AddItemToCart(int item_id) {
  Item * target;
  for (Item * i : inventory_) {
    if (i->get_id() == item_id) {
      i->DecreaseQuantity(1);
      target = i->Clone();
      break;
    }
  }
  cart_->AddItem(target);
}

/**
	Remove an item from cart
    @param int ID number of an item
    @return nothing
*/
void Store::RemoveItemFromCart(int item_id) {
  Item * target;
  for (Item * i : cart_->get_items()) {
    if (i->get_id() == item_id) {
      target = i;
      break;
    }
  }
  cart_->RemoveItem(target);
  for (Item * i : inventory_) {
    if (i->get_id() == item_id) {
      i->IncreaseQuantity(1);
    }
  }
}

/**
	Create a string with all the items in the cart
    @param Nothing
    @return A string showing items in the cart
*/
std::string Store::DisplayCart() {
  return cart_->DisplayCart();
}


/**
	Create a string with all the items in inventory
    @param Nothing
    @return A string showing items in inventory
*/
std::string Store::DisplayInventory() {
  std::string inv = "";
  for (Item * i : inventory_) {
    inv.append(i->ToString());
    inv.append("\n");
  }
  return inv;
}

/**
	Get the total cost of the items in cart and update inventory
    @param Nothing
    @return A double representing the total cost of items that were in cart
*/
double Store::Checkout() {
  
  double total = 0.0;
  for (Item * i : cart_->get_items()) {
    // tax rate for 80309
    total += (i->get_cost() * i->get_quantity()) * 1.08845;
  }

  // then we will overwrite the file
  std::ofstream ofs;
  ofs.open (filename_, std::ofstream::out);

  ofs << name_ << std::endl << std::endl;
  ofs << "Inventory:" << std::endl;
  for (Item * i : inventory_) {
    ofs << i->get_type() << "," << std::to_string(roundf(i->get_cost() * 100) / 100)
     << "," << std::to_string(i->get_quantity()) << std::endl;
  }
  ofs.close();

  this->ClearCart();

  return total;
}

/**
	Remove all items from cart
    @param Nothing
    @return Nothing
*/
void Store::ClearCart() {
  cart_->ClearCart();
}

