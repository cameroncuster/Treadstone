#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// read func
vector<uint8_t> read(ifstream & is) {
	char ch;
	vector<uint8_t> text;
	while (is.get(ch))
		text.push_back(ch);
	return text;
}

// echo func
void echo(const vector<uint8_t> & text) {
	int n = text.size();
	for (int i = 0; i < n; i++) {
		printf("%c", text[i]);
		if ((i + 1) % 80 == 0)
			printf("\n");
	}
	printf("\n");
}

// main func
int main(int argc, char *argv[]) {
	printf("\n");
	ifstream fin(argv[1]);
	int bits = stoi(argv[2]);

	if (bits != 8 && bits != 16 && bits != 32) {
		fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
		return 0;
	}

	// read the text
	auto text = read(fin);

	// padding with X
	while (text.size() % (bits / 8))
		text.push_back('X');

	// echo the text
	echo(text);

	// calc the checksum
	int bit = 0;
	uint32_t mask = 0;
	uint32_t checksum = 0;
	for (auto ch : text) {
		mask |= ch;
		bit += 8;
		if (bit == bits) {
			checksum += mask;
			mask = 0;
			bit = 0;
		}
		mask <<= 8;
	}

	// output the resulting checksum
	switch (bits) {
		case 8:
			printf("%2d bit checksum is %8lx for all %4d chars\n", bits, uint8_t(checksum), text.size());
			break;
		case 16:
			printf("%2d bit checksum is %8lx for all %4d chars\n", bits, uint16_t(checksum), text.size());
			break;
		default:
			printf("%2d bit checksum is %8lx for all %4d chars\n", bits, checksum, text.size());
	}

	return 0;
}
