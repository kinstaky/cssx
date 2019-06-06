#include <iostream>

using namespace std;

int n, k;
bool valid[8][8];
bool vc[8];
bool vr[8];
int br;


int Count(int m) {
	if (m == 0) return 1;
	if (br == n) return 0;
	int ways = 0;
	for (int i = br; i != n; ++i) {
		if (!vr[i]) continue;
		for (int j = 0; j != n; ++j) {
			if (!vc[j]) continue;
			if (!valid[i][j]) continue;
			valid[i][j] = 0;
			vr[i] = 0;
			vc[j] = 0;
			br = i+1;
			ways += Count(m-1);
			valid[i][j] = 1;
			vr[i] = 1;
			vc[j] = 1;
		}
	}
	return ways;
}



int main() {
	while ((cin >> n >> k) &&  n != -1) {
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != n; ++j) {
				char c;
				cin >> c;
				if (c == '#') valid[i][j] = 1;
				else valid[i][j] = 0;
			}
		}
		for (int i = 0; i != 8; ++i) vc[i] = 1;
		for (int i = 0; i != 8; ++i) vr[i] = 1;
		br = 0;
		cout << Count(k) << endl;
	}
	return 0;
}