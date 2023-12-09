#include "gts.h"
#include "header.h"
#include "pipe.h"
#include "cstation.h"
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
void gts::printmenu() {
	cout << "Menu: " << endl
		<< "1. Add a pipe." << endl
		<< "2. Add a compressor station." << endl
		<< "3. View all pipes." << endl
		<< "4. View all compressor stations." << endl
		<< "5. Save data to file." << endl
		<< "6. Load data from file." << endl
		<< "7. Delete pipes." << endl
		<< "8. Delete cstations." << endl
		<< "9. Edit pipes." << endl
		<< "10. Edit cstations. " << endl
		<< "11. Combine pipes and cstations." << endl
		<< "12. View gts. " << endl
		<< "13. Topological graph sorting. " << endl
		<< "14. Delete a connection in gts. " << endl
		<< "0. Exit." << endl
		<< "--------------------------------" << endl
		<< "Enter the required number:" << endl;
}
void gts::viewpipes(unordered_map<int, pipe> pipes) {
	if (pipes.size() == 0) {
		cout << "There is no data about pipes. " << endl;
	}
	else {
		for (auto& p : pipes) {
			cout << p.second;
		}
	}
}
void gts::viewcs(unordered_map<int, cstation> cstations) {
	if (cstations.size() == 0) {
		cout << "There is no data about cstations. " << endl;
	}
	else {
		for (auto& cs : cstations) {
			cout << cs.second;
		}
	}
}
void gts::save_data(unordered_map<int, pipe> pipes, unordered_map<int, cstation> cstations) {
	ofstream fout;
	string filename;
	cout << "Enter file name: ";
	cin >> filename;
	fout.open(filename, ofstream::app, ofstream::trunc);
	if (fout.is_open()) {
		if (pipes.size() == 0 && cstations.size() == 0) {
			cout << "There is no data about pipes and cstations." << endl;
		}
		else {
			fout << pipes.size() << " " << cstations.size() << endl;
			for (auto& p : pipes) {
				fout << p.second;
			}
			for (auto& cs : cstations) {
				fout << cs.second;
			}
			cout << "Data was successfully saved." << endl;
		}
		fout.close();
	}
	else {
		cout << "File couldn't be open." << endl;
	}
}
void gts::load_data(unordered_map<int, pipe>& pipes, unordered_map<int, cstation>& cstations) {
	ifstream fin;
	string filename;
	string line;
	int numberpipe;
	int numbercstation;
	cout << "Enter file name: ";
	cin >> filename;
	fin.open(filename, ifstream::app);
	if (fin.is_open()) {
		if (fin.peek() == ifstream::traits_type::eof()) {
			cout << "There is no data in file or the file name is incorrect." << endl;
		}
		else {
			fin >> numberpipe >> numbercstation;
			if (numberpipe == 0) {
				cout << "There is no data about pipes. " << endl;
				for (int i = 1; i <= numbercstation; i++) {
					cstation cs;
					fin >> cs;
					cstations.insert({ cs.getid(), cs });
				}
			}
			else if (numbercstation == 0) {
				cout << "There is no data about cstations. " << endl;
				for (int i = 1; i <= numberpipe; i++) {
					pipe p;
					fin >> p;
					pipes.insert({ p.getid(),p });
				}
			}
			else {
				for (int i = 1; i <= numberpipe; i++) {
					pipe p;
					fin >> p;
					pipes.insert({ p.getid(),p });
				}
				for (int i = 1; i <= numbercstation; i++) {
					cstation cs;
					fin >> cs;
					cstations.insert({ cs.getid(), cs });
				}
			}

		}
	}
	else {
		cout << "File couldn't be open." << endl;
	}
}
void gts::deletepipes(unordered_map<int, pipe>& pipes, unordered_map<int, cstation>& cstations, vector < vector <int> >& adjmatrix) {
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
		adjmatrix.clear();
		for (auto& cs : cstations) {
			cs.second.pipes = 0;
		}
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
				for (int j = 0; j < adjmatrix.size(); j++) {
					for (int k = 0; k < adjmatrix.size(); k++) {
						if (adjmatrix[j][k] == i) {
							adjmatrix[j][k] = 0;
							cstations[j].pipes -= 1;
							cstations[k].pipes -= 1;
						}
					}
				}
			}
			cout << "Selected pipes have been deleted. " << endl;
		}
	}
}
void gts::changeinrepair(unordered_map <int, pipe>& pipes) {
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
				int i = p.second.getid();
				if (contains(selectpipes, i)) {
					p.second.inrepair = !p.second.inrepair;
				}
			}
			cout << "Selected pipes have been edited. " << endl;
		}
	}
}
vector<int> gts::selectpipe(unordered_map<int, pipe> pipes) {
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
				selectpipes.push_back(p.second.getid());
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
				selectpipes.push_back(p.second.getid());
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
void gts::deletecstations(unordered_map <int, pipe>& pipes, unordered_map<int, cstation>& cstations, vector < vector <int> >& adjmatrix) {
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
		adjmatrix.clear();
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
				for (int j = 0; j < adjmatrix.size(); j++) {
					for (int k = 0; k < adjmatrix.size(); k++) {
						if ((j == i or k == i) and adjmatrix[j][k] != 0) {
							pipes[adjmatrix[j][k]].used = false;
						}
					}
				}
				adjmatrix.erase(adjmatrix.begin() + i);
				for (int j = 0; j < adjmatrix.size(); j++) {
					adjmatrix[j].erase(adjmatrix[j].begin() + i);
				}
			}
			cout << "Selected cstations have been deleted. " << endl;
		}
	}
}
void gts::changeworkshops(unordered_map<int, cstation>& cstations) {
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
			cout << "--------------------------------" << endl;
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
				int i = cs.second.getid();
				if (contains(selectcstations, i)) {
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
					cout << "--------------------------------" << endl;
				}
			}
			cout << "Selected cstations have been edited. " << endl;
		}
	}
}
vector<int> gts::selectcs(unordered_map<int, cstation> cstations) {
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
				selectcstations.push_back(cs.second.getid());
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
			if (cs.second.efficiency == 100 - efficiency) {
				selectcstations.push_back(cs.second.getid());
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
void gts::combine(unordered_map <int, cstation>& cstations, unordered_map <int, pipe>& pipes, vector <vector <int> >& adjmatrix) {
	int idcs1 = 0;
	int idcs2 = 0;
	int idp = 0;
	int piped = 0;
	if (cstations.size() != 0  || cstations.size() != 1) {
		viewcs(cstations);
		cout << "Enter the start CStation ID: ";
		getcorrectnumber(idcs1);
		for (int i = 1; i <= cstations.size(); i++) {
			if (cstations[i].getid() == idcs1 and cstations[i].pipes < 2) {
				cstations[i].pipes++;
				break;
			}
			if (i == cstations.size()) {
				cout << "There is no selected cstations. Try again! " << endl;
				return;
			}
		}
		if (idcs1 >= adjmatrix.size()) {
			adjmatrix.resize(idcs1 + 1);
			for (int i = 0; i < adjmatrix.size(); i++) {
				adjmatrix[i].resize(idcs1 + 1);
			}
		}
		cout << "Enter the end CStation ID: ";
		getcorrectnumber(idcs2);
		for (int i = 1; i <= cstations.size(); i++) {
			if (cstations[i].getid() == idcs2 and cstations[i].pipes < 2 and idcs1 != idcs2) {
				cstations[i].pipes++;
				break;
			}
			if (i == cstations.size()) {
				cout << "There is no selected cstations. Try again! " << endl;
				return;
			}
		}
		if (idcs2 >= adjmatrix.size()) {
			adjmatrix.resize(idcs2 + 1);
			for (int i = 0; i < adjmatrix.size(); i++) {
				adjmatrix[i].resize(idcs2 + 1);
			}
		}
		cout << "--------------------------------" << endl;
		viewpipes(pipes);
		cout << "Enter pipe diameter (500, 700, 1000 or 1400 mm): " << endl;
		getcorrectnumber(piped);
		while (piped != 500 and piped != 700 and piped != 1000 and piped != 1400) {
			cout << "Enter 500, 700, 1000 or 1400! " << endl;
			getcorrectnumber(piped);
		}

		for (int i = 1; i <= pipes.size(); i++) {
			if (pipes[i].diameter == piped and pipes[i].used == false) {
				pipes[i].used = true;
				idp = i;
				break;
			}
			else if (i == pipes.size()) {
				cout << "There are no free pipes with entered diameter. Create a new pipe: " << endl;
				pipe edge;
				cin >> edge;
				edge.used = true;
				pipes.insert({ edge.getid(), edge });
				while (edge.diameter != piped) {
					cout << "Create a pipe with diameter = " << piped << ". " << endl;
					pipe edge;
					cin >> edge;
					edge.used = true;
					idp = edge.getid();
					pipes.insert({ edge.getid(), edge });
				}
			}
		}
		if (adjmatrix[idcs2][idcs1] == 0) {
			adjmatrix[idcs2][idcs1] = idp;
			viewgts(adjmatrix);
		}
		else {
			cout << "Connection cann't be established. Try again!" << endl;
			pipes[adjmatrix[idcs2][idcs1]].used = false;
			adjmatrix[idcs2][idcs1] = 0;
			cstations[idcs1].pipes = 0;
			cstations[idcs2].pipes = 0;
			pipes[idp].used = false;
		}
	}
}
void gts::viewgts(vector<vector<int>>& graph) {
	for (int i = 1; i < graph.size(); i++) {
		if (graph[i - 1].size() > 0) {
			cout << "Cstation id: " << i << " \tIncident pipes: ";
			for (int j = 1; j < graph.size(); j++) {
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}
}
void gts::topologicalsorting(vector<vector<int>>& adjmatrix) {
	int numVertices = adjmatrix.size();
	vector<bool> visited(numVertices, false);
	stack<int> result;
	for (int i = 0; i < numVertices; ++i) {
		if (!visited[i]) {
			topologicalsortutil(adjmatrix, i, visited, result);
		}
	}
	cout << "Topological sorting: " << endl;
	while (!result.empty()) {
		if (result.top() != 0) {
			cout << result.top() << " ";
		}
		result.pop();
	}
	cout << endl;
}
void gts::topologicalsortutil(vector<vector<int>>& adjmatrix, int vertex, vector<bool>& visited, stack<int>& result) {
	visited[vertex] = true;
	for (int i = 0; i < adjmatrix.size(); ++i) {
		if (adjmatrix[vertex][i] != 0 && !visited[i]) {
			topologicalsortutil(adjmatrix, i, visited, result);
		}
	}
	result.push(vertex);
}
bool gts::loopcheck(vector<vector<int>>& adjmatrix) {
	for (int i = 0; i < adjmatrix.size(); i++) {
		for (int j = 0; j < adjmatrix[1].size(); j++) {
			if (adjmatrix[i][j] != 0 && adjmatrix[j][i] != 0) {
				return false;
			}
		}
	}
	return true;
}
void gts::deleteconnection(unordered_map <int, pipe>& pipes, unordered_map<int, cstation>& cstations, vector < vector <int> >& adjmatrix) {
	int idcs1;
	int idcs2;
	int idp;
	cout << "Enter the start CStation ID: ";
	getcorrectnumber(idcs1);
	for (int i = 1; i <= cstations.size(); i++) {
		if (cstations[i].getid() == idcs1) {
			break;
		}
		if (i == cstations.size()) {
			cout << "There is no selected cstations. Try again! " << endl;
			return;
		}
	}
	cout << "Enter the end CStation ID: ";
	getcorrectnumber(idcs2);
	for (int i = 1; i <= cstations.size(); i++) {
		if (cstations[i].getid() == idcs2) {
			break;
		}
		if (i == cstations.size()) {
			cout << "There is no selected cstations. Try again! " << endl;
			return;
		}
	}
	idp = adjmatrix[idcs2][idcs1];
	pipes[idp].used = false;
	adjmatrix[idcs2][idcs1] = 0;
	cstations[idcs1].pipes -= 1;
	cstations[idcs2].pipes -= 1;
}