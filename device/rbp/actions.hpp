#ifndef _ACTIONS_HPP_
#define _ACTIONS_HPP_

#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include "headers.hpp"

class DataProcessor {
private:
	//RuntimeParams Params;
	//int ErrorNum;

	std::map <std::string, std::string> AppParams;
	size_t CurrentTimeoutMinutes;
	int Arduino;
	std::string PublicKey;
	std::string DeviceIdHash;
	time_t TimeBegin;

	bool ReadParams(void);
	bool Start(void);
	std::string ServerQuery(std::map<std::string, std::string> params);
	void GetPubKey(void);
	long long CheckRegistration(void);
	bool Register(void);

public:
	DataProcessor(void);
	~DataProcessor(void);

	void PrintParams(void);
	bool IsCorrect(void);
	void InitServerConnection(void);
};

#endif
