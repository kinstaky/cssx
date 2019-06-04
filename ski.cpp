#include <iostream>
//#include <vector>
//#include <deque>
#include <cstring>

using namespace std;

// struct point {
// 	int x;
// 	int y;
// 	point(int xx = 0, int yy = 0): x(xx), y(yy) {}
// };


int c, r;
int h[105][105];
int d[105][105];
//point pre[105][105];
int maxd;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};



void Dis(int x, int y) {
	for (int di = 0; di != 4; ++di) {
		int nx = x + dx[di];
		int ny = y + dy[di];
		if (nx >= 0 && nx < r && ny >= 0 && ny < c && h[nx][ny] < h[x][y]) {
			if (!d[nx][ny]) Dis(nx, ny);
			if (d[nx][ny] + 1 > d[x][y]) {
				d[x][y] = d[nx][ny] + 1;
				maxd = maxd < d[x][y] ? d[x][y] : maxd;
			}
		}
	}
	return;
}


int main() {
	maxd = 0;
	int minh = 100000;
	//memset(pre, 0xff, sizeof(pre));
	cin >> r >> c;
	for (int i = 0; i != r; ++i) {
		for (int j = 0; j != c; ++j) {
			cin >> h[i][j];
			minh = h[i][j] < minh ? h[i][j] : minh;
		}
	}
	// for (int i = 0; i != r; ++i) {
	// 	for (int j = 0; j != c; ++j) {
	// 		m.push_back(point(i, j));
	// 	}
	// }
	// for (int i = 0; i != r; ++i) {
	// 	for (int j = 0; j != c; ++j) {
	// 		d[i][j] = 1;
	// 	}
	// }
	memset(d, 0, sizeof(d));

	for (int i = 0; i != r; ++i) {
		for (int j = 0; j != c; ++j) {
			Dis(i, j);
		}
	}

	cout << maxd+1 << endl;

	// for (int i = 0; i != r; ++i) {
	// 	for (int j = 0; j != c; ++j) {
	// 		cout << d[i][j] << "  ";
	// 	}
	// 	cout << endl;
	// }
	return 0;
}