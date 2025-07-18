#include <variant>
#include <sstream>
#include <iostream>
#include <string>

std::variant<int, std::string> typedInput() {

	std::string inputData;
	std::getline(std::cin, inputData);
	std::cin.clear();

	std::istringstream iss(inputData);
	int outInt;
	if (iss >> outInt && iss.eof()) {
		return outInt;
	}
	else {
		return inputData;
	}

}

template <typename T>
T correctInput();

template<>
int correctInput<int>() {
	while (true) {
		auto input = typedInput();

		if (auto* convertedInt = std::get_if<int>(&input)) {
			return *convertedInt;
		}
		else {
			std::cout << "Seriously? This is not a number, but some kind of nonsense. Try again\n";
		}
	}
}

template<>
std::string correctInput<std::string>() {
	auto input = typedInput();
	return std::get<std::string>(input);
}