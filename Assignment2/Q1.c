#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node{
    struct Node* leftChild;
    struct Node* rightChild;
    int value;
    char letter;
} Node;

// Creating a new node
Node* createNode(int value, char letter){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode != NULL){ // If memory is allocated correctly
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        newNode->value = value;
        newNode->letter = letter;
    }
    return newNode;
}

// Inserting a new node into the tree
Node* insertNode(Node* root, int value, char letter){
    // If the tree is empty (root == NULL), create a new node
    if(root == NULL){
        root = createNode(value, letter);
    }
    // If new value is less than root value, place newNode in left subtree, else place it in the right one
    if(value < root->value){
        root->leftChild = insertNode(root->leftChild, value, letter);
    } else if(value > root->value) {
        root->rightChild = insertNode(root->rightChild, value, letter);
    }
    // Return pointer to root
    return root;
}

// Build the tree that looks like this (to get A,B,C,D,E,F,G,H,I,J,K)
//            7
//        /       \
//       4         9
//      / \       / \
//     2   6    8   11
//    / \  /       /
//   1   3 5      10
Node* buildTree(){
    Node* root = NULL;
    // Hardcoding the tree - Read in breadth-first order
    root = insertNode(root, 7, 'A');
    insertNode(root, 4, 'B');
    insertNode(root, 9, 'C');
    insertNode(root, 2, 'D');
    insertNode(root, 6, 'E');
    insertNode(root, 8, 'F');
    insertNode(root, 11, 'G');
    insertNode(root, 1, 'H');
    insertNode(root, 3, 'I');
    insertNode(root, 5, 'J');
    insertNode(root, 10, 'K');
    return root;
}

// Printing the tree in postorder
void postOrder(Node* root){
    if(root != NULL){
        postOrder(root->leftChild);
        postOrder(root->rightChild);
        printf("%c ", root->letter); //Change this to printf("%d ", root->value); to print the values instead of letters
    }
}

// Creating the main function that builds the tree and outputs the postorder traversal
int main(){
    Node* root = buildTree();
    printf("The postorder traversal of the tree is: ");
    postOrder(root);
}