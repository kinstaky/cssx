#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

const int DRAGON = 0;
const int NINJA = 1;
const int ICEMAN = 2;
const int LION = 3;
const int WOLF = 4;
const char wname[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const int SWORD = 0;
const int BOMB = 1;
const int ARROW = 2;
const char sname[3][10] = {"sword", "bomb", "arrow"};
int whp[5];
int kcase;

class Warrior{
protected:
	int type;
	int hp;
	int owner;
	Warrior(int tt, int hh, int oo) :type(tt), hp(hh), owner(oo) {}
	~Warrior(){}
};

class Dragon: public Warrior {
private:
	double morale;
	int weapon;
public:
	Dragon(int hh, int oo, int nn, int th)
	:Warrior(DRAGON, hh, oo), morale((double)th / (double(whp[DRAGON]))), weapon(nn % 3) {
		cout << "It has a " << sname[weapon] << ",and it's morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl;
	}
};

class Ninja: public Warrior {
private:
	int weapon[2];
public:
	Ninja(int hh, int oo, int nn)
	:Warrior(NINJA, hh, oo) ,weapon{nn % 3, (nn+1) % 3} {
		cout << "It has a " << sname[weapon[0]] << " and a " << sname[weapon[1]] << endl;
	}
};


class Iceman: public Warrior {
private:
	int weapon;
public:
	Iceman(int hh, int oo, int nn)
	:Warrior(ICEMAN, hh, oo), weapon(nn % 3) {
		cout << "It has a " << sname[weapon] << endl;
	}
};


class Lion: public Warrior {
private:
	int loyalty;
public:
	Lion(int hh, int oo, int th)
	:Warrior(LION, hh, oo), loyalty(th) {
		cout << "It's loyalty is " << loyalty << endl;
	}
};


class Wolf: public Warrior {
public:
	Wolf(int hh, int oo)
	:Warrior(WOLF, hh, oo) {}
};


class Headquarter{
private:
	static int colorindex;
	char name[10];
	int color;
	int hp;
	int order[5];						//The order of the warrior.
	int count[5];						//The count of the warrior of the kind.
	int cnt;
	int cntsum;
	vector< Warrior* > warriors;
public:
	bool stopcall;
	Headquarter(const char * nn, int hh, int* oo);
	void call(int time);
};


int Headquarter::colorindex = 0;

Headquarter::Headquarter(const char *nn, int hh, int *oo) :hp(hh) {
	strcpy(name, nn);
	for (int i = 0; i != 5; ++i) {
		order[i] = oo[i];
		count[i] = 0;
	}
	cnt = 0;
	cntsum = 0;
	stopcall = false;
	warriors.clear();
	color = colorindex++;
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
			Warrior *p;
			switch (t) {
				case DRAGON:
					p = new Dragon(whp[t], color, cntsum, hp);
					break;
				case NINJA:
					p = new Ninja(whp[t], color, cntsum);
					break;
				case ICEMAN:
					p = new Iceman(whp[t], color, cntsum);
					break;
				case LION:
					p = new Lion(whp[t], color, hp);
					break;
				case WOLF:
					p = new Wolf(whp[t], color);
					break;
				default:
					cout << "error: more than 5 types of soldiers" << endl;
			}
			warriors.push_back(p);
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