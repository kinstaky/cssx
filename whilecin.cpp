#include <iostream>

using namespace std;

class MyCin {
private:
	bool readpos;
public:
	MyCin() {
		readpos = true;
	}
	template < class T >
	MyCin & operator>>(T &a) {
		cin >> a;
		if (a == -1) readpos = false;
		return *this;
	}
	operator bool() {
		return readpos;
	}
};


int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}