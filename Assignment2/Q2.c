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

// Count the number of nodes in the tree
int countNodes(Node* root){
    // If the tree is empty, return 0
    if(root == NULL){
        return 0;
    }
    // Count the number of nodes in the left subtree and the right subtree and add 1 for the root
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);
}

// Add the tree to an array through inorder traversal
void inOrderWrite(Node* root, int* arr, int* i){
    if(root != NULL){
        inOrderWrite(root->leftChild, arr, i);   // Traverse the left subtree
        arr[*i] = root->value;     // Add the root's value to the array
        (*i)++;                    // Increment the index
        inOrderWrite(root->rightChild, arr, i);  // Traverse the right subtree
    }
}

int *inOrder(Node* root){
    int n = countNodes(root);
    int *arr = malloc(sizeof(int)*n);   // Allocate memory for the array
    int i = 0;
    inOrderWrite(root, arr, &i);   // Calling the inOrderWrite function to write the tree to the array
    return arr;
}


// Print the tree inorder ------ FOR TESTING ONLY
void printInOrder(Node* root){
    if(root != NULL){
        printInOrder(root->leftChild);  // Traverse the left subtree
        printf("%d ", root->value);     // Print the root's value
        printInOrder(root->rightChild); // Traverse the right subtree
    }
}

// Build the first BST (from the example: 3,2,5,1) - Read in breadth-first order
//            3
//          /   \
//         2     5
//        /
//       1
Node* buildTree1(){
    Node* root = NULL;
    root = insertNode(root, 3);
    insertNode(root, 2);
    insertNode(root, 5);
    insertNode(root, 1);
//    printInOrder(root); // Print the tree inorder ----- FOR TESTING ONLY
//    printf("\n");
    return root;
}

// Build the second BST (from the example: 4,1,7,2,9) - Read in breadth-first order
//            4
//          /   \
//         1     7
//          \     \
//           2     9
Node* buildTree2(){
    Node* root = NULL;
    root = insertNode(root, 4);
    insertNode(root, 1);
    insertNode(root, 7);
    insertNode(root, 2);
    insertNode(root, 9);
//    printInOrder(root); // Print the tree inorder ----- FOR TESTING ONLY
//    printf("\n");
    return root;
}

// Build the final binary tree from the merged array (with the array, i being the starting index and n being the end index)
Node * buildTree3(int arr[], int i, int n){
    if (i > n){ // Base case to stop the recursion (if the start index is greater than the end index)
        return NULL;
    }
    // Find the middle index
    int middle = (n+i)/2;
    // Create a new node with the value of the middle index
    Node* root3 = createNode(arr[middle]);
    root3->leftChild = buildTree3(arr, i, middle-1);     // Decrease the end index (now set to middle) by 1
    root3->rightChild = buildTree3(arr, middle+1, n);    // Increase the start index (now set to middle) by 1
    return root3;
}

// Merge the two trees into an array
Node* merge(Node* root1, Node* root2){
    // Ensure that both trees are not empty
    if (root1 == NULL && root2 == NULL){
        printf("Both trees are empty\n");
        return 0;
    }
    int size1 = countNodes(root1);
    int size2 = countNodes(root2);
    int *arr1 = inOrder(root1);
//    // Print elements of array 1
//    printf("Array 1: ");
//    for(int i = 0; i < size1; i++){
//        printf("%d ", arr1[i]);
//    }
//    printf("\n");

    int *arr2 = inOrder(root2);

//    // Print elements of array 2
//    printf("Array 2: ");
//    for(int i = 0; i < size2; i++){
//        printf("%d ", arr2[i]);
//    }
//    printf("\n");
    // Find the size of the merged array
    int size3 = size1 + size2;
    int *arr3 = (int*)malloc(sizeof(int)*(size3));  // Allocate memory for the array
    int i = 0, j = 0 ,k = 0;
    // Merge the two arrays into arr3
    while (i < size1 && j < size2){
        // If the value in arr1 is smaller than the one in arr2, add it to arr3
        if (arr1[i] < arr2[j]){
            arr3[k++] = arr1[i++];
        }
        else{
            arr3[k++] = arr2[j++];
        }
    }
    // Add the remaining elements of arr1 to arr3
    while (i < size1){
        arr3[k++] = arr1[i++];
    }
    // Add the remaining elements of arr2 to arr3
    while (j < size2){
        arr3[k++] = arr2[j++];
    }
//    // Print elements of array 3
//    printf("Array 3: ");
//    for(int i = 0; i < size3; i++){
//        printf("%d ", arr3[i]);
//    }
//    printf("\n");

    // -1 since starting at 0 and ending at index size-1
    Node* rootMerged = buildTree3(arr3, 0, (countNodes(root1)+countNodes(root2))-1);
    return rootMerged;
}

// Find the height of a tree
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

// Prints nodes on the same level of the tree
void printLevel(Node* root, int level){
    // Ensuring that the tree is not empty
    if (root == NULL){
        return;
    }
    if (level == 1){ // At the top level (root)
        printf("%d ", root->value);
    }
    // Traverse the left and right subtrees
    else if (level > 1){
        printLevel(root->leftChild, level-1);
        printLevel(root->rightChild, level-1);
    }
}


// Print the tree in breadth first order
void breadthFirstTraversal(Node* root){
    int heightOfTree = height(root);    // Get the height of the tree using the height function
    printf("Breadth First Traversal: ");
    for (int i = 1; i <= heightOfTree; i++){    // Loop through the levels of the tree
        printLevel(root, i);
    }
}

int main(){
    Node* root1 = buildTree1(); // Build the first tree
    Node* root2 = buildTree2(); // Build the second tree
    Node* root3 = merge(root1, root2); // Merge the two trees into an array
//    printInOrder(root3);
//    printf("\n");
    breadthFirstTraversal(root3); // Print the tree in breadth first order
}