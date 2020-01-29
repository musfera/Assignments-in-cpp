//Musfera Khan, N10654695, HW07 Separate Compilation 
//implementation file for Noble class 
#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
namespace WarriorCraft {

	
	Noble::Noble(const string& name): nobleName(name){}
		string Noble::getNobleName() { return nobleName; }
		void Noble::battle(Noble& enemy) {//BATTLE METHOD 
			cout << nobleName << " battles: " << enemy.nobleName << endl;

			if (armyStr() == 0 && enemy.armyStr() == 0)
			{
				cout << "Oh, NO! They're both dead! Yuck!" << endl;
			}
			else if (enemy.armyStr() == 0)
			{
				cout << "He's dead " << nobleName << endl;
			}
			else if (armyStr() > enemy.armyStr())
			{
				float strRatio = enemy.armyStr() / armyStr();
				//for each warrior on our side, set str to: str - (str * strRatio);
				//for each warrior on enemy side, set str to: 0;
				for(int i = 0; i < army.size(); i++) {

					enemy.army[i]->setNewStrength(strRatio);

				}
				for(int i = 0; i < enemy.army.size(); i++) {
					enemy.army[i]->setNewStrength(1);
				}
				cout << nobleName << " defeats " << enemy.nobleName << endl;
			}
			else if (armyStr() < enemy.armyStr())
			{
				float strRatio = armyStr() / enemy.armyStr();

				for(int i = 0; i < enemy.army.size(); i++) {
					enemy.army[i]->setNewStrength(strRatio);
				}
				for (int i = 0; i < army.size(); i++) {
					army[i]->setNewStrength(1);
				}
				//for each warrior on enemy side, set str to: str - (str * strRatio);
				//for each warrior on our side, set str to: 0;
				cout << enemy.nobleName << "defeats" << nobleName << endl;
			}
			else if (armyStr() == enemy.armyStr()) {
				for(int i = 0; i < army.size(); i++) {
					army[i]->setNewStrength(1);
				}
				for (int i = 0; i < enemy.army.size(); i++) {
					enemy.army[i]->setNewStrength(1);
				}
				
				//for each warrior on enemy side, set str to: 0;
				//for each warrior on our side, set str to: 0;
				cout << "Mutual Annihilation: " << nobleName << "and " << enemy.nobleName << " die at each other's hands" << endl;
			}
		}

		int Noble::armyStr() const {//METHOD TO CALCULATE ARMY STRENGTH 
			int total = 0;
			for (int i = 0; i < army.size(); i++)
			{
				total += army[i]->getStrength();
			}
			return total;
		}


		void Noble::hire(Warrior& AWarrior) {//HIRE METHOD- adds warrior to the Noble's army 
			army.push_back(&AWarrior);
			AWarrior.getHired(this);

		}

		void Noble::fire(Warrior* AWarrior) {//FIRE METHOD- removes Warrior from Noble's army  
			for(int i = 0; i < army.size(); i++) {
				if (army[i] == AWarrior) {
					Warrior* temp = army[army.size() - 1];
					army[army.size() - 1] = army[i];
					army[i] = temp;
					army.pop_back();
					AWarrior->getFired(this);
				}
			}
		}

		void Noble::remove(Warrior* AWarrior) {//METHOD FOR WARRIOR RUNNING AWAY  
			for (int i = 0; i < army.size(); i++) {
				if (army[i] == AWarrior) {//will this work? is a temp variable necessary 
					Warrior* temp = army[army.size() - 1];
					army[army.size() - 1] = army[i];
					army[i] = temp;
					army.pop_back();
				}
			}
		}
		void Noble::display() {//NOBLES DISPLAY METHOD 
			cout << nobleName << " has an army of " << army.size() << endl;
			for (int i = 0; i < army.size(); i++) {

				cout << army[i]->getWarriorName() << ": " << army[i]->getStrength() << endl;
			}


		}
		

		//the << operator will be overloaded to print out the nobles full name, army size, warriors and their strengths 
		std::ostream& operator<<(std::ostream& os, const Noble& n) {
			os << n.nobleName << " has an army of " << n.army.size() << endl;
			for(int i = 0; i <n.army.size(); i++) {
				os<< "	" << n.army[i]->getWarriorName();
				os<< ": ";
				os << n.army[i]->getStrength() << endl;
			}
			return os;
		}
	
}