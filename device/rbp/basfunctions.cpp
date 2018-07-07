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
	cout << str << endl;
	//const char *str_tmp = str.c_str();
	unsigned char *str_tmp = new unsigned char[str.size()];
	for (size_t i = 0; i < str.size(); i++) {
		str_tmp[i] = str[i];
		cout << (int) str[i] << ":" << str[i] << endl;
	}
	cout << "Size1: " << sizeof(str_tmp) << endl;
	cout << "Size2: " << str.size() << endl;
	cout << "Size3: " << str.length() << endl;
	//strcpy(str_tmp, str.c_str());
	unsigned char str_tmp1[] = "eDCvyH1MTwc1t8AX";
	cout << (int) str_tmp[16] << endl;
	cout << "Size4: " << sizeof(str_tmp1) << endl;
	SHA1((unsigned char *)str_tmp, str.size() - 1, hash);
	delete [] str_tmp;
	//return string(hash);
	char mdString[SHA1_HASH_LEN*2+1];
	for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
    	sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);
	}
	cout << mdString << endl;
	string res = "";
	for (size_t i = 0; i < SHA1_HASH_LEN; i++) {
		//cout << (int) hash[i] << " ";
		res += CharToHex(hash[i]);
	}
	cout << endl;
	return res;
}

