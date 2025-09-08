/**
 * @file Stack.c
 *
 * @brief Stack operations.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#include "Stack.h"

int initStack(Stack **stack)
{
    (*stack) = (Stack *)malloc(sizeof(Stack));
    if ((*stack) == NULL)
    {
        printf("Could not allocate the stack!\n");
        return EXIT_FAILURE;
    }
    (*stack)->top = NULL;
    (*stack)->size = 0;
    return EXIT_SUCCESS;
}

int push(Stack *s, char *value)
{
    Node *p = NULL;
    if (s == NULL)
    {
        printf("Stack is NULL!\n");
        return EXIT_FAILURE;
    }

    p = (Node *)malloc(sizeof(Node));
    if (p == NULL)
    {
        printf("Could not allocate the new node!\n");
        return EXIT_FAILURE;
    }
    p->data = (char *)malloc(strlen(value) + 1);
    if ((p->data) == NULL)
    {
        printf("Could not allocate the name of the node!\n");
        return EXIT_FAILURE;
    }
    strcpy((p->data), value);
    p->next = s->top;
    s->top = p;
    (s->size)++;
    return EXIT_SUCCESS;
}

int pop(Stack *s, char *retval)
{
    Node *p = NULL;
    if (s == NULL || s->size == 0)
    {
        printf("Sorry, stack is empty!\n");
        return EXIT_FAILURE;
    }

    if (retval == NULL)
    {
        printf("Retval is null!\n");
        return EXIT_FAILURE;
    }
    strcpy(retval, (s->top)->data);
    p = s->top;
    s->top = p->next;
    (s->size)--;
    free(p->data);
    free(p);
    return EXIT_SUCCESS;
}

void freeStack(Stack *stack)
{
    Node *cur = stack->top;
    Node *temp = NULL;

    while (cur != NULL)
    {
        temp = cur;
        cur = cur->next;
        free(temp->data);
        free(temp);
    }
    free(stack);
}

#ifdef DEBUG
/**
 * @brief Main function for testing the stack functions.
 *
 * This function tests the stack functions by initializing a stack,
 * pushing elements onto it, popping elements off, and printing them.
 * It lastly frees them from the memory.
 *
 * @return int Returns 0 on success or -1 on failure.
 */
int main(void)
{
    Stack *s = NULL;
    if (initStack(&s) == EXIT_FAILURE)
    {
        printf("unable to initialize stack!\n");
        return -1;
    }

    char *input = NULL;
    for (char ch = 'A'; ch <= 'F'; ch++)
    {
        input = (char *)malloc(2);
        char buf[2];
        buf[0] = ch;
        buf[1] = '\0';
        strcpy(input, buf);
        if (push(s, input) == EXIT_FAILURE)
        {
            printf("push function failed...\n");
            return -1;
        }
        free(input);
    }

    char *retval = NULL;
    while (s->size > 0)
    {
        retval = (char *)malloc(2);
        if (pop(s, retval) == EXIT_FAILURE)
        {
            printf("pop function failed...\n");
            return -1;
        }
        printf("%s has been popped\n", retval);
        free(retval);
    }

    freeStack(s);
    printf("Stack free from memory!\n");
    return 0;
}
#endif