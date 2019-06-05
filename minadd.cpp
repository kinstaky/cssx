#include <iostream>
#include <cstring>


using namespace std;


int n, m;
char s[55];
char dp[55][55];

int cmp(char *s1, char *s2) {
	int len = strlen(s1);
	int len2 = strlen(s2);
	if (len < len2) return -1;
	if (len > len2) return 1;
	for (int i = 0; i != len; ++i) {
		if (s1[i] < s2[i]) return -1;
		if (s1[i] > s2[i]) return 1;
	}
	return 0;
}

void Add(char *aa, char *bb, char *sum) {
	char a[55], b[55];
	strcpy(a, aa);
	strcpy(b, bb);
	int lena = strlen(a);
	int lenb = strlen(b);
	int len;
	if (lena < lenb) {
		len = lenb - lena;
		for (int i = lenb; i >= len; --i) a[i] = a[i-len];
		for (int i = 0; i != len; ++i) a[i] = '0';
		len = lenb;
	}
	else if (lena > lenb) {
		len = lena - lenb;
		for (int i = lena; i >= len; --i) b[i] = b[i-len];
		for (int i = 0; i != len; ++i) b[i] = '0';
		len = lena;
	}
	else len = lena;
	int c = 0;
	for (int i = len-1; i >= 0; --i) {
		int t = a[i] + b[i] + c - '0' - '0';
		if (t > 9) {
			c = 1;
			t -= 10;
		}
		else c = 0;
		sum[i] = t + '0';
	}
	if (c == 1) {
		for (int i = len; i != 0; --i) sum[i] = sum[i-1];
		sum[0] = '1';
		sum[len+1] = 0;
	}
	else sum[len] = 0;
}


void Solve(char *s, int na, char *ans) {
	if (na == 0) {
		strcpy(ans, s);
		return;
	}
	for (int j = 0; j != m; ++j) {
		memcpy(dp[j], s, j+1);
		dp[j][j+1] = 0;
	}
	for (int i = 1; i <= na; ++i) {
		for (int j = m; j > i; --j) {
			char mint[55];
			mint[0] = 0;
			for (int k = i; k != j; ++k) {
				char t[55];
				char num[55];
				memcpy(num, s+k, j-k);
				num[j-k] = 0;
				Add(dp[k-1], num, t);
				if (!strlen(mint) || cmp(mint, t) == 1) {
					strcpy(mint, t);
				}
			}
			strcpy(dp[j-1], mint);
		}
	}
	strcpy(ans, dp[m-1]);
	return;
}


int main() {
	while (cin >> n) {
		cin >> s;
		memset(dp, 0, sizeof(dp));
		m = strlen(s);
		char ans[55];
		Solve(s, n, ans);
		cout << ans << endl;
	}
}