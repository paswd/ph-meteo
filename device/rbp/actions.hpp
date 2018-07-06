#ifndef _ACTIONS_HPP_
#define _ACTIONS_HPP_

#include <ctime>
#include <string>
#include <string.h>
#include <unistd.h>
#include "headers.hpp"

bool ReadParams(void);
void PrintParams(void);
bool StartDataProcessor(void);
std::string ServerGetQuery(std::map<std::string, std::string> params, GetQueryType query_type);

#endif
