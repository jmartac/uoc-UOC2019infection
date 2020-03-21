#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "infectiousAgent.h"

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent* object, char* name, float r0, char* medium, tDate* date, char* city, tReservoirTable* reservoirList) {

    // PR1_EX2
    //TODO check if it must be the same address or a new one
//    object->reservoirList = (tReservoirTable*) malloc(sizeof(tReservoirTable));
//    object->reservoirList->elements = (tReservoir*) malloc(reservoirList->size * sizeof(tReservoir));

    object->name = (char*) malloc(strlen(name)+1 * sizeof(char));
    object->medium = (char*) malloc(strlen(medium)+1 * sizeof(char));
    object->date = (tDate*) malloc(sizeof(tDate));
    object->city = (char*) malloc(strlen(city)+1 * sizeof(char));

    if( object->name == NULL ||
        object->medium == NULL ||
        object->date == NULL ||
        object->city == NULL)
    {
        return ERR_MEMORY_ERROR;
    }

    strcpy(object->name, name);
    object->r0 = r0;
    strcpy(object->medium, medium);
    object->date->day = date->day;
    object->date->month = date->month;
    object->date->year = date->year;
    strcpy(object->city, city);
    object->reservoirList = reservoirList;

    return OK;
}

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent* object) {
    
    // PR1_EX2
    //TODO must change if the infectiousAgent_init has change the way iDate is init

    assert(object != NULL);

    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
    object->r0 = 0;
    if(object->medium != NULL) {
        free(object->medium);
        object->medium = NULL;
    }
    if(object->date != NULL) {
        free(object->date);
        object->date = NULL;
    }
    if(object->city != NULL) {
        free(object->city);
        object->city = NULL;
    }
    if(object->reservoirList != NULL) {
        reservoirTable_free(object->reservoirList);
        object->reservoirList = NULL;
    }
}

// Get the reservoirs list of an infectious agent
tReservoirTable* infectiousAgent_getReservoirs(tInfectiousAgent* object) {
    
	// PR1_EX2

	return object->reservoirList;
}

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent* infectiousAgent1, tInfectiousAgent* infectiousAgent2) {
    
    // PR1_EX2
//todo remove this before last release
    if (infectiousAgent1 == NULL || infectiousAgent2 == NULL)
        return false;

    if(strcmp(infectiousAgent1->name, infectiousAgent2->name) != 0) {
        return false;
    }
    if(infectiousAgent1->r0 != infectiousAgent2->r0) {
        return false;
    }
    
    return true;
}

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent* dest, tInfectiousAgent* src) {
    
    // PR1_EX2

    infectiousAgent_free(dest);

    return infectiousAgent_init(dest, src->name, src->r0, src->medium, src->date, src->city, src->reservoirList);
	
//    return OK;
}

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable* table) {
	
    // PR1_EX3

    table->size = 0;
    table->elements = NULL;
}

// Remove the memory used by infectious agent table structure
void infectiousAgentTable_free(tInfectiousAgentTable* object) {
	
    // PR1_EX3

    if(object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    object->size = 0;
}

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    
    // PR1_EX3

    // Check if reservoirs already is on the table
    if (infectiousAgentTable_find(table, infectiousAgent->name))
        return ERR_DUPLICATED;

    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc). Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.
    if(table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size++;

        // Since the table is empty, and we do not have any previous memory block, we have to use malloc. The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type). In this case the type is tReservoir.
        table->elements = (tInfectiousAgent *) malloc(table->size * sizeof(tInfectiousAgent));
    } else {
        // table with elements

        // Increase the number of elements of the table
        table->size++;

        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command. The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type). In this case the type is tReservoir. We provide the previous block of memory.
        table->elements = (tInfectiousAgent*) realloc(table->elements, table->size * sizeof(tInfectiousAgent));
    }

    // Check that the memory has been allocated
    if(table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array of tReservoir elements, we initialize the new element (which is the last one). The last element is " table->elements[table->size - 1] " (we start counting at 0)
    return infectiousAgent_init(&(table->elements[table->size - 1]), infectiousAgent->name, infectiousAgent->r0, infectiousAgent->medium, infectiousAgent->date, infectiousAgent->city, infectiousAgent->reservoirList);
	
    return ERR_NOT_IMPLEMENTED;
}                      

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    
    // PR1_EX3

    int i;
    bool found;

    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for(i=0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happen for the first one). We use the ADDRESS
        // of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(infectiousAgent_cpy(&(table->elements[i-1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else if(infectiousAgent_equals(&table->elements[i], infectiousAgent)) {
            // The current element is the element we want to remove. Set found flag to true to start element movement.
            found = true;
        }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if(found) {
        // Modify the number of elements
        table->size--;

        // If we are removing the last element, we will assign the pointer to NULL, since we cannot allocate zero bytes
        if (table->size == 0) {
            table->elements = NULL;
        } else {
            // Modify the used memory. As we are modifying a previously allocated block, we need to use the realloc command.
            table->elements = (tInfectiousAgent*) realloc(table->elements, table->size * sizeof(tInfectiousAgent));

            // Check that the memory has been allocated
            if(table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }
        }
    } else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }

    return OK;


    return ERR_NOT_IMPLEMENTED;
}

// Get infectious agent by infectious agent name
tInfectiousAgent* infectiousAgentTable_find(tInfectiousAgentTable* table, const char* infectiousAgentName) {
    // PR1_EX3

    int i;

    // Search over the table and return once we found the element.
    for(i=0; i<table->size; i++) {
        if(strcmp(table->elements[i].name, infectiousAgentName) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable* table) {
	// PR1_EX3

	return table->size;

	return ERR_NOT_IMPLEMENTED;
}