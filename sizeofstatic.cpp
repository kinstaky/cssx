#include <iostream>

using namespace std;

class A {
private:
	int x;
	int y;
	static int num;
};


int main() {
	cout << sizeof(A) << endl;
	return 0;
}