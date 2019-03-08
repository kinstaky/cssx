#include <iostream>

using namespace std;

class Complex {
private:
	double real;
	double imag;
public:
	Complex(double r, double i);
	Complex(double i);
	Complex(const Complex &c);
	~Complex();
	void print();
};

Complex::Complex(double r, double i) :real(r), imag(i) {
	cout<< "constuctor 1 construct " << real << "," << imag << endl;
}


Complex::Complex(double i) {
	real = i;
	imag = 0;
	cout << "doubleconstructor construct " << real << "," << imag << endl;
}


Complex::Complex(const Complex &c) {
	real = c.real;
	imag = c.imag;
	cout << "copy constructor construct " << real << "," << imag << endl;
}


Complex::~Complex() {
	cout<< "destructor destruct " << real << "," << imag << endl;
}



void Complex::print() {
	cout << real << "," << imag << endl;
	return;
}

int main() {
	cout << "begin main" << endl;
	Complex c1(1, 2);
	Complex c2 = 5;
	c1 = 4;
	cout << "end main" << endl;
	return 0;
}