#pragma once
#include <string>
using namespace std;
class cstation {
private:
	int id = 0;
public:
	string name = "";
	int workshop = 0;
	int workingwshop = 0;
	double efficiency = 0;
	int pipes = 0;
	static int ID;
	cstation();
	friend istream& operator >> (istream& in, cstation& cs);
	friend ostream& operator << (ostream& out, cstation& cs);
	friend ofstream& operator << (ofstream& fout, cstation& cs);
	friend ifstream& operator >> (ifstream& fin, cstation& cs);
	int getid() { return id; };
};