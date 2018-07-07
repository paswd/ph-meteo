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
	int ErrorNum;

	Dict AppParams;
	size_t CurrentTimeoutMinutes;
	int Arduino;
	std::string PublicKey;
	std::string DeviceIdHash;
	Weather CurrentWeather;

	bool ReadParams(void);
	bool Start(void);
	std::string ServerQuery(Dict params);
	void GetPubKey(void);
	long long Check(void);
	bool Register(void);
	bool ProcessData(void);

public:
	DataProcessor(void);
	~DataProcessor(void);

	void PrintParams(void);
	bool IsCorrect(void);
	bool InitServerConnection(void);
	bool Timer(void);
};

#endif
