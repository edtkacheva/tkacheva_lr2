#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <format>
#include "pipe.h"
#include "cstation.h"
#include "header.h"
#include "gts.h"
using namespace chrono;
int main() {
	redirected_output cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time + ".txt");
	if (logfile) {
		cerr_out.redirect(logfile);
	}
	unordered_map <int, pipe> pipes;
	unordered_map <int, cstation> cstations;
	gts uni;
	while (true) {
		uni.printmenu();
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
			uni.save_data(pipes, cstations);
			break;
		}
		case 6: {
			uni.load_data(pipes, cstations);
			break;
		}
		case 7: {
			uni.deletepipes(pipes);
			break;
		}
		case 8: {
			uni.deletecstations(cstations);
			break;
		}
		case 9: {
			uni.changeinrepair(pipes);
			break;
		}
		case 10: {
			uni.changeworkshops(cstations);
			break;
		}
		case 0: {
			return 0;
		}
		}
	}
	return 0;
}