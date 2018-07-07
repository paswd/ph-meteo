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
public:
	DataProcessor(void);
	~DataProcessor(void);

	bool ReadParams(void);
	void PrintParams(void);
	bool Start(void);
	std::string ServerQuery(std::map<std::string, std::string> params);
	bool IsStarted(void);
};

#endif
