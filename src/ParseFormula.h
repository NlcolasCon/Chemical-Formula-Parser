/**
 * @file ParseFormula.h
 *
 * @brief Chemical formula parser.
 *
 * This file contains function prototypes to parse chemical formulas from input files,
 * compute extended formulas, total proton numbers, and verify balanced parentheses.
 *
 * The program uses a stack to process the parsing of
 * chemical formulas. The chemical formulas are processed according to
 * user commands to produce output files with the results.
 *
 * @author Nicolas Constantinou
 * @date 23/10/2024
 */
#ifndef ParseFormula_h
#define ParseFormula_h

#include <ctype.h>

/**
 * @brief Computes the extended version of chemical formulas from a file.
 *
 * This function reads chemical formulas from an input file, expands them
 * by resolving groups and parentheses, and writes the expanded formula to an output file.
 *
 * @param fileName Name of the input file with chemical formulas.
 * @param outFileName Name of the output file to write expanded formulas.
 * @param table Pointer to the periodic table structure.
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int extTable(char *fileName, char *outFileName, PeriodicTable *table);

/**
 * @brief Computes total proton number for each formula in the file.
 *
 * This function calculates the total number of protons for each chemical formula
 * in an input file and writes the results to an output file.
 *
 * @param fileName Name of the input file with chemical formulas.
 * @param table Pointer to the periodic table structure.
 * @param outFileName Name of the output file to write proton numbers.
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int pnTable(char *fileName, PeriodicTable *table, char *outFileName);

/**
 * @brief Verifies balanced parentheses in chemical formulas.
 *
 * This function checks if the parentheses in each formula in a file are balanced.
 * It reports whether each line passes or fails the validation.
 *
 * @param fileName Name of the file with chemical formulas.
 * @return int EXIT_SUCCESS if balanced, EXIT_FAILURE if unbalanced.
 */
int vTable(char *fileName);

/**
 * @brief Verifies balanced parentheses in a file without outputting line information.
 *
 * This function validates if the parentheses in each formula are balanced.
 * Used for preprocessing to check formula validity before further parsing.
 *
 * @param fileName Name of the input file with formulas.
 * @return int EXIT_SUCCESS if all formulas are balanced, EXIT_FAILURE otherwise.
 */
int vTableForOthers(char *fileName);

/**
 * @brief Checks if parentheses in a formula are balanced.
 *
 * This function uses a stack to ensure all opening and closing parentheses
 * are correctly balanced within a single chemical formula string.
 *
 * @param buffer The chemical formula string.
 * @return int EXIT_SUCCESS if balanced, EXIT_FAILURE if unbalanced.
 */
int checkValidity(char *buffer);

/**
 * @brief Computes total proton number for a formula from the stack.
 *
 * Calculates the total proton count for a formula by using the atomic number of each element in the formula.
 *
 * @param stack Pointer to the stack with elements of the formula.
 * @param table Pointer to the periodic table.
 * @param outFileName Name of the output file for results.
 * @param fileName Name of the input file for error reporting.
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int printMoleculeNumber(Stack *stack, PeriodicTable *table, char *outFileName, char *fileName);

/**
 * @brief Parses a single molecule type from a formula string.
 *
 * This function scans a chemical formula string for molecule symbols and numbers,
 * correctly grouping and counting elements using a stack.
 *
 * @param buffer The formula string.
 * @param stack Pointer to the stack used for processing formula elements.
 * @param table Pointer to the periodic table structure.
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int openMoleculeType(char *buffer, Stack *stack, PeriodicTable *table);

/**
 * @brief Prints the contents of the stack to a file.
 *
 * Writes each element in the stack to an output file in reverse order,
 * reconstructing the chemical formula structure.
 *
 * @param stack Pointer to the stack with elements to print.
 * @param outFileName Name of the output file to write the formula.
 * @return int EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int printStack(Stack *stack, char *outFileName);

/**
 * @brief Retrieves atomic number for a molecule in a formula.
 *
 * This function sums atomic numbers from elements in the formula string
 * based on entries in the periodic table.
 *
 * @param buffer Formula string containing the molecule symbols.
 * @param table Pointer to the periodic table structure.
 * @return int The total atomic number sum for the formula.
 */
int getMoleculeNumber(char *buffer, PeriodicTable *table);

/**
 * @brief Finds the atomic number of a molecule in the periodic table.
 *
 * Looks up the atomic number of a molecule by name in the periodic table.
 *
 * @param molecule Name of the molecule.
 * @param table Pointer to the periodic table.
 * @return int The atomic number of the molecule or 0 if not found.
 */
int findMoleculeNumber(char *molecule, PeriodicTable *table);

/**
 * @brief Parses an integer from a formula string at a given position.
 *
 * This function extracts a multi-digit integer from a formula string
 * starting at a given index.
 *
 * @param buffer The formula string.
 * @param index Pointer to the current index in the string.
 * @return int The parsed integer value.
 */
int findNumber(char *buffer, int *index);

#endif