#ifndef __INFECTION__H__
#define __INFECTION__H__

#include <stdbool.h>
#include "error.h"
#include "infectiousAgent.h"
#include "country.h"

// Definition of an infection
typedef struct {
	tInfectiousAgent* infectiousAgent;
    tCountry* country;    
    tDate* date; 
    int totalCases;
    int totalCriticalCases;
    int totalDeaths;
    int totalRecovered;
} tInfection;

// Table of infections
typedef struct {
    unsigned int size;
    
    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS. That means that we are using the same amount of memory when the table is empty and when is full. We cannot add more elements than MAX_ELEMENTS.
    // tInfection elemets[MAX_ELEMENTS];
    
    // Using dynamic memory, the elements is a pointer to a region of memory. Initially, we have no memory (NULL), and we need to allocate memory when we want to add elements. We can add as many elements as we want, the only limit is the total amount of memory of our computer.
    tInfection* elements;
    
} tInfectionTable;

// Initialize the Infection structure
tError infection_init(tInfection* object, tInfectiousAgent* infectiousAgent, tCountry* country,  tDate* date);

// Remove the memory used by Infection structure
void infection_free(tInfection* object);

// Compare two infections
bool infection_equals(tInfection* infection1, tInfection* infection2);

// Update cases and deaths of an Infection
void infection_update(tInfection* infection, int cases, int deaths, int criticalCases, int recovered);

// Update cases and deaths of an Infection rescursively
void infection_update_recursive(tInfection* infection);

// Initialize the Table of infections
void infectionTable_init(tInfectionTable* table);

// Remove the memory used by InfectionTable structure
void infectionTable_free(tInfectionTable* object);

// Add a new Infection to the table
tError infectionTable_add(tInfectionTable* table, tInfection* Infection);

// Get the size of the table
unsigned int infectionTable_size(tInfectionTable* table);

// Get Infection by Infection and country name
tInfection* infectionTable_find(tInfectionTable* table, const char* infectiousAgentName, tCountry* country);

// Compare two Table of infections
bool infectionTable_equals(tInfectionTable* InfectionTable1, tInfectionTable* InfectionTable2);

// Copy the data of a Infection to another Infection
tError infection_cpy(tInfection* dest, tInfection* src);

// Remove a Infection from the table
tError infectionTable_remove(tInfectionTable* table, tInfection* Infection);

// Given an infectious agent and a table of type tInfectionTable, 
// it performs a search of the country with the largest infected population, 
// offering us a pointer to it. In case of a tie, the country that is first on the list will be returned. 
// In case of not finding the infectious agent in the list, it will return NULL.
tInfection* infectionTable_getMaxInfection (tInfectionTable* table, const char* infectiousAgentName);

// Given an infectious agent and a tInfectionTable type table, 
// calculate the mortality rate of an infectious agent worldwide, 
// adding all the deceased and dividing it by the number of affected.
float infectionTable_getMortalityRate (tInfectionTable* table, const char* infectiousAgentName);



#endif // __infection__H__