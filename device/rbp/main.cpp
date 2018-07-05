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

	return 0;
}
