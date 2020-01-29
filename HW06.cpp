//Musfera Khan CS 1124, N10654695, HW06

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Protector;

//person strength is his own
//lord strength is combined strength of army -> calls a protector from army

class Noble {//two types of nobles - Person, who have their own strength, and Lords, who hire Protectors into their army
    //each noble has a name given
protected:
    string nobleName;
    
    
public:
    Noble(string& n): nobleName(n), isAlive(true) {}
    virtual string getName() { return nobleName; }
    bool isAlive; //once this value is false, a Lord cannot hire a protector, but they CAN declare a battle
    virtual double getStrength() = 0; //pure virtual
    
    virtual void setNewStrength(double dam) = 0; //pure virtual
    virtual void battleCry() { return; } //doesnt do anything by default
    virtual void battle(Noble& enemy) {
        //x battles y
        cout << nobleName << " battles " << enemy.getName() << endl;
        /*1*/if (this ->isAlive == false && enemy.isAlive == false)
        {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        /*2*/else if (enemy.isAlive == false)//(enemy.getStrength() == 0)
        {
            cout << "He's dead, " << nobleName << endl;
        }
        else if (this->isAlive == false)//(your Strength() == 0)
        {
            cout << "He's dead, " << enemy.getName() << endl;
        }
        /*3*/else if (this->getStrength() > enemy.getStrength())
        {
            this -> battleCry();
            enemy.battleCry();
            //double dam = this->getStrength() - enemy.getStrength();
            this->setNewStrength(this->getStrength()-enemy.getStrength());
            enemy.setNewStrength(enemy.getStrength());
            //DO RATIO IN LORD'S SET STRENGTH
            //float strRatio = enemy.getStrength() / this ->getStrength();
            
            cout << nobleName << " defeats " << enemy.getName() << endl;
        }
        /*4*/else if (getStrength() < enemy.getStrength())
            
        {
            this -> battleCry();
            enemy.battleCry();
            //damage that is done to each
            //double dam = enemy.getStrength() - this->getStrength();
            //float strRatio = this->getStrength() / enemy.getStrength();
            enemy.setNewStrength(enemy.getStrength()-this->getStrength());
            this->setNewStrength(this->getStrength());
            
            //for each warrior on enemy side, set str to: str - (str * strRatio);
            //for each warrior on our side, set str to: 0;
            
            cout << enemy.getName() << " defeats " << nobleName << endl;
        }
        /*5*/else if (getStrength() == enemy.getStrength()) {
            this -> battleCry();
            enemy.battleCry();
            
            this->setNewStrength(0);
            enemy.setNewStrength(0);
            
            
            cout << "Mutual Annihilation: " << nobleName << " and " << enemy.nobleName << " die at each other's hands" << endl;
        }
    }
};


//fight on their own, have their own strength that is changed when they fight
class PersonWithStrengthToFight : public Noble {
    
public:
    PersonWithStrengthToFight(string n, double s) : Noble(n), strength(s){}
    
    double getStrength() { return strength; }
    
    void setNewStrength(double dam) {
        strength = strength - dam;
        if (strength <= 0){
            isAlive = false;
        }
        
        
    }
private:
    double strength;
};


//hire protectors into their army, and the protectors fight for them
//strength is combined strength of army
class Lord : public Noble {
    vector<Protector*> army;
    
public:
    Lord(string n) : Noble(n) {}
    void hires(Protector & AProtector);
    void fire(Protector* AProtector);
    
    double getStrength();
    
    void setNewStrength(double dam);//changes the strength based on the battle
    
    void battleCry();
};

//get hired by lords into the army, which is the vector of Protector pointers
class Protector {
protected:
    string name;
    double strength;
    Lord* lordPtr; //pointer to the lord that hired them
public:
    Protector(string& n, double s, Lord* lordPtr = nullptr) : name(n), strength(s), isAlive(true) {}
    bool isAlive;
    double getStrength() const { return strength; }
    void setNewStrength(double strRatio) {
        strength = strength - strength*strRatio;
        if (strength <= 0){
            isAlive = false;
        }
    }
    
    void getHired(Lord* x) { //x points to the lord that hired this protector
        if (lordPtr == nullptr){//not hired by anyone yet
            this->lordPtr = x; //make it point to the lord that hired it
        }
        else if (lordPtr != nullptr) { return; } //cannot get hired because a lord already hired it
    }
    void getFired() { //lordptr no longer points to the lord that hired it
        lordPtr = nullptr;
    }
    virtual void display() = 0; //this method will display the battle cries of all the different protector types
};

class Wizard : public Protector {
public:
    Wizard(string name, double strength) : Protector(name, strength) {}
    void display() {
        cout << "POOF! " << endl;
    }
};

class Warrior : public Protector {
public:
    Warrior(string name, double strength): Protector(name, strength){}
    
};

class Archer : public Warrior {
public:
    Archer(string name, double strength) : Warrior (name, strength) {}
    void display() {
        cout << "TWANG! " << name << " says: Take that in the name of my lord, " << lordPtr->getName() << endl;
    }
};

class Swordsman : public Warrior {
public:
    Swordsman (string name, double strength) : Warrior(name, strength) {}
    void display() {
        cout << "CLANG! " << name << " says: Take that in the name of my lord, " << lordPtr->getName() << endl;
    }
};

void Lord::hires(Protector & AProtector) {
    bool isAlive = true;
    if (isAlive){
    army.push_back(&AProtector);
    AProtector.getHired(this); //what does this function take in? this? //want to take in THIS lord
}
    else if (isAlive == false){ return;}
}
void Lord::fire(Protector * AProtector) {
    for (int i = 0; i < army.size(); i++) {
        if (army[i] == AProtector) {
            Protector* temp = army[army.size() - 1];
            army[i] = army[army.size() - 1];
            army.pop_back();
            army.push_back(temp);
            AProtector->getFired();
        }
    }
}

double Lord::getStrength() {
    //provides the current strength of the lord's army
    //calculates army's strength
    double strength = 0;
    for (int i = 0; i <army.size(); i++)
    {
        strength += army[i]->getStrength();
    }
    return strength;
}

void Lord::setNewStrength(double dam) {
    //ratio
    double str = getStrength();
    double temp = str - dam;
    if (temp <= 0){
        isAlive = false;
    }
    float strRatio = temp / str;
    
    for (int i = 0; i < army.size(); i++) {
        army[i]->setNewStrength(strRatio); //strength of each member of the army is modified accordingly
       
    }
    
}

void Lord::battleCry() {
    for (int i = 0; i < army.size(); i++) {
        army[i]->display(); //goes through each protector's display for their battle cry
    }
}

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
