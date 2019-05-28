#include <iostream>

using namespace std;

void delim() {
	char c;
	while (cin.peek() == ' ') cin.get(c);
}

bool E();

bool G() {
	delim();
	char c = cin.peek();
	bool val;
	switch (c) {
		case '!':
			cin >> c;
			val = !G();
			break;
		case '(':
			cin >> c;
			val = E();
			cin >> c;
			break;
		case 'V':
			cin >> c;
			val = true;
			break;
		case 'F':
			cin >> c;
			val = false;
			break;
		default:
			cerr << "Error: Undefined G state with c = " << c << endl;
	}
	return val;
}

bool Tp(bool h) {
	delim();
	char c = cin.peek();
	if (c == '&') {
		cin >> c;
		bool val = G();
		h = Tp(h && val);
	}
	return h;
}

bool T() {
	bool val = G();
	return Tp(val);
}

bool Ep(bool h) {
	delim();
	char c = cin.peek();
	if (c == '|') {
		cin >> c;
		bool val = T();
		h = Ep(val || h);
	}
	return h;
}


bool E() {
	bool val = T();
	return Ep(val);
}


int main() {
	int iter = 0;
	while (!cin.eof()) {
		cout << "Expression " << ++iter << ": " << (E() ? "V" : "F") << endl;
		delim();
		char c;
		if (cin.peek() == '\n') cin.get(c);
		else if (!cin.eof()) cerr << "Error: Unexpected ending." << endl;
	}
	return 0;
}