#ifndef __RESERVOIR__H__
#define __RESERVOIR__H__

#include <stdbool.h>
#include "error.h"

// Definition of a reservoir
typedef struct {
    char* name;    // Name of the reservoir. It is a unique identifier   
    char* species;
} tReservoir;

// Table of reservoirs
typedef struct {
    unsigned int size;
    
    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS. That means that we are using the same amount of memory when the table is empty and when is full. We cannot add more elements than MAX_ELEMENTS.
    // tReservoir elemets[MAX_ELEMENTS];
    
    // Using dynamic memory, the elements is a pointer to a region of memory. Initially, we have no memory (NULL), and we need to allocate memory when we want to add elements. We can add as many elements as we want, the only limit is the total amount of memory of our computer.
    tReservoir* elements;
    
} tReservoirTable;

// Initialize the reservoir structure
tError reservoir_init(tReservoir* object, const char* reservoirname, const char* name);

// Remove the memory used by reservoir structure
void reservoir_free(tReservoir* object);

// Compare two reservoir
bool reservoir_equals(tReservoir* reservoir1, tReservoir* reservoir2);

// Compare two Table of reservoirs
bool reservoirTable_equals(tReservoirTable* reservoirTable1, tReservoirTable* reservoirTable2);

// Copy the data of a reservoir to another reservoir
tError reservoir_cpy(tReservoir* dest, tReservoir* src);

// Initialize the Table of reservoirs
void reservoirTable_init(tReservoirTable* table);

// Remove the memory used by reservoirTable structure
void reservoirTable_free(tReservoirTable* object);

// Add a new reservoir to the table
tError reservoirTable_add(tReservoirTable* table, tReservoir* reservoir);

// Remove a reservoir from the table
tError reservoirTable_remove(tReservoirTable* table, tReservoir* reservoir);

// Get reservoir by reservoirname
tReservoir* reservoirTable_find(tReservoirTable* table, const char* reservoirname);

// Get the size of the table
unsigned int reservoirTable_size(tReservoirTable* table);

// print the table in the console
void reservoirTable_print(tReservoirTable * table);

#endif // __reservoir__H__