#include <iostream>

using namespace std;

class A {
private:
	int i;
public:
	void hello();
};

void A::hello() {
	cout << "Hello World" << endl;
}

int main() {
	A *p = nullptr;
	p->hello();
	return 0;
}