#include <iostream>

using namespace std;

class Sample {
public:
	int v;
    Sample(const Sample &a) {
        v = a.v + 2;
    }
    Sample(int vv = 0) :v(vv) {}
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}