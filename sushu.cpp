#include <iostream>
#include <set>

using namespace std;

const int MAX = 3161;

int main() {
	set< int > s;
	s.insert(2);
	s.insert(3);
	for (int i = 5; i <= MAX; i += 2) {
		bool sushu = true;
		for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter) {
			if (i % *iter == 0) {
				sushu = false;
				break;
			}
		}
		if (sushu) s.insert(i);
	}
	for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter) {
		cout << "sushu.insert(" << *iter << ");" << endl;
	}
}