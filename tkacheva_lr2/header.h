#pragma once
#include <iostream>
using namespace std;
template <typename T>
void getcorrectnumber(T& x) {
	cin >> x;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Try again!" << endl;
		cin >> x;
	}
}
template<class C, typename T>
bool contains(C& c, T& t) {
	return find(begin(c), end(c), t) != end(c);
};