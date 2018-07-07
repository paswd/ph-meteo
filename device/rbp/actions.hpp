#ifndef _ACTIONS_HPP_
#define _ACTIONS_HPP_

#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include "headers.hpp"

class DataProcessor {
private:
	RuntimeParams Params;
	int ErrorNum;

	bool ReadParams(void);
	bool Start(void);
	std::string ServerQuery(std::map<std::string, std::string> params);
	void GetPubKey(void);
	bool CheckRegistration(void);
	bool Register(void);

public:
	DataProcessor(void);
	~DataProcessor(void);

	void PrintParams(void);
	bool IsStarted(void);
	void InitServerConnection(void);
};

#endif
