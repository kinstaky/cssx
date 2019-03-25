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
const int ARROWONE = 3;
const int ARROWTWO = 2;
const char sname[4][10] = {"sword", "bomb", "arrow", "arrow"};
const char hname[2][5] = {"red", "blue"};
int whp[5];
int wattack[5];
int kcase;

class Warrior{
protected:
	int type;
	int wpnum;
	int weapon[4];							//the number of the weapon
	int present_weapon;
	int present_index;
	inline void add_weapon(int i, int n) {
		wpnum += n;
		if (wpnum > 10) {
			n -= wpnum - 10;
			wpnum = 10;
		}
		weapon[i] += n;
	}
	void next_weapon() {				//After being robbed or use all weapons of one type
		switch (present_weapon) {
			case SWORD:
				present_weapon = BOMB;
				if (weapon[present_weapon]) break;
			case BOMB:
				present_weapon = ARROWONE;
				if (weapon[present_weapon]) break;
			case ARROWONE:
				present_weapon = ARROWTWO;
				if (weapon[present_weapon]) break;
			case ARROWTWO:
				present_weapon = SWORD;
				break;
			default:
				present_weapon = -1;
		}
		present_index = 0;
		if (!weapon[present_weapon] && wpnum) next_weapon();
	}
	Warrior(int tt, int hh, int oo, int aa, int ww, int cc, int nn)
	:type(tt), hp(hh), owner(oo), attack(aa), wpnum(ww), cityno(cc), num(nn) {
		memset(weapon, 0, sizeof(weapon));
	}
public:
	int cityno;
	int num;
	int hp;
	int attack;
	int owner;

	virtual ~Warrior(){}

	bool Alive() {
		return hp > 0;
	}

	bool Change() {
		if (wpnum == 0) return false;
		if (weapon[BOMB] == 0 && weapon[ARROWONE] == 0 && weapon[ARROWTWO] == 0 && attack < 5) return false;
		return true;
	}

	virtual void Attack(Warrior &w) {
		if (wpnum == 0) return;
		int power;
		//cout << hname[owner] << " " << wname[type] << " " << num << " use ";
		//cout << sname[present_weapon] << " " << " hit ";
		//cout << hname[w.owner] << " " << wname[w.Type()] << " " << w.num << endl;
		switch(present_weapon) {
			case SWORD:
				power = (double)attack * 2 / 10;
				++present_index;
				if (present_index == weapon[present_weapon]) next_weapon();
				w.Hurted(power);
				break;
			case BOMB:
				power = (double)attack * 4 / 10;
				--weapon[BOMB];
				--wpnum;
				if (!weapon[BOMB]) next_weapon();
				w.Hurted(power);
				if (type != NINJA) Hurted((int)((double)power * 5 / 10));
				break;
			case ARROWONE:
				power = (double)attack * 3 / 10;
				--weapon[ARROWONE];
				--wpnum;
				if (!weapon[ARROWONE]) next_weapon();
				w.Hurted(power);
				break;
			case ARROWTWO:
				power = (double)attack * 3 / 10;
				--weapon[ARROWTWO];
				++weapon[ARROWONE];
				present_weapon = ARROWONE;
				present_index = 0;
				w.Hurted(power);
				break;
			default:
				cout << "ERROR::Undefinde weapon  " << present_weapon << endl;
		}
	}

	virtual void Hurted(int a) {
		hp -= a;
		//cout << hname[owner] << " " << wname[type] << " " << num << " hp -" << a <<endl;
		return;
	}

	int Type() {
		return type;
	}

	int Pop_weapon(int &a) {						//return the index of the weapon
		if (wpnum == 0) {
			a = 0;
			return -1;
		}
		for (int i = 0; i != 4; ++i) {
			if (weapon[i]) {
				a = weapon[i];
				weapon[i] = 0;
				wpnum -= a;
				if (wpnum && present_weapon != ARROWONE) {
					Init_weapon();
				}
				return i;
			}
		}
		a = 0;
		return -1;
	}

	void Rob(Warrior &w, bool all, int &t, int &n) {
		int a;
		if (all) {
			for (int i = w.Pop_weapon(a); i != -1 && wpnum < 10; i = w.Pop_weapon(a)) {
				add_weapon(i, a);
			}
		}
		else {
			t = w.Pop_weapon(a);
			if (t != -1) {
				n = a;
				add_weapon(t, a);
				if (t == ARROWTWO) {
					int t2 = w.Pop_weapon(a);
					if (t2 != -1) {
						if (wpnum < 10) add_weapon(t2, a);
						n += a;
					}
				}
			}
			/*else {
				cout << hname[owner] << " " << wname[type] << " " << num;
				cout << " wants to rob " << hname[w.owner] << " " << wname[w.Type()] << " " << w.num;
				cout << " but fail because Pop_weapon return t = " << t << " and num = " << a << endl;
			}*/
		}
	}

	void Init_weapon() {
		present_weapon = SWORD;
		if (!weapon[SWORD]) next_weapon();
		present_index = 0;
	}

	void Report(int hour) {
		cout << setfill('0') << setw(3) << hour << ":55 ";
		cout << hname[owner] << " " << wname[type] << " " << num;
		cout << " has " << weapon[0] << " sword " << weapon[1] << " bomb ";
		cout << weapon[2] + weapon[3] << " arrow and " << hp << " elements" << endl;
	}
};

class Dragon: public Warrior {
private:
public:
	Dragon(int hh, int oo, int n, int aa, int cc)
	:Warrior(DRAGON, hh, oo, aa, 1, cc, n) {
		weapon[n % 3]++;
		present_weapon = n % 3;
		present_index = 0;
	}
	virtual ~Dragon() {}
	void Yell(int hour) {
		cout << setfill('0') << setw(3) << hour << ":40";
		if (owner == 0) cout << " red";
		else cout << " blue";
		cout << " dragon " << num << " yelled in city " << cityno << endl;
	}
};

class Ninja: public Warrior {
private:
public:
	Ninja(int hh, int oo, int n, int aa, int cc)
	:Warrior(NINJA, hh, oo, aa, 2, cc, n) {
		int x = n % 3;
		int y = (x + 1) % 3;
		if (x > y) {
			int t = x;
			x = y;
			y = t;
		}
		++weapon[x];
		++weapon[y];
		present_weapon = x;
		present_index = 0;
	}
	virtual ~Ninja() {}
};


class Iceman: public Warrior {
private:
public:
	Iceman(int hh, int oo, int n, int aa, int cc)
	:Warrior(ICEMAN, hh, oo, aa, 1, cc, n) {
		weapon[n % 3]++;
	}
	virtual ~Iceman() {}
	void Melt() {
		hp -= (int)((double)hp / 10);
	}
};


class Lion: public Warrior {
private:
	int loyalty;
	static int k;
public:
	static void Setk(int kk) {
		k = kk;
		return;
	}
	Lion(int hh, int oo, int n, int aa, int cc, int th)
	:Warrior(LION, hh, oo, aa, 1, cc, n), loyalty(th) {
		weapon[n % 3]++;
		cout << "Its loyalty is " << loyalty << endl;
	}
	virtual ~Lion() {}
	bool Run(){
		loyalty -= k;
		return loyalty < 0;
	}
};


class Wolf: public Warrior {
public:
	Wolf(int hh, int oo, int n, int aa, int cc)
	:Warrior(WOLF, hh, oo, aa, 0, cc, n) {}
	virtual ~Wolf() {}
};


class Headquarter{
private:
	char name[10];
	int color;
	int hp;
	int order[5];						//The order of the warrior.
	int count[5];						//The count of the warrior of the kind.
	int cnt;
	int cntsum;
	vector< Warrior* > warriors;
	int cityno;
public:
	static int colorindex;
	bool Nottaken;
	bool stopcall;
	Headquarter(const char *nn, int hh, int *oo, int cc): cityno(cc) {
		strcpy(name, nn);
		for (int i = 0; i != 5; ++i) {
			order[i] = oo[i];
			count[i] = 0;
		}
		hp = hh;
		cnt = 0;
		cntsum = 0;
		stopcall = false;
		warriors.clear();
		color = colorindex++;
		Nottaken = true;
	}

	Warrior* Call(int time) {
		if (stopcall) return nullptr;
		Warrior *p = nullptr;
		int t = order[cnt];
		cnt = (cnt + 1) % 5;
		if (hp >= whp[t]) {
			hp -= whp[t];
			++count[t];
			++cntsum;
			cout << setfill('0') << setw(3) << time << ":00 ";
			cout << name << " " << wname[t] << " " << cntsum;
			cout << " born" << endl;
			switch (t) {
				case DRAGON:
					p = new Dragon(whp[t], color, cntsum, wattack[t], cityno);
					break;
				case NINJA:
					p = new Ninja(whp[t], color, cntsum, wattack[t], cityno);
					break;
				case ICEMAN:
					p = new Iceman(whp[t], color, cntsum, wattack[t], cityno);
					break;
				case LION:
					p = new Lion(whp[t], color, cntsum, wattack[t], cityno, hp);
					break;
				case WOLF:
					p = new Wolf(whp[t], color, cntsum, wattack[t], cityno);
					break;
				default:
					cout << "ERROR::More than 5 types of warriors." << endl;
				}
			warriors.push_back(p);
		}
		else stopcall = true;
		return p;
	}
	int LionRun(int time) {
		int l = -1;
		int vecsize = warriors.size();
		for (int i = 0; i != vecsize; ++i) {
			if (warriors[i]->Type() == LION && ((Lion*)warriors[i])->Run()) {
				cout << setfill('0') << setw(3) << time << ":05 ";
				cout << name << " lion " << warriors[i]->num << " ran away" << endl;
				l = i;
			}
		}
		if (l != -1) {
			delete warriors[l];
			--count[LION];
		//	cities[warriors[l].cityno].w[color] = nullptr;
			warriors.erase(warriors.begin() + l);
			l = warriors[l]->cityno;
		}
		return l;
	}
	void Report(int hour) {
		for (auto iter = warriors.begin(); iter != warriors.end(); ++iter) {
			if (!(*iter)->Alive()) {
				--count[(*iter)->Type()];
				auto temp = iter;
				--iter;
				warriors.erase(temp);
			}
		}
		cout << setfill('0') << setw(3) << hour << ":50 ";
		cout << hp << " elements in " << hname[color] << " headquarter" << endl;
	}
};


int Headquarter::colorindex = 0;
int Lion::k = 0;

struct City {
	Warrior* w[2];
};

class Map {
private:
	City *cities;
	int citynum;
public:
	Map(int n) :citynum(n) {
		cities = new City[n+2];
		memset(cities, 0, sizeof(cities));
	}

	void Born(Warrior *w, int n, int color) {
		cities[n].w[color] = w;
	}

	void LionRun(int i, int color) {
		cities[i].w[color] = nullptr;
	}

	int March(int hour) {
		int ret = 0;
		for (int i = 0; i <= citynum; ++i) {
			cities[i].w[1] = cities[i+1].w[1];
			if (cities[i].w[1]) cities[i].w[1]->cityno = i;
		}
		for (int i = citynum+1; i >= 1; --i) {
			cities[i].w[0] = cities[i-1].w[0];
			if (cities[i].w[0]) cities[i].w[0]->cityno = i;
		}
		if (cities[0].w[1]) {
			Warrior *w = cities[0].w[1];
			if (w->Type() == ICEMAN) ((Iceman*)w)->Melt();
			cout << setfill('0') << setw(3) << hour << ":10 ";
			cout << "blue " << wname[w->Type()] << " " << w->num;
			cout << " reached red headquarter with " << w->hp;
			cout << " elements and force " << w->attack << endl;
			cout << setfill('0') << setw(3) << hour << ":10 ";
			cout << "red headquarter was taken" << endl;
			ret = ret | 0x1;
		}
		for (int i = 1; i <= citynum; ++i) {
			if (cities[i].w[0]) {
				Warrior *w = cities[i].w[0];
				if (w->Type() == ICEMAN) ((Iceman*)w)->Melt();
				cout << setfill('0') << setw(3) << hour << ":10 ";
				cout << "red " << wname[w->Type()] << " " << w->num;
				cout << " marched to city " << i << " with " << w->hp;
				cout << " elements and force " << w->attack << endl;
			}
			if (cities[i].w[1]) {
				Warrior *w = cities[i].w[1];
				if (w->Type() == ICEMAN) ((Iceman*)w)->Melt();
				cout << setfill('0') << setw(3) << hour << ":10 ";
				cout << "blue " << wname[w->Type()] << " " << w->num;
				cout << " marched to city " << i << " with " << w->hp;
				cout << " elements and force " << w->attack << endl;
			}
		}
		if (cities[citynum+1].w[0]) {
			Warrior *w = cities[citynum+1].w[0];
			if (w->Type() == ICEMAN) ((Iceman*)w)->Melt();
			cout << setfill('0') << setw(3) << hour << ":10 ";
			cout << "red " << wname[w->Type()] << " " << w->num;
			cout << " reached blue headquarter with " << w->hp;
			cout << " elements and force " << w->attack << endl;
			cout << setfill('0') << setw(3) << hour << ":10 ";
			cout << "blue headquarter was taken" << endl;
			ret = ret | 0x2;
		}
		return ret;
	}

	void WolfRob(int hour) {
		for (int i = 1; i <= citynum; ++i) {
			Warrior *w = nullptr;
			Warrior *r = nullptr;
			if (cities[i].w[0] && cities[i].w[0]->Type() == WOLF) {
				w = cities[i].w[0];
				r = cities[i].w[1];
			}
			if (cities[i].w[1] && cities[i].w[1]->Type() == WOLF) {
				if (w) {
					//cout << setfill('0') << setw(3) << hour << ":35 ";
					//cout << "two wolf in city " << i << endl;
					continue;
				}
				else {
					w = cities[i].w[1];
					r = cities[i].w[0];
				}
			}
			if (!w || !r) {
				//cout << setfill('0') << setw(3) << hour << ":35 ";
				//cout << "no wolf in city " << i << endl;
				continue;
			}
			w->Init_weapon();
			r->Init_weapon();
			int t, q;
			w->Rob(*r, false, t, q);
			if (t == -1) {
				//cout << setfill('0') << setw(3) << hour << ":35 ";
				//cout << "one wolf in city " << i << " but no weapon" << endl;
				continue;
			}
			cout << setfill('0') << setw(3) << hour << ":35 ";
			cout << hname[w->owner] << " wolf " << w->num << " took ";
			cout << q << " " << sname[t] << " from " << hname[r->owner];
			cout << " " << wname[r->Type()] << " " << r->num << " in city " << i << endl;
		}
	}

	void Battle(int hour) {
		for (int i = 1; i <= citynum; ++i) {
			if (!cities[i].w[0] || !cities[i].w[1]) continue;
			Warrior *rw = cities[i].w[0];
			Warrior *bw = cities[i].w[1];
			Warrior *x = cities[i].w[(i+1) % 2];
			Warrior *y = cities[i].w[i % 2];
			x->Init_weapon();
			y->Init_weapon();
			while (x->Alive() && y->Alive() && (x->Change() || y->Change())) {
				x->Attack(*y);
				if (y->Alive() && x->Alive()) y->Attack(*x);
			}
			cout << setfill('0') << setw(3) << hour << ":40 ";
			if (rw->Alive()) {
				if (bw->Alive()) {
					cout << "both red " << wname[rw->Type()] << " " << rw->num;
					cout << " and blue " << wname[bw->Type()] << " " << bw->num;
					cout << " were alive in city " << i << endl;
					if (rw->Type() == DRAGON) ((Dragon*)rw)->Yell(hour);
					if (bw->Type() == DRAGON) ((Dragon*)bw)->Yell(hour);
				}
				else {
					cout << "red " << wname[rw->Type()] << " " << rw->num;
					cout << " killed blue " << wname[bw->Type()] << " " << bw->num;
					cout << " in city " << i << " remaining " << rw->hp << " elements"<<endl;
					int t, q;
					rw->Rob(*bw, true, t, q);
					if (rw->Type() == DRAGON) ((Dragon*)rw)->Yell(hour);
					cities[i].w[1] = nullptr;
				}
			}
			else {
				if (bw->Alive()) {
					cout << "blue " << wname[bw->Type()] << " " << bw->num;
					cout << " killed red " << wname[rw->Type()] << " " << rw->num;
					cout << " in city " << i << " remaining " << bw->hp << " elements" << endl;
					int t, q;
					bw->Rob(*rw, true, t, q);
					if (bw->Type() == DRAGON) ((Dragon*)bw)->Yell(hour);
					cities[i].w[0] = nullptr;
				}
				else {
					cout << "both red " << wname[rw->Type()] << " " << rw->num;
					cout << " and blue " << wname[bw->Type()] << " " << bw->num;
					cout << " died in city " << i << endl;
					cities[i].w[0] = nullptr;
					cities[i].w[1] = nullptr;
				}
			}
		}
	}

	void Report(int hour) {
		for (int i = 1; i <= citynum; ++i) {
			if (cities[i].w[0]) cities[i].w[0]->Report(hour);
			if (cities[i].w[1]) cities[i].w[1]->Report(hour);
		}
		return;
	}
};


int main() {
	cin >> kcase;
	int k = 0;
	while (kcase--) {
		cout << "Case " << ++k << ":" << endl;
		memset(whp, 0, sizeof(whp));
		int totalhp, lionk, citinum, end_time;
		cin >> totalhp >> citinum >> lionk >> end_time;
		Lion::Setk(lionk);
		for (int i = 0; i != 5; ++i) cin >> whp[i];
		for (int i = 0; i != 5; ++i) cin >> wattack[i];
		int redorder[5] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
		int blueorder[5] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
		Headquarter::colorindex = 0;
		Headquarter red("red", totalhp, redorder, 0);
		Headquarter blue("blue", totalhp, blueorder, citinum+1);
		Map battlemap(citinum);
		int time = 0;
		while (time <= end_time && red.Nottaken && blue.Nottaken) {
			int hour = time / 60;
			int minute = time % 60;
			int t1, t2;
			switch (minute) {
				case 0:
					//cout<<"case0"<<endl;
					if (!red.stopcall) battlemap.Born(red.Call(hour), 0, 0);
					if (!blue.stopcall) battlemap.Born(blue.Call(hour), citinum+1, 1);
					time += 5;
					break;
				case 5:
					//cout <<"case5"<<endl;
					t1 = red.LionRun(hour);
					if (t1 != -1) battlemap.LionRun(t1, 0);
					t1 = blue.LionRun(hour);
					if (t1 != -1) battlemap.LionRun(t1, 1);
					time += 5;
					break;
				case 10:
					//cout<<"case10"<<endl;
					t2 = battlemap.March(hour);
					if (t2 & 0x1) red.Nottaken = false;
					if (t2 & 0x2) blue.Nottaken = false;
					time += 25;
					break;
				case 35:
					//cout<<"case35"<<endl;
					battlemap.WolfRob(hour);
					time += 5;
					break;
				case 40:
					//cout<<"case40"<<endl;
					battlemap.Battle(hour);
					time += 10;
					break;
				case 50:
					//cout<<"case50"<<endl;
					red.Report(hour);
					blue.Report(hour);
					time += 5;
					break;
				case 55:
					//cout<<"case55"<<endl;
					battlemap.Report(hour);
					time += 5;
					break;
				default:
					cout << "ERROR::Unkown time." << endl;
			}
		}
	}
	return 0;
}