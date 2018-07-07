#ifndef _HEADERS_HPP_
#define _HEADERS_HPP_

#include <map>

typedef std::map<std::string,std::string> Dict;
typedef std::pair<std::string,std::string> DictUnit;

const size_t TEMP_ARR_LEN = 3;
const size_t PRESS_ARR_LEN = 6;
const size_t ALT_ARR_LEN = 4;
const size_t HUM_ARR_LEN = 3;
const size_t INPUT_MESSAGE_SIZE =
	TEMP_ARR_LEN +
	PRESS_ARR_LEN +
	ALT_ARR_LEN +
	HUM_ARR_LEN + 1;

const std::string COLOR_RED("\033[0;31m");
const std::string COLOR_GREEN("\033[1;32m");
const std::string COLOR_YELLOW("\033[1;33m");
const std::string COLOR_CYAN("\033[0;36m");
const std::string COLOR_MAGENTA("\033[0;35m");
const std::string COLOR_RESET("\033[0m");

const std::string MESSAGE_FATAL_ERROR = COLOR_RED + "FATAL ERROR! The server was interrupt" + COLOR_RESET;

class RuntimeParams {
public:
	std::map <std::string, std::string> AppParams;
	size_t CurrentTimeoutMinutes;
	int Arduino;
	std::string PublicKey;
	std::string DeviceIdHash;
};

//extern RuntimeParams PARAMS;

/*typedef enum {
	DATA_SEND,
	REG,
	CHECK,
	TEST
} GetQueryType;*/

#endif
