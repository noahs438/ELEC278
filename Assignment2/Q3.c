// Assignment 2, Q3 - Serhan, Noah
// Given a binary search tree that may be unbalanced, convert it into an AVL tree that has minimum possible height.

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node{
    struct Node* leftChild;
    struct Node* rightChild;
    int value;
} Node;

// Creating a new node
Node* createNode(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode != NULL){ // If memory is allocated correctly
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        newNode->value = value;
    }
    return newNode;
}

// Inserting a new node into the tree
Node* insertNode(Node* root, int value){
    // If the tree is empty (root == NULL), create a new node
    if(root == NULL){
        root = createNode(value);
    }
    // If the new value is < than the root's value, then it belongs in the left subtree
    if(value < root->value){
        root->leftChild = insertNode(root->leftChild, value);
    }
    // If the new value is > than the root's value, then it belongs in the right subtree
    else if(value > root->value) {
        root->rightChild = insertNode(root->rightChild, value);
    }
    // Return the root
    return root;
}

// Build the binary search tree (from the example: 12, 8, 18, 5, 9, 17, 4, 2) - Read in breadth-first order
//            12
//         /      \
//       8         18
//      / \       / \
//     5   9    17
//    /
//   4
Node* buildTree(){
    Node* root = NULL;
    root = insertNode(root, 12);
    insertNode(root, 8);
    insertNode(root, 18);
    insertNode(root, 5);
    insertNode(root, 9);
    insertNode(root, 17);
    insertNode(root, 4);
    insertNode(root, 2);
    return root;
}

// Height function to be used to check if the tree is balanced or not
int height(Node* root){
    if (root == NULL){
        return 0;
    }
    // Find the height of the left subtree and the right subtree and add 1 for the root
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    // Return the maximum height
    if (leftHeight > rightHeight){
        return leftHeight + 1;
    }
    else{
        return rightHeight + 1;
    }
}

// Check to see if the tree is balanced or not
int isBalanced(Node* root){
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);

    // If the difference between the left and right subtree is <= 1, then the tree is balanced (check both subtrees too)
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->leftChild) && isBalanced(root->rightChild)){
        return 1;
    }
    else{
        return 0;
    }
}

// Get the balance factor of a tree
int balance(Node* root){
    return (height(root->leftChild) - height(root->rightChild)); // Without the absolute value to check for negative balance factors (right heavy)
}

// Print the tree in pre-order
void printPreOrder(Node* root){
    // Ensuring that the tree is not empty
    if (root == NULL) {
        return;
    }
    // Print the root
    printf("%d ", root->value);
    // Print the left subtree
    printPreOrder(root->leftChild);
    // Print the right subtree
    printPreOrder(root->rightChild);
}

// Rotate the BST to the right
Node* rotateRight(Node* root){
    // Create a new node to be the new root
    Node* newRoot = root->leftChild;
    // Make the new root's right child the old root
    root->leftChild = newRoot->rightChild;
    // Make the old root the new root's right child
    newRoot->rightChild = root;
    // Return the new root
    return newRoot;
}

// Rotate the BST to the left
Node* rotateLeft(Node* root){
    // Create a new node to be the new root
    Node* newRoot = root->rightChild;
    // Make the new root's left child the old root
    root->rightChild = newRoot->leftChild;
    // Make the old root the new root's left child
    newRoot->leftChild = root;
    // Return the new root
    return newRoot;
}

// Balance the tree
Node* rotate(Node* root){
    // Ensuring that the tree is not empty
    if (root == NULL){
        return root;
    }

    Node* temp = root;
    if (balance(root) > 1){
        if (balance(root->leftChild) == 1){
            // Perform a left rotation (on the following example tree)
            //        A
            //         \
            //          B
            //           \
            //            C
            temp = rotateRight(root);
            return temp;
        }
        else if (balance(root->leftChild) == -1){
            // The right subtree is left-heavy (need a right-left rotation) - (on the following example tree)
            //        A
            //         \
            //          B
            //         /
            //        C
            root->leftChild = rotateLeft(root->leftChild);
            temp = rotateRight(root);
            return temp;
        }
        // If the subtree balance is neither 1 or -1 then the height must be > 1 or < -1, recursively call the balance on the left subtree
        else if (balance(root->leftChild) != 0){
            temp->leftChild = rotate(temp->leftChild);
            return temp;
        }
    }
    else if (balance(root) < 1){
        if (balance(root->rightChild) == 1){
            //  Perform a left rotation (on the following example tree)
            //        A
            //         \
            //          B
            //           \
            //            C
            temp = rotateLeft(root);
            return temp;
        }
        else if (balance(root->leftChild) == -1){
            // The right subtree is left-heavy (need a right-left rotation) - (on the following example tree)
            //        A
            //         \
            //          B
            //         /
            //        C
            root->rightChild = rotateRight(root->rightChild);
            temp = rotateLeft(root);
            return temp;
        }
        // If the subtree balance is neither 1 or -1 then the height must be > 1 or < -1, recursively call the balance on the left subtree
        else if (balance(root->leftChild) != 0){
            temp->rightChild = rotate(temp->rightChild);
            return temp;
        }
    }
    return root;
}

// Main function
int main(){
    // Build the tree
    Node* root = buildTree();
    // Print the tree in pre-order -- JUST FOR TESTING PURPOSES
//    printf("Pre-order: ");
//    printPreOrder(root);
//    printf("\n");
    if (isBalanced(root)){
        printf("The tree is balanced.\n");
    }
    else{
        printf("The tree is not balanced.\n");
    }
    if (!isBalanced(root)){
        root = rotate(root);
    }
    printf("Pre-order traversal of the balanced tree: ");
    printPreOrder(root);
}