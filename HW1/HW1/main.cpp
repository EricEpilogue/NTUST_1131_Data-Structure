#include <iostream>
#include <string>

int main(){
	std::string input;
	std::getline(std::cin, input);
	bool result = true;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] != input[input.length() - i - 1]) {
			result = false;
		}
	}

	if (result == true) {
		std::cout << "The list is a palindrome" << std::endl;
	}
	else {
		std::cout << "The list is not a palindrome" << std::endl;
	}
	return 0;
}
