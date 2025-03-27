#include <iostream>
#include <string>
#include <math.h>

const int MAX = 100;
char postfix[MAX] = {};
char symbols[MAX] = {};
std::string binaryStack[MAX] = {};
int P_top, S_top, B_top = -1;

int order(char operators);
void push(char stack[], char value, int top);
char pop(char stack[], int top);
char peek(char stack[], int top);
std::string decToBin(int value);
int binaryToDecimal(std::string binary);
void bin_push(std::string stack[], std::string binary, int top);
std::string bin_pop(std::string stack[], int top);
std::string bin_peek(std::string stack[], int top);
std::string AND(std::string from, std::string to);
std::string NOT(std::string target);
std::string OR(std::string from, std::string to);
std::string XOR(std::string from, std::string to);

int main(int argc, char** argv) {
	std::string input;
	std::cin >> input;
	input += ')';
	push(symbols, '(', S_top++);

	//convert infix to postfix
	for (unsigned int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			push(symbols, input[i], S_top++);
		}
		else if (std::isspace(input[i])) {
			continue;
		}
		else if (std::isdigit(input[i])) {
			push(postfix, input[i], P_top++);
		}
		else if (input[i] == ')') {
			while (peek(symbols, S_top) != '(') {
				char ch = pop(symbols, S_top--);
				push(postfix, ch, P_top++);
			}
			pop(symbols, S_top--);
		}
		else {
			while (order(input[i]) <= order(peek(symbols, S_top))) {
				char ch = pop(symbols, S_top--);
				push(postfix, ch, P_top++);
			}
			push(symbols, input[i], S_top++);
		}
	}

	for (int i = 0; i <= S_top; i++) {
		push(postfix, pop(symbols, S_top--), P_top++);
	}

	for (int i = 1; i < P_top; i++) {
		std::cout << postfix[i];
	}

	std::cout << "\n";

	for (int i = 1; i < P_top; i++) {
		if (std::isdigit(postfix[i])) {
			bin_push(binaryStack, decToBin(postfix[i] - '0'), B_top++);
		}
		else {
			std::string from, to, target = "";
			if (postfix[i] == '~') {
				target = bin_pop(binaryStack, B_top--);
				bin_push(binaryStack, NOT(target), B_top++);
			}
			if (postfix[i] == '&') {
				from = bin_pop(binaryStack, B_top--);
				to = bin_pop(binaryStack, B_top--);
				bin_push(binaryStack, AND(from, to), B_top++);
			}
			if (postfix[i] == '^') {
				from = bin_pop(binaryStack, B_top--);
				to = bin_pop(binaryStack, B_top--);
				bin_push(binaryStack, XOR(from, to), B_top++);
			}
			if (postfix[i] == '|') {
				from = bin_pop(binaryStack, B_top--);
				to = bin_pop(binaryStack, B_top--);
				bin_push(binaryStack, OR(from, to), B_top++);
			}
		}

		std::cout << binaryToDecimal(bin_peek(binaryStack, B_top));
		if (i != P_top - 1)
			std::cout << " ";
	}
}

int order(char operators) {
	switch (operators) {
	case '~':
		return 4;
		break;
	case '&':
		return 3;
		break;
	case '^':
		return 2;
		break;
	case '|':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

void push(char stack[], char ch, int top) {
	if (top != MAX - 1) {
		top++;
		stack[top] = ch;
	}

	return;
}

char pop(char stack[], int top) {
	char ch;
	if (top != -1) {
		ch = stack[top];
		top--;
		return ch;
	}
	return {};
}

char peek(char stack[], int top) {
	if (top != -1) {
		return stack[top];
	}
	return {};
}

std::string decToBin(int value) {
	const int bits = 8;
	std::string binary(bits, '0');

	if (value < 0) {
		value = (1 << bits) + value;
	}

	for (int i = bits - 1; i >= 0; --i) {
		if (value % 2 == 1) {
			binary[i] = '1';
		}
		value /= 2;
	}

	return binary;
}

int binaryToDecimal(std::string binary) {
	int decimal = 0;

	if (binary[0] == '1') {
		for (int i = 0; i < binary.length(); ++i) {
			decimal += (binary[binary.length() - 1 - i] - '0') * std::pow(2, i);
		}
		decimal -= (1 << binary.length());
	}
	else {
		for (int i = 0; i < binary.length(); ++i) {
			decimal += (binary[binary.length() - 1 - i] - '0') * std::pow(2, i);
		}
	}

	return decimal;
}

void bin_push(std::string stack[], std::string binary, int top) {
	if (top != MAX - 1) {
		top++;
		stack[top] = binary;
	}

	return;
}

std::string bin_pop(std::string stack[], int top) {
	std::string str;

	if (top != -1) {
		str = stack[top];
		stack[top] = "";
		top--;
		return str;
	}
	return "";
}

std::string bin_peek(std::string stack[], int top) {
	if (top != -1) {
		return stack[top];
	}

	return {};
}

std::string AND(std::string from, std::string to) {
	int a = binaryToDecimal(from);
	int b = binaryToDecimal(to);

	int andResult = a & b;

	std::string result = decToBin(andResult);
	return result;
}

std::string NOT(std::string target) {
	int a = binaryToDecimal(target);

	int notResult = ~a & 0xFF;

	std::string result = decToBin(notResult);
	return result;
}

std::string OR(std::string from, std::string to) {
	int a = binaryToDecimal(from);
	int b = binaryToDecimal(to);

	int orResult = a | b;

	std::string result = decToBin(orResult);
	return result;
}

std::string XOR(std::string from, std::string to) {
	int a = binaryToDecimal(from);
	int b = binaryToDecimal(to);

	int xorResult = a ^ b;

	std::string result = decToBin(xorResult);
	return result;
}