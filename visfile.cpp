#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void delim() {
	char c = cin.peek();
	while (c == '\n' || c == ' ') {
		cin.get(c);
		c = cin.peek();
	}
	return;
}

struct dir{
	string name;
	int layer;
	vector< dir* > dirs;
	vector< string > file;
};

dir root;

ostream & operator<<(ostream &os, dir d) {
	string s = "";
	for (int i = 0; i != d.layer; ++i) s += "|     ";
	cout << s << d.name << endl;
	for (auto iter = d.dirs.begin(); iter != d.dirs.end(); ++iter) {
		cout << **iter;
	}
	if (!d.file.empty()) sort(d.file.begin(), d.file.end());
	for (vector<string>::iterator iter = d.file.begin(); iter != d.file.end(); ++iter) {
		cout << s << *iter << endl;
	}
	return os;
}

void del(dir d) {
	for (auto iter =  d.dirs.begin(); iter != d.dirs.end(); ++iter) {
		del(**iter);
		delete *iter;
	}
}


void S(dir *d);

void D(dir *d) {
	dir *dp = new dir;
	cin >> dp->name;
	delim();
	//cout << endl << "D " << d->name << "  " << dp->name << hex << "   "<< *nextdir << endl;
	dp->layer = d->layer + 1;
	dp->file.clear();
	dp->dirs.clear();
	d->dirs.push_back(dp);
	// cout << "here" << endl;
	S(dp);
	char c;
	cin >> c; 						//read ']'
	delim();
	return;
}

void B(dir *d) {
	//cout << "B " << d->name << hex << "   " << *nextdir;
	if (cin.peek() == 'd') D(d);
	else {
		string fname;
		cin >> fname;
		d->file.push_back(fname);
		delim();
		//cout << "  " << fname << endl;
	}
}

void S(dir *d) {
	//cout << "S " << d->name << hex << "   " << *nextdir << endl;
	delim();
	if (cin.peek() == 'f' || cin.peek() == 'd') {
		B(d);
		S(d);
	}
	//else cout << "S.cin.peek() = " << (char)cin.peek() << endl;
	return;
}


int main() {
	int kcase = 0;
	while (cin.peek() != '#') {
		root.name = "ROOT";
		root.layer = 0;
		root.dirs.clear();
		root.file.clear();
		//cout << "root.son = " << hex << root.son << endl;
		S(&root);
		//cout << "root.son = " << hex << root.son << endl;
		char c;
		cin >> c;
		delim();
		//cout << "c = " << (char)c << endl;
		cout << "DATA SET " << ++kcase << ":" << endl;
		cout << root << endl;
		del(root);
	}
}