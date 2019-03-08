#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
private:
    int *a;
public:
    int n;
    int m;
    Array2(int nn, int mm):n(nn), m(mm) {
        a = new int[n * m];
        memset(a, 0, sizeof(a));
    }
    Array2() {
        a = nullptr;
        n = m = 0;
    }
    ~Array2() {
        if (a) delete[] a;
    }
    int * operator[](int x) const{
        return a + x * m;
    }
    const Array2 & operator=(const Array2 &b) {
        if (b.n != 0 && b.m != 0) {
            if (a) delete[] a;
            a = new int [b.n * b.m];
            n = b.n;
            m = b.m;
            for (int i = 0; i != n; ++i) {
                for (int j = 0; j != m; ++j) {
                    a[i * m + j] = b[i][j];
                }
            }
        }
        else {
            if (a) delete[] a;
        }
        return *this;
    }
    int operator()(int x, int y) {
        return a[x * m + y];
    }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;
    b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
        }
    return 0;
}