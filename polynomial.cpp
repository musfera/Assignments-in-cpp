//Musfera Khan, CS 1124, N10654695, HW08 Linked Lists
//cpp file 

#include "polynomial.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//default constructor- this is used when a polynomial is created without any member variables 
Polynomial::Polynomial() {
	head = new Node(0);
}

//other constructor 
Polynomial::Polynomial(const vector<int>& coef) : degree(coef.size() - 1) {
	head = new Node(coef[coef.size() - 1]);
	Node* temp = head;
	for (int i = coef.size() - 2; i >= 0; i--) {
		temp->next = new Node(coef[i]);
		temp = temp->next;
	}
}

//destructor- deletes data
Polynomial::~Polynomial() {
	if (head != nullptr) {
		Node* p = head;
		Node* n = head->next;
		while (n != nullptr){
			delete p;
			p = n;
			n = n->next;
		}
		delete p;
	}
}


//assignment operator 
Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this != &rhs) {
		if (head != nullptr) {
		Node* p = head;
		Node* n = head->next;
		while (n != nullptr){
			delete p;
			p = n;
			n = n->next;
		}
		delete p;
	}

		head = new Node(rhs.head->data);
		for (Node* n = head, *ptr = rhs.head->next; ptr != nullptr; n = n->next, ptr = ptr->next) {
			n->next = new Node(ptr->data);
		}
		degree = rhs.degree;
	}
	return *this;

}
//copy constructor- gives a polynomial the same information as another polynomial 
Polynomial::Polynomial(const Polynomial& rhs) {
	head = new Node(rhs.head->data);
	for (Node* n = head, *ptr = rhs.head->next; ptr != nullptr; n = n->next, ptr = ptr->next) {
		n->next = new Node(ptr->data);
	}
	degree = rhs.degree;
}


//overloaded += operator 
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	int diff = abs(rhs.degree - degree);
	Node* a = head;
	Node* b = rhs.head;
	while (a != nullptr && b!= nullptr){
			a->data += b->data;
			a = a->next;
			b = b->next;
	}

	return *this;
	 
}
//overloaded + operator 
Polynomial Polynomial::operator+(const Polynomial& rhs) {
	
	Polynomial temp = *this;
	temp+=rhs;
	return temp;

}


//evaluate method 
double Polynomial::evaluate(double x) {
	Node* p = head;
	double result = 0;
	for (int i = 0; i <= degree; ++i) {
		result += p->data*pow(x, i);
		p = p->next;
	}
	return result;
}
//overloaded == operator
bool Polynomial::operator==(const Polynomial& rhs) {
	if (degree != rhs.degree)
		return false;
	for (int i = 0; i < degree; i++) {
		Node* a = head;
		Node* b = rhs.head;
		if (a->data != b->data) {
			return false;
		}
		a = a->next;
		b = b->next;
	}
	return true;
}

//overloaded != operator 
bool Polynomial::operator!=(const Polynomial& rhs) {
	return !(*this == rhs);
}
//overloaded output operator as a friend 
ostream& operator<<(ostream& os, const Polynomial& p) {
	
	vector<int> numbers (p.degree+1,0); //(6,4,9)
	Node* temp = p.head;
	int d = p.degree;
	while (temp != nullptr){
		numbers[d] = temp->data;
		d--;
		temp = temp -> next;
	}
	d = p.degree;

	for(int i =0; i< numbers.size(); i++){
		if (numbers[i] != 0){
			os << numbers[i];

			if (d !=0){
				os << "x";
				if (d != 1){
					os << "^" << d;
				}
				cout << " + "; 
			}

		}

		d--;
		
	}
	os << endl;
	return os;
}




