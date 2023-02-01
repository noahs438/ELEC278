// Assignment 1, Q2 - Serhan, Noah
// Create a stack to solve the problem: Given a string containing opening and
// closing braces, check if it represents a balanced expression or not.

#include <stdio.h>

#define size 30 // Defining the size of the stack (bigger than what is needed)

int top = -1; // Setting the top of the stack to = -1 (meaning that it is empty - the first element is placed at position 0)
// Disadvantage of arrays is the waste of memory when the stack is small - however, in our case it can be ignored
char stack[size]; // Declaring an array of size 30 (extra space in case of larger test strings) to hold the characters of the string in a stack

char pop(void){ // Since we are going to initialize a variable to check later with this function, we set it as a char with arg void
    if(top==-1){ // If top==-1 then the stack is empty
        printf("Error: the stack is empty.\n");
        return 0;
    }
    else{
        top--; // Decrease the top by 1 and return the value of the stack at the index top
        return stack[top];
    }
}

void push(char x){
    if(top==size-1){
        printf("Error: the stack is full.\n");
    }
    else{
        stack[top]=x; // Setting the stack's top = to the pushed character
        top++;
    }
}

void check(char exp[size]){
    char check;
    int output;
    for(int i=0; exp[i]!='\0'; i++){
        if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{'){
            push(exp[i]); // If the character is an opening character then push it to the stack
        }
        if(exp[i]==')' || exp[i]==']' || exp[i]=='}') { // If the character is a closing character, then pop from the stack
            check = pop(); // Set the check variable = to the last character pushed to the stack (which should be an open character)
        }
        if((check=='{' && exp[i]=='}') || (check=='[' && exp[i]==']') || (check=='(' && exp[i]==')')){
            output = 1; // If the check character is == to the character from the expression then that portion is balanced
        }
        else{
            output = 0;
        }
    }
    printf("Balanced: %d\n", output);
}

int main(){
    stack[0] = '\0'; // Clearing the stack before the next check
    char expression1[size] = "{[{}{}]}[()]"; // Declaring and initializing the first test expression (balanced)
    check(expression1);
    stack[0] = '\0'; // Clearing the stack before the next check
    char expression2[size] = "{{}{}}"; // Declaring and initializing the second test expression (balanced)
    check(expression2);
    stack[0] = '\0'; // Clearing the stack before the next check
    char expression3[size] = "[]{}()"; // Declaring and initializing the third test expression (balanced)
    check(expression3);
    stack[0] = '\0'; // Clearing the stack before the next check
    char expression4[size] = "{()}[)"; // Declaring and initializing the fourth test expression (not balanced)
    check(expression4);
    stack[0] = '\0'; // Clearing the stack before the next check
    char expression5[size] = "{(})"; // Declaring and initializing the fifth test expression (not balanced)
    check(expression5);
}