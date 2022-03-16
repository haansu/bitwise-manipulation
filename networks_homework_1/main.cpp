#include <iostream>
#include "BitParity.h"
#include "CyclicRedundancy.h"

void BitParityProblem() {
	BitParity* bitPar = new BitParity();

	while (true) {
		std::cout << "Insert your message:\n";
		std::string message;
		std::cin >> message; // "011010110011000110100"

		bool check = bitPar->Set(message);
		bitPar->Print();

		if (check)
			break;
		else
			std::cout << "\nInsert your message again:\n";
	}

	delete bitPar;
}

void CRCProblem() {
	CyclicRedundancy* cyclicRedundancy = new CyclicRedundancy();

	while (true) {
		std::string message, generator;
		std::cout << "M: ";
		std::cin >> message;
		std::cout << "G: ";
		std::cin >> generator;

		bool check = cyclicRedundancy->Set(message, generator); //"10010101" "1001"
		
		if (check) // 101101101 - 1001
			break;
	}
	delete cyclicRedundancy;
}

void Menu() {
	int option = -1;

	while (option < 0 || option > 2) {
		system("cls");
		std::cout << "1. Bit Parity;\n2. Cyclic Redundancy;\n0. Exit.\n";
		std::cin >> option;

		system("cls");

		switch (option) {
		case 1:
			BitParityProblem();
			break;
		case 2:
			CRCProblem();
			break;
		case 0:
			return;
		default:
			system("cls");
			std::cout << "A valid option is required!\n";
			system("PAUSE");
			break;
		}
	}
}

int main() {
	Menu();
	return 0;
}