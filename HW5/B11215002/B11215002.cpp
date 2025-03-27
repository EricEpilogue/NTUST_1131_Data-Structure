#include <iostream>
#include <string>

const int SIZE = 10;

struct Chest{
	int number = 0;
	std::string nameArray[3] = {};
	int valueArray[3] = {};

	Chest() : number(0), nameArray(), valueArray() {}
};

int top = 0, count = 0, chests = 1;
Chest backpack[SIZE];

void push(Chest backpack[], Chest treasures);
void swap(Chest backpack[], int from, int to, int index);
void sort(Chest backpack[], int chests);
void display(Chest backpack[]);

int main(int argc, char* argv[]){
	Chest chest;
	std::string itemName, input;
	int itemValue;
	bool isFull = true;

	while (std::getline(std::cin, input)) {
		size_t position = input.find(' ');
		if (position == std::string::npos) {
			break;
		}
		itemName = input.substr(0, position);
		itemValue = std::stoi(input.substr(position + 1));
		//insert
		chest.number = chests;
		chest.nameArray[count] = itemName;
		chest.valueArray[count] = itemValue;
		count++;
		push(backpack, chest);
		if (count == 0) {
			chest = Chest();
		}
	}
	
	if (count != 0) {
		//last chest not full
		isFull = false;
	}
	else {
		top--;
	}
	sort(backpack, chests);
	//debug
	backpack;
	display(backpack);
}

void push(Chest backpack[], Chest treasures) {
	if (top == SIZE - 1) {
		return;
	}
	else {
		backpack[top] = treasures;
		if (count == 3) {
			count = 0;
			chests++;
			top++;
		}
	}
}

void swap(Chest backpack[], int from, int to, int index) {
	//from backpack[i].valueArray[k] to backpack[i].valueArray[k + 1]
	int tempValue;
	tempValue = backpack[index].valueArray[from];
	backpack[index].valueArray[from] = backpack[index].valueArray[to];
	backpack[index].valueArray[to] = tempValue;

	std::string tempName;
	tempName = backpack[index].nameArray[from];
	backpack[index].nameArray[from] = backpack[index].nameArray[to];
	backpack[index].nameArray[to] = tempName;
}

void sort(Chest backpack[], int chests){
	bool swapped = false;
	for (int i = 0; i < chests; i++) {
		//implement bubble sort for backpack[i]
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3 - j - 1; k++) {
				if (backpack[i].valueArray[k] < backpack[i].valueArray[k + 1]) {
					swap(backpack, k, k + 1, i);
				}
			}
		}
	}
}

void display(Chest backpack[]){
	for (int i = top; i > -1; i--) {
		std::cout << "Backpack: " << backpack[i].number << "\n";
		for(int j = 0; j < 3; j++){
			if(backpack[i].nameArray[j] != "")
				std::cout << backpack[i].nameArray[j] << ": " << backpack[i].valueArray[j] << "\n";
		}
		std::cout << std::endl;
	}
}
