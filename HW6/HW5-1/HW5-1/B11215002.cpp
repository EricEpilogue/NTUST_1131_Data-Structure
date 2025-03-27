#include <iostream>
const int MAX = 10;

bool DFS(int reference[][MAX], int modify[][MAX], int x, int y);
bool judgeRot(int matrix[][MAX]);
int timer = 0;

int main() {
	int m, n;
	std::cin >> m >> n;
	int appleMatrix[MAX][MAX] = {};
	int copyMatrix[MAX][MAX] = {};
	int input;

	//initialize and fill empty area as wall
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			appleMatrix[i][j] = -1;
			copyMatrix[i][j] = -1;
		}
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> input;
			appleMatrix[i][j] = input;
		}
	}

	bool hasChanged = true;
	while (hasChanged) {
		hasChanged = false;		
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				copyMatrix[i][j] = appleMatrix[i][j];
			}
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (appleMatrix[i][j] == 2) {
					if (i + 1 <= MAX)
						if (DFS(appleMatrix, copyMatrix, i + 1, j) == true)
							hasChanged = true;
					if (j + 1 <= MAX)
						if (DFS(appleMatrix, copyMatrix, i, j + 1) == true)
							hasChanged = true;
					if (i - 1 >= 0)
						if (DFS(appleMatrix, copyMatrix, i - 1, j) == true)
							hasChanged = true;
					if (j - 1 >= 0)
						if (DFS(appleMatrix, copyMatrix, i, j - 1) == true)
							hasChanged = true;
				}
			}
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				appleMatrix[i][j] = copyMatrix[i][j];
			}
		}

		if(hasChanged)
			timer += 1;
	}

	if (judgeRot(appleMatrix) == false) {
		std::cout << "-1";
	}
	else {
		std::cout << timer;
	}
}

bool DFS(int reference[][MAX], int modify[][MAX], int x, int y) {
	bool hasChanged = false;

	//not rotten or wall
	if (reference[x][y] == 0) {
		modify[x][y] = 1;
		hasChanged = true;
	}
	else if (reference[x][y] == 1) {
		modify[x][y] = 2;
		hasChanged = true;
	}


	return hasChanged;
}

bool judgeRot(int matrix[][MAX]){
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (matrix[i][j] != 2 && matrix[i][j] != -1) {
				return false;
			}
		}
	}
	return true;
}

