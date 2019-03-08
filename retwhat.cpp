#include <iostream>

using namespace std;

class A {
public:
	int val;

	A(int i = 123) :val(i) {
        cout << "call constructor 1 and val is " << val << endl;
    }
    A& GetObj() {
        return *this;
    }
    /*A(const A &a) {
        cout << "call copy constructor and val is " << val << " while a.val is " << a.val << endl;
        val = a.val;
    }
    void operator=(const A &a) {
        cout << "call = and val is " << val << " while a.val is " << a.val <<endl;
        val = a.val;
    }*/
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}