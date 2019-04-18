#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v )
			c |= (1 << bp);
		else
			c &= ~(1 << bp);
	}

private:
	struct Bit {
		char *cp;
		char v;
		int sta;
		Bit(char *aa, int xx) {
			cp = aa + xx / 8;
			v = 1<<(xx % 8);
			sta = (*cp & v) == 0 ? 0 : 1;
		}
		Bit & operator=(const int &val) {
			if (val == 1) *cp |= v;
			else *cp &= ~v;
			sta = val;
			return *this;
		}
		Bit & operator=(const Bit &b) {
			if (b.sta == 1) *cp |= v;
			else *cp &= ~v;
			sta = b.sta;
			return *this;
		}
		friend ostream & operator<<(ostream &os, const Bit &b) {
			os << b.sta;
			return os;
		}

	};

public:
	Bit  & operator[](int x) const {
		return Bit(a, x);
	}

	Bit operator[](int x) {
		return Bit(a, x);
	}


	void Print() {
		for(int i = 0;i < bitNum; ++i)
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}