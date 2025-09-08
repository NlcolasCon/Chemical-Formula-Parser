/**
 * @file periodic_table.c
 * @brief Functions for handling a periodic table.
 *
 * This file contains the functions for loading, managing, and sorting the elements of a periodic table from a file.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#include "periodicTable.h"

int createTable(PeriodicTable **table, int size)
{
    (*table) = (PeriodicTable *)malloc(sizeof(PeriodicTable));
    if ((*table) == NULL)
    {
        printf("Could not allocate the periodic table!\n");
        return EXIT_FAILURE;
    }
    (*table)->size = size;
    (*table)->array = (Molecule *)malloc(sizeof(Molecule) * size);
    if ((*table)->array == NULL)
    {
        printf("Could not allocate the periodic table array!\n");
        free(*table); // Free table if array allocation fails
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int createMolecule(PeriodicTable *table, char *buffer, int number, int index)
{

    if (table == NULL)
    {
        printf("Tabel is NULL!\n");
        return EXIT_FAILURE;
    }

    Molecule *newMolecule = NULL;
    newMolecule = (Molecule *)malloc(sizeof(Molecule));
    if (newMolecule == NULL)
    {
        printf("Could not allocate a new molecule!\n");
        free(newMolecule);
        return EXIT_FAILURE;
    }

    newMolecule->periodicNum = number;
    newMolecule->name = (char *)malloc(strlen(buffer) + 1);
    if (newMolecule->name == NULL)
    {
        printf("Could not alocate the new molecule's name!\n");
        return EXIT_FAILURE;
    }

    strcpy((newMolecule->name), buffer);
    table->array[index] = *newMolecule;
    free(newMolecule);
    return EXIT_SUCCESS;
}

void insertionSort(PeriodicTable *table)
{
    for (int i = 1; i < table->size; i++)
    {
        int value = table->array[i].periodicNum;
        char name[1024];
        strcpy(name, table->array[i].name);

        int j = i - 1;
        while (j >= 0 && table->array[j].periodicNum > value)
        {
            table->array[j + 1].periodicNum = table->array[j].periodicNum;
            strcpy(table->array[j + 1].name, table->array[j].name);
            j--;
        }

        table->array[j + 1].periodicNum = value;
        strcpy(table->array[j + 1].name, name);
    }
}

PeriodicTable *getTable(char *fileName)
{
    char input[1024];
    strcpy(input, fileName);

    FILE *fp;
    fp = fopen(input, "r");
    if (fp == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return NULL;
    }
    char buffer[1024];
    int size = 0;
    while (!feof(fp))
    {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
        {
            break;
        }
        size++;
    }
    fclose(fp);

    PeriodicTable *table;
    if (createTable(&table, size) == EXIT_FAILURE)
    {
        printf("Could not allocate the table!");
        return NULL;
    }
    FILE *fp2;
    fp2 = fopen(input, "r");
    if (fp2 == NULL)
    {
        printf("Could not open file!");
        return NULL;
    }
    int number = 0;
    int i = 0;
    while (!feof(fp2))
    {
        int f1 = fscanf(fp2, "%s", buffer);
        int f2 = fscanf(fp2, "%d", &number);
        if (f1 == EOF || f2 == EOF)
        {
            break;
        }
        if (f1 == 0 || f2 == 0)
        {
            fclose(fp2);
            freeCurrTable(table, i);
            return NULL;
        }
        createMolecule(table, buffer, number, i);
        i++;
    }
    fclose(fp2);

    insertionSort(table);

    return table;
}

void freeTable(PeriodicTable *table)
{
    for (int i = 0; i < table->size; i++)
    {
        free(table->array[i].name);
    }
    free(table->array);
    free(table);
}

void freeCurrTable(PeriodicTable *table, int currentSize)
{
    for (int i = 0; i < currentSize; i++)
    {
        free(table->array[i].name);
    }
    free(table->array);
    free(table);
}

int isMolecule(char *molecule, PeriodicTable *table)
{
    if (molecule == NULL || table == NULL)
    {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < table->size; i++)
    {
        if (strcmp(table->array[i].name, molecule) == 0)
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

#ifdef DEBUG
/**
 * @brief Main function for testing the periodic table functions.
 *
 * This function creates a periodic table by reading
 * data from a file, displaying the contents of the table, and freeing
 * allocated memory.
 *
 * @return int Returns 0 on success or -1 on failure.
 */
int main(void)
{
    PeriodicTable *table = NULL;
    if ((table = getTable("periodicTable.txt")) == NULL)
    {
        printf("Could not initialize table!\n");
        return -1;
    }

    for (int i = 0; i < table->size; i++)
    {
        printf("%s, %d\n", table->array[i].name, table->array[i].periodicNum);
    }
    printf("periodicTable created, allocated and sorted!\n");

    freeTable(table);
    printf("periodicTable free from memory!\n");
}
#endif