#include "headers.hpp"
#include "actions.hpp"
#include "basfunctions.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include <wiringSerial.h>

//#define APP_PARAMS this->AppParams

using namespace std;

//RuntimeParams PARAMS;

DataProcessor::DataProcessor(void) {
	this->ErrorNum = 0;
	if (!this->Start()) {
		cout << MESSAGE_FATAL_ERROR << endl;
		this->ErrorNum = 1;
	}
}

DataProcessor::~DataProcessor(void) {}

bool DataProcessor::ReadParams(void) {
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
			this->AppParams.insert(pair <string, string>(name_tmp, tmp));
		}
		is_first_param = !is_first_param;
	}
	this->CurrentTimeoutMinutes = (size_t) StringToNum(this->AppParams["TIMEOUT_DEFAULT_MINUTES"]);
	return true;
}
void DataProcessor::PrintParams(void) {
	for (auto it = this->AppParams.begin(); it != this->AppParams.end(); it++) {
    	cout << it->first << " : "<< it->second << endl;
	}
}

bool DataProcessor::Start(void) {
	cout << "Reading config... ";
	if (this->ReadParams()) {
		cout << COLOR_GREEN << "[OK]" << COLOR_RESET << endl;
	} else {
		cout << COLOR_RED << "[FAILED]" << COLOR_RESET << endl;
		return false;
	}

	this->DeviceIdHash = sha1_hash(this->AppParams["DEVICE_ID"]);
	//PrintParams();

	cout << endl << "Finding arduino" << endl;
	string base = "/dev/ttyACM";
	this->Arduino = -1;
	for (int i = 0; this->Arduino == -1 && i < 10; i++) {
		char tmp = i + '0';
		string addr = base + tmp;
		cout << "Connecting " << addr << "... ";
		this->Arduino = serialOpen(addr.c_str(), 9600);
		if (this->Arduino != -1) {
			cout << COLOR_GREEN << "[OK]" << COLOR_RESET;
		} else {
			cout << COLOR_RED << "[FAILED]" << COLOR_RESET;
		}
		cout << endl;
	}
	if (this->Arduino == -1) {
		cout << COLOR_RED << "Arduino connection error" << COLOR_RESET << endl;

		return false;
	}
	cout << "Arduino has been found" << endl;
	cout << endl << COLOR_GREEN << "Data processor has been successfully started" << COLOR_RESET << endl << endl;
	return true;
}

string DataProcessor::ServerQuery(Dict variables) {
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
	/*string script_path;
	switch (query_type) {
		case DATA_SEND:
			script_path = this->AppParams["SERVER_SCRIPT_DATA_PATH"];
			break;
		case REG:
			script_path = this->AppParams["SERVER_SCRIPT_REG_PATH"];
			break;
		case CHECK:
			script_path = this->AppParams["SERVER_SCRIPT_CHECK_PATH"];
			break;
		case TEST:
			script_path = this->AppParams["SERVER_SCRIPT_TEST_PATH"];
			break;
	}*/
	string query_href = this->AppParams["SERVER_PROTOCOL"] + "://" + this->AppParams["SERVER_HOST"] +
		this->AppParams["SERVER_SCRIPT_PATH"] + query_variables;
	string query = "wget \"" +  query_href + "\" -O " + this->AppParams["QUERY_TEMP_FILE"] + " -q";
	system(query.c_str());

	ifstream query_res_file(this->AppParams["QUERY_TEMP_FILE"].c_str());
	char ch;
	string res = "";
	while (query_res_file.get(ch)) {
		res += ch;
		//cout << ch << endl;
	}
	query_res_file.close();
	system(("rm " + this->AppParams["QUERY_TEMP_FILE"]).c_str());

	return res;
}

bool DataProcessor::IsCorrect(void) {
	if (this->ErrorNum == 0) {
		return true;
	}
	return false;
}
void DataProcessor::GetPubKey(void) {
	Dict query_params;
	query_params.insert(DictUnit("type", "getpubkey"));
	string pubkey = this->ServerQuery(query_params);
	ofstream fout(this->AppParams["PUBLIC_KEY_FILE"].c_str(), ios::out);
	fout << pubkey << endl;
	fout.close();
}

long long DataProcessor::CheckRegistration(void) {
	Dict query_params;
	query_params.insert(DictUnit("type", "check"));
	query_params.insert(DictUnit("unic_id", this->DeviceIdHash));
	long long res = StringToNum(this->ServerQuery(query_params));
	if (res > 0) {
		this->CurrentTimeoutMinutes = res;
	}
	return res;
}

bool DataProcessor::Register(void) {
	cout << "Checking registration... ";
	if (this->CheckRegistration() != -1) {
		cout << COLOR_GREEN << "[REGISTERED]" << endl;
		return true;
	}
	cout << COLOR_YELLOW << "[NOT REGISTERED]" << endl;
	cout << "Registering... ";
	Dict query_params;
	query_params.insert(DictUnit("type", "registration"));
	query_params.insert(DictUnit("unic_id", this->DeviceIdHash));
	long long res = StringToNum(this->ServerQuery(query_params));
	this->ErrorNum = res;
	switch (res) {
		case 0:
			cout << COLOR_GREEN << "[OK]" << COLOR_RESET << endl;
			break;
		case 2:
			cout << COLOR_RED << "[FAILED]" << endl;
			cout << COLOR_RED << "Required parameters (unic_id) is missing" << COLOR_RESET << endl;
			break;

		default:
			cout << COLOR_RED << "[FAILED]" << endl;
			cout << COLOR_RED << "Unknown error occurred in registration" << COLOR_RESET << endl;
			break;
	}

	return res == 0 ? true : false;
}

void DataProcessor::InitServerConnection(void) {
	if (!this->Register()) {
		return;
	}
	/*Dict testquery;
	testquery.insert(DictUnit("type", "test"));
	testquery.insert(DictUnit("var", this->DeviceIdHash));
	string res = this->ServerQuery(testquery);
	cout << res << endl;*/
}
