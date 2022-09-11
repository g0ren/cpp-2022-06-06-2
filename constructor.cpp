#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Unit {
	map<int, float> *tmp;
public:
	Unit(int i = 0, float f = 0) {
		this->tmp = new map<int, float>;
		this->tmp->insert(make_pair(i, f));
	}
	Unit(Unit *&unit) {
		this->tmp = unit->tmp;
	}
	Unit(Unit *&&unit) {
		this->tmp = unit->tmp;
	}
	void addVal(int i, float f) {
		this->tmp->insert(make_pair(i, f));
	}
	void show() {
		for (const auto& [i, f] : *(this->tmp))
			cout << i << ',' << f << ' ';
	}
};

class ListVect {
	list<vector<Unit*>> lvect;
	Unit **matrixUnit;
public:
	ListVect(Unit *unit) {
		vector<Unit*> vect;
		vect.push_back(unit);
		list<vector<Unit*>> lst;
		lst.push_front(vect);
		this->lvect = lst;
		this->matrixUnit = nullptr;
	}
	ListVect() :
			ListVect(nullptr) {

	}
	ListVect(ListVect &listvect) {
		for (auto v : listvect.lvect) {
			vector<Unit*> vect(v.size());
			for (size_t i = 0; i < v.size(); i++) {
				vect[i] = v[i];
			}
			this->lvect.push_back(vect);
		}
		this->matrixUnit = listvect.matrixUnit;
	}

	ListVect(ListVect &&listvect) {
		this->lvect = listvect.lvect;
		this->matrixUnit = listvect.matrixUnit;
	}

	void show() {
		for (auto v : this->lvect) {
			for (auto u : v) {
				u->show();
				cout << "; ";
			}
			cout << endl;
		}
	}

};

int main() {
	Unit *u = new Unit(0, 1.0);
	u->addVal(1, 1.1);
	u->addVal(2, 2.2);
	u->addVal(3, 4.2);
	//u->show();
	Unit *u2 = u;
	//u2->show();
	ListVect lv(u);
	lv.show();
	ListVect lv2 = lv;
	lv2.show();
	ListVect lv3(move(lv));
	lv3.show();
	return 0;
}
