#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class sierpinski {
private:
	int n;
	sierpinski *up;
	int width;
public:
	sierpinski(int nn) :n(nn), width(pow(2, n)) {
		if (n > 1) {
			//left = new sierpinski(n-1, base);
			//right = new sierpinski(n-1, 0);
			up = new sierpinski(n-1);
		}
		else up = nullptr;
	}

	~sierpinski() {
		if (n > 1) {
			delete up;
		}
	}

	friend ostream& operator<<(ostream &os, const sierpinski &sier) {
		for (int i = 0; i != sier.width; ++i) {
			cout << sier.line(i) << endl;
		}
		return os;
	}

	string line(int m) const {
		if (n == 1) {
			if (m == 0) return string(" /\\");
			return string("/__\\");
		}
		else {
			if (m < width/2) {
				string s(width/2, ' ');
				return s + up->line(m);
			}
			else {
				int t = m - width/2;
				string s1 = up->line(t);
				string s2(lineshift(t), ' ');
				return s1 + s2 + s1;
			}
		}
	}

	int lineshift(int m) const {
		return width - up->line(m).length();
	}
};


int main() {
	int n;
	cin >> n;
	while (n) {
		cout << sierpinski(n) << endl;
		cin >> n;
	}
	return 0;
}