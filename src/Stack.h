/**
 * @file Stack.h
 *
 * @brief Stack function prototypes push, pop, initialization and free.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#ifndef Stack_h
#define Stack_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @struct Node
 *
 * @brief Structure of an element in the stack.
 */
typedef struct node
{
    char *data;
    struct node *next;
} Node;

/**
 * @struct Stack
 *
 * @brief Structure of stack to hold elements.
 */
typedef struct stack
{
    struct node *top;
    int size;
} Stack;

/**
 * @brief Creates a new stack.
 *
 * This function allocates memory for a new stack, its top to NULL and its size to 0.
 * If memory allocation fails, prints error and returns failure.
 *
 * @param stack Double pointer to the stack that will be initialized and memory allocated.
 * @return int Returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int initStack(Stack **stack);

/**
 * @brief Pushes a new element on the stack.
 *
 * This function takes a value and pushes it on the top of the stack.
 *
 * @param s Pointer of stack.
 * @param value The data to push on the stack.
 * @return int Returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int push(Stack *stack, char *value);

/**
 * @brief Pops the top element from the stack and returns its data.
 *
 * This function removes the top element from the stack and returns its data.
 *
 * @param s Pointer of stack.
 * @param retval Pointer to store the data of the popped element.
 * @return int Returns EXIT_SUCCESS on success or EXIT_FAILURE if the stack is empty or another error occurs.
 */
int pop(Stack *stack, char *retval);

/**
 * @brief Frees the stack and its nodes from the memory.
 *
 * This function frees all nodes in the stack, including their data, and lastly frees the stack itself.
 *
 * @param stack Pointer of stack.
 */
void freeStack(Stack *stack);

#endif