#ifndef _BASFUNCTIONS_HPP_
#define _BASFUNCTIONS_HPP_

#include "headers.hpp"

long long StringToNum(std::string str);
long long StringToNum(char *str, size_t len);
std::string NumToSting(long long num);
long long DoubleToNum(double val);
std::string sha1_hash(std::string str);


#endif
