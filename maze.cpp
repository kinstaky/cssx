#include <iostream>


using namespace std;


int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int s[25][4];
int a[25];
int visit[25];
int q[16];
int head, tail;
int pre[25];

inline bool inmaze(int x, int y) {
	return (x >= 0 && x <= 4 && y >= 0 && y <= 4);
}

void bfs(int st, int e) {
	head = 0;
	tail = 1;
	q[head] = st;
	visit[st] = 2;
	pre[st] = -1;
	while (head != tail) {
		int qh = q[head];
		visit[qh] = 1;
		++head;
		head %= 16;
		if (qh == e) return;
		for (int i = 0; i != 4; ++i) {
			int p = s[qh][i];
			if (p >= 0 && !visit[p]) {
				q[tail] = p;
				pre[p] = qh;
				visit[p] = 2;
				++tail;
				tail %= 16;
			}
		}
	}
	return;
}

void printpath(int x) {
	if (x < 0) return;
	printpath(pre[x]);
	cout << "(" << x / 5 << ", " << x % 5 << ")" << endl;
	return;
}

int main() {
	for (int i = 0; i != 25; ++i) cin >> a[i];
	for (int x = 0; x != 5; ++x) {
		for (int y = 0; y != 5; ++y) {
			for (int i = 0; i != 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (inmaze(nx, ny) && !a[nx*5 + ny]) {
					s[x*5+y][i] = nx*5+ny;
				}
				else s[x*5+y][i] = -1;
			}
		}
	}
	for (int i = 0; i != 25; ++i) visit[i] = 0;
	bfs(0, 24);
	printpath(24);
	return 0;
}