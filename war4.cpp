#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <deque>

using namespace std;

const int DRAGON = 0;
const int NINJA = 1;
const int ICEMAN = 2;
const int LION = 3;
const int WOLF = 4;
const char SNAME[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const int SWORD = 0;
const int BOMB = 1;
const int ARROW = 2;
const char WNAME[4][10] = {"sword", "bomb", "arrow"};
const char COLORNAME[2][5] = {"red", "blue"};
const int RED = 0;
const int BLUE = 1;
const int NOFLAG = -1;

int shp[5];
int sforce[5];
int Arrow_Force;
int N;
int Red_Base;
int Blue_Base;

class Soldier {
protected:
	int type;
	int hp;
	int force;
	int no;
	int weapon[3];
	int cityno;
	int color;
	int killed;
	Soldier(int hh, int ff, int nn, int city, int cc);
public:
	virtual ~Soldier();
	virtual void March(int hour);
	virtual void Attack(Soldier &s, int hour);
	void Shot(Soldier &s, int hour);
	void Bomb(Soldier &s, int hour);
	virtual void Fight_back(Soldier &s, int hour);
	void HurtAndCure(int hh);
	bool simAttack(const Soldier &s) const;
	bool simHurt(int t) const;
	virtual bool simFight_back(const Soldier &s) const;
	void Killed();
	void Weapon(int &s, int &a, int &b) const;
	int Type() const;
	bool Alive() const;
	int No() const;
	void Report(int hour) const;
	void Earned(int e, int hour, int minute);
	bool Havebomb();
	void Died(int hour) const;
};

class Dragon :public Soldier {
private:
	double morale;
public:
	Dragon(int nn, int city, int cc, double mm);
	virtual ~Dragon();
	void Yell(int hour);
	void Set_Morale(double mm);
};

class Ninja :public Soldier {
private:
public:
	Ninja(int nn, int city, int cc);
	virtual ~Ninja();
	virtual void Fight_back(Soldier &s, int hour);
	virtual bool simFight_back(const Soldier &s) const;
};

class Iceman :public Soldier {
private:
	int step;
public:
	Iceman(int nn, int city, int cc);
	virtual ~Iceman();
	virtual void March(int hour);
};


class Lion :public Soldier {
private:
	int loyalty;
	static int decl;
public:
	Lion(int nn, int city, int cc, int ll);
	virtual ~Lion();
	bool Run(int hour);
	int HP() const;
	static void SetDec(int dd);
	void DecLoyalty();
};


class Wolf :public Soldier {
private:
public:
	Wolf(int nn, int city, int cc);
	virtual ~Wolf();
	void Rob(const Soldier &s);
};

struct City {
	Soldier* s[2];
	int Flag;
	int Win[2];
	int elements;
	int no;
};

class Headquarter {
private:
	int color;
	int elements;
	int order[5];
	//vector < Soldier* > sv;
	int sindex;
	int cityno;
	int taken;
public:
	static int colorindex;
	Headquarter();
	~Headquarter();
	void Init(int ee, int *oo, int cc);
	void Report(int hour);
	Soldier* Call(int hour);
	bool Taken(int hour);
	void SetE(int e);
	int HP() const;
};


class World {
private:
	City cities[25];
	Headquarter h[2];
	int totalcity;
	bool bluetaken;
	bool redtaken;
	Soldier * taker[2];
public:
	World(int nn, int mm);
	~World();
	bool finish();
	void Call(int hour);
	void LionRun(int hour);
	void March(int hour);
	void Produce();
	void Arrow(int hour);
	void Bomb(int hour);
	void Battle(int hour);
	void Report(int hour);
	void SReport(int hour);
	void Earned(int hour);
};

int Headquarter::colorindex = 0;
int Lion::decl = 0;

int main() {
	int kcase;
	cin >> kcase;
	for (int kkt = 1; kkt <= kcase; ++kkt) {
		Headquarter::colorindex = 0;
		cout << "Case " << kkt << ":" << endl;
		int m, k, t;
		cin >> m >> N >> Arrow_Force >> k >> t;
		World world(N, m);
		Red_Base = 0;
		Blue_Base = N+1;
		Lion::SetDec(k);
		for (int i = 0; i != 5; ++i) cin >> shp[i];
		for (int i = 0; i != 5; ++i) cin >> sforce[i];
		int time = 0;
		while (time <= t && !world.finish()) {
			int hour = time / 60;
			int minute = time % 60;
			int t1, t2;
			switch (minute) {
				case 0:
					world.Call(hour);
					time += 5;
					break;
				case 5:
					world.LionRun(hour);
					time += 5;
					break;
				case 10:
					world.March(hour);
					time += 10;
					break;
				case 20:
					world.Produce();
					time += 10;
					break;
				case 30:
					world.Earned(hour);
					time += 5;
					break;
				case 35:
					world.Arrow(hour);
					time += 3;
					break;
				case 38:
					world.Bomb(hour);
					time += 2;
					break;
				case 40:
					world.Battle(hour);
					time += 10;
					break;
				case 50:
					world.Report(hour);
					time += 5;
					break;
				case 55:
					world.SReport(hour);
					time += 5;
					break;
				default:
					cerr << "ERROR::Unkown time." << endl;
			}
		}
	}
	return 0;
}


Soldier::Soldier(int hh, int ff, int nn, int city, int cc)
:hp(hh), force(ff), no(nn), cityno(city), color(cc) {
	killed = 0;
	weapon[SWORD] = 0;
	weapon[BOMB] = 0;
	weapon[ARROW] = 0;
}

Soldier::~Soldier() {}

void Soldier::Attack(Soldier &s, int hour) {
	cout << setfill('0') << setw(3) << hour << ":40 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	cout << " attacked " << COLORNAME[color ^ 1] << " " << SNAME[s.Type()];
	cout << " " << s.No() << " in city " << cityno << " with ";
	cout << hp << " elements and force " << force << endl;;
	s.HurtAndCure(-(weapon[SWORD] + force));
	weapon[SWORD] = weapon[SWORD] * 8 / 10;
	if (s.Alive()) s.Fight_back(*this, hour);
	return;
}


bool Soldier::simAttack(const Soldier &s) const {
	return s.simHurt(weapon[SWORD] + force);
}

bool Soldier::simHurt(int t) const {
	return hp <= t;
}

bool Soldier::simFight_back(const Soldier &s) const {
	return s.simHurt(weapon[SWORD] + force / 2);
}


void Soldier::March(int hour) {
	cityno += color == RED ? 1 : -1;
	cout << setfill('0') << setw(3) << hour << ":10 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	if (color == RED && cityno == Blue_Base) cout << " reached blue headquarter with ";
	else if (color == BLUE && cityno == Red_Base) cout << " reached red headquarter with ";
	else cout << " marched to city " << cityno << " with ";
	cout << hp << " elements and force " << force << endl;
	return;
}

void Soldier::Shot(Soldier &s, int hour) {
	if (weapon[ARROW] == 0) return;
	s.HurtAndCure(-Arrow_Force);
	--weapon[ARROW];
	cout << setfill('0') << setw(3) << hour << ":35 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no << " shot";
	if (!s.Alive()) s.Killed();
	else cout << endl;
	return;
}


void Soldier::Bomb(Soldier &s, int hour) {
	cout << setfill('0') << setw(3) << hour << ":38 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no << " used a bomb";
	s.Killed();
}


void Soldier::Fight_back(Soldier &s, int hour) {
	cout << setfill('0') << setw(3) << hour << ":40 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	cout << " fought back against " << COLORNAME[color ^ 1];
	cout << " " << SNAME[s.Type()] << " " << s.No();
	cout << " in city " << cityno << endl;
	s.HurtAndCure(-(force /  2 + weapon[SWORD]));
	weapon[SWORD] = weapon[SWORD] * 8 / 10;
	return;
}

void Soldier::HurtAndCure(int hh) {
	hp += hh;
	if (hp <= 0) killed = 1;
	//if (hh > 0) cout << "   " << ":40 " << COLORNAME[color] << " " << SNAME[type] << " " << no << " get " << hh << " elements" << endl;
	return;
}


void Soldier::Killed() {
	killed = 1;
	hp = 0;
	cout << " and killed " << COLORNAME[color] << " " << SNAME[type] << " " << no << endl;
	return;
}


void Soldier::Weapon(int &s, int &a, int &b) const {
	s = weapon[SWORD];
	a = weapon[BOMB];
	b = weapon[ARROW];
	return;
}


int Soldier::Type() const {
	return type;
}


bool Soldier::Alive() const {
	return (killed == 0);
}


int Soldier::No() const {
	return no;
}

void Soldier::Report(int hour) const {
	cout << setfill('0') << setw(3) << hour << ":55 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	cout << " has ";
	bool first = true;
	if (weapon[ARROW]) {
		if (!first) cout << ",";
		cout << "arrow(" << weapon[ARROW] << ")";
		first = false;
	}
	if (weapon[BOMB]) {
		if (!first) cout << ",";
		cout << "bomb";
		first = false;
	}
	if (weapon[SWORD]) {
		if (!first) cout << ",";
		cout << "sword(" << weapon[SWORD] << ")";
		first = false;
	}
	if (first) cout << "no weapon";
	cout << endl;
	return;
}


void Soldier::Earned(int e, int hour, int minute) {
	cout << setfill('0') << setw(3) << hour << ":" <<  minute << " ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	cout << " earned " << e << " elements for his headquarter" << endl;
	return;
}


bool Soldier::Havebomb() {
	return weapon[BOMB];
}

void Soldier::Died(int hour) const {
	cout << setfill('0') << setw(3) << hour << ":40 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	cout << " was killed in city " << cityno << endl;
	return;
}


Dragon::Dragon(int nn, int city, int cc, double mm)
:Soldier(shp[0], sforce[0], nn, city, cc), morale(mm) {
	int c = nn % 3;
	if (c == SWORD) weapon[SWORD] = force / 5;
	else if (c == ARROW) weapon[ARROW] = 3;
	else weapon[BOMB] = 1;
	type = DRAGON;
	cout << "Its morale is " << setiosflags(ios::fixed) << setprecision(2) << morale << endl;
}

Dragon::~Dragon() {}

void Dragon::Yell(int hour) {
	if (killed == 0 && morale > 0.8) {
		cout << setfill('0') << setw(3) << hour << ":40 " << COLORNAME[color];
		cout << " dragon " << no << " yelled in city " << cityno << endl;
	}
	return;
}

void Dragon::Set_Morale(double mm) {
	morale += mm;
	return;
}

Ninja::Ninja(int nn, int city, int cc)
:Soldier(shp[1], sforce[1], nn, city, cc) {
	int c = (nn + 2) % 3;
	if (c != SWORD) weapon[SWORD] = force / 5;
	if (c != ARROW) weapon[ARROW] = 3;
	if (c != BOMB) weapon[BOMB] = 1;
	type = NINJA;
}


Ninja::~Ninja() {}

void Ninja::Fight_back(Soldier &s, int hour) {}

bool Ninja::simFight_back(const Soldier &S) const {
	return false;
}


Iceman::Iceman(int nn, int city, int cc)
:Soldier(shp[2], sforce[2], nn, city, cc) {
	int c = nn % 3;
	if (c == SWORD) weapon[SWORD] = force / 5;
	else if (c == ARROW) weapon[ARROW] = 3;
	else weapon[BOMB] = 1;
	step = 2;
	type = ICEMAN;
}

Iceman::~Iceman() {}

void Iceman::March(int hour) {
	--step;
	if (step == 0) {
		hp -= 9;
		if (hp <= 0) hp = 1;
		step = 2;
		force += 20;
	}
	cityno += color == RED ? 1 : -1;
	cout << setfill('0') << setw(3) << hour << ":10 ";
	cout << COLORNAME[color] << " " << SNAME[type] << " " << no;
	if (color == RED && cityno == Blue_Base) cout << " reached blue headquarter with ";
	else if (color == BLUE && cityno == Red_Base) cout << " reached red headquarter with ";
	else cout << " marched to city " << cityno << " with ";
	cout << hp << " elements and force " << force << endl;
	return;
}


Lion::Lion(int nn, int city, int cc, int ll)
:Soldier(shp[3], sforce[3], nn, city, cc), loyalty(ll) {
	cout << "Its loyalty is " << loyalty << endl;
	type = LION;
}

Lion::~Lion() {}

bool Lion::Run(int hour) {
	if (loyalty <= 0) {
		killed = 1;
		cout << setfill('0') << setw(3) << hour << ":05 ";
		cout << COLORNAME[color] << " lion " << no << " ran away" << endl;
		return true;
	}
	return false;
}

int Lion::HP() const {
	return hp;
}


void Lion::SetDec(int dd) {
	decl = dd;
	return;
}

void Lion::DecLoyalty() {
	loyalty -= decl;
	return;
}



Wolf::Wolf(int nn, int city, int cc)
:Soldier(shp[4], sforce[4], nn, city, cc) {
	type = WOLF;
}

Wolf::~Wolf() {}

void Wolf::Rob(const Soldier &s) {
	int w[3];
	s.Weapon(w[0], w[1], w[2]);
	for (int i = 0; i != 3; ++i) {
		if (weapon[i] == 0) weapon[i] = w[i];
	}
	return;
}


Headquarter::Headquarter() {}


Headquarter::~Headquarter() {}


void Headquarter::Init(int ee, int *oo, int cc) {
	elements = ee;
	cityno = cc;
	for (int i = 0; i != 5; ++i) order[i] = oo[i];
	sindex = 1;
	color = colorindex++;
	taken = 2;
}


Soldier* Headquarter::Call(int hour) {
	Soldier *sp = nullptr;
	int ind = order[(sindex-1) % 5];
	if (elements >= shp[ind]) {
		elements -= shp[ind];
		cout << setfill('0') << setw(3) << hour << ":00 ";
		cout << COLORNAME[color] << " " << SNAME[ind] << " " << sindex;
		cout << " born" << endl;
		switch (ind) {
			case DRAGON:
				sp = new Dragon(sindex++, cityno, color, (double)elements / (double)shp[ind]);
				break;
			case NINJA:
				sp = new Ninja(sindex++, cityno, color);
				break;
			case ICEMAN:
				sp = new Iceman(sindex++, cityno, color);
				break;
			case LION:
				sp = new Lion(sindex++, cityno, color, elements);
				break;
			case WOLF:
				sp = new Wolf(sindex++, cityno, color);
				break;
			default:
				cout << "ERROR::Undefined type of soldier." << endl;
		}
		//sv.push_back(sp);
	}
	return sp;
}

bool Headquarter::Taken(int hour) {
	--taken;
	if (taken == 0) {
		cout << setfill('0') << setw(3) << hour << ":10 ";
		cout << COLORNAME[color] << " headquarter was taken" << endl;
		return true;
	}
	return false;
}

void Headquarter::Report(int hour) {
	cout << setfill('0') << setw(3) << hour << ":50 ";
	cout << elements << " elements in " << COLORNAME[color] << " headquarter" << endl;
	return;
}


void Headquarter::SetE(int e) {
	elements += e;
	return;
}

int Headquarter::HP() const {
	return elements;
}


World::World(int nn, int mm): totalcity(nn) {
	for (int i = 0; i <= totalcity+1; ++i) {
		cities[i].s[RED] = nullptr;
		cities[i].s[BLUE] = nullptr;
		cities[i].Flag = NOFLAG;
		cities[i].Win[RED] = 0;
		cities[i].Win[BLUE] = 0;
		cities[i].elements = 0;
		cities[i].no = i;
	}
	Headquarter::colorindex = 0;
	int redorder[5] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
	int blueorder[5] = {LION, DRAGON, NINJA, ICEMAN, WOLF};
	h[0].Init(mm, redorder, 0);
	h[1].Init(mm, blueorder, totalcity+1);
	redtaken = false;
	bluetaken = false;
	taker[RED] = nullptr;
	taker[BLUE] = nullptr;
}

World::~World() {
	for (int i = 0; i <= totalcity+1; ++i) {
		if (cities[i].s[RED]) delete cities[i].s[RED];
		cities[i].s[RED] = nullptr;
		if (cities[i].s[BLUE]) delete cities[i].s[BLUE];
		cities[i].s[BLUE] = nullptr;
	}
	if (taker[RED]) delete taker[RED];
	if (taker[BLUE]) delete taker[BLUE];
	taker[RED] = nullptr;
	taker[BLUE] = nullptr;
}

bool World::finish() {
	return bluetaken || redtaken;
}

void World::Call(int hour) {
	cities[0].s[RED] = h[RED].Call(hour);
	cities[totalcity+1].s[BLUE] = h[BLUE].Call(hour);
	return;
}

void World::LionRun(int hour) {
	for (int i = 0; i <= totalcity+1; ++i) {
		if (cities[i].s[RED] && cities[i].s[RED]->Type() == LION) {
			if (((Lion*)cities[i].s[RED])->Run(hour)) {
				delete cities[i].s[RED];
				cities[i].s[RED] = nullptr;
			}
		}
		if (cities[i].s[BLUE] && cities[i].s[BLUE]->Type() == LION) {
			if (((Lion*)cities[i].s[BLUE])->Run(hour)) {
				delete cities[i].s[BLUE];
				cities[i].s[BLUE] = nullptr;
			}
		}
	}
	return;
}


void World::March(int hour) {
	for (int i = totalcity+1; i > 0; --i) cities[i].s[RED] = cities[i-1].s[RED];
	cities[0].s[RED] = nullptr;
	for (int i = 0; i <= totalcity; ++i) cities[i].s[BLUE] = cities[i+1].s[BLUE];
	cities[totalcity+1].s[BLUE] = nullptr;
	if (cities[0].s[BLUE]) {
		cities[0].s[BLUE]->March(hour);
		if (h[RED].Taken(hour)) redtaken = true;
		else taker[RED] = cities[0].s[BLUE];
		//delete cities[0].s[BLUE];
		cities[0].s[BLUE] = nullptr;
	}
	for (int i = 1; i <= totalcity; ++i) {
		Soldier *sp = cities[i].s[RED];
		if (sp) sp->March(hour);
		sp = cities[i].s[BLUE];
		if (sp) sp->March(hour);
	}
	if (cities[totalcity+1].s[RED]) {
		cities[totalcity+1].s[RED]->March(hour);
		if (h[BLUE].Taken(hour)) bluetaken = true;
		else taker[BLUE] = cities[totalcity+1].s[RED];
		//delete cities[totalcity+1].s[RED];
		cities[totalcity+1].s[RED] = nullptr;
	}
	return;
}


void World::Produce() {
	for (int i = 1; i <= totalcity; ++i) cities[i].elements += 10;
	return;
}


void World::Earned(int hour) {
	for (int i = 1; i <= totalcity; ++i) {
		if (cities[i].elements != 0) {
			if (!cities[i].s[RED] && cities[i].s[BLUE]) {
				cities[i].s[BLUE]->Earned(cities[i].elements, hour, 30);
				h[BLUE].SetE(cities[i].elements);
				cities[i].elements = 0;
			}
			else if (!cities[i].s[BLUE] && cities[i].s[RED]) {
				cities[i].s[RED]->Earned(cities[i].elements, hour, 30);
				h[RED].SetE(cities[i].elements);
				cities[i].elements = 0;
			}
		}
	}
}

void World::Arrow(int hour) {
	for (int i = 1; i <= totalcity; ++i) {
 		if (cities[i].s[RED] && cities[i+1].s[BLUE]) cities[i].s[RED]->Shot(*(cities[i+1].s[BLUE]), hour);
 		if (cities[i].s[BLUE] && cities[i-1].s[RED]) cities[i].s[BLUE]->Shot(*(cities[i-1].s[RED]), hour);

	}
}


void World::Bomb(int hour) {
	for (int i = 1; i <= totalcity; ++i) {
		Soldier *sp1 = nullptr;
		Soldier *sp2 = nullptr;
		if (cities[i].Flag == NOFLAG) {
			sp1 = i % 2 ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = i % 2 ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		else {
			sp1 = cities[i].Flag == RED ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = cities[i].Flag == RED ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		if (sp1 == nullptr || sp2 == nullptr) continue;
		if (!sp1->Alive() || !sp2->Alive()) continue;
		if (sp1->Havebomb()) {
			if (!sp1->simAttack(*sp2) && sp2->simFight_back(*sp1)) {
				sp1->Bomb(*sp2, hour);
				delete cities[i].s[RED];
				delete cities[i].s[BLUE];
				cities[i].s[RED] = nullptr;
				cities[i].s[BLUE] = nullptr;
				continue;
			}
		}
		if (sp2->Havebomb()) {
			if (sp1->simAttack(*sp2)) {
				sp2->Bomb(*sp1, hour);
				delete cities[i].s[RED];
				delete cities[i].s[BLUE];
				cities[i].s[RED] = nullptr;
				cities[i].s[BLUE] = nullptr;
			}
		}
	}
	return;
}

void World::Battle(int hour) {
	deque < Soldier* > rre;
	deque < Soldier* > bre;
	for (int i = 1; i <= totalcity; ++i) {
		Soldier *sp1 = nullptr;
		Soldier *sp2 = nullptr;
		if (cities[i].Flag == NOFLAG) {
			sp1 = i % 2 ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = i % 2 ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		else {
			sp1 = cities[i].Flag == RED ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = cities[i].Flag == RED ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		if (sp1 && sp2) {
			Soldier *winner = nullptr;
			if (!sp1->Alive() && sp2->Alive()) winner = sp2;
			else if (sp1->Alive() && !sp2->Alive()) winner = sp1;
			else if (sp1->Alive() && sp2->Alive()) {
				if (sp1->simAttack(*sp2)) winner = sp1;
				else if (sp2->simFight_back(*sp1)) winner = sp2;
			}
			if (winner) {
				if (winner == cities[i].s[RED]) {
					rre.push_front(winner);
					//cout << "push_front red " << SNAME[winner->Type()] << endl;
				}
				else {
					bre.push_back(winner);
					//cout << "push_back blue " << SNAME[winner->Type()] << endl;
				}
			}
		}
	}
	int awardnum = h[RED].HP() / 8;
	while (rre.size() > awardnum) {
		//cout << "pop_back red " << SNAME[rre.back()->Type()] << endl;
		rre.pop_back();
	}
	awardnum = h[BLUE].HP() / 8;
	while (bre.size() > awardnum) bre.pop_back();

	for (int i = 1; i <= totalcity; ++i) {
		Soldier *sp1 = nullptr;
		Soldier *sp2 = nullptr;
		if (cities[i].Flag == NOFLAG) {
			sp1 = i % 2 ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = i % 2 ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		else {
			sp1 = cities[i].Flag == RED ? cities[i].s[RED] : cities[i].s[BLUE];
			sp2 = cities[i].Flag == RED ? cities[i].s[BLUE] : cities[i].s[RED];
		}
		if (sp1 && !sp2) {
			if (!sp1->Alive()) {
				if (sp1 == cities[i].s[RED]) cities[i].s[RED] = nullptr;
				else cities[i].s[BLUE] = nullptr;
				delete sp1;
			}
		}
		else if (!sp1 && sp2) {
			if (!sp2->Alive()) {
				if (sp2 == cities[i].s[RED]) cities[i].s[RED] = nullptr;
				cities[i].s[BLUE] = nullptr;
				delete sp2;
			}
		}
		else if (sp1 && sp2) {
			if (!sp1->Alive() && !sp2->Alive()) {
				delete cities[i].s[RED];
				delete cities[i].s[BLUE];
				cities[i].s[RED] = nullptr;
				cities[i].s[BLUE] = nullptr;
				continue;
			}
			Soldier *winner = nullptr;
			Soldier *loser = nullptr;
			if (!sp1->Alive()) {
				winner = sp2;
				loser = sp1;
			}
			else if (!sp2->Alive()) {
				winner = sp1;
				loser = sp2;
			}
			else {
				int lhp1, lhp2;
				if (sp1->Type() == LION) lhp1 = ((Lion*)sp1)->HP();
				if (sp2->Type() == LION) lhp2 = ((Lion*)sp2)->HP();
				sp1->Attack(*sp2, hour);
				if (sp2->Alive()) {
					if (sp1->Alive()) {
						cities[i].Win[RED] = cities[i].Win[BLUE] = 0;
						winner = nullptr;
						loser = nullptr;
						if (sp1->Type() == DRAGON) {
							((Dragon*)sp1)->Set_Morale(-0.2);
							((Dragon*)sp1)->Yell(hour);
						}
						if (sp2->Type() == DRAGON) ((Dragon*)sp2)->Set_Morale(-0.2);
						if (sp1->Type() == LION) ((Lion*)sp1)->DecLoyalty();
						if (sp2->Type() == LION) ((Lion*)sp2)->DecLoyalty();
					}
					else {
						winner = sp2;
						loser = sp1;
					}
				}
				else {
					winner = sp1;
					loser = sp2;
				}
				if (winner && loser) {
					if (loser->Type() == LION) {
						int lhp = loser == sp1 ? lhp1 : lhp2;
						winner->HurtAndCure(lhp);
					}
					loser->Died(hour);
				}
			}
			if (winner && loser) {
				if (winner->Type() == DRAGON) {
					((Dragon*)winner)->Set_Morale(0.2);
					if (winner == sp1) ((Dragon*)winner)->Yell(hour);
				}
				if (winner->Type() == WOLF) {
					((Wolf*)winner)->Rob(*loser);
				}
				if (winner == cities[i].s[RED]) {
					if (winner == rre.back()) {
						rre.pop_back();
						winner->HurtAndCure(8);
						h[RED].SetE(-8);
					}
					if (cities[i].elements > 0) {
						winner->Earned(cities[i].elements, hour, 40);
						h[RED].SetE(cities[i].elements);
						cities[i].elements = 0;
					}
				}
				else {
					if (winner == bre.front()) {
						bre.pop_front();
						winner->HurtAndCure(8);
						h[BLUE].SetE(-8);
					}
					if (cities[i].elements > 0) {
						winner->Earned(cities[i].elements, hour, 40);
						h[BLUE].SetE(cities[i].elements);
						cities[i].elements = 0;
					}
				}
				if (loser == cities[i].s[RED]) cities[i].s[RED] = nullptr;
				else cities[i].s[BLUE] = nullptr;
				delete loser;
				if (winner == cities[i].s[RED]) {
					++cities[i].Win[RED];
					cities[i].Win[BLUE] = 0;
					if (cities[i].Win[RED] == 2 && cities[i].Flag != RED) {
						cities[i].Win[RED] = 0;
						cities[i].Flag = RED;
						cout << setfill('0') << setw(3) << hour << ":40 ";
						cout << "red flag raised in city " << i << endl;
					}
				}
				else {
					++cities[i].Win[BLUE];
					cities[i].Win[RED] = 0;
					if (cities[i].Win[BLUE] == 2 && cities[i].Flag != BLUE) {
						cities[i].Win[BLUE] = 0;
						cities[i].Flag = BLUE;
						cout << setfill('0') << setw(3) << hour << ":40 ";
						cout << "blue flag raised in city " << i << endl;
					}
				}
			}
		}
	}
}

void World::Report(int hour) {
	h[RED].Report(hour);
	h[BLUE].Report(hour);
	return;
}

void World::SReport(int hour) {
	for (int i = 1; i <= totalcity; ++i) {
		if (cities[i].s[RED]) cities[i].s[RED]->Report(hour);
	}
	if (taker[BLUE]) taker[BLUE]->Report(hour);
	if (taker[RED]) taker[RED]->Report(hour);
	for (int i = 1; i <= totalcity; ++i) {
		if (cities[i].s[BLUE]) cities[i].s[BLUE]->Report(hour);
	}
}