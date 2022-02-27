/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Cameron Custer
| Language: c, c++, Java
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2022
| Instructor: McAlpin
| Due Date: 7 February 2022
|
+=============================================================================*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// encode func
vector<int> encode(ifstream & is) {
	char ch;
	vector<int> alpha;
	while (is.get(ch) && alpha.size() < 512)
		// only accept alpha
		if (isalpha(ch))
			// use integer offsets
			alpha.push_back(tolower(ch) - 'a');
	return alpha;
}

// echo func
void echo(const vector<int> & text) {
	for (int i = 0; i < (int) text.size(); i++) {
		cout << char(text[i] + 'a');
		if ((i + 1) % 80 == 0)
			cout << '\n';
	}
	cout << '\n';
}

// main func
int main(int argc, char *argv[]) {
	cout << "\n\n";
	// capture the key
	ifstream keyin(argv[1]);
	vector<int> key = encode(keyin);
	keyin.close();

	cout << "Vigenere Key:\n\n";
	echo(key);
	cout << "\n\n";

	// capture the text
	ifstream textin(argv[2]);
	vector<int> text = encode(textin);
	textin.close();

	// pad with 'x'
	while (text.size() < 512)
		text.push_back('x' - 'a');

	cout << "Plaintext:\n\n";
	echo(text);
	cout << "\n\n";

	// encrypt the message
	vector<int> enc;
	for (int i = 0; i < (int) text.size(); i++) {
		enc.push_back(text[i] + key[i % key.size()]);
		if (enc.back() >= 26)
			enc.back() -= 26;
	}

	cout << "Ciphertext:\n\n";
	echo(enc);

	return 0;
}

/*=============================================================================
| I Cameron Custer (ca448424) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
