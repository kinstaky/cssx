#include <iostream>
#include <bitset>

using namespace std;


int main() {
	int n;
	cin >> n;
	bitset<15> lim = (1<<n)-1;
	bitset<15> wall[15];
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != n; ++j) {
			char c;
			cin >> c;
			wall[i][j] = c == 'w' ? 1 : 0;
		}
	}
	int min = 500;
	int pown = 1 << n;
	for (int i = 0; i != pown; ++i) {
		bitset<15> pswtch = 0;
		bitset<15> swtch = i;
		int cnt = 0;
		for (int j = 0; j != n; ++j) {
			cnt += swtch.count();
			bitset<15> pwall = wall[j] ^ swtch ^ pswtch ^ ((swtch<<1)&lim) ^ (swtch>>1);
			pswtch = swtch;
			swtch = pwall;
		}
		if (swtch.none() && cnt < min) min = cnt;
	}
	if (min != 500) cout << min << endl;
	else cout << "inf" << endl;
	return 0;
}
