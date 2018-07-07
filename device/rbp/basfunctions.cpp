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
	unsigned char primary_hash[SHA1_HASH_LEN];
	cout << str << endl;
	//const char *str_tmp = str.c_str();
	unsigned char *str_tmp = new unsigned char[str.size() + 1];
	for (size_t i = 0; i < str.size(); i++) {
		str_tmp[i] = str[i];
		//cout << (int) str[i] << ":" << str[i] << endl;
	}
	str_tmp[str.size()] = 0;
	SHA1((unsigned char *)str_tmp, str.size(), primary_hash);
	delete [] str_tmp;
	//return string(hash);
	char hash[SHA1_HASH_LEN*2+1];
	for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
    	sprintf(&hash[i*2], "%02x", (unsigned int)primary_hash[i]);
	}
	cout << hash << endl;
	string res = "";
	for (size_t i = 0; i < SHA1_HASH_LEN * 2 + 1; i++) {
		cout << (int) hash[i] << " ";
		res += CharToHex(hash[i]);
	}
	cout << endl;
	return res;
}

