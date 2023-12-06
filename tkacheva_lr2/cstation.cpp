#include <unordered_map>
#include <cmath>
#include <fstream>
#include "cstation.h"
#include "header.h"
int cstation::ID = 1;
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
ostream& operator<<(ostream& out, cstation& cs) {
	out << "Compressor station ID: " << cs.id << endl;
	out << "Compressor station name: " << cs.name << endl;
	out << "The number of workshops: " << cs.workshop << endl;
	out << "The number of working workshops: " << cs.workingwshop << endl;
	out << "Effiency: " << cs.efficiency << "%" << endl;
	out << "--------------------------------" << endl;
	return out;
}
ofstream& operator<<(ofstream& fout, cstation& cs) {
	fout << cs.name << endl << cs.workshop << endl << cs.workingwshop << endl << cs.efficiency << endl << cs.pipes << endl;
	return fout;
}
ifstream& operator>>(ifstream& fin, cstation& cs) {
	fin.ignore();
	getline(fin, cs.name);
	fin >> cs.workshop;
	fin >> cs.workingwshop;
	fin >> cs.efficiency;
	fin >> cs.pipes;
	return fin;
}