#include <iostream>
#include <cstring>
using namespace std;

const int INF = 1 << 30;
const int LEN = 1 << 14;

int minL[15][1<<14];
int w[16][16];
int visit[16];
int mincost = INF;
int n;
int cost;
int finish;


void Cost(int present, int state) {
	if (cost >= mincost) return;
	if (minL[present][state] == 0 || cost < minL[present][state]) {
		minL[present][state] = cost;
	}
	else return;
	if (state == finish) {
		int tc = cost + w[present][n-1];
		mincost = tc < mincost ? tc : mincost;
		return;
	}
	for (int i = 1; i != n-1; ++i) {
		if (visit[i]) continue;
		visit[i] = 1;
		cost += w[present][i];
		Cost(i, state | (1 << (i-1)));
		cost -= w[present][i];
		visit[i] = 0;
	}
	return;
}

int main() {
	cin >> n;
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != n; ++j) {
			cin >> w[i][j];
		}
	}
	memset(visit, 0, sizeof(visit));
	memset(minL, 0, sizeof(minL));
	visit[0] = 1;
	finish = (1 << (n-2)) - 1;
	cost = 0;
	Cost(0, 0);
	cout << mincost << endl;
	return 0;
}


//another version 
// #include <iostream>


// using namespace std;

// const int INF = 1 << 30;
// const int LEN = 1 << 14;

// int minL[15][1<<14];
// int w[16][16];
// int visit[16];
// int mincost = INF;
// int n;
// int cost;
// int finish;


// void Cost(int present, int state) {
// 	if (cost >= mincost) return;
// 	if (cost >= minL[present][state]) return; //must be >=, if > it will TLE
// 	else minL[present][state] = cost;
// 	if (state == finish) {
// 		int tc = cost + w[present][n-1];
// 		mincost = tc < mincost ? tc : mincost;
// 		return;
// 	}
// 	for (int i = 1; i != n-1; ++i) {
// 		if (visit[i]) continue;
// 		visit[i] = 1;
// 		cost += w[present][i];
// 		Cost(i, state | (1 << (i-1)));
// 		cost -= w[present][i];
// 		visit[i] = 0;
// 	}
// 	return;
// }

// int main() {
// 	cin >> n;
// 	for (int i = 0; i != n; ++i) {
// 		for (int j = 0; j != n; ++j) {
// 			cin >> w[i][j];
// 		}
// 	}

// 	for (int i = 0; i != 15; ++i) {
// 		for (int j = 0; j != LEN; ++j) {
// 			minL[i][j]  = INF;
// 		}
// 	}
// 	for (int i = 1; i != 16; ++i) visit[i] = 0;
// 	visit[0] = 1;
// 	finish = (1 << (n-2)) - 1;
// 	cost = 0;
// 	Cost(0, 0);
// 	cout << mincost << endl;
// 	return 0;
// }