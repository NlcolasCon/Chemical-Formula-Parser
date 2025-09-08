# Chemical Formula Parser (C)

A C program that parses, validates, and evaluates **molecular chemical formulas** using **dynamic stacks**.  
It supports validation, expansion into extended form, and computation of total proton number.

---

## Project Explanation

### What it does
- **Validation (`-v`)**: Checks balanced parentheses and subscripts in all formulas of the input file.  
- **Expansion (`-ext`)**: Expands chemical formulas into their extended atom list (e.g. `Ca(OH)2` → `Ca O H O H`).  
- **Proton count (`-pn`)**: Computes the total number of protons based on atomic numbers from a periodic table.

### Data structures
- **Dynamic stack** used to handle nested parentheses and multipliers.  
- **Array/linked list** to store the periodic table loaded from file.  
- **No recursion**: Only iterative stack-based parsing is allowed.  

---

## Repository Structure
Chemical-Formula-Parser/
┣ src/
┃ ┣ parseFormula.c
┃ ┣ parseFormula.h
┃ ┣ stack.c
┃ ┣ stack.h
┃ ┣ periodicTable.c
┃ ┣ periodicTable.h
┣ data/
┃ ┣ periodicTable.txt
┃ ┣ testFile.txt
┃ ┣ chemFormulas.txt
┣ makefile
┣ LICENSE
┣ README.md

---

## Features
- Load periodic table dynamically from file
- Validate nested parentheses & coefficients
- Expand formulas into explicit atom sequences
- Compute total proton count
- Modular, extensible design
- Memory safe (tested with `valgrind`)

---

## Technologies
- Language: C
- Paradigm: Structured programming with modular files
- Data structures: Dynamic stack, array/list
- Tools: GCC + Valgrind + Makefile

---

## Author
- Developed by Nicolas Constantinou
- 2024

---

## Usage

### Build and Run (different ways)
```bash
make
./parseFormula data/periodicTable.txt -v data/testFile.txt
./parseFormula data/periodicTable.txt -ext data/testFile.txt data/extFile.txt
./parseFormula data/periodicTable.txt -pn data/testFile.txt data/pnFile.txt



