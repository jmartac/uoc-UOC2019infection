#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "infectiousAgent.h"

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent* object, char* name, float r0, char* medium, tDate* date, char* city, tReservoirTable* reservoirList) {
    
    // PR1_EX2
	
    return ERR_NOT_IMPLEMENTED;
}

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent* object) {
    
    // PR1_EX2
}

// Get the reservoirs list of an infectious agent
tReservoirTable* infectiousAgent_getReservoirs(tInfectiousAgent* object) {
    
	// PR1_EX2
    
    return NULL;
}

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent* infectiousAgent1, tInfectiousAgent* infectiousAgent2) {
    
    // PR1_EX2
    
    return false;
}

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent* dest, tInfectiousAgent* src) {
    
    // PR1_EX2
	
    return ERR_NOT_IMPLEMENTED;
}

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable* table) {
	
    // PR1_EX3
}

// Remove the memory used by infectious agent table structure
void infectiousAgentTable_free(tInfectiousAgentTable* object) {
	
    // PR1_EX3 
}

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    
    // PR1_EX3
	
    return ERR_NOT_IMPLEMENTED;
}                      

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    
    // PR1_EX3
	
    return ERR_NOT_IMPLEMENTED;
}

// Get infectious agent by infectious agent name
tInfectiousAgent* infectiousAgentTable_find(tInfectiousAgentTable* table, const char* infectiousAgentName) {
    // PR1_EX3

    return NULL;
}

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable* table) {
	// PR1_EX3
	return ERR_NOT_IMPLEMENTED;
}