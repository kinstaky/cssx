#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) {
    int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s) {
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
}
int strcmp(const char * s1,const char * s2) {
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s) {
	int len = strlen(d);
	strcpy(d+len,s);
}

class MyString {
public:
    char *str;

    MyString(const char *s) {
        if (s) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
            str[strlen(s)] = 0;
        }
        else str = nullptr;
    }

    MyString() {
        str = nullptr;
    }

    MyString(const MyString &sour) {
        char *s = sour.str;
        if (s) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
            str[strlen(s)] = 0;
        }
        else str = nullptr;
    }

    ~MyString() {
        delete[] str;
    }

    friend ostream & operator<<(ostream &os, const MyString &s) {
        if (s.str) os << s.str;
        return os;
    }

    char &operator[](int x) {
        return str[x];
    }

    const MyString &operator=(const MyString &sour) {
        if (&sour == this) return *this;
        char *s = sour.str;
        if (s) {
            if (!str) delete[] str;
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }
        else if (!str) delete[] str;
    }

    void operator+=(const char *s) {
        char *t = new char[strlen(s) + strlen(str) + 1];
        strcpy(t, str);
        strcpy(t + strlen(str), s);
        if (str) delete[] str;
        str = t;
    }

    MyString operator+(const char *s) const {
        int len = strlen(s) + strlen(str);
    	char *t = new char[len+ 1];
    	strcpy(t, str);
    	strcpy(t + strlen(str), s);
        t[len] = 0;
    	return MyString(t);
    }

    MyString operator+(const MyString &s) const {
    	return operator+(s.str);
    }

    friend MyString operator+(const char *sour, const MyString &s) {
        int len = strlen(sour) + strlen(s.str);
    	char *t = new char[len + 1];
        strcpy(t, sour);
        strcpy(t + strlen(sour), s.str);
        t[len] = 0;
        return MyString(t);
    }

    bool operator<(const MyString &s) {
    	return strcmp(str, s.str) == -1;
    }

    bool operator==(const MyString &s) {
    	return !strcmp(str, s.str);
    }

    bool operator>(const MyString &s) {
    	return strcmp(str, s.str) == 1;
    }
    MyString operator()(int x, int len) {
    	char *t = new char[len+1];
    	for (int i = 0; i != len; ++i) t[i] = str[x+i];
        t[len] = 0;
    	return MyString(t);
    }
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}