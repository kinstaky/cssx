#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
template <class T>
class CArray3D {
private:
	class CArray2D {
	private:
		int y;
		int z;
		T *p;
	public:
		CArray2D(T *pp, int yy, int zz): z(zz), y(yy), p(pp) {}
		T * operator[](int i) {
			return p + i * z;
		}
		operator T*() {
			return p;
		}
	};
	int x;
	int y;
	int z;
	T *p;

public:
	CArray3D(int xx, int yy, int zz): x(xx), y(yy), z(zz) {
		p = new T[x * y *z];
	}
	CArray2D operator[](int i) {
		return CArray2D(p + i * y * z, y, z);
	}

};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k)
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}
void PrintB()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k)
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));
	memset(a[1],-1 ,20*sizeof(int));
	PrintA();
	memset(a[1][1],0 ,5*sizeof(int));
	PrintA();

	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;

	return 0;
}