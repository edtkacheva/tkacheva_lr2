#include "pipe.h"
#include "header.h"
#include <unordered_map>
#include <fstream>
using namespace std;
int pipe::ID = 0;
pipe::pipe()
{
	id = ID++;
}
istream& operator>>(istream& in, pipe& p)
{
	cout << "Enter pipe name: " << endl;
	in.ignore();
	getline(in, p.name);
	cout << "Enter pipe length: " << endl;
	getcorrectnumber(p.length);
	cout << "Enter pipe diameter: " << endl;
	getcorrectnumber(p.diameter);
	cout << "Is the pipe being repaired? (1 - yes, 0 - no): " << endl;
	getcorrectnumber(p.inrepair);
	return in;
}
ostream& operator<<(ostream& out, unordered_map<int, pipe>& pipes)
{
	if (pipes.size() == 0) {
		cout << "There is no data about pipes. " << endl;
	}
	else {
		for (auto& p : pipes) {
			out << "Pipe ID: " << p.second.id << endl;
			out << "Pipe name: " << p.second.name << endl;
			out << "Pipe length: " << p.second.length << endl;
			out << "Pipe diameter: " << p.second.diameter << endl;
			out << "Condition 'under repair': " << p.second.inrepair << endl;
		}
	}
	return out;
}
ofstream& operator<<(ofstream& fout, pipe& p)
{
	fout << p.name << endl << p.length << endl << p.diameter << endl << p.inrepair << endl;
	return fout;
}
ifstream& operator>>(ifstream& fin, pipe& p)
{
	fin.ignore();
	getline(fin, p.name);
	fin >> p.length;
	fin >> p.diameter;
	fin >> p.inrepair;
	return fin;
}
void deletepipes(unordered_map<int, pipe>& pipes) {
	int action;
	cout << "1. Delete all pipes. " << endl
		<< "2. Select pipes to delete. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	while (action < 0 || action > 2) {
		cout << "Try again!" << endl;
		getcorrectnumber(action);
	}
	if (action == 1) {
		pipes.clear();
		cout << "All pipes have been deleted. " << endl;
	}
	else {
		vector <int> selectpipes = selectpipe(pipes);
		if (selectpipes.size() == 0) {
			cout << "No items selected. " << endl;
		}
		else {
			int i = 0;
			for (int i : selectpipes) {
				pipes.erase(i);
			}
			cout << "Selected pipes have been deleted. " << endl;
		}
	}
}
void changeinrepair(unordered_map<int, pipe>& pipes) {
	int action;
	cout << "1. Edit all pipes. " << endl
		<< "2. Select pipes to edit. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	while (action < 0 || action > 2) {
		cout << "Try again!" << endl;
		getcorrectnumber(action);
	}
	if (action == 1) {
		for (auto& p : pipes) {
			p.second.inrepair = !p.second.inrepair;
		}
		cout << "All pipes have been edited." << endl;
	}
	else {
		vector <int> selectpipes = selectpipe(pipes);
		if (selectpipes.size() == 0) {
			cout << "No items selected. " << endl;
		}
		else {
			for (auto& p : pipes) {
				if (contains(selectpipes, p.second.id)) {
					p.second.inrepair = !p.second.inrepair;
				}
			}
			cout << "Selected pipes have been edited. " << endl;
		}
	}
}
vector<int> selectpipe(unordered_map<int, pipe> pipes) {
	int action;
	vector <int> selectpipes;
	cout << "1. Select pipes by name. " << endl
		<< "2. Select pipe based on the characteristics in repair. " << endl
		<< "0. Exit. " << endl
		<< "Chose action: ";
	getcorrectnumber(action);
	switch (action) {
	case 1: {
		string name;
		cout << "Enter pipe name: ";
		cin.ignore();
		getline(cin, name);
		for (auto& p : pipes) {
			if (p.second.name.find(name) != string::npos) {
				selectpipes.push_back(p.second.id);
			}
		}
		break;
	}
	case 2: {
		bool characteristic;
		cout << "Enter characteristic in repair (0 or 1): ";
		getcorrectnumber(characteristic);
		for (auto& p : pipes) {
			if (p.second.inrepair == characteristic) {
				selectpipes.push_back(p.second.id);
			}
		}
		break;
	}
	case 0: {
		return selectpipes;
		break;
	}
	}
	return selectpipes;
}
