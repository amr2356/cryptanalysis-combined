//Project:Enigma
//Free for Distribution and use

#include "enigma.h"

using namespace std;

constexpr short plug_number {10};


class EnigmaPlugboardText : public EnigmaText{
public:
	char sub_list[26];
	EnigmaPlugboardText(string t): EnigmaText{t}, sub_list{} {strncpy(sub_list, alphabet, 26);}
	EnigmaPlugboardText(): EnigmaText{}, sub_list{} {strncpy(sub_list, alphabet, 26);}
	void read_plugboard();
	void encrypt(string key, string ring_setting) {
		for(int i=0;i<length;++i){
			encrypted[i] = sub_list[character_location(alphabet,decrypted[i])];
		}
		encrypted = encryption_decryption(key, ring_setting, true);
		for(int i=0;i<length;++i){
			encrypted[i] = sub_list[character_location(alphabet,encrypted[i])];
		}
	}
};


void EnigmaPlugboardText::read_plugboard() {
	char loc_holder[2];
	for(short i=1; i<=plug_number; ++i) {
		//taking input of two credentials
		cout<<"#"<<i<<" plug at: ";
		cin>>loc_holder[0];
		cout<<"#"<<i<<" plug end at: ";
		cin>>loc_holder[1];
		sub_list[character_location(alphabet, loc_holder[0])] = loc_holder[1];
		sub_list[character_location(alphabet, loc_holder[1])] = loc_holder[0];
	}
}
