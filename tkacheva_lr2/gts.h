#pragma once
#include "pipe.h"
#include "cstation.h"
#include <unordered_map>
class gts {
public: 
	static void printmenu();
	static void viewpipes(unordered_map <int, pipe> pipes);
	static void viewcs(unordered_map <int, cstation> cstations);
	static void save_data(unordered_map <int, pipe> pipes, unordered_map <int, cstation> cstations);
	static void load_data(unordered_map <int, pipe>& pipes, unordered_map <int, cstation>& cstations);
	static void deletepipes(unordered_map <int, pipe>& pipes);
	static void changeinrepair(unordered_map<int, pipe>& pipes);
	static vector <int> selectpipe(unordered_map<int, pipe> pipes);
	static void deletecstations(unordered_map <int, cstation>& cstations);
	static void changeworkshops(unordered_map <int, cstation>& cstations);
	static vector<int> selectcs(unordered_map<int, cstation> cstations);
	static void combine();
};