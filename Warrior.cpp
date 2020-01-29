//Musfera Khan, N10654695, HW07 Separate Compilation 
#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <vector>
#include <string>

//implementation file for Warrior class 
using namespace std;
namespace WarriorCraft {


	Warrior::Warrior(const string& name, int s, Noble* noblePtr) : warriorName(name), strength(s), noblePtr(noblePtr) {}
		string Warrior::getWarriorName() const { return warriorName; }
		int Warrior::getStrength() const { return strength; }
		void Warrior::setNewStrength(float strRatio) { strength = strength - strength*strRatio; }
		void Warrior::getHired(Noble* x) {
			if (noblePtr == nullptr) {//not hired by anyone yet
				this->noblePtr = x; //make it point to the lord that hired it
			}
			else if (noblePtr != nullptr) { return; }
		}
		void Warrior::getFired(Noble * x) { //lordptr no longer points to the lord that hired it
			noblePtr = nullptr;
		}
		void Warrior::runaway() {//the warrior flees from the noble'sarmy 
			cout << warriorName << " flees in terror, abandoning his lord, " << noblePtr->getNobleName() << endl;
			noblePtr->remove(this);
			noblePtr = nullptr;
		}

}