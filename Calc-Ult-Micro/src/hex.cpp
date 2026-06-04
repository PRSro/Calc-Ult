#include "hex.h"
#include "safeinput.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

const char padding = '0';
const std::string hexalphabet = "0123456789abcdef";

void split(const std::string &a, std::string &c) {
	int s = a.length();
	c = "";
	if (s % 2 == 1) {
		c += padding;
		c += a.at(0);
		c += ' ';
		for (int i = 1; i < s; i += 2) {
			c += a.at(i);
			c += a.at(i + 1);
			c += ' ';
		}
	} else {
		for (int i = 0; i < s; i += 2) {
			c += a.at(i);
			c += a.at(i + 1);
			c += ' ';
		}
	}
}

void parser(const std::string &a, std::string &final) {
	for (char l : a) {
		if (l == ' ') continue;
		final += l;
	}
}

void reverser(const std::string &a, std::string &c) {
	int n = a.length();
	c = "";
	for (int y = n - 1; y >= 0; y--)
		c += a.at(y);
}

int deconvert_pair(const std::string &pair) {
	int h = hexalphabet.find(pair.at(0));
	int l = hexalphabet.find(pair.at(1));
	return h * 16 + l;
}

void base16_deconvert(const std::string &a, long long &b) {
	if (a == "0") { b = 0; return; }
	bool negative = (a.at(0) == '-');
	std::string temp = negative ? a.substr(1) : a, clean, c;
	split(temp, c);
	parser(c, clean);
	b = 0;
	int la = clean.length();
	for (int i = 0; i < la; i += 2) {
		std::string pair = {clean.at(i), clean.at(i + 1)};
		b = b * 256 + deconvert_pair(pair);
	}
	if (negative) b *= -1;
}

void base16_convert(long long b, std::string &final) {
	final = "";
	if (b == 0) { final = "0"; return; }
	long long d = (b < 0) ? -b : b;
	while (d != 0) {
		int r = d % 16;
		final += hexalphabet.at(r);
		d /= 16;
	}
	std::string temp;
	reverser(final, temp);
	final = temp;
	if (b < 0) final.insert(0, "-");
}

void raw_bytes_print(const std::string &a) {
	for (char c : a)
		std::cout << (int)(unsigned char)c << ' ';
}

void suggestions() {
	std::cout << "THE OBSCURON's PERSONAL HEX LIBRARY IN CPP FOR SPEED AND EFFICIENCY\n";
	std::cout << "═══════════════════════════════════════════════════════════════════════════════\n";
	std::cout << "│        function      │             intent              │        params       │\n";
	std::cout << "───────────────────────────────────────────────────────────────────────────────\n";
	std::cout << "│ split                │ chunk string into hex pairs     │ (str, &out)         │\n";
	std::cout << "│ parser               │ strip spaces from hex string    │ (str, &out)         │\n";
	std::cout << "│ reverser             │ reverse a string                │ (str, &out)         │\n";
	std::cout << "│ deconvert_pair       │ hex pair to byte value          │ (str) → int         │\n";
	std::cout << "│ base16_convert       │ number to hex string            │ (long long, &out)   │\n";
	std::cout << "│ base16_deconvert     │ hex string to number            │ (str, &out)         │\n";
	std::cout << "│ raw_bytes_print      │ print raw byte values           │ (str)               │\n";
	std::cout << "│ large_hex_encrypt    │ encrypt string to hex           │ (str, &out)         │\n";
	std::cout << "│ large_hex_decrypt    │ decrypt hex to string           │ (str, &out)         │\n";
	std::cout << "│ hex_operators        │ command dispatcher              │ (char)              │\n";
	std::cout << "│ suggestions          │ print this help table           │ none                │\n";
	std::cout << "│ hex_xor              │ XOR hex against key             │ (str, key, &out)    │\n";
	std::cout << "│ hex_xor_bruteforce   │ brute force XOR                 │ (str)               │\n";
	std::cout << "═══════════════════════════════════════════════════════════════════════════════\n";
}

void large_hex_encrypt(const std::string &a, std::string &out) {
	out = "";
	for (char ch : a) {
		std::string part;
		base16_convert((long long)(unsigned char)ch, part);
		out += part + ' ';
	}
}

void large_hex_decrypt(const std::string &a, std::string &out) {
	out = "";
	std::string clean;
	parser(a, clean);
	int n = clean.length();
	for (int i = 0; i < n; i += 2) {
		std::string pair = {clean.at(i), clean.at(i + 1)};
		out += (char)deconvert_pair(pair);
	}
}

void hex_xor(const std::string &a, unsigned char key, std::string &out) {
	out = "";
	std::string clean;
	if (a.find(' ') != std::string::npos) {
		parser(a, clean);
	} else {
		std::string paired;
		split(a, paired);
		parser(paired, clean);
	}
	int m = clean.length();
	for (int i = 0; i < m; i += 2) {
		std::string pair = {clean.at(i), clean.at(i + 1)};
		unsigned char byte = (unsigned char)deconvert_pair(pair);
		byte ^= key;
		std::string part;
		base16_convert((long long)byte, part);
		if (part.length() == 1) part = "0" + part;
		out += part + ' ';
	}
}

void hex_xor_bruteforce(const std::string &a) {
	const std::string common = "etaoinshrdlu ";
	int best_key = 0;
	int best_score = -1;
	std::string best_result;
	for (int key = 0; key < 256; key++) {
		std::string candidate;
		hex_xor(a, (unsigned char)key, candidate);
		std::string decoded;
		large_hex_decrypt(candidate, decoded);
		int score = 0;
		for (char c : decoded)
			if (common.find((char)tolower(c)) != std::string::npos)
				score++;
		std::cout << "key=0x" << std::hex << std::setw(2) << std::setfill('0') << key
		          << std::dec << " score=" << std::setw(3) << score
		          << " | " << decoded << '\n';
		if (score > best_score) {
			best_score = score;
			best_key   = key;
			best_result = decoded;
		}
	}
	std::cout << "\nBEST: key=0x" << std::hex << std::setw(2) << std::setfill('0') << best_key
	          << std::dec << " (" << best_key << ") score=" << best_score << " result=" << best_result << "\n";
}

void hex_operators(char a) {
	switch (a) {
	case 'e': {
		long long num = safeInput<long long>("Enter number: ");
		std::string result;
		base16_convert(num, result);
		std::cout << "hex: " << result << '\n';
		break;
	}
	case 'd': {
		std::string hex = safeInput<std::string>("Enter hex: ");
		long long result;
		base16_deconvert(hex, result);
		std::cout << "decimal: " << result << '\n';
		break;
	}
	case 'x': {
		std::string hex = safeInput<std::string>("Enter hex string: ");
		int key = safeInput<int>("Enter key (0-255): ");
		std::string result;
		hex_xor(hex, (unsigned char)key, result);
		std::cout << "xored: " << result << '\n';
		break;
	}
	case 'b': {
		std::string input = safeInput<std::string>("Enter string to encrypt: ");
		std::string result;
		large_hex_encrypt(input, result);
		std::cout << "encrypted: " << result << '\n';
		break;
	}
	case 'r': {
		std::string input = safeInput<std::string>("Enter hex to decrypt: ");
		std::string result;
		large_hex_decrypt(input, result);
		std::cout << "decrypted: " << result << '\n';
		break;
	}
	case 'w': {
		std::string input = safeInput<std::string>("Enter string for raw bytes: ");
		std::cout << "bytes: ";
		raw_bytes_print(input);
		std::cout << '\n';
		break;
	}
	case 'p': {
		std::string input = safeInput<std::string>("Enter hex to display: ");
		std::string paired;
		split(input, paired);
		std::cout << "paired: " << paired << '\n';
		break;
	}
	case 'l': {
		std::string raw = safeInput<std::string>("Enter ciphertext: ");
		std::string paired, clean;
		split(raw, paired);
		parser(paired, clean);
		std::cout << "normalized: " << clean << "\npaired: " << paired << '\n';
		break;
	}
	case 'f': {
		std::string hex = safeInput<std::string>("Enter hex ciphertext: ");
		hex_xor_bruteforce(hex);
		break;
	}
	case 'q':
		std::cout << "exiting hex mode\n";
		break;
	default:
		suggestions();
		break;
	}
}
