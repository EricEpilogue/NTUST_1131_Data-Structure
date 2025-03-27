#include <iostream>
#include <string>
#include <cstring>

const int MAX = 20;
int front = -1, rear = -1;
const int SIZE = 20;

struct generalTree {
    char data;
    int level = 0;
    generalTree* leftmostChild;
    generalTree* rightSibling;

    generalTree(char input) : data(input), level(0), leftmostChild(nullptr), rightSibling(nullptr) {}
};

struct binaryTree {
    char data;
    int level = 0;
    binaryTree* left;
    binaryTree* right;

    binaryTree(char input) : data(input), level(0), left(nullptr), right(nullptr) {}
};

//queue for traveral
generalTree* nodeQ[MAX];

void newNode(generalTree* root, char rootData, generalTree* inputNode);
void traversebyLevel(generalTree* root);
void insert(generalTree* node);
generalTree* dequeue();
binaryTree* generalToBinary(generalTree* root, int binaryLevel);
void printInorder(binaryTree* root);
void printPreorder(binaryTree* root);
void printPostorder(binaryTree* root);

int main(int argc, char* argv[]){
    char directory[SIZE][SIZE] = {};
    int line = 0;
    int index = 0;
    std::string input, form;
    //collect data from input
    while (std::getline(std::cin, input)) {
        if (input != "prefix" && input != "postfix" && input != "infix") {
            for (int i = 0; i < input.length(); ++i) {
                if (input[i] != ' ') {
                    directory[line][index++] = input[i];
                }
            }
            directory[line][index] = '\0';
        }
        else {
            form = input;
            break;
        }
        line++;
        index = 0;
    }

    char nodes[SIZE][SIZE] = {};

    for (char alphabet = 'a'; alphabet <= 'z'; alphabet++) {
        for (int i = 0; i < line; i++) {
            if (directory[i][0] == alphabet) {
                //sort
                strcpy(nodes[index++], directory[i]);
            }
        }
    }

    generalTree* root = nullptr;

    //add nodes to the general tree
    for (int i = 0; i < line; i++) {
        generalTree* parent = new generalTree(nodes[i][0]);
        if (i == 0) {
            root = parent;
        }
        int temp = 1;

        while (nodes[i][temp] != '\0') {
            generalTree* input = new generalTree(nodes[i][temp]);
            //use root so we search from top down
            newNode(root, nodes[i][0],input);
            temp++;
        }
    }

    //print by level
    traversebyLevel(root);

    std::cout << "\n";

    binaryTree* B_root = generalToBinary(root, 0);

    B_root;

    if (form == "infix") {
        printInorder(B_root);
    }
    else if (form == "prefix") {
        printPreorder(B_root);
    }
    else if (form == "postfix") {
        printPostorder(B_root);
    }

    return 0;
}

generalTree* findNode(generalTree* root, char data) {
    if (!root)
        return nullptr;

    if (root->data == data) 
        return root; //found node

    //if cant find then move to higher level and start from left
    generalTree* foundNode = findNode(root->leftmostChild, data);
    if (foundNode) 
        return foundNode;

    //search the right
    return findNode(root->rightSibling, data);
}

void newNode(generalTree* root, char rootData, generalTree* inputNode) {
    //find and inherit the level with the same character
    generalTree* parent = findNode(root, rootData);

    //if parent has no child
    if (!parent->leftmostChild) {
        //become left child
        parent->leftmostChild = inputNode;
        parent->leftmostChild->level = parent->level + 1;
    }
    else {
        generalTree* current = parent->leftmostChild;
        //find the left child and become the right sibling
        while (current->rightSibling) {
            current = current->rightSibling;
        }
        current->rightSibling = inputNode;
        current->rightSibling->level = parent->level + 1;
    }
}

void traversebyLevel(generalTree* root) {
    insert(root);
    int currentLevel = root->level;

    while (front != -1 && rear != -1) {
        generalTree* tempNode = dequeue();

        std::cout << tempNode->data;
        if (tempNode->level > currentLevel) {
            currentLevel = tempNode->level;
        }
        //insert next level starting from the left to the right
        generalTree* siblings = nullptr;

        if (tempNode->leftmostChild) {
            insert(tempNode->leftmostChild);
            siblings = tempNode->leftmostChild->rightSibling;
        }
        else {
            siblings = nullptr;
        }

        while (siblings) {
            insert(siblings);
            siblings = siblings->rightSibling;
        }
    }
}

//implement queue for level wise traverse
void insert(generalTree* node) {
    if (rear == MAX - 1) {
        //overflow
        return;
    }
    else if (front == -1 && rear == -1) {
        front = rear = 0;
    }
    else
        rear++;
    nodeQ[rear] = node;
}

generalTree* dequeue() {
    generalTree* output = nullptr;
    if (front == -1) {
        //underflow
        return nullptr;
    }
    else {
        output = nodeQ[front];
        front++;
        //no more things to remove
        if (front > rear)
            front = rear = -1;
        return output;
    }
}

binaryTree* generalToBinary(generalTree* root, int binaryLevel){
    binaryTree* node = new binaryTree(root->data);
    node->level = binaryLevel;
    int convertedLevel;

    //fix level
    if (root->leftmostChild) {
        convertedLevel = root->level + 1;
        node->left = generalToBinary(root->leftmostChild, convertedLevel);
    }
    if (root->rightSibling) {
        convertedLevel = root->level + 1;
        node->right = generalToBinary(root->rightSibling, convertedLevel);
    }

    return node;
}

void printInorder(binaryTree* root){
    if (!root)
        return;
    printInorder(root->left);
    std::cout << root->data;
    printInorder(root->right);
}

void printPreorder(binaryTree* root) {
    if (!root)
        return;
    std::cout << root->data;
    printPreorder(root->left);
    printPreorder(root->right);
}

void printPostorder(binaryTree* root) {
    if (!root)
        return;    
    printPostorder(root->left);
    printPostorder(root->right);
    std::cout << root->data;
}