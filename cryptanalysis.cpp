#include <iostream>
#include <chrono>
#include <vector>
#include <future>

#include "quadgram_analysis.h"
#include "vigenere.h"
#include "enigma.h"

using namespace std::chrono;

class Cipher {
public:
	std::string label, decrypted, settings;
	double score;
	long time_taken;
	Cipher(std::string l, std::string d, std::string s, double c, long t): label{l}, decrypted{d}, settings{s}, score{c}, time_taken{t} {}
};

template<typename T>
Cipher cryptanalysis(std::string label, T ciphertext) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	ciphertext.cryptanalysis();
	auto end = high_resolution_clock::now();
	auto time_taken = duration_cast<seconds>(end-start).count();
	Cipher result {label, ciphertext.decrypted, ciphertext.settings(), ciphertext.score, time_taken};
	std::cout << '\n' << result.label << ":\n" << result.decrypted << '\n' << result.settings << "\nTime taken: " << result.time_taken << " s\nScore: " << result.score << '\n';
	return result;
}


int main(){

	std::string input_text;
	std::cout << "Ciphertext: ";
	std::cin >> input_text;
	
	//Add or remove ciphers here
	std::vector<std::future<Cipher>> cipher_tasks;
	cipher_tasks.push_back(std::async([&]{return cryptanalysis("Vigenere", VigenereText(input_text));}));
	cipher_tasks.push_back(std::async([&]{return cryptanalysis("Commercial Enigma", EnigmaText(input_text));}));
	
	return 0;
}


