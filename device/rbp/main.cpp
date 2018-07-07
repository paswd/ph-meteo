#include <iostream>
#include <string>
#include "headers.hpp"
#include "basfunctions.hpp"
#include "actions.hpp"

using namespace std;

int main(void) {
	DataProcessor dp;
	if (!dp.IsStarted()) {
		return 0;
	}

	map <string, string> testparams;
	testparams.insert(pair <string, string>("type", "getpubkey"));
	//testparams.insert(pair <string, string>("var", "value1"));
	string res = dp.ServerQuery(testparams);
	cout << res << endl;

	return 0;
}
