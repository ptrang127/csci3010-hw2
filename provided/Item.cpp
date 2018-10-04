#include <iostream>
#include <string>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <math.h>

#include "Item.h"

/** 
  Provided code for CSCI 3010, HW 2, Fall 2018
*/

/**
	Create a string with info of an item
    @param Nothing
    @return A string showing the item info
*/
std::string Item::ToString() const {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << cost_;
  std::string s = stream.str();
  return type_ + ": " + s + " - " + std::to_string(quantity_);
}

/**
	Overload the << operator to print a stringified version of item.
	@param item
    @return Stream with item info
*/
std::ostream& operator<<(std::ostream& os_lhs, const Item& i) {
  os_lhs << i.ToString();
  return os_lhs;
}
