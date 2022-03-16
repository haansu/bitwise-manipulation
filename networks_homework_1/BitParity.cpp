#include <iostream>
#include "BitParity.h"

BitParity::BitParity() { }

bool BitParity::Set(std::string _bitString) {
	// Checks for dimension validity
	if (_bitString.length() % 7 != 0) {
		std::cout << "The number of bits sent must be a multiple of 7!\n";
		return false;
	}

	// Checks for character validity
	for (char elem : _bitString)
		if ((elem != '0') && (elem != '1')) {
			std::cout << "The bit string is allowed to have only 0s and 1s!\n";
			return false;
		}

	uint8_t split = 0;
	uint8_t count = 0;

	for (int i = 0; i < _bitString.length() + 1; i++) {
		if (i % 7 == 0 && i) {
			// Extra bitshift considering the entry having 7 bits and the error verifiers adding one extra
			split <<= 1;

			// Sets last bit to 1 if there is an odd number of 1s on the line
			if (count % 2)
				split++;
			
			bitMat.push_back(split);

			// Resets for next line
			split = 0;
			count = 0;
		}

		// Bit shift left 1 position
		split <<= 1;
		if (_bitString[i] == '1') {
			split++; // split |= 0b00000001; has the same effect
			count++;
		}
	}

	// Computes and adds last line to bitMat
	uint8_t lastSplit = 0;
	for (uint8_t elem : bitMat)
		lastSplit ^= elem;

	if (!CheckParity(lastSplit)) {
		std::cout << "An error has occured in the message!\n";
		bitMat.erase(bitMat.begin(), bitMat.end());
		return false;
	}

	bitMat.push_back(lastSplit);
	return true;
}


bool BitParity::CheckParity(uint8_t _bitLine) {
	std::bitset<8> line(_bitLine);
	line &= 0b11111110;

	return line.count() % 2 == _bitLine % 2;
}

void BitParity::Print() {
	for (uint8_t elem : bitMat) {
		std::bitset<8> bits(elem);
		std::cout << bits << "\n";
	}
}
