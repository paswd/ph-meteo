#include "actions.hpp"
#include "basfunctions.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <wiringSerial.h>

#define APP_PARAMS PARAMS.AppParams

using namespace std;

RuntimeParams PARAMS;

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
	PARAMS.CurrentTimeoutMinutes = (size_t) StringToNum(APP_PARAMS["TIMEOUT_DEFAULT_MINUTES"]);
	return true;
}
void PrintParams(void) {
	for (auto it = APP_PARAMS.begin(); it != APP_PARAMS.end(); it++) {
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

	cout << endl << "Finding arduino" << endl;
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

string ServerGetQuery(map<string, string> variables, GetQueryType query_type) {
	string query_variables = "?";
	bool first = true;
	for (auto it = variables.begin(); it != variables.end(); it++) {
		if (first) {
			first = false;
		} else {
			query_variables += "&";
		}
		query_variables += it->first + "=" + it->second;
	}
	string script_path;
	switch (query_type) {
		case DATA_SEND:
			script_path = APP_PARAMS["SERVER_SCRIPT_DATA_PATH"];
			break;
		case REG:
			script_path = APP_PARAMS["SERVER_SCRIPT_REG_PATH"];
			break;
		case CHECK:
			script_path = APP_PARAMS["SERVER_SCRIPT_CHECK_PATH"];
			break;
		case TEST:
			script_path = APP_PARAMS["SERVER_SCRIPT_TEST_PATH"];
			break;
	}
	string query_href = APP_PARAMS["SERVER_PROTOCOL"] + "://" + APP_PARAMS["SERVER_HOST"] +
		script_path + query_variables;
	string query = "wget \"" +  query_href + "\" -O " + APP_PARAMS["QUERY_TEMP_FILE"] + " -q";
	system(query.c_str());

	ifstream query_res_file(APP_PARAMS["QUERY_TEMP_FILE"].c_str());
	char ch;
	string res = "";
	while((ch = query_res_file.get()) != EOF) {
		res += ch;
	}
	query_res_file.close();
	system(("rm " + APP_PARAMS["QUERY_TEMP_FILE"]).c_str());

	return res;
}