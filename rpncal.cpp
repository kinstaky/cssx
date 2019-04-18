#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>
#include <stack>


using namespace std;

priority_queue < double ,vector<double>, greater<double> > mem;
stack < double > sta;


int L() {
	char s[21];
	if (!(cin >> s)) return 0;
	while (s[0] != '=') {
		if (s[0] <= '9' && s[0] >= '0') sta.push(atof(s));
		else if (s[0] == '-' && s[1] != 0) sta.push(atof(s));
		else {
			double x, y;
			x = sta.top();
			sta.pop();
			y = sta.top();
			sta.pop();
			switch (s[0]) {
				case '+':
					sta.push(x+y);
					break;
				case '-':
					sta.push(y-x);
					break;
				case '*':
					sta.push(y*x);
					break;
				case '/':
					sta.push(y/x);
					break;
				case '^':
					sta.push(pow(y, x));
					break;
				default:
					cerr << "Error:Undefined operator." << endl;
			}
			//cout << y << " " << s[0] << " " << x << " = " << sta.top() << endl;
		}
		cin >> s;
	}
	mem.pop();
	mem.push(sta.top());
	cout << setiosflags(ios::scientific) << setprecision(6) << sta.top() << endl;
	sta.pop();
	return 1;
}


int main() {
	int n;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		double x;
		cin >> x;
		mem.push(x);
	}
	while (L() != 0);
	cout << endl;
	for (int i = 0; i != n; ++i) {
		cout << mem.top() << " ";
		mem.pop();
		if ((i+1) % 10 == 0) cout << endl;
	}
	cout << endl;
	return 0;
}