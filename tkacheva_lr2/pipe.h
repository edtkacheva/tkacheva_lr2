#pragma once
#include <string>
using namespace std;
class pipe {
private:
	int id = 0;
public:
	string name = "";
	double length = 0;
	int diameter = 0;
	bool inrepair = false;
	bool used = false;
	static int ID;
	pipe();
	friend istream& operator >> (istream& in, pipe& p);
	friend ostream& operator << (ostream& out, pipe& p);
	friend ofstream& operator << (ofstream& fout, pipe& p);
	friend ifstream& operator >> (ifstream& fin, pipe& p);
	int getid() { return id; };
};