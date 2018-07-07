#ifndef _ACTIONS_HPP_
#define _ACTIONS_HPP_

#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include "headers.hpp"

class Weather {
public:
	int Temperature;
	int APressure;
	int Altitude;
	int Humidity;

	void GetValues(char *bf);
};

class DataProcessor {
private:
	//RuntimeParams Params;
	int ErrorNum;

	std::map <std::string, std::string> AppParams;
	size_t CurrentTimeoutMinutes;
	int Arduino;
	std::string PublicKey;
	std::string DeviceIdHash;
	time_t TimeBegin;
	//Weather CurrentWeather;

	bool ReadParams(void);
	bool Start(void);
	std::string ServerQuery(std::map<std::string, std::string> params);
	void GetPubKey(void);
	long long Check(void);
	bool Register(void);
	void ProcessData(void);

public:
	DataProcessor(void);
	~DataProcessor(void);

	void PrintParams(void);
	bool IsCorrect(void);
	void InitServerConnection(void);
	bool Timer(void);
};

#endif
