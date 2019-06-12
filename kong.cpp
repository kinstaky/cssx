#include <iostream>
#include <deque>
#include <cstring>

using namespace std;

const int SNAKE = 10;
const int NONE = 0;
const int WALL = -1;
const int TANG = 20;

int G[105][105];
int m;
int n;
int mint[105][105][10][32];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int kongx;
int kongy;
int mincost;

inline bool inmap(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < n);
}


struct state {
	int x;
	int y;
	int k;
	int s;
	state(int xx, int yy, int kk, int ss): x(xx), y(yy), k(kk), s(ss) {}
};

deque< state > q;


void bfs(int snake) {
	memset(mint, 1, sizeof(mint));
	mincost = -1;
	q.clear();
	q.push_back(state(kongx, kongy, 0, snake));
	mint[kongx][kongy][0][snake] = 0;
	while (!q.empty()) {
		state psta = q.front();
		q.pop_front();
		int ptime = mint[psta.x][psta.y][psta.k][psta.s];
		for (int i = 0; i != 4; ++i) {
			int x = psta.x + dx[i];
			int y = psta.y + dy[i];
			if (!inmap(x, y)) continue;
			if (G[x][y] == WALL) continue;
			bool gotonone = 0;
			if (G[x][y] >= SNAKE && G[x][y] < SNAKE + 5) {
				int snakenum = G[x][y] - SNAKE;
				snakenum = 1 << snakenum;
				if (psta.s & snakenum) {							//snake alive
					int nsnake = psta.s & ~snakenum;
					int ntime = ptime + 2;
					int &mintime = mint[x][y][psta.k][nsnake];
					if (ntime < mintime || mintime < 0) {
						mintime = ntime;
						q.push_back(state(x, y, psta.k, nsnake));
					}
				}
				else gotonone = 1;										//snake is dead
			}
			else if (G[x][y] <= 9 && G[x][y] >= 1) {
				if (G[x][y] == psta.k + 1) {
					int ntime = ptime + 1;
					int &mintime = mint[x][y][psta.k+1][psta.s];
					if (ntime < mintime || mintime < 0) {
						mintime = ntime;
						q.push_back(state(x, y, psta.k+1, psta.s));
					}
				}
				else gotonone = 1;
			}
			else if (G[x][y] == TANG) {
				if (psta.k < m) gotonone = 1;							//lack of key
				else {
					int ntime = ptime + 1;
					if (ntime < mincost || mincost < 0) mincost = ntime;
				}
			}
			else gotonone = 1;
			if (gotonone) {
				int ntime = ptime + 1;
				int &mintime = mint[x][y][psta.k][psta.s];
				if (ntime < mintime || mintime < 0) {
					mintime = ntime;
					q.push_back(state(x, y, psta.k, psta.s));
				}
			}
		}
	}
}



int main() {
	cin >> n >> m;
	while (n) {
		int snakecnt = 0;
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != n; ++j) {
				char c;
				cin >> c;
				switch (c) {
					case 'K':
						kongx = i;
						kongy = j;
						G[i][j] = NONE;
						break;
					case 'T':
						G[i][j] = TANG;
						break;
					case 'S':
						G[i][j] = SNAKE + snakecnt;
						++snakecnt;
						break;
					case '.':
						G[i][j] = NONE;
						break;
					case '#':
						G[i][j] = WALL;
						break;
					default:
						if (c <= '9' && c >= '1') {
							G[i][j] = c - 48;
						}
						else cerr << "Error: Undefined map item." << endl;
				}
			}
		}
		bfs((1<<snakecnt)-1);
		if (mincost > 0) cout << mincost << endl;
		else cout << "impossible" << endl;
		cin >> n >> m;
	}
	return 0;
}