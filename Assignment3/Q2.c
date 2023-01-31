// Assignment 3, Q2 - Serhan, Noah

#include <stdio.h>
#include <stdlib.h>

// Create a node
struct node {
    int key;
    int value;
    struct node *next;
    struct node *prev;
};

// Create cache structure
struct Cache {
    int size;
    int capacity;
    struct node *left;
    struct node *right;
};

// Create a new node
struct node *newNode(int key, int value){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    new->key = key;
    new->value = value;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// Create a new cache (cache() function but renamed newCache() to avoid confusion)
struct Cache *newCache(int capacity){
    // Ensure that the capacity is a positive value
    if (capacity <= 0){
        printf("Error: the capacity must be a positive number\n");
        return NULL;
    }

    struct Cache *new = (struct Cache*)malloc(sizeof(struct Cache));
    new->size = 0;
    new->capacity = capacity;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void removeNode(struct Cache *cache, struct node *node){
    if (node->prev != NULL){ // If the node is not the leftmost node
        node->prev->next = node->next; // Set the previous node's next to the next node
    }
    else {
        cache->left = node->next; // If the node is the leftmost node, set the cache's left to the next node
    }
    if (node->next != NULL){ // If the node is not the rightmost node
        node->next->prev = node->prev; // Set the next node's previous to the previous node
    }
    else { // If the node is the rightmost node
        cache->right = node->prev; // Set the cache's right to the previous node
    }
    cache->size--; // Decrease the cache's size by 1
    free(node); // Free the node
}

void insert(struct Cache *cache, struct node *node){
    if (cache->left == NULL){ // If the cache is empty
        cache->left = node; // Set the cache's left to the node
        cache->right = node; // Set the cache's right to the node
    }
    else { // If the cache is not empty
        node->next = cache->left; // Set the node's next to the cache's left
        cache->left->prev = node; // Set the cache's left's previous to the node
        cache->left = node; // Set the cache's left to the node (i.e. the node is now the leftmost node - most recently used)
    }
    cache->size++; // Increase the cache's size by 1
}

// Move a node to the leftmost position
void move(struct Cache *cache, struct node *node){
    if (node == cache->left){   // If the node is the leftmost node set the cache left = to the next node
        cache->left = node->next;
    }
    if (node->prev != NULL){   // If the node is not the leftmost node, set the previous node's next = to the next node
        node->prev->next = node->next;
    }
    if (node->next != NULL){  // If the node is not the rightmost node, set the next node's previous = to the previous node
        node->next->prev = node->prev;
    }
    if (node == cache->right){ // If the node is the rightmost node, set the cache right = to the previous node
        cache->right = node->prev;
    }
    // Reinsert the node to the leftmost position
    node->prev = NULL;
    node->next = cache->left;
    cache->left->prev = node;
    cache->left = node;
}

// Add a node to the cache
void put(struct Cache *cache, int key, int value){
    struct node *node = newNode(key, value);
    if (cache->size == cache->capacity){
        removeNode(cache, cache->right);
//        printf("Cache is full, removing the least recently used node\n");
    }
    insert(cache, node);
//    printf("Adding %d to the cache\n", value);
}

// Get a node from the cache
int get(struct Cache *cache, int key){
    struct node *temp = cache->left; // Start at the left
    while(temp != NULL){ // While we haven't reached the end of the cache
        if(temp->key == key){ // If we find the key
            // For testing purposes
            printf("%d\n", temp->value);
            move(cache, temp); // Move the node to the leftmost position (most recently used)
            return temp->value; // Return the value of the key
        }
        temp = temp->next; // If we haven't found the key, move on to the next node
    }
    // For testing purposes
    printf("Key not found\n");
    return -1; // If the key is not in the cache, return -1
}

// Print the cache
void printCache(struct Cache *cache){
    struct node *temp = cache->left;
    printf("Cache: \n");
    while (temp != NULL){
        printf("Key: %d, Value: %d \n", temp->key, temp->value);
        temp = temp->next;
    }
    printf("End of cache. \n");
}

int main(){
    struct Cache *cache = newCache(2);
    if (cache == NULL){
        // The cache was initialized with a negative or 0 capacity value - error was already printed in the newCache() function
        return -1;
    }
    else{
        put(cache, 1, 10);
//    printCache(cache);
        put(cache, 2, 20);
//    printCache(cache);
        get(cache, 1);
        put(cache, 3, 30);
//    printCache(cache);
        get(cache, 2);
        put(cache, 4, 40);
//    printCache(cache);
        get(cache, 1);
        get(cache, 3);
        get(cache, 4);
        put(cache, 5, 50);
//    printCache(cache);
    }
    free(cache);
    return 0;
}