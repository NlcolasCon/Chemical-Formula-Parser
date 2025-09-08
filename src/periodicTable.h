/**
 * @file periodic_table.h
 * @brief Functions for handling a periodic table.
 *
 * This file contains the functions prototypes for loading, managing, and sorting the elements of a periodic table from a file.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#ifndef periodicTable_h
#define periodicTable_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @struct Molecule
 * @brief Structure to represent a molecule and its proton number.
 */
typedef struct molecule
{
    int periodicNum;
    char *name;
} Molecule;

/**
 * @struct PeriodicTable
 * @brief Structure representing a periodic table with a list of molecules.
 */
typedef struct periodicTable
{
    Molecule *array;
    int size;
} PeriodicTable;

/**
 * @brief Creates a periodic table.
 *
 * This function initializes a PeriodicTable with a size
 * and allocates memory for the array of its molecule.
 *
 * @param table Pointer of pointer of  PeriodicTable to be created.
 * @param size The size of the periodic table.
 * @return int Returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int createTable(PeriodicTable **table, int size);

/**
 * @brief Creates a new molecule and adds it to the periodic table.
 *
 * This function allocates memory and initializes a new Molecule and inserts it into the periodic table at a specified index.
 *
 * @param table Pointer of PeriodicTable.
 * @param buffer The name of the molecule to be added.
 * @param number The atomic number of the molecule to be added.
 * @param index The index in the array where the molecule will be stored.
 * @return int Returns EXIT_SUCCESS on success or EXIT_FAILURE on failure.
 */
int createMolecule(PeriodicTable *table, char *buffer, int number, int index);

/**
 * @brief Loads a periodic table from a file.
 *
 * This function reads a file containing the names and atomic numbers of the elements,
 * creates a PeriodicTable, and fills it with the elements read from the file, then sorts it using insertion sort.
 *
 * @param fileName The name of the file containing the periodic table data.
 * @return PeriodicTable* Pointer of PeriodicTable or NULL on failure.
 */
PeriodicTable *getTable(char *fileName);

/**
 * @brief Sorts the periodic table using insertion sort on atomic numbers.
 *
 * This function sorts the elements in the periodic table array in ascending
 * based on their atomic numbers.
 *
 * @param table Pointer of PeriodicTable.
 */
void insertionSort(PeriodicTable *table);

/**
 * @brief Frees the memory allocated for the periodic table.
 *
 * This function frees all memory of the periodic table,
 * including the names of the molecules and lastly the table.
 *
 * @param table Pointer of PeriodicTable to be freed.
 */
void freeTable(PeriodicTable *table);

/**
 * @brief Frees memory associated with a partially filled periodic table.
 *
 * Frees only the initialized molecules in the table, then frees the table array and structure.
 *
 * @param table The partially filled periodic table.
 * @param currentSize The current number of initialized molecules.
 */
void freeCurrTable(PeriodicTable *table, int currentSize);

/**
 * @brief Checks if a molecule exists in the periodic table.
 *
 * Searches for a molecule name in the table to determine if it exists.
 *
 * @param molecule The name of the molecule to search for.
 * @param table The periodic table to search.
 * @return int Returns EXIT_SUCCESS if the molecule is found, otherwise EXIT_FAILURE.
 */
int isMolecule(char *molecule, PeriodicTable *table);

#endif