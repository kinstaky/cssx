#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    Complex() {}
    Complex(const char *str) {
        char ss[20];
        strcpy(ss, str);
        char *s = ss;
        char *pch = strchr(s, '+');
        *pch = '\0';
        r = atof(s);
        s = pch + 1;
        pch = strchr(s, 'i');
        *pch = '\0';
        i = atof(s);
    }
};

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}