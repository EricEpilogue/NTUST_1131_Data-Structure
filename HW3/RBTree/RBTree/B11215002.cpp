#include <iostream>
#include <string>

struct rbTree {
    int data;
    char colour;
    rbTree* left;
    rbTree* right;

    rbTree(int input) : data(input), colour('r'), left(nullptr), right(nullptr) {}
};

rbTree* LL(rbTree* parentNode);
rbTree* RR(rbTree* parentNode);
rbTree* colourChange(rbTree* root, int key);
rbTree* add(rbTree* root, int key);
rbTree* judgeRotation(rbTree* root);
void insert(rbTree*& root, int data);
std::string print(rbTree* root);

int main() {
    std::string input;
    rbTree* root = nullptr;

    while (std::getline(std::cin, input)) {
        if (input == "Print") {
            std::cout << print(root) << std::endl;
        }
        else if (input.substr(0, 6) == "Insert") {
            int data = 0;
            if (std::isalpha(input[7]))
                data = input[7];
            else
                data = std::stoi(input.substr(input.find(' ') + 1));

            insert(root, data);
        }
    }

    return 0;
}

rbTree* LL(rbTree* parentNode) {
    rbTree* newNode = parentNode->left;
    parentNode->left = newNode->right;
    newNode->right = parentNode;

    newNode->colour = 'b';
    parentNode->colour = 'r';

    return newNode;
}

rbTree* RR(rbTree* parentNode) {
    rbTree* newNode = parentNode->right;
    parentNode->right = newNode->left;
    newNode->left = parentNode;

    newNode->colour = 'b';
    parentNode->colour = 'r';

    return newNode;
}

rbTree* colourChange(rbTree* root, int key) {
    if (root == nullptr) 
        return root;

    if (root->left && root->right && root->left->colour == 'r' && root->right->colour == 'r') {
        root->colour = 'r';
        root->left->colour = 'b';
        root->right->colour = 'b';
    }

    if (key < root->data) {
        root->left = colourChange(root->left, key);
    }
    else if (key >= root->data) {
        root->right = colourChange(root->right, key);
    }

    return root;
}

rbTree* add(rbTree* root, int key) {
    if (root == nullptr) 
        return new rbTree(key);

    if (key < root->data) {
        root->left = add(root->left, key);
    }
    else if (key >= root->data) {
        root->right = add(root->right, key);
    }

    return root;
}

rbTree* judgeRotation(rbTree* root) {
    if (root->left && root->left->colour == 'r') {
        //LL
        if (root->left->left && root->left->left->colour == 'r') {
            root = LL(root);
        }
        //LR
        else if (root->left->right && root->left->right->colour == 'r') {
            root->left = RR(root->left);
            root = LL(root);
        }
    }

    if (root->right && root->right->colour == 'r') {
        //RR
        if (root->right->right && root->right->right->colour == 'r') {
            root = RR(root);
        }
        //RL
        else if (root->right->left && root->right->left->colour == 'r') {
            root->right = LL(root->right);
            root = RR(root);
        }
    }

    if (root->left) {
        root->left = judgeRotation(root->left);
    }
    if (root->right) {
        root->right = judgeRotation(root->right);
    }

    return root;
}

void insert(rbTree*& root, int data) {
    if (root == nullptr) {
        root = add(root, data);
        root = colourChange(root, data);
        root = judgeRotation(root);
    }
    else {
        root = colourChange(root, data);
        root = judgeRotation(root);
        root = add(root, data);
        root = judgeRotation(root);
    }

    if (root->colour == 'r') {
        root->colour = 'b';
    }
}

std::string print(rbTree* root) {
    if (root == nullptr) 
        return "";

    std::string leftNode = print(root->left);
    std::string rightNode = print(root->right);
    std::string result = "(" + leftNode + ")<-" + std::to_string(root->data) + "_" + root->colour + "->(" + rightNode + ")";

    return result;
}