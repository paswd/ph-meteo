#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <wiringSerial.h>

using namespace std;

const size_t TEMP_ARR_LEN = 3;
const size_t PRESS_ARR_LEN = 6;
const size_t ALT_ARR_LEN = 4;
const size_t HUM_ARR_LEN = 3;
const size_t INPUT_MESSAGE_SIZE =
	TEMP_ARR_LEN +
	PRESS_ARR_LEN +
	ALT_ARR_LEN +
	HUM_ARR_LEN + 1;

const string COLOR_RED("\033[0;31m");
const string COLOR_GREEN("\033[1;32m");
const string COLOR_YELLOW("\033[1;33m");
const string COLOR_CYAN("\033[0;36m");
const string COLOR_MAGENTA("\033[0;35m");
const string COLOR_RESET("\033[0m");

const string MESSAGE_FATAL_ERROR = COLOR_RED + "FATAL ERROR! The server was interrupt" + COLOR_RESET;

map <string, string> APP_PARAMS;

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
			APP_PARAMS.insert(pair <string, string>(name_tmp, tmp));
		}
		is_first_param = !is_first_param;
	}
	return true;
}
void PrintParams(void) {
	for (auto it = APP_PARAMS.begin(); it != v.end(); it++) {
    	cout << it->first << " : "<< it->second << endl;
	}
}

int main(void) {
	cout << "Reading config... ";
	if (ReadParams()) {
		cout << COLOR_GREEN << "[OK]" << COLOR_RESET << endl;
	} else {
		cout << COLOR_RED << "[FAILED]" << COLOR_RESET << endl;
		cout << MESSAGE_FATAL_ERROR << endl;
		return 0;
	}
	PrintParams();

	cout << "Arduino connection initialization" << endl;
	string base = "/dev/ttyACM";
	int fd = -1;
	for (int i = 0; fd == -1 && i < 10; i++) {
		char tmp = i + '0';
		string addr = base + tmp;
		cout << "Connecting " << addr << "... ";
		fd = serialOpen(addr.c_str(), 9600);
		if (fd != -1) {
			cout << COLOR_GREEN << "[OK]" << COLOR_RESET;
		} else {
			cout << COLOR_RED << "[FAILED]" << COLOR_RESET;
		}
		cout << endl;
	}
	if (fd == -1) {
		cout << COLOR_RED << "Arduino connection error" << COLOR_RESET << endl;
		cout << MESSAGE_FATAL_ERROR << endl;

		return 0;
	}
	cout << COLOR_GREEN << "Arduino has been successfuly found" << COLOR_RESET << endl;
	//char bf[INPUT_MESSAGE_SIZE + 1];
	//bf[INPUT_MESSAGE_SIZE] = '\n';

	return 0;
}
