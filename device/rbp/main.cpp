#include <iostream>
#include <string>
#include "headers.hpp"
#include "basfunctions.hpp"
#include "actions.hpp"

using namespace std;

int main(void) {
	DataProcessor dp;
	if (!dp.IsCorrect()) {
		return 0;
	}
	dp.InitServerConnection();
	cout << "DEBUG::START TIMER" << endl;
	while (dp.Timer());

	return 0;
}
