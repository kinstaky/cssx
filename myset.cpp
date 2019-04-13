#include <iostream>
#include <set>

using namespace std;

int main() {
	multiset< int > ms;
	set< int > ss;
	int n;
	char s[5];
	cin >> n;
	for (int i = 0; i != n; ++i) {
		int x;
		cin >> s >> x;
		switch (s[1]) {
			case 'd':
				ms.insert(x);
				ss.insert(x);
				cout << ms.count(x) << endl;
				break;
			case 'e':
				cout << ms.count(x) << endl;
				ms.erase(x);
				break;
			case 's':
				if (ss.find(x) == ss.end()) cout << "0 0" << endl;
				else cout << "1 " << ms.count(x) << endl;
				break;
		}
	}
	return 0;
}