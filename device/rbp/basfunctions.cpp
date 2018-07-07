#include "basfunctions.hpp"
#include <sstream>
#include <openssl/sha.h>

using namespace std;

const size_t SHA1_HASH_LEN = 40;

long long StringToNum(string str) {
	stringstream sstream(str);
	long long res;
	sstream >> res;
	return res;
}

string sha1_hash(string str) {
	unsigned char hash[SHA1_HASH_LEN];
	SHA1(reinterpret_cast<const unsigned char *>(str.c_str()), str.size() - 1, hash);
	return string(hash);
}

