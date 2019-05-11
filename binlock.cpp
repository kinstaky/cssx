#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
	string s;
	cin >> s;
	bitset<30> lock(s);
	cin >> s;
	int len = s.length();
	lock ^= bitset<30>(s);

	int min = 100;
	bitset<30> lim = (1 << len) - 1;
	for (int i = 0; i != (1 << len); ++i) {
		bitset<30> swtch = i;
		int cnt = swtch.count();
		swtch ^= lock ^ ((swtch<<1) & lim) ^ (swtch>>1);
		if (swtch.none() && cnt < min) min = cnt;
	}
	if (min == 100) cout << "impossible" << endl;
	else cout << min << endl;
	return 0;
}