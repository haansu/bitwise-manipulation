#include "CyclicRedundancy.h"
#include <iostream>
#include <bitset>

CyclicRedundancy::CyclicRedundancy() { }

bool CyclicRedundancy::Set(std::string _message, std::string _generator) {
	// Validity checking for message and generator
	for (char elem : _message)
		if ((elem != '0') && (elem != '1')) {
			std::cout << "The message is allowed to have only 0s and 1s!\n";
			return false;
		}

	for (char elem : _generator)
		if ((elem != '0') && (elem != '1')) {
			std::cout << "The generator is allowed to have only 0s and 1s!\n";
			return false;
		}

	if (_message.length() < _generator.length()) {
		std::cout << "The length of the message has to be bigger than that of the generator!\n";
		return false;
	}

	// Converting input to uint32_t (unsigned int)
	uint64_t message = BinaryToInt(_message);
	uint64_t generator = BinaryToInt(_generator);

	// Transfering data into bitsets for output
	std::bitset<64> bitMessage(message);
	std::bitset<64> bitGenerator(generator);

	std::cout << "Intoduced data:\n" << bitMessage << "\n" << bitGenerator << "\n\n";

	uint8_t genDegree = PolinomeDegree(generator);

	// Shifting the message to the left by the degree of the generator
	message <<= genDegree;
	bitMessage = std::bitset<64>(message);
	
	uint64_t messageManip = message;
	
	// Matching the degree of the generator with the degree of the message (shifting generator to the left)
	generator <<= PolinomeDegree(messageManip) - genDegree;

	while (PolinomeDegree(messageManip) >= genDegree && genDegree != 0) {
		// Converting data to bitsets for output
		bitMessage = std::bitset<64>(messageManip);
		bitGenerator = std::bitset<64>(generator);
		std::cout << "----------------------------------------------------------------\n";
		std::cout << bitMessage << "\n" << bitGenerator << "\n";

		messageManip ^= generator;
		// Matching degree again (bitshift to the right)
		generator >>= PolinomeDegree(generator) - PolinomeDegree(messageManip);
	}
	std::cout << "----------------------------------------------------------------\n";

	bitMessage = std::bitset<64>(messageManip);
	std::cout << bitMessage << "\n\n";

	bitMessage = std::bitset<64>(message ^ messageManip);
	std::cout << "Result:\n" << bitMessage << "\n";

	return true;
}

uint8_t CyclicRedundancy::PolinomeDegree(uint64_t _bitPolinome) {
	uint8_t degree = 63;
	uint64_t check = 0x8000000000000000; // 2^63 0b1000....0 (64 bits)

	while (check != 0) {
		if ((check & _bitPolinome) == check)
			return degree;

		check >>= 1;
		degree--;
	}

}

uint64_t CyclicRedundancy::BinaryToInt(std::string _bitString) {
	uint64_t result = 0;
	for (char elem : _bitString) {
		result <<= 1;
		if (elem == '1')
			result++;
	}

	return result;
}