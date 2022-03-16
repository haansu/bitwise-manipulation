#pragma once
#include <string>

class CyclicRedundancy {
public:
	CyclicRedundancy();
	bool Set(std::string _message, std::string _generator);

private:
	uint64_t BinaryToInt(std::string _bitString);
	uint8_t PolinomeDegree(uint64_t _bitPolinome);
};

