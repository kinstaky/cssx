#include <iostream>
#include <cstring>

using namespace std;

const char wname[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int order[5];

int main() {
	for (int i = 0; i != 5; ++i) {
		cout << wname[i] << "    len = " << strlen(wname[i]) << endl;
	}
	int order[5] = {1, 2, 3, 4, 5};
	for (int i = 0; i != 5; ++i) cout << order[i] << endl;
	//order = {2, 1, 4, 5, 3};
	//for (int i = 0; i != 5; ++i) cout << order[i] << endl;
	return 0;
}