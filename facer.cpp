#include <iostream>
#include <map>

using namespace std;

multimap<int, int> mp; //first is attack(key), second is id(value)

int main() {
	int n;
	cin >> n;
	mp.insert(multimap<int, int>::value_type(1000000000, 1));
	for (int i = 0; i != n; ++i) {
		int key, val;
		cin >> val >> key;
		//mp.insert(multimap<int, int>::value_type(key, val));
		auto iter = mp.lower_bound(key);
		auto iter2 = iter;
		iter2--;
		if (iter == mp.begin()) {
			cout << val << " " << iter->second << endl;
		}
		else if (iter == mp.end()) {
			cout << val << " " << iter2->second << endl;
		}
		else {
			int diff = iter->first - key;
			int diff2 = key - iter2->first;
			if (diff < diff2) {
				cout << val << " " << iter->second << endl;
			}
			else cout << val << " " << iter2->second << endl;
		}
		mp.insert(multimap<int, int>::value_type(key, val));
	}
	return 0;
}