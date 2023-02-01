// Assignment 1, Q1 - Serhan, Noah
// Define the data structure of a doubly linked list and write functions:
// 1. void create() to create the list
// 2. void insertFirst() to insert a new node at the beginning of the list
// 3. void deleteFirst() to delete the first node of the list
// 4. void insertPos() to insert a node in the right position
// 5. void merge() to merge two linked lists

#include <stdio.h>
#include <stdlib.h>

// Defining what a node in our doubly linked list looks like
struct node{
    int data;
    struct node *prev;
    struct node *next
};

// Global pointers
struct node *head1 = NULL;
struct node *tail1 = NULL;
struct node *head2 = NULL;
struct node *tail2 = NULL;

struct node *create(int i, int j, int k){
    // Declaring the local node pointers (and allocating memory) for the new nodes
    struct node *new1 = (struct node*)malloc(sizeof(struct node));
    struct node *new2 = (struct node*)malloc(sizeof(struct node));
    struct node *new3 = (struct node*)malloc(sizeof(struct node));

    new1->data = i; // Setting the data value = to 10 to hardcode the first element of the linked list
    new2->data = j; // Setting the data value = to 20 to hardcode the second element of the linked list
    new3->data = k; // Setting the data value = to 50 to hardcode the last element of the linked list

    // Setting the head and tail = to the first new node
    head1 = new1;
    tail1 = new1;

    head1->prev = NULL;// Head's previous points to NULL (start)
    tail1->next = new2; // Setting the pointer after the tail = to the second new node
    new2->prev = tail1; // Linking that new node back to the tail
    tail1 = new2; // Moving the tail over so that it = the end of the list, which is now the new node
    tail1->next = new3; // Setting the value after the new node = to the third new node
    new3->prev = tail1; // Linking that new node back to the tail
    tail1 = new3; // Moving the tail over so that it = the end of the list, which is now the new node
    tail1->next = NULL; // Setting the value after the new node = to NULL
}

void insertFirst(){
    // Declaring the local node pointer (and allocating memory)
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = 5; // Setting the data value = to 50 to hardcode the last element of the linked list

    head1->prev = new; // Setting the head's previous pointing to the new node
    new->next = head1; // Setting the new node's next pointing to head
    head1 = new; // Moving the head back so that it is corrected to = the new node
    head1->prev = NULL; // Setting the head's previous = to NULL (which is now the new node's previous as well)
}

void  deleteFirst(){
    if(head1!=NULL){ // As long as the list is not empty
        head1 = head1->next; // Set the head = to the next node in the list
        head1->prev = NULL; // Set the new head's previous pointer to point to NULL (as opposed to the old first value)
    }
}

void insertPos(int value){
    struct node *current = head1; // Declaring a temporary node current to hold the values of the list and setting it = to head
    struct node *new = (struct node*)malloc(sizeof(struct node)); // Declaring the local node pointer for the new node
    new->data = value; // Setting the value of the data at the new node = to 30

    // While the next node in the list is not the end and the value of the next node is not = or larger than the value of the new node
    while(current->next!=NULL && current->next->data<=new->data){
        current = current->next; // Iterate through the list (setting the current node = to the next one)
    }
    new->next = current->next; // The new node's next node is = to the current node's next node
    current->next = new; // Overriding the current node's next node with the new node
}

void merge(){
    // HardCoding creating a second list with head2 and tail2
    // Declaring the local node pointers (and allocating memory) for the new nodes
    struct node *new1 = (struct node*)malloc(sizeof(struct node));
    struct node *new2 = (struct node*)malloc(sizeof(struct node));
    struct node *new3 = (struct node*)malloc(sizeof(struct node));

    new1->data = 24; // Setting the data value = to 10 to hardcode the first element of the linked list
    new2->data = 25; // Setting the data value = to 20 to hardcode the second element of the linked list
    new3->data = 36; // Setting the data value = to 50 to hardcode the last element of the linked list

    // Setting the head and tail = to the first new node
    head2 = new1;
    tail2 = new1;

    head2->prev = NULL;// Head's previous points to NULL (start)
    tail2->next = new2; // Setting the pointer after the tail = to the second new node
    new2->prev = tail2; // Linking that new node back to the tail
    tail2 = new2; // Moving the tail over so that it = the end of the list, which is now the new node
    tail2->next = new3; // Setting the value after the new node = to the third new node
    new3->prev = tail2; // Linking that new node back to the tail
    tail2 = new3; // Moving the tail over so that it = the end of the list, which is now the new node
    tail2->next = NULL; // Setting the value after the new node = to NULL


    // BEGINNING OF MERGE
    struct node *current2 = head2; // Declaring and initializing temporary nodes for each list
    while(current2!=NULL){ // While the new list is not empty
        insertPos(current2->data); // Call the insertPos function to place the node at the correct location in list 1
        current2=current2->next; // Set the current temporary node = to the next one in the list 2
    }
}

void printList(){
    struct node *current = head1; // Declaring a temporary node current to hold the values of the list to be printed
    // Ensure that the list is not empty
    if(current==NULL){ // If there is nothing at the head node, then the list is empty
        printf("The list is empty");
    }
    while(current!=NULL){ // While the current node is not at the end of the list
        printf("%d ", current->data); // Print the value at the current node
        current=current->next; // Set the current = to the next node in the list
    }
    printf("\n");
    free(current); // Freeing the memory allocated to current
}

int main() {
    create(10,20,50);
    printList(); // Use printList after each step
    insertFirst();
    printList();
    deleteFirst();
    printList();
    insertPos(30);
    printList();
    merge();
    printList();
}
