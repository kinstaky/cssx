#include <iostream>

using namespace std;

const int INF = 1 << 20;
const int mask = (1 << 4) - 1;

int w[4];
int ans;

int count(int x, int len = 32) {
	int ret = 0;
	for (int i = 0; i != len; ++i) {
		if ((1 << i) & x) ++ ret;
	}
	return ret;
}

void revert() {
	for (int i = 0; i != 4; ++i) {
		w[i] = mask & (~w[i]);
	}
	return;
}


void Solve() {
	for (int i = 0; i != 16; ++i) {
		int cnt = 0;
		cnt += count(i, 4);
		if (cnt >= ans) continue;
		int flip = i;
		int up = w[0] ^ i ^ ((i << 1) & mask) ^ (i >> 1);
		for (int j = 1; j != 4; ++j) {
			int t = flip;
			flip = up & mask;
			int ct = count(flip, 4);
			if (cnt + ct > ans) {
				up = 1;
				break;
			}
			cnt += ct;
			up = w[j] ^ t ^ flip ^ ((flip<<1) & mask) ^ (flip >> 1);
		}
		if (up == 0 && cnt < ans) {
			ans = cnt;
		}
	}
}

int main() {
	for (int i = 0; i != 4; ++i) {
		w[i] = 0;
		for (int j = 0; j != 4; ++j) {
			char c;
			cin >> c;
			if (c == 'w') w[i] |= 1<<(3-j);
		}
	}
	ans = INF;
	Solve();
	revert();
	Solve();
	if (ans == INF) cout << "Impossible" << endl;
	else cout << ans << endl;
	return 0;
}