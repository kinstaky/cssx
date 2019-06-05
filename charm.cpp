#include <iostream>

using namespace std;


int n, m;
int dp[12900];
int w[3405];
int d[3405];


void Solve() {
	for (int i = 1; i != n; ++i) {
		for (int j = m; j >= w[i]; --j) {
			int t = dp[j-w[i]] + d[i];
			if (t > dp[j]) dp[j] = t;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i != n; ++i) cin >> w[i] >> d[i];
	for (int i = 0; i < w[0]; ++i) dp[i] = 0;
	for (int i = w[0]; i <= m; ++i) dp[i] = d[0];
	Solve();
	cout << dp[m] << endl;
}