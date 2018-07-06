#include <iostream>
#include <string>
#include "headers.hpp"
#include "basfunctions.hpp"
#include "actions.hpp"

using namespace std;

int main(void) {
	if (!StartDataProcessor()) {
		cout << MESSAGE_FATAL_ERROR << endl;
		return 0;
	}

	map <string, string> testparams;
	testparams.insert(pair <string, string>("var1", "value1"));
	testparams.insert(pair <string, string>("var2", "value2"));
	string res = ServerGetQuery(testparams, TEST);
	cout << res << endl;

	return 0;
}
