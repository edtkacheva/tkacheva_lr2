#include <iostream>
#include <fstream>
#include <unordered_map>
#include "pipe.h"
#include "cstation.h"
#include "header.h"
void printmenu() {
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
		<< "0. Exit." << endl
		<< "--------------------------------" << endl
		<< "Enter the required number:" << endl;
}
void save_data(unordered_map <int, pipe> pipes, unordered_map <int, cstation> cstations) {
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
		}
		cout << "Data was successfully saved." << endl;
		fout.close();
	}
	else {
		cout << "File couldn't be open." << endl;
	}
}
void load_data(unordered_map <int, pipe>& pipes, unordered_map <int, cstation>& cstations) {
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
				cout << cstations;
			}
			else if (numbercstation == 0) {
				cout << "There is no data about cstations. " << endl;
				for (int i = 1; i <= numberpipe; i++) {
					pipe p;
					fin >> p;
					pipes.insert({ p.getid(),p });
				}
				cout << pipes;
			}
			else {
				for (int i = 1; i <= numberpipe; i++) {
					pipe p;
					fin >> p;
					pipes.insert({ p.getid(),p });
				}
				cout << pipes;
				for (int i = 1; i <= numbercstation; i++) {
					cstation cs;
					fin >> cs;
					cstations.insert({ cs.getid(), cs });
				}
				cout << cstations;
			}
		}
	}
	else {
		cout << "File couldn't be open." << endl;
	}
}
int main() {
	unordered_map <int, pipe> pipes;
	unordered_map <int, cstation> cstations;
	while (true) {
		printmenu();
		int choice;
		getcorrectnumber(choice);
		switch (choice) {
		case 1: {
			pipe p;
			cin >> p;
			pipes.insert({ p.getid(),p });
			break;
		}
		case 2: {
			cstation cs;
			cin >> cs;
			cstations.insert({cs.getid(), cs});
			break;
		}
		case 3: {
			cout << pipes;
			break;
		}
		case 4: {
			cout << cstations;
			break;
		}
		case 5: {
			save_data(pipes, cstations);
			break;
		}
		case 6: {
			load_data(pipes, cstations);
			break;
		}
		case 7: {
			deletepipes(pipes);
			break;
		}
		case 8: {
			deletecstations(cstations);
			break;
		}
		case 9: {
			changeinrepair(pipes);
			break;
		}
		case 10: {
			changeworkshops(cstations);
			break;
		}
		case 0: {
			return 0;
		}
		}
	}
	return 0;
}