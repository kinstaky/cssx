#include <list>
#include <iostream>
#include <map>
#include <string>

using namespace std;

list<int> *q[10000];

int main() {
	int n;
	int x, y, z;
	cin >> n;
	for (int i = 0; i != n; ++i) {
		string s;
		cin >> s;
		switch (s[0]) {
			case 'n':
				cin >> x;
				q[x] = new list<int>;
				break;
			case 'a':
				cin >> x >> y;
				q[x]->push_back(y);
				break;
			case 'm':
				cin >> x >> y;
				q[x]->merge(*q[y]);
				break;
			case 'u':
				cin >> x;
				q[x]->sort();
				q[x]->unique();
				break;
			case 'o':
				cin >> x;
				q[x]->sort();
				for (auto it = q[x]->begin(); it != q[x]->end(); ++it) {
					cout << *it << " ";
				}
				cout << endl;
				break;
		}
	}
	return 0;
}