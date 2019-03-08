#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt {
public:
    char a[210];
    CHugeInt(int n) {
        memset(a, 0, sizeof(a));
        int t = n;
        for (int i = 0; t != 0; ++i) {
            a[i] = 48 + (t % 10);
            t /= 10;
        }
        if (strlen(a) == 0) a[0] = '0';
    }

    CHugeInt(char *s) {
        memset(a, 0, sizeof(0));
        int len = strlen(s);
        for (int i = 0; i != len; ++i) {
            a[i] = s[len-i-1];
        }
    }

    CHugeInt(const CHugeInt &b) {
        memset(a, 0, sizeof(a));
        strcpy(a, b.a);
    }

    CHugeInt operator+(const CHugeInt &b) const{
        char s[210];
        memset(s, 0, sizeof(s));
        strcpy(s, a);
        int carry = 0;
        int i = 0;
        for (; a[i] != '\0' && b.a[i] != '\0'; ++i) {
            int t = a[i] + b.a[i] + carry - 96;
            carry = t / 10;
            t = t % 10;
            s[i] = t + 48;
        }
        while (b.a[i] == '\0' && a[i] != '\0') {
            int t = carry + a[i] - 48;
            carry = t / 10;
            t = t % 10;
            s[i] = t + 48;
            ++i;
        }
        while (a[i] == '\0' && b.a[i] != '\0') {
            int t = carry + b.a[i] - 48;
            carry = t / 10;
            t = t % 10;
            s[i] = t + 48;
            ++i;
        }
        if (carry) s[i] = carry + 48;
        //inverse
        int len = strlen(s);
        int half = len / 2;
        for (int j = 0; j != half; ++j) {
            char t = s[j];
            s[j] = s[len-j-1];
            s[len-j-1] = t;
        }
        CHugeInt temp(s);
        return temp;
    }

    CHugeInt operator+(int x) const {
        CHugeInt b(x);
        return this->operator+(b);
    }

    friend CHugeInt operator+(int x, const CHugeInt &b) {
        return b.operator+(x);
    }

    void operator+=(int x) {
        char b[210];
        memset(b, 0, sizeof(b));
        int t = x;
        for (int i = 0; t != 0; ++i) {
            b[i] = 48 + (t % 10);
            t /= 10;
        }
        int carry = 0;
        int i = 0;
        for (; a[i] != '\0' && b[i] != '\0'; ++i) {
            int t = a[i] + b[i] + carry - 96;
            carry = t / 10;
            t = t % 10;
            a[i] = t + 48;
        }
        while (b[i] == '\0' && a[i] != '\0') {
            int t = carry + a[i] - 48;
            carry = t / 10;
            t = t % 10;
            a[i] = t + 48;
            ++i;
        }
        while (a[i] == '\0' && b[i] != '\0') {
            int t = carry + b[i] - 48;
            carry = t / 10;
            t = t % 10;
            a[i] = t + 48;
            ++i;
        }
        if (carry) a[i] = 48 + carry;
        if (strlen(a) == 0) a[0] = '0';
    }

    const CHugeInt& operator++() {
        int carry = 1;
        for (int i = 0; carry == 1; ++i) {
            a[i] = a[i] + 1;
            if (a[i] == 58) {
                carry = 1;
                a[i] = '0';
            }
            else carry = 0;
        }
        return *this;
    }

    CHugeInt operator++(int) {
        CHugeInt temp(*this);
        int carry = 1;
        for (int i = 0; carry == 1; ++i) {
            a[i] = a[i] + 1;
            if (a[i] > '9') {
                a[i] = '0';
                carry = 1;
            }
            else carry = 0;
        }
        return temp;
    }

    friend ostream & operator<<(ostream &os, const CHugeInt &b) {
        for (int i = strlen(b.a) - 1; i >= 0; --i) os<<b.a[i];
        return os;
    }
};
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}