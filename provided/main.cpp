/**
Cristian Mendivil
Phi Trang
Homework 2
A program that lets a user electronically shop at a store
*/

#include<iostream>
#include "Item.h"
#include "Store.h"
#include "TextUI.h"

int main(int argc, char *argv[]) {

	if(argc == 2) { //CHeck if store file was provided
		TextUI menu;
		Store store(argv[1]); //getting store file
		std::string choice;
		while(choice != "Leave") {
			choice = menu.MainMenu(); //get input
			menu.RouteChoice(store, choice);  //Routing store given the user choice
		}
		return 0;		
	} else {
		return 0;
	}

}
