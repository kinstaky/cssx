#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;
	}
	~MyString() { if(p) delete [] p; }
    MyString(const MyString &s) {
        const char *str1 = s.str();
        if (p == str1) return;
        if (str1) {
            p = new char[strlen(str1) + 1];
            strcpy(p, str1);
        }
        else p = NULL;
    }
    const char *str() const{
        return p;
    }
    void operator=(const char *s) {
        if (s) {
            if (s == p) return;
            else {
                if (p) delete [] p;
                p = new char[strlen(s) + 1];
                strcpy(p, s);
            }
        }
        else if (p) delete [] p;
        return;
    }
    void operator=(const MyString &s) {
        const char *str1 = s.str();
        if (str1) {
            if (str1 == p) return;
            else {
                if (p) delete[] p;
                p = new char[strlen(str1) + 1];
                strcpy(p, str1);
           }
        }
        else if (p) delete[] p;
        return;
    }
    void Copy(const char *s) {
        if (s) {
            if (s == p) return;
            else {
                if (p) delete [] p;
                p = new char[strlen(s) + 1];
                strcpy(p, s);
            }
        }
        else if (p) delete [] p;
        return;
    }
    friend ostream & operator<<(ostream &o, MyString &s) {
        o<<s.p;
        return o;
    }
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
	}
}