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

int main(void) {
	cout << "Server starting..." << endl;

	map

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
		return 0;
	}
	char bf[INPUT_MESSAGE_SIZE + 1];
	bf[INPUT_MESSAGE_SIZE] = '\n';

	return 0;
}
