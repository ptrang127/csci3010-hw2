#include<iostream>
#include "Item.h"
#include "Store.h"
#include "TextUI.h"

int main(int argc, char *argv[]) {

	if(argc == 2) {
		TextUI menu;
		Store store(argv[1]);
		std::string choice;
		while(choice != "Leave") {
			choice = menu.MainMenu();
			menu.RouteChoice(store, choice);
		}
		return 0;		
	} else {
		return 0;
	}

}