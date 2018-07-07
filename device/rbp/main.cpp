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
	if (!dp.InitServerConnection()) {
		return 0;
	}
	while (dp.Timer());

	return 0;
}
