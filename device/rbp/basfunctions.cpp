#include "basfunctions.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <openssl/sha.h>

using namespace std;

const size_t SHA1_HASH_LEN = 40;

long long CharToNum(char ch) {
	if (ch >= '0' && ch <= '9') {
		return (long long) (ch - '0');
	}
	return 0;
}

long long StringToNum(string str) {
	stringstream sstream(str);
	long long res;
	sstream >> res;
	return res;
}
long long StringToNum(char *str, size_t len) {
	long long res = 0;
	for (size_t i = 0; i < len; i++) {
		res *= 10;
		res += CharToNum(str[i]);
	}
	return res;
}

string NumToString(long long num) {
	stringstream ss;
	ss << num;
	return ss.str();
}

long long DoubleToNum(double val) {
	long long res = (long long) val;
	long long md = (long long) (val * 10);
	md %= 10;
	if (md >= 5) {
		res++;
	}
	return res;
}

string sha1_hash(string str) {
	unsigned char primary_hash[SHA1_HASH_LEN];
	unsigned char *str_tmp = new unsigned char[str.size() + 1];
	
	for (size_t i = 0; i < str.size(); i++) {
		str_tmp[i] = str[i];
	}
	str_tmp[str.size()] = 0;
	SHA1((unsigned char *)str_tmp, str.size(), primary_hash);
	delete [] str_tmp;
	char hash[SHA1_HASH_LEN*2+1];
	
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf(&hash[i*2], "%02x", (unsigned int)primary_hash[i]);
	}
	string res = "";
	
	for (size_t i = 0; i < SHA1_HASH_LEN; i++) {
		res += (char) hash[i];
	}
	return res;
}

