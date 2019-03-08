#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
private:
    char name[20];
    int year;
    int num;
    double score[4];
    double average;
public:
    void input();
    void calculate();
    void output();
};

void Student::input() {
    char str[100];
    cin.getline(str, 100);
    char *s = str;
    char *pch = strchr(s, ',');
    *pch = '\0';
    strcpy(name, s);
    s = pch + 1;
    pch = strchr(s, ',');
    *pch = '\0';
    year = atoi(s);
    s = pch + 1;
    pch = strchr(s, ',');
    *pch = '\0';
    num = atoi(s);
    s = pch + 1;
    for (int i = 0; i != 3; ++i) {
        pch = strchr(s, ',');
        *pch = '\0';
        score[i] = atof(s);
        s = pch + 1;
    }
    score[3] = atof(s);
}

void Student::calculate() {
    average = (score[0] + score[1] + score[2] + score[3]) / 4;
}


void Student::output() {
    cout<<name<<","<<year<<","<<num<<","<<average<<endl;
}

int main() {
	Student student;       // 定义类的对象
	student.input();       // 输入数据
	student.calculate();       // 计算平均成绩
	student.output();          // 输出数据
}