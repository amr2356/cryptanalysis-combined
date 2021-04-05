#include <iostream>
#include <chrono>
#include <vector>
#include <future>

#include "quadgram_analysis.h"
#include "vigenere.h"
#include "enigma_plugboard.h"

class Cipher {
public:
	std::string label, decrypted, settings;
	double time_taken;
	Cipher(std::string l, std::string d, std::string s, double t): label{l}, decrypted{d}, settings{s}, time_taken{t} {}
};

template<typename T>
Cipher cryptanalysis(std::string label, T ciphertext) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	bool success = ciphertext.cryptanalysis();
	auto end = high_resolution_clock::now();
	double time_ms = duration_cast<milliseconds>(end-start).count();
	Cipher result {label, ciphertext.decrypted, ciphertext.settings(), time_ms/1000.0};
	if(success) std::cout << '\n' << result.label << ":\n" << result.decrypted << '\n' << result.settings << "\nTime taken: " << result.time_taken << " s\n";
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
	cipher_tasks.push_back(std::async([&]{return cryptanalysis("Military Enigma", EnigmaPlugboardText(input_text));}));
	
	return 0;
}


