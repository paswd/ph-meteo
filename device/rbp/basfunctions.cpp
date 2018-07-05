#include "basfunctions.hpp"
#include <sstream>

using namespace std;

long long StringToNum(string str) {
	stringstream sstream(str);
	long long res;
	sstream >> res;
	return res;
}

