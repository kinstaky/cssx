#include <iostream>
#include <map>

using namespace std;


map< int, int > mp;					//first s attack(key), second is id(val)

int main() {
	int n;
	cin >> n;
	mp.insert(make_pair(1000000000, 1));
	for (int i = 0; i != n; ++i) {
		int val, key;
		cin >> val >> key;
		if (mp.find(key) != mp.end()) {
			cout << val << " " << mp[key] << endl;
			if (val < mp[key]) mp[key] = val;
		}
		else {
			auto iter1 = mp.lower_bound(key);
			auto iter2 = iter1;
			if (iter1 == mp.begin()) {
				cout << val << " " << iter1->second << endl;
			}
			else if (iter1 == mp.end()) {
				--iter1;
				cout << val << " " << iter1->second << endl;
			}
			else {
				iter2--;
				int diff1 = iter1->first - key;
				int diff2 = key - iter2->first;
				int minid = iter1->second < iter2->second ? iter1->second : iter2->second;
				if (diff1 == diff2) cout << val << " " << minid << endl;
				else if (diff1 < diff2) cout << val << " " << iter1->second << endl;
				else cout << val << " " << iter2->second << endl;
			}
			mp.insert(make_pair(key, val));
		}
	}
	return 0;
}