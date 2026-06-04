#ifndef HEX_H
#define HEX_H

#include <string>

void split(const std::string &a, std::string &c);
void parser(const std::string &a, std::string &final);
void reverser(const std::string &a, std::string &c);
int deconvert_pair(const std::string &pair);
void base16_deconvert(const std::string &a, long long &b);
void base16_convert(long long b, std::string &final);
void raw_bytes_print(const std::string &a);
void suggestions();
void large_hex_encrypt(const std::string &a, std::string &out);
void large_hex_decrypt(const std::string &a, std::string &out);
void hex_xor(const std::string &a, unsigned char key, std::string &out);
void hex_xor_bruteforce(const std::string &a);
void hex_operators(char a);

#endif
