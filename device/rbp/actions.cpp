#include "actions.hpp"
#include "basfunctions.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <wiringSerial.h>

using namespace std;

bool ReadParams(void) {
	ifstream fin("init.conf");
	if (!fin.is_open()) {
		return false;
	}
	string tmp;
	bool is_first_param = true;
	string name_tmp = "";
	while (fin >> tmp) {
		if (is_first_param) {
			name_tmp = tmp;
		} else {
			PARAMS.AppParams.insert(pair <string, string>(name_tmp, tmp));
		}
		is_first_param = !is_first_param;
	}
	PARAMS.CurrentTimeoutMinutes = (size_t) StringToNum(PARAMS.AppParams["TIMEOUT_DEFAULT_MINUTES"]);
	return true;
}
void PrintParams(void) {
	for (auto it = PARAMS.AppParams.begin(); it != PARAMS.AppParams.end(); it++) {
    	cout << it->first << " : "<< it->second << endl;
	}
}

bool StartDataProcessor(void) {
	cout << "Reading config... ";
	if (ReadParams()) {
		cout << COLOR_GREEN << "[OK]" << COLOR_RESET << endl;
	} else {
		cout << COLOR_RED << "[FAILED]" << COLOR_RESET << endl;
		return false;
	}
	//PrintParams();

	cout << "Finding arduino" << endl;
	string base = "/dev/ttyACM";
	PARAMS.Arduino = -1;
	for (int i = 0; PARAMS.Arduino == -1 && i < 10; i++) {
		char tmp = i + '0';
		string addr = base + tmp;
		cout << "Connecting " << addr << "... ";
		PARAMS.Arduino = serialOpen(addr.c_str(), 9600);
		if (PARAMS.Arduino != -1) {
			cout << COLOR_GREEN << "[OK]" << COLOR_RESET;
		} else {
			cout << COLOR_RED << "[FAILED]" << COLOR_RESET;
		}
		cout << endl;
	}
	if (PARAMS.Arduino == -1) {
		cout << COLOR_RED << "Arduino connection error" << COLOR_RESET << endl;

		return false;
	}
	cout << "Arduino has been found" << endl;
	cout << endl << COLOR_GREEN << "Data processor has been successfully started" << COLOR_RESET << endl;
	return true;
}