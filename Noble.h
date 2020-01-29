//Musfera Khan, N10654695, HW07 Separate Compilation 

//header file for Noble class 

#ifndef NOBLE_H
#define NOBLE_H
#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Warrior; 
	class Noble {
	private: //define private members of the class 
		std::vector<Warrior*> army;
		std::string nobleName;
	public:
		Noble(const std::string& name) ;

		friend std::ostream& operator<< (std::ostream& stream, const Noble& ANoble);
		std::string getNobleName();
		void battle(Noble& enemy);
		void hire(Warrior& AWarrior); 
		void fire(Warrior* AWarrior); 
		int armyStr() const; 
		void remove (Warrior* AWarrior);
		void display(); 
		
	};
}


#endif 
