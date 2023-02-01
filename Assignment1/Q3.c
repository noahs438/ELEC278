// Assignment 1, Q3 - Serhan, Noah
// Given an integer k and a queue of integers, the task is to reverse the order of
// the first k elements of the queue, leaving the other elements in the same relative
// order.

#include <stdio.h>
#include <stdlib.h>

// Defining what a node in our doubly linked list looks like
struct node{
    int data;
    struct node *next;
    struct node *prev;
};

// Global pointers
struct node *head = NULL;

// LOTS OF CODE TAKEN FROM Q1

void printList(){
    struct node *current = head; // Declaring a temporary node current to hold the values of the list to be printed
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

void insertFirst(int item){
    // Declaring the local node pointer (and allocating memory)
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->data = item; // Setting the data value

    head->prev = new; // Setting the head's previous pointing to the new node
    new->next = head; // Setting the new node's next pointing to head
    head = new; // Moving the head back so that it is corrected to = the new node
    head->prev = NULL; // Setting the head's previous = to NULL (which is now the new node's previous as well)
}

int deleteFirst(){
    int data = head->data;
    if(head!=NULL){ // As long as the list is not empty
        head = head->next; // Set the head = to the next node in the list
        head->prev = NULL; // Set the new head's previous pointer to point to NULL (as opposed to the old first value)
    }
    return data;
}

void append(int new_data){
    struct node* new = (struct node*)malloc(sizeof(struct node));
    struct node* last = head;

    new->data = new_data;
    new->next = NULL;

    if (head == NULL) { // If the list is empty, set the head = to the new node
        new->prev = NULL;
        head = new;
        return;
    }

    while (last->next != NULL) { // find the tail with a while loop
        last = last->next;
    }
    last->next = new; // The last node is set to the new node
    new->prev = last;
}

void reverse(int k) {
    struct node *reversedNew = NULL;

    for (int i = 0; i < k; i++) { // Delete the first node and append it to the list
        append(deleteFirst());
    }
    reversedNew = head;

    for (int i = 0; i<k; i++) {
        insertFirst(reversedNew->data);
    }
    head = reversedNew;
}

int main(){
    append(10);
    append(20);
    append(30);
    append(40);
    append(50);
    append(60);
    append(70);
    append(80);
    append(90);
    append(100);
    int k = 5;
    printList(); // Print the list before it is reversed
    reverse(k);
    printList();
    return 0;
}