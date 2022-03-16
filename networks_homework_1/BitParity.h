#pragma once
#include <vector>
#include <cstdint>
#include <bitset>

class BitParity {

public:
	BitParity();
	bool Set(std::string _bitString);
	void Print();

private:
	bool CheckParity(uint8_t _bitLine);

	std::vector<uint8_t> bitMat;
};

