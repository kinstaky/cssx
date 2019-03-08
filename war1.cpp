#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int DRAGON = 0;
const int NINJA = 1;
const int ICEMAN = 2;
const int LION = 3;
const int WOLF = 4;
const char wname[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int whp[5];
int kcase;

class Headquarter{
private:
	char name[10];
	int hp;
	int order[5];						//The order of the warrior.
	int count[5];						//The count of the warrior of the kind.
	int cnt;
	int cntsum;
public:
	bool stopcall;
	Headquarter(const char * nn, int hh, int* oo);
	void call(int time);
};

Headquarter::Headquarter(const char *nn, int hh, int *oo) :hp(hh) {
	strcpy(name, nn);
	for (int i = 0; i != 5; ++i) {
		order[i] = oo[i];
		count[i] = 0;
	}
	cnt = 0;
	cntsum = 0;
	stopcall = false;
	/*cout << "construct headquarter name is " << name << "with hp " << hp << " with order";
	for (int i = 0; i != 5; ++i) cout << " " << wname[order[i]];
	cout << endl;*/
}

void Headquarter::call(int time) {
	if (stopcall) return;
	int i = 0;
	for (; i != 5; ++i) {
		int t = order[cnt];
		cnt = (cnt + 1) % 5;
		if (hp >= whp[t]) {
			hp -= whp[t];
			++count[t];
			++cntsum;
			cout << setfill('0') << setw(3) << time << " ";
			cout << name << " " << wname[t] << " " << cntsum;
			cout << " born with strength " << whp[t] << ",";
			cout << count[t] << " " << wname[t] << " in ";
			cout << name << " headquarter"<<endl;
			break;
		}
	}
	if (i == 5) {
		stopcall = true;
		cout << setfill('0') << setw(3) << time << " ";
		cout << name << " headquarter stops making warriors" << endl;
	}
}

int main() {
	cin >> kcase;
	int k = 0;
	while (kcase--) {
		cout << "Case:" << ++k << endl;
		memset(whp, 0, sizeof(whp));
		int totalhp;
		cin >> totalhp;
		for (int i = 0; i != 5; ++i) cin >> whp[i];
		int redorder[5] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
		int blueorder[5] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
		Headquarter red("red", totalhp, redorder);
		Headquarter blue("blue", totalhp, blueorder);
		for (int i = 0; !red.stopcall || !blue.stopcall; ++i) {
			red.call(i);
			blue.call(i);
		}
	}
	return 0;
}