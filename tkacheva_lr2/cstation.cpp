#include <unordered_map>
#include <cmath>
#include <fstream>
#include "cstation.h"
#include "header.h"
int cstation::ID = 0;
cstation::cstation()
{
	id = ID++;
}
istream& operator>>(istream& in, cstation& cs)
{
	cout << "Enter the name of the compressor station: " << endl;
	in.ignore();
	getline(in, cs.name);
	cout << "Enter the number of workshops: " << endl;
	getcorrectnumber(cs.workshop);
	cout << "Enter the number of workshops in operation: " << endl;
	getcorrectnumber(cs.workingwshop);
	while (cs.workshop < cs.workingwshop) {
		cout << "The number of operating compressor stations can't be more than the total number of stations!" << endl << "Try again!" << endl;
		getcorrectnumber(cs.workingwshop);
	}
	cs.efficiency = round(double(cs.workingwshop) / double(cs.workshop) * 100);
	cout << "Cstation effiency = " << cs.efficiency << "%" << endl;
	return in;
}
ostream& operator<<(ostream& out, unordered_map <int, cstation>& cstations) {
	if (cstations.size() == 0) {
		cout << "There is no data about cstations. " << endl;
	}
	else {
		for (auto& cs : cstations) {
			out << "Compressor station ID: " << cs.second.id << endl;
			out << "Compressor station name: " << cs.second.name << endl;
			out << "The number of workshops: " << cs.second.workshop << endl;
			out << "The number of working workshops: " << cs.second.workingwshop << endl;
			out << "Effiency: " << cs.second.efficiency << "%" << endl;
		}
	}
	return out;
}
ofstream& operator<<(ofstream& fout, cstation& cs) {
	fout << cs.name << endl << cs.workshop << endl << cs.workingwshop << endl << cs.efficiency << endl;
	return fout;
}
ifstream& operator>>(ifstream& fin, cstation& cs) {
	fin.ignore();
	getline(fin, cs.name);
	fin >> cs.workshop;
	fin >> cs.workingwshop;
	fin >> cs.efficiency;
	return fin;
}
void deletecstations(unordered_map<int, cstation>& cstations) {
	int action;
	cout << "1. Delete all cstations. " << endl
		<< "2. Select cstations to delete. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	while (action < 0 || action > 2) {
		cout << "Try again!" << endl;
		getcorrectnumber(action);
	}
	if (action == 1) {
		cstations.clear();
		cout << "All cstations have been deleted. " << endl;
	}
	else {
		vector <int> selectcstations = selectcs(cstations);
		if (selectcstations.size() == 0) {
			cout << "No items selected. " << endl;
		}
		else {
			int i = 0;
			for (int i : selectcstations) {
				cstations.erase(i);
			}
			cout << "Selected cstations have been deleted. " << endl;
		}
	}
}
vector<int> selectcs(unordered_map<int, cstation> cstations) {
	int action;
	vector <int> selectcstations;
	cout << "1. Select cstation by name. " << endl
		<< "2. Select cstation by efficiency. " << endl
		<< "0. Exit. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	switch (action) {
	case 1: {
		string name;
		cout << "Enter cstation name: ";
		cin.ignore();
		getline(cin, name);
		for (auto& cs : cstations) {
			if (cs.second.name.find(name) != string::npos) {
				selectcstations.push_back(cs.second.id);
			}
		}
		break;
	}
	case 2: {
		int efficiency;
		cout << "Enter efficiency percentage: ";
		getcorrectnumber(efficiency);
		while (efficiency > 100 || efficiency < 0) {
			cout << "Try again!";
			getcorrectnumber(efficiency);
		}
		for (auto& cs : cstations) {
			if (cs.second.efficiency == efficiency) {
				selectcstations.push_back(cs.second.id);
			}
		}
		break;
	}
	case 0: {
		return selectcstations;
		break;
	}
	}
	return selectcstations;
}
void changeworkshops(unordered_map<int, cstation>& cstations) {
	int action;
	cout << "1. Edit all cstations. " << endl
		<< "2. Select cstations to edit. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	while (action < 0 || action > 2) {
		cout << "Try again!" << endl;
		getcorrectnumber(action);
	}
	if (action == 1) {
		for (auto& cs : cstations) {
			cout << "The name of cstation: " << cs.second.name << endl;
			cout << "The number of workshops: " << cs.second.workshop << endl;
			cout << "The number of working workshops: " << cs.second.workingwshop << endl;
			cout << "Enter new number of working workshops: " << endl;
			getcorrectnumber(cs.second.workingwshop);
			while (cs.second.workshop < cs.second.workingwshop) {
				cout << "The number of operating compressor stations can't be more than the total number of stations!" << endl << "Try again!" << endl;
				getcorrectnumber(cs.second.workingwshop);
			}
			cs.second.efficiency = round(double(cs.second.workingwshop) / double(cs.second.workshop) * 100);
			cout << "Cstation effiency = " << cs.second.efficiency << "%" << endl;
		}
		cout << "All cstations have been edited." << endl;
	}
	else {
		vector <int> selectcstations = selectcs(cstations);
		if (selectcstations.size() == 0) {
			cout << "No items selected. " << endl;
		}
		else {
			for (auto& cs : cstations) {
				if (contains(selectcstations, cs.second.id)) {
					cout << "The name of cstation: " << cs.second.name << endl;
					cout << "The number of workshops: " << cs.second.workshop << endl;
					cout << "The number of working workshops: " << cs.second.workingwshop << endl;
					cout << "Enter new number of working workshops: " << endl;
					getcorrectnumber(cs.second.workingwshop);
					while (cs.second.workshop < cs.second.workingwshop) {
						cout << "The number of operating compressor stations can't be more than the total number of stations!" << endl << "Try again!" << endl;
						getcorrectnumber(cs.second.workingwshop);
					}
					cs.second.efficiency = round(double(cs.second.workingwshop) / double(cs.second.workshop) * 100);
					cout << "Cstation effiency = " << cs.second.efficiency << "%" << endl;
				}
			}
			cout << "Selected cstations have been edited. " << endl;
		}
	}
}
