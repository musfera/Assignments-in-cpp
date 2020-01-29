//Musfera Khan, CS 1124, N10654695, HW08 Linked Lists
//header file

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>

struct Node {
	int data;
	Node* next;
	Node(int data) : data(data) { next = nullptr; }
};

class Polynomial {
	int degree;
	Node* head;
	
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
public: 
	Polynomial();
	Polynomial(const std::vector<int>& coef);
	Polynomial(const Polynomial& p);
	~Polynomial();
	
	Polynomial& operator=(const Polynomial& rhs);
	Polynomial& operator+=(const Polynomial& rhs);
	Polynomial operator+(const Polynomial& rhs);
	bool operator==(const Polynomial& rhs);
	bool operator!=(const Polynomial& rhs);
	
	double evaluate(double x);
	
	
};

#endif





 
