#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;



int sum[10005];
int must[205];
int mn;
int a[205];
int x, n;
int cn;
int csum[10005];


void Add(int c) {
	if (sum[c]) return;
	sum[c] = 1;
	csum[cn++] = c;
	return;
}


int main() {
	cin >> n >> x;
	for (int i = 0; i != n; ++i) cin >> a[i];
	//for (int i = 0; i != n; ++i) valid[i] = 1;
	memset(must, 0, sizeof(must));
	mn = 0;
	for (int i = 0; i != n; ++i) {
		cn = 0;
		memset(sum, 0, sizeof(sum));
		memset(csum, 0, sizeof(csum));
		int solve = 0;
		Add(0);
		for (int j = 0; j != n; ++j) {
			if (j == i) continue;
			//if (!valid[j]) continue;
			int len = cn;
			for (int k = 0; k != len; ++k) {
				int t = csum[k] + a[j];
				if (t == x) {
					solve = 1;
					break;
				}
				if (t < x) Add(t);
			}
			if (solve) break;
		}
		if (!solve) {
			must[mn++] = a[i];
			//valid[i] = 0;
			//x -= a[i];
		}
	}
	cout << mn << endl;
	for (int i = 0; i != mn; ++i) cout << must[i] << " ";
	cout << endl;
	return 0;
}