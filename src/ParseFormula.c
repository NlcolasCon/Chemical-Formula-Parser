/**
 * @file ParseFormula.c
 *
 * @brief Chemical formula parser.
 *
 * This file contains functions to parse chemical formulas from input files,
 * compute extended formulas, total proton numbers, and verify balanced parentheses.
 *
 * The program uses a stack to process the parsing of
 * chemical formulas. The chemical formulas are processed according to
 * user commands to produce output files with the results.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#include "Stack.h"
#include "periodicTable.h"
#include "ParseFormula.h"

/**
 * @brief Main entry for chemical formula parser.
 *
 * This function processes command-line arguments to specify operations 
 * (formula extension, proton count, or parentheses validation) and manages
 * the input and output files accordingly.
 *
 * @param argc The count of command line arguments.
 * @param argv Array of command line argument strings.
 * @return int 0 on success, -1 on failure.
 */
int main(int argc, char *argv[])
{

    if (argc != 4 && argc != 5)
    {
        printf("Wrong arguments! try:\n1. ./parseFormula inputFile.txt -ext testFile.txt outputFile.txt\n2. ./parseFormula inputFile.txt -pn testFile.txt outputFile.txt\n3. ./parseFormula inputFile.txt -v testFile.txt\n");
        return -1;
    }

    PeriodicTable *table = NULL;
    if ((table = getTable(argv[1])) == NULL)
    {
        printf("Wrong input given from files!\n");
        return -1;
    }

    if (strcmp(argv[2], "-ext") == 0 && argc == 5)
    {
        if (vTableForOthers(argv[3]) == EXIT_FAILURE)
        {
            printf("Not valid parenthesis!\n");
            freeTable(table);
            return -1;
        }
        if (extTable(argv[3], argv[4], table) == EXIT_FAILURE)
        {
            printf("Wrong input given from files!\n");
            freeTable(table);
            return -1;
        }
    }
    else if (strcmp(argv[2], "-pn") == 0 && argc == 5)
    {
        if (vTableForOthers(argv[3]) == EXIT_FAILURE)
        {
            printf("Not valid parenthesis!\n");
            freeTable(table);
            return -1;
        }
        if (pnTable(argv[3], table, argv[4]) == EXIT_FAILURE)
        {
            printf("Wrong input given from files!\n");
            freeTable(table);
            return -1;
        }
    }
    else if (strcmp(argv[2], "-v") == 0 && argc == 4)
    {
        if (vTable(argv[3]) == EXIT_FAILURE)
        {
            printf("Wrong input given from files!\n");
            freeTable(table);
            return -1;
        }
    }
    else
    {
        printf("Wrong arguments! try:\n1. ./parseFormula inputFile.txt -ext testFile.txt outputFile.txt\n2. ./parseFormula inputFile.txt -pn testFile.txt outputFile.txt\n3. ./parseFormula inputFile.txt -v testFile.txt\n");
        freeTable(table);
        return -1;
    }

    freeTable(table);
    return 0;
}

int extTable(char *fileName, char *outFileName, PeriodicTable *table)
{

    FILE *fp = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return EXIT_FAILURE;
    }

    FILE *outFile = NULL;
    outFile = fopen(outFileName, "w");
    if (outFile == NULL)
    {
        printf("Could not open %s!\n", outFileName);
        return EXIT_FAILURE;
    }
    fclose(outFile);

    char buffer[1024];
    while (!feof(fp))
    {
        Stack *stack = NULL;
        if (initStack(&stack) == EXIT_FAILURE)
        {
            fclose(fp);
            return EXIT_FAILURE;
        }
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            freeStack(stack);
            break;
        }
        if (openMoleculeType(buffer, stack, table) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        if (printStack(stack, outFileName) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        freeStack(stack);
    }
    printf("Compute extended version of formulas in %s\n", fileName);
    printf("Writing formulas to %s\n", outFileName);
    fclose(fp);
    return EXIT_SUCCESS;
}

int pnTable(char *fileName, PeriodicTable *table, char *outFileName)
{
    FILE *fp = NULL;
    fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return EXIT_FAILURE;
    }

    FILE *outFile = NULL;
    outFile = fopen(outFileName, "w");
    if (outFile == NULL)
    {
        printf("Could not open %s!\n", outFileName);
        return EXIT_FAILURE;
    }
    fclose(outFile);

    char buffer[1024];
    while (!feof(fp))
    {
        Stack *stack = NULL;
        if (initStack(&stack) == EXIT_FAILURE)
        {
            fclose(fp);
            return EXIT_FAILURE;
        }
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            freeStack(stack);
            break;
        }
        if (openMoleculeType(buffer, stack, table) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        if (printMoleculeNumber(stack, table, outFileName, fileName) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        freeStack(stack);
    }
    printf("Compute total proton number of formulas in %s\n", fileName);
    printf("Writing formulas to %s\n", outFileName);
    fclose(fp);
    return EXIT_SUCCESS;
}

int vTable(char *fileName)
{
    char testFile[1024];
    strcpy(testFile, fileName);

    FILE *fp = NULL;
    fp = fopen(testFile, "r");
    if (fp == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return EXIT_FAILURE;
    }
    printf("Verify balanced parentheses in %s\n", testFile);

    char buffer[1024];
    int line = 1;
    int valid = 1;
    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            break;
        }
        if (checkValidity(buffer) == EXIT_FAILURE)
        {
            printf("Parentheses NOT balanced in line: %d\n", line);
            valid = 0;
        }
        line++;
    }
    if (valid == 1)
    {
        printf("Parentheses are balanced for all chemical formulas\n");
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int vTableForOthers(char *fileName)
{
    char testFile[1024];
    strcpy(testFile, fileName);

    FILE *fp = NULL;
    fp = fopen(testFile, "r");
    if (fp == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return EXIT_FAILURE;
    }

    char buffer[1024];
    int line = 1;
    int valid = 1;
    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            break;
        }
        if (checkValidity(buffer) == EXIT_FAILURE)
        {
            valid = 0;
        }
        line++;
    }
    fclose(fp);
    if (valid == 1)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int checkValidity(char *buffer)
{
    Stack *stack = NULL;
    if (initStack(&stack) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < strlen(buffer) - 1; i++)
    {
        if (buffer[i] == '(')
        {
            if (push(stack, "(") == EXIT_FAILURE)
            {
                freeStack(stack);
                return EXIT_FAILURE;
            }
        }
        if (buffer[i] == ')')
        {
            if (stack->size == 0)
            {
                freeStack(stack);
                return EXIT_FAILURE;
            }
            char retval[1024];
            if (pop(stack, retval) == EXIT_FAILURE)
            {
                if (stack != NULL)
                {
                    freeStack(stack);
                }
                free(buffer);
                return EXIT_FAILURE;
            }
            if (strcmp(retval, ")") == 0)
            {
                freeStack(stack);
                return EXIT_FAILURE;
            }
        }
    }
    if (stack->size > 0)
    {
        freeStack(stack);
        return EXIT_FAILURE;
    }
    freeStack(stack);
    return EXIT_SUCCESS;
}

int printMoleculeNumber(Stack *stack, PeriodicTable *table, char *outFileName, char *fileName)
{

    Stack *extraStack = NULL;
    initStack(&extraStack);

    FILE *outFile = NULL;
    outFile = fopen(outFileName, "a");
    if (outFile == NULL)
    {
        printf("Could not open %s!\n", outFileName);
        freeStack(extraStack);
        return EXIT_FAILURE;
    }

    char retval[1024];
    int moleculeNumber = 0;
    while (stack->size > 0)
    {
        if (pop(stack, retval) == EXIT_FAILURE)
        {
            fclose(outFile);
            freeStack(extraStack);
            return EXIT_FAILURE;
        }
        if (push(extraStack, retval) == EXIT_FAILURE)
        {
            fclose(outFile);
            freeStack(extraStack);
            return EXIT_FAILURE;
        }
    }

    while (extraStack->size > 0)
    {
        if (pop(extraStack, retval) == EXIT_FAILURE)
        {
            fclose(outFile);
            freeStack(extraStack);
            return EXIT_FAILURE;
        }
        moleculeNumber += getMoleculeNumber(retval, table);
    }
    fprintf(outFile, "%d\n", moleculeNumber);

    freeStack(extraStack);
    fclose(outFile);
    return EXIT_SUCCESS;
}

int openMoleculeType(char *buffer, Stack *stack, PeriodicTable *table)
{

    for (int i = 0; i < strlen(buffer); i++)
    {

        if (buffer[i] >= 'A' && buffer[i] <= 'Z')
        {
            char molecule[1024];
            int count = 0;
            molecule[count] = buffer[i];
            if (buffer[i + 1] >= 'a' && buffer[i + 1] <= 'z')
            {
                count++;
                i++;
                while (buffer[i] >= 'a' && buffer[i] <= 'z')
                {
                    molecule[count] = buffer[i];
                    i++;
                    count++;
                }
                i--;
                count--;
            }
            molecule[count + 1] = '\0';
            if (isMolecule(molecule, table) == EXIT_SUCCESS)
            {
                if (push(stack, molecule) == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
            else
            {
                return EXIT_FAILURE;
            }
        }

        else if (buffer[i] == '(')
        {
            if (push(stack, "(") == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
        }

        else if (buffer[i] == ')')
        {
            char retval[1024];
            char buffer2[1024];
            int times = 0;
            if (i + 1 < strlen(buffer) && ((buffer[i + 1]) - '0') >= 0 && ((buffer[i + 1]) - '0') <= 9)
            {
                i++;
                times = findNumber(buffer, &i);
                i--;
            }
            else
            {
                times = 1;
            }
            char hold[1024];
            if (pop(stack, retval) == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
            strcpy(buffer2, retval);
            if (pop(stack, retval) == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
            while (strcmp(retval, "(") != 0)
            {
                strcpy(hold, buffer2);
                strcat(retval, hold);
                strcpy(buffer2, retval);
                if (pop(stack, retval) == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
            for (int count = 0; count < times; count++)
            {
                if (push(stack, buffer2) == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
        }

        else if (((buffer[i]) - '0') >= 0 && ((buffer[i]) - '0') <= 9)
        {
            int times = 0;
            if (i + 1 < strlen(buffer) && ((buffer[i + 1]) - '0') >= 0 && ((buffer[i + 1]) - '0') <= 9)
            {
                times = findNumber(buffer, &i);
                i--;
            }
            else
            {
                times = buffer[i] - '0';
            }
            char retval[1024];
            if (pop(stack, retval) == EXIT_FAILURE)
            {
                return EXIT_FAILURE;
            }
            for (int count = 0; count < times; count++)
            {
                if (push(stack, retval) == EXIT_FAILURE)
                {
                    return EXIT_FAILURE;
                }
            }
        }
        else if (buffer[i] >= 'a' && buffer[i] <= 'z')
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int printStack(Stack *stack, char *outFileName)
{
    Stack *extraStack = NULL;
    if (initStack(&extraStack) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    FILE *outFile = NULL;
    outFile = fopen(outFileName, "a");
    if (outFile == NULL)
    {
        printf("Could not open %s!\n", outFileName);
        freeStack(extraStack);
        return EXIT_FAILURE;
    }

    char retval[1024];
    while (stack->size > 0)
    {
        if (pop(stack, retval) == EXIT_FAILURE)
        {
            freeStack(extraStack);
            fclose(outFile);
            return EXIT_FAILURE;
        }
        if (push(extraStack, retval) == EXIT_FAILURE)
        {
            freeStack(extraStack);
            fclose(outFile);
            return EXIT_FAILURE;
        }
    }

    while (extraStack->size > 0)
    {
        if (pop(extraStack, retval) == EXIT_FAILURE)
        {
            freeStack(extraStack);
            fclose(outFile);
            return EXIT_FAILURE;
        }
        fprintf(outFile, "%s", retval);
    }
    fprintf(outFile, "\n");

    freeStack(extraStack);
    fclose(outFile);
    return EXIT_SUCCESS;
}

int getMoleculeNumber(char *buffer, PeriodicTable *table)
{
    int number = 0;
    for (int i = 0; i < strlen(buffer); i++)
    {

        if (buffer[i] >= 'A' && buffer[i] <= 'Z')
        {
            char molecule[1024];
            int count = 0;
            molecule[count] = buffer[i];
            if (i + 1 < strlen(buffer) && buffer[i + 1] >= 'a' && buffer[i + 1] <= 'z')
            {
                count++;
                i++;
                while (buffer[i] >= 'a' && buffer[i] <= 'z')
                {
                    molecule[count] = buffer[i];
                    i++;
                    count++;
                }
                i--;
                count--;
            }
            molecule[count + 1] = '\0';
            number += findMoleculeNumber(molecule, table);
        }
    }
    return number;
}

int findMoleculeNumber(char *molecule, PeriodicTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(molecule, table->array[i].name) == 0)
        {
            return table->array[i].periodicNum;
        }
    }
    return 0;
}

int findNumber(char *buffer, int *index)
{
    int num = 0;

    while (isdigit(buffer[*index]))
    {
        num = num * 10 + (buffer[*index] - '0');
        (*index)++;
    }

    return num;
}
