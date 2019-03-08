#include <iostream>

using namespace std;

class Apple {
private:
    static int nTotalNumber;
public:
    static void PrintTotal() {
		cout << nTotalNumber << endl;
	}
    Apple() {
        ++nTotalNumber;
    }
    ~Apple() {
        --nTotalNumber;
    }
};
int Apple::nTotalNumber = 0;

Apple Fun(const Apple & a) {
	a.PrintTotal();
	return a;
}
int main()
{
	Apple * p = new Apple[4];
	Fun(p[2]);
	Apple p1,p2;
	Apple::PrintTotal ();
	delete [] p;
	p1.PrintTotal ();
	return 0;
}