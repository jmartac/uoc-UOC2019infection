#include "error.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "commons.h"
#include "infection.h"
#include <stdio.h>

// Initialize the Infection structure
tError infection_init(tInfection* object, tInfectiousAgent* infectiousAgent, const char* country,  tDate* date, int cases, int deaths){
	// PR1_EX4

    return ERR_NOT_IMPLEMENTED;
}

// Remove the memory used by Infection structure
void infection_free(tInfection* object){
	// PR1_EX4
}

// Update cases and deaths of an Infection
void infection_update(tInfection* infection, int cases, int deaths){
	// PR1_EX4
}

// Compare two infections
bool infection_equals(tInfection* infection1, tInfection* infection2) {    
	// PR1_EX4

    return false;   
}

// Get the size of the table
unsigned int infectionTable_size(tInfectionTable* table){
    // PR1_EX4

    return ERR_NOT_IMPLEMENTED;
}

// Initialize the Table of infections
void infectionTable_init(tInfectionTable* table){
	// PR1_EX4
}

// Remove the memory used by InfectionTable structure
void infectionTable_free(tInfectionTable* object){
	// PR1_EX4
}

// Add a new Infection to the table
tError infectionTable_add(tInfectionTable* table, tInfection* infection){
	// PR1_EX4

    return ERR_NOT_IMPLEMENTED;
}

// Get Infection by Infection and country name
tInfection* infectionTable_find(tInfectionTable* table, const char* infectiousAgentName, const char* country){
	// PR1_EX4

    return NULL;
}

// Compare two Table of infections
bool infectionTable_equals(tInfectionTable* infectionTable1, tInfectionTable* infectionTable2){
	// PR1_EX4

    return false;    
}

// Copy the data of a Infection to another Infection
tError infection_cpy(tInfection* dst, tInfection* src){
	// PR1_EX4

    return ERR_NOT_IMPLEMENTED;
}

// Remove a Infection from the table
tError infectionTable_remove(tInfectionTable* table, tInfection* infection){
	// PR1_EX4

    return ERR_NOT_IMPLEMENTED;
}

// Given an infectious agent and a table of type tinfectionTable, 
// it performs a search of the country with the largest infected population, 
// offering us a pointer to it. In case of a tie, the country that is first on the list will be returned. 
// In case of not finding the infectious agent in the list, it will return NULL.
tInfection* infectionTable_getMaxInfection (tInfectionTable* table, const char* infectiousAgentName){
	// PR1_EX4

    return NULL;
}

// Given an infectious agent and a tinfectionTable type table, 
// calculate the mortality rate of an infectious agent worldwide, 
// adding all the deceased and dividing it by the number of affected.
float infectionTable_getMortalityRate (tInfectionTable* table, const char* infectiousAgentName){
	// PR1_EX4

    return 0.0;
}