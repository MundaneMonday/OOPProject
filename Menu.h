//Andrew Qin
//132244195
//aqin1@myseneca.ca
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
const int MAX_NO_OF_ITEMS = 10;
namespace sdds {
	class MenuItem {
	private:
		char* ItemInput;
		//Constructor//
		MenuItem();
		MenuItem(const char* input);
		void init(const char* input);
		//Destructor//
		~MenuItem();
		bool isEmpty() const;
		std::ostream& display(std::ostream & = std::cout) const;
		//constructor for prohibiting copies//
		MenuItem(const MenuItem& source) = delete;
		MenuItem& operator =(const MenuItem& source) = delete;
		friend class Menu;
		


};

	

	class Menu {
		int MenuIndex;
		char* Title;
		MenuItem* menuitem[MAX_NO_OF_ITEMS];
		int Indent;

	public:
		Menu();
		~Menu();
		Menu(const char* m_title, int m_indent = 0);
		//Copy Assignment Operator//
		Menu& operator=(const Menu& menu1);
		//Copy Constructor//
		Menu(const Menu& menu1);
		//Overloading the cast operator with bool
		operator int()const;
		operator bool()const;
		//isEmpty Function//
		bool isEmpty() const;
		//Display Function//
		std::ostream& display(std::ostream & = std::cout) const;
		//Add Function//
		void add(const char*);
		//Setting Indent//
		void SetIndent(int m_indent);
		Menu& operator=(const char*);
		int run() const;
		void setInput(const char* title1);
};
	
	Menu& operator<<(Menu& lhs, const char* rhs);
}




#endif