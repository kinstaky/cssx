#include <iostream>
#include <string>

using namespace std;

string str[21];
int n;

bool legalnum(const string &s) {
	int len = s.length();
	if (len > 5) return false;
	for (int i = 0; i != len; ++i) {
		if (s[i] < '0') return false;
		if (s[i] > '9') return false;
	}
	return true;
}



string add(const string &s1, const string &s2) {
	if (legalnum(s1) && legalnum(s2)) return to_string(stoi(s1) + stoi(s2));
	return s1 + s2;
}

int N();

string S() {
	string s;
	cin >> s;
	if (s == "copy") {
		int n1, n2, n3;
		n1 = N();
		n2 = N();
		n3 = N();
		return string(str[n1], n2, n3);
	}
	else if (s == "add") {
		string s1 = S();
		string s2 = S();
		//cout << " add   " << s1 << "   " << s2 << "   res is   " << add(s1, s2) << endl;
		return add(s1, s2);
	}
	else return s;
}



int N() {
	int m;
	string s;
	cin >> s;
	if (s == "find") {
		string ss = S();
		int tn = N();
		m = str[tn].find(ss);
		if (m == string::npos) return str[tn].length();
		else return m;
	}
	else if (s == "rfind") {
		string ss = S();
		int tn = N();
		m = str[tn].rfind(ss);
		if (m == string::npos) return str[tn].length();
		else return m;
	}
	else return stoi(s);
}




int L() {
	string s;
	cin >> s;
	string ss;
	switch (s[0]) {
		case 'o':
			return 0;
		case 'i':
			ss = S();
			int n1, n2;
			n1 = N();
			n2 = N();
			//cout << " insert " << n1 << "  " << n2 << "  " << ss << endl;
			str[n1].insert(n2, ss);
			return 1;
		case 'r':
			ss = S();
			int n3;
			n3 = N();
			//cout << " reset  " << ss << "  " << n << endl;
			str[n3] = ss;
			return 1;
		case 'p':
			if (s.length() == 5) cout << str[N()] << endl;
			else {
				for (int i = 1; i <= n; ++i) cout << str[i] << endl;
			}
			return 1;
		default:
			return 1;
	}
}


int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> str[i];
	while (L());
	return 0;
}