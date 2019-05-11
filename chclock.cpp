#include <iostream>
#include <bitset>

using namespace std;


bitset<9> s[9] = {
	27, 	//000011011,
	7, 		//000000111,
	54,		//000110110,
	73,		//001001001,
	186,	//010111010,
	292,	//100100100,
	216,	//011011000,
	448,	//111000000,
	432		//110110000
};



bool check(bitset<9> clol, bitset<9> cloh, const bitset<9> &chgl, const bitset<9> &chgh) {
	for (int i = 0; i != 9; ++i) {
		if (chgl[i]) {
			cloh ^= s[i] & clol;
			clol ^= s[i];
		}
		if (chgh[i]) cloh ^= s[i];
	}
	//cout << clol << " " << cloh << "    " << chgl << " " << chgh << endl;
	return clol.none() && cloh.none();
}


int main() {
	bitset<9> cloh;
	bitset<9> clol;
	bitset<9> chgh;
	bitset<9> chgl;
	for (int i = 0; i != 9; ++i) {
		int t;
		cin >> t;
		cloh[i] = t / 2;
		clol[i] = t % 2;
	}
	int min = 100;
	int minch[9];
	for (int i = 0; i != 512; ++i) {
		for (int j = 0; j != 512; ++j) {
			chgh = i;
			chgl = j;
			if (check(clol, cloh, chgl, chgh)) {
				int t = chgh.count() * 2 + chgl.count();
				if (min > t) {
					min = t;
					for (int k = 0; k != 9; ++k)
						minch[k] = chgh[k]*2 + chgl[k];
				}
			}
		}
	}
	for (int i = 0; i != 9; ++i) {
		for (int j = 0; j != minch[i]; ++j)
			cout << i+1 << " ";
	}
	cout << endl;

}