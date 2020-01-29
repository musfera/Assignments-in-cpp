//Musfera Khan, N10654695, HW07 Separate Compilation 
//header file for Warrior class 

#ifndef WARRIOR_H
#define WARRIOR_H
#include<string>


namespace WarriorCraft { //warrior class is in the WarriorCraft namespace 
	class Noble; 
	class Warrior {//define private members of the class in the header file 
		int strength;
		std::string warriorName;
		Noble* noblePtr;

	public:
		Warrior(const std::string& name, int s, Noble* noblePtr = nullptr); //warriorName(name), strength(s) {}
		std::string getWarriorName() const;
		int getStrength() const; 
		void setNewStrength(float strRatio);
		void getHired(Noble* x);
		void getFired(Noble* x);
		void runaway();
	};
}


#endif 
