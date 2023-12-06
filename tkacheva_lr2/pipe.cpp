#include "pipe.h"
#include "header.h"
#include <unordered_map>
#include <fstream>
using namespace std;
int pipe::ID = 1;
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
	cout << "Enter pipe diameter (500, 700, 1000 or 1400 mm): " << endl;
	getcorrectnumber(p.diameter);
	while (p.diameter != 500 and p.diameter != 700 and p.diameter != 1000 and p.diameter != 1400) {
		cout << "Enter 500, 700, 1000 or 1400! " << endl;
		getcorrectnumber(p.diameter);
	}
	cout << "Is the pipe being repaired? (1 - yes, 0 - no): " << endl;
	getcorrectnumber(p.inrepair);
	return in;
}
ostream& operator<<(ostream& out, pipe& p) {
	out << "Pipe ID: " << p.id << endl;
	out << "Pipe name: " << p.name << endl;
	out << "Pipe length: " << p.length << endl;
	out << "Pipe diameter: " << p.diameter << endl;
	out << "Condition 'under repair': " << p.inrepair << endl;
	out << "--------------------------------" << endl;
	return out;
}
ofstream& operator<<(ofstream& fout, pipe& p)
{
	fout << p.name << endl << p.length << endl << p.diameter << endl << p.inrepair << endl << p.used << endl;
	return fout;
}
ifstream& operator>>(ifstream& fin, pipe& p)
{
	fin.ignore();
	getline(fin, p.name);
	fin >> p.length;
	fin >> p.diameter;
	fin >> p.inrepair;
	fin >> p.used;
	return fin;
}