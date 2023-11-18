#pragma once
#include <string>
#include <unordered_map>
using namespace std;
class pipe {
private:
private:
	int id = 0;
public:
	string name = "";
	double length = 0;
	double diameter = 0;
	bool inrepair = false;
	static int ID;
	pipe();
	friend istream& operator >> (istream& in, pipe& p);
	friend ostream& operator << (ostream& out, unordered_map <int, pipe>& pipes);
	friend ofstream& operator << (ofstream& fout, pipe& p);
	friend ifstream& operator >> (ifstream& fin, pipe& p);
	friend void deletepipes(unordered_map<int, pipe>& pipes);
	friend void changeinrepair(unordered_map<int, pipe>& pipes);
	friend vector <int> selectpipe(unordered_map<int, pipe> pipes);
	int getid() { return id; };
};