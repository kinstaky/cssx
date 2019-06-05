#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Node {
	int pre;
	int last;
	int mscore;
	int fday;
};
Node dp[(1<<16)+10];



int n;
string name[16];
int ddl[16];
int c[16];


int cmp(int x, int y) {			// x < y -1, x > y 1, x == y 0
	if (x == 0) return 0;
	int p = cmp(dp[x].pre, dp[y].pre);
	if (p != 0) return p;
	if (name[dp[x].last] < name[dp[y].last]) return -1;
	if (name[dp[x].last] > name[dp[y].last]) return 1;
	return 0;
}


void Solve() {
	for (int i = 1; i != 1<<n; ++i) {
		int x = i;
		for (int j = 0; j != n; ++j) {
			int mask = 1 << j;
			if (mask & x) {
				int p = x & ~mask;
				int day = dp[p].fday + c[j];
				int score = day - ddl[j];
				score = score < 0 ? 0 : score;
				score += dp[p].mscore;
				if (dp[x].last == -1 || dp[x].mscore > score) {
					dp[x].pre = p;
					dp[x].last = j;
					dp[x].mscore = score;
					dp[x].fday = day;
				}
				else if (dp[x].mscore == score) {
					if (cmp(p, dp[x].pre) == -1) {
						dp[x].pre = p;
						dp[x].last = j;
						dp[x].mscore = score;
						dp[x].fday = day;
					}
				}
			}
		}
	}
}

void print(int s) {
	if (s == 0) return;
	print(dp[s].pre);
	cout << name[dp[s].last] << endl;
	return;
}


int main() {
	int kcase;
	cin >> kcase;
	while (kcase--) {
		memset(dp, 0, sizeof(dp));
		memset(ddl, 0, sizeof(ddl));
		memset(c, 0, sizeof(c));
		cin >> n;
		for (int i = 0; i != n; ++i) {
			cin >> name[i] >> ddl[i] >> c[i];
		}
		dp[0].last = -1;
		dp[0].mscore = 0;
		dp[0].fday = 0;
		dp[0].pre = -1;
		for (int i = 0; i != 1<<n; ++i) dp[i].last = -1;
		Solve();
		cout << dp[(1<<n) - 1].mscore << endl;
		print((1<<n)-1);

	}
	return 0;
}