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
			out << "--------------------------------" << endl;
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