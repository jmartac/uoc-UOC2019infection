#ifndef __INFECTIOUS_AGENT_H__
#define __INFECTIOUS_AGENT_H__

#include <stdbool.h>
#include "error.h"
#include "commons.h"
#include "reservoir.h"

// Definition of a infectious agent
typedef struct {
    char* name;     // Name of the infectious agent. It is a unique identifier
    float r0;       // Basic reproductive ratio R0
    char* medium;   // Transmission medium
    tDate* date;    // Date of first infection
    char* city;     // City of first infection
    tReservoirTable* reservoirList; // Infectious agent reservoir list
} tInfectiousAgent;

// Table of infectious agents
typedef struct {
    unsigned int size;
    
    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS. That means that we are using the same amount of memory when the table is empty and when is full. We cannot add more elements than MAX_ELEMENTS.
    // tReservoir elemets[MAX_ELEMENTS];
    
    // Using dynamic memory, the elements is a pointer to a region of memory. Initially, we have no memory (NULL), and we need to allocate memory when we want to add elements. We can add as many elements as we want, the only limit is the total amount of memory of our computer.
    tInfectiousAgent* elements;
    
} tInfectiousAgentTable;

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent* object, char* name, float r0, char* medium, tDate* date, char* city, tReservoirTable* reservoirList);

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent* object);

// Get the reservoirs list of an infectious agent
tReservoirTable* infectiousAgent_getReservoirs(tInfectiousAgent* object);

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent* infectiousAgent1, tInfectiousAgent* infectiousAgent2);

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent* dest, tInfectiousAgent* src);

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable* table);

// Remove the memory used by reservoirTable structure
void infectiousAgentTable_free(tInfectiousAgentTable* object);

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent);

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent);

// Get infectious agent by infectious agent name
tInfectiousAgent* infectiousAgentTable_find(tInfectiousAgentTable* table, const char* infectiousAgentName);

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable* table);

// print the table in the console
void infectiousAgentTable_print(tInfectiousAgentTable * table);


#endif // __INFECTIOUS_AGENT_H__