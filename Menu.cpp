//Andrew Qin
//132244195
//aqin1@myseneca.ca
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"

using namespace sdds;

namespace sdds {
	MenuItem::MenuItem() {
		ItemInput = nullptr;

	}
	MenuItem::MenuItem(const char* input) {
		init(input);
	}
	void MenuItem::init(const char* input) {
		if (ItemInput != nullptr) {
			delete[] ItemInput;
			ItemInput = nullptr;
		}
		if (input != nullptr) {
			ItemInput = new char[strlen(input) + 1];
			strcpy(ItemInput, input);
		}
		else {

			ItemInput = nullptr;
		}


	}

	//Destructor
	MenuItem::~MenuItem() {
		if (ItemInput != nullptr) {
			delete[] ItemInput;
			ItemInput = nullptr;
		}
	}
	bool MenuItem::isEmpty() const {
		if (ItemInput == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	std::ostream& MenuItem::display(std::ostream& os) const {
		if (!(isEmpty())) {
			os << ItemInput << std::endl;
		}
		return os;
	}

	Menu::Menu():menuitem() {
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

			menuitem[i] = nullptr;
		}
		MenuIndex = 0;
		Title = nullptr;

		

		Indent = 0;
	};
	Menu::~Menu() {
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
			if (menuitem != nullptr) {
				delete menuitem[i];
				menuitem[i] = nullptr;
			}
			
		}
		
		
		if(Title != nullptr){
			delete[] Title;
			Title = nullptr;
		}
	};

void Menu::SetIndent(int m_indent){

Indent = m_indent;
}
	Menu::Menu(const char* m_title, int m_indent) {
		MenuIndex = 0;
		Title = nullptr;
		Indent = 0;

		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

			menuitem[i] = nullptr;

		}
		if (m_title[0] == '\0' || m_title == nullptr) {
			*this = Menu();

		}
		else {

			setInput(m_title);
			Indent = m_indent;

		}
	};
	//Copy Assignment Operator//
	Menu& Menu::operator=(const Menu& menu1) {
		if (this != &menu1) {
			MenuIndex = menu1.MenuIndex;
			Indent = menu1.Indent;
			if (Title != nullptr) {
				delete[] Title;
				Title = nullptr;
			}

			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				if (menuitem[i] != nullptr) {
					delete menuitem[i];
					menuitem[i] = nullptr;
				}
			}

			if (menu1.Title != nullptr) {
				setInput(menu1.Title);
			}
			else {
				Title = nullptr;
			}

			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

				if (menu1.menuitem[i] != nullptr) {
					menuitem[i] = new MenuItem;
					menuitem[i]->ItemInput = new char[strlen(menu1.menuitem[i]->ItemInput)+1];
					strcpy(menuitem[i]->ItemInput,menu1.menuitem[i]->ItemInput);



				}
				else {
					menuitem[i] = nullptr;



				}

			}
		}
		return *this;


	};
	//Copy Constructor//
	Menu::Menu(const Menu& menu1) : MenuIndex(menu1.MenuIndex), Title(menu1.Title),menuitem(),Indent(menu1.Indent) {
		
		
		MenuIndex = menu1.MenuIndex;
		Indent = menu1.Indent;
		if (menu1.Title != nullptr) {
			setInput(menu1.Title);
		}
		else {
			Title = nullptr;
		}
		for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

			if (menu1.menuitem[i] != nullptr) {


				menuitem[i] = new MenuItem;
				menuitem[i]->ItemInput = new char[strlen(menu1.menuitem[i]->ItemInput)+1];
				strcpy(menuitem[i]->ItemInput,menu1.menuitem[i]->ItemInput);



			}
			else {
				menuitem[i] = nullptr;



			}

		}
	};

	
	//Overloading the cast operator with bool
	Menu::operator int()const {
		return run();
	};
	Menu::operator bool()const {
		if (Title != nullptr) {
		
			
			return true;
		}
		else {
			return false;
		}

	};
	//isEmpty Function//
	bool Menu::isEmpty() const {
		if (Title == nullptr) {
			return true;
		}
		else {
			return false;
		}
	};
	//Display Function//
	std::ostream& Menu::display(std::ostream& os) const {
		if (isEmpty()) {
			os << "Invalid Menu!" << std::endl;
		}
		else if (menuitem[0] == nullptr) {
			for (int i = 0; i < Indent; i++) {
				os << "    ";
			}
			os << Title << std::endl;
			os << "No Items to display!" << std::endl;

		}
		else {
			for (int i = 0; i < Indent; i++) {
				os << "    ";
			}
			os << Title << std::endl;
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				if (menuitem[i] != nullptr) {
					for (int i = 0; i < Indent; i++) {
						os << "    ";
					}
					os << i + 1 << '-' << ' ';
					menuitem[i]->display(os); //Displaying MenuItem


				}
				else {
					break;
				}

			}


			for (int i = 0; i < Indent; i++) {
				os << "    ";
			}
			std::cout << "> ";
		}

		return os;
	};

	//Assigning Menu Object to a Constant Character Pointer
	Menu& Menu::operator=(const char* title) {
		if (Title != nullptr) {
			delete[] Title;
			Title = nullptr;
		}
		if (title == nullptr) {
			*this = Menu();
		}
		else {
			Title = new char[strlen(title) + 1];
			strcpy(Title, title);
		}
		return *this;
	};
	//Add Function//
	void Menu::add(const char* input) {

		if (input == nullptr) {
			MenuIndex = 0;
			
			Indent = 0;
		
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				delete menuitem[i];
			}
			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {
				menuitem[i] = nullptr;
			}
			
			
			
			
			if (Title != nullptr) {
				delete[] Title;
				Title = nullptr;
			}
		
		

		}
		else {

			for (int i = 0; i < MAX_NO_OF_ITEMS; i++) {

				if (menuitem[i] == nullptr) {
					menuitem[i] = new MenuItem;
					menuitem[i]->init(input);
					MenuIndex = i;

					break;
				}




			}

		}
	};

	int Menu::run() const {
		Menu::display();
		int number = 0;
		if (menuitem[0] != nullptr) {

			while (!(std::cin >> number) || number > MenuIndex + 1 || number <= 0) {
				if (!(std::cin.good())) {

					std::cout << "Invalid Integer, try again: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');
				}
				else if (number > MenuIndex + 1 || number <= 0) {

					std::cout << "Invalid selection, try again: ";
					std::cin.clear();
					std::cin.ignore(1000, '\n');

				}


			};
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		return number;

	};
	void Menu::setInput(const char* title1) {

		Title = new char[strlen(title1) + 1];
		strcpy(Title, title1);
	};


	Menu& operator<<(Menu& lhs, const char* rhs) {
		if (lhs.isEmpty()) {

		}
		else {

			lhs.add(rhs);
		}
		return lhs;
	};


}