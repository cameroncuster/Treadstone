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
