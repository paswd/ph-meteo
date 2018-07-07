#include "basfunctions.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <openssl/sha.h>

using namespace std;

const size_t SHA1_HASH_LEN = 40;

long long StringToNum(string str) {
	stringstream sstream(str);
	long long res;
	sstream >> res;
	return res;
}

char CharToHex(unsigned char ch) {
	if (ch <= 9) {
		return ch + '0'; 
	}
	return ch + 'a' - 10;
}

string sha1_hash(string str) {
	unsigned char hash[SHA1_HASH_LEN];
	char *str_tmp = NULL;
	strcpy(str_tmp, str.c_str());
	SHA1((unsigned char *)&str_tmp, str.size() - 1, hash);
	//return string(hash);
	string res = "";
	for (size_t i = 0; i < SHA1_HASH_LEN; i++) {
		cout << (int) hash[i] << " ";
		res += CharToHex(hash[i]);
	}
	cout << endl;
	return res;
}

