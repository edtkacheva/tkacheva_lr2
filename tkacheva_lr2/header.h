#pragma once
#include <iostream>
using namespace std;
//class redirected_output
//{
//private:
//	ostream& out;
//	streambuf* buf;
//public:
//	redirected_output(ostream& src)
//		:buf(src.rdbuf()), out(src)
//	{}
//	~redirected_output() {
//		out.rdbuf(buf);
//	}
//	void redirect (ostream& dest) {
//		out.rdbuf(dest.rdbuf());
//	}
//};
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
	/*cerr << x << endl;*/
}
template<class C, typename T>
bool contains(C& c, T& t) {
	return find(begin(c), end(c), t) != end(c);
};