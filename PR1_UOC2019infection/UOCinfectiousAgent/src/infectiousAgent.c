#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "infectiousAgent.h"

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent *object, char *name, float r0, char *medium, tDate *date, char *city,
                            tReservoirTable *reservoirList) {

    // PR1_EX2
    assert(object != NULL);
    assert(reservoirList != NULL);
    assert(date != NULL);


    int i;
    tReservoir *reservoir_aux;
    tError result;

    // memory allocation
    object->name = (char *) malloc(strlen(name) + 1 * sizeof(char));
    object->medium = (char *) malloc(strlen(medium) + 1 * sizeof(char));
    object->date = (tDate *) malloc(sizeof(tDate));
    object->city = (char *) malloc(strlen(city) + 1 * sizeof(char));
    object->reservoirList = (tReservoirTable *) malloc(sizeof(tReservoirTable));
    reservoirTable_init(object->reservoirList);

    // checking for memory errors
    if (object->name == NULL ||
        object->medium == NULL ||
        object->date == NULL ||
        object->city == NULL ||
        object->reservoirList == NULL)
    {
        return ERR_MEMORY_ERROR;
    }

    // deep copy of values
    strcpy(object->name, name);
    object->r0 = r0;
    strcpy(object->medium, medium);
    object->date->day = date->day;
    object->date->month = date->month;
    object->date->year = date->year;
    strcpy(object->city, city);

    // Initializes a copy of each reservoirList param, then adds it to object->objectList
    // If there are any errors during this process, the method will abort the operation and return the appropriate error code
    for (i = 0; i < reservoirList->size; i++) {
        reservoir_aux = (tReservoir *) malloc(sizeof(tReservoir));
        if (reservoir_aux == NULL)
            return ERR_MEMORY_ERROR;

        result = reservoir_init(reservoir_aux, reservoirList->elements[i].name, reservoirList->elements[i].species);
        if (result == OK) {
            result = reservoirTable_add(object->reservoirList, reservoir_aux);
            if (result != OK)
                return result;
        } else
            return result;
        free(reservoir_aux);
    }

    return OK;
}

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent *object) {

    // PR1_EX2
    assert(object != NULL);

    if (object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
    if (object->medium != NULL) {
        free(object->medium);
        object->medium = NULL;
    }
    if (object->date != NULL) {
        free(object->date);
        object->date = NULL;
    }
    if (object->city != NULL) {
        free(object->city);
        object->city = NULL;
    }
    if (object->reservoirList != NULL) {
        reservoirTable_free(object->reservoirList);
        object->reservoirList = NULL;
    }

    object->r0 = 0;
}

// Get the reservoirs list of an infectious agent
tReservoirTable *infectiousAgent_getReservoirs(tInfectiousAgent *object) {

    // PR1_EX2
    assert(object != NULL);

    return object->reservoirList;
}

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent *infectiousAgent1, tInfectiousAgent *infectiousAgent2) {

    // PR1_EX2
    assert(infectiousAgent1 != NULL);
    assert(infectiousAgent2 != NULL);

    if (strcmp(infectiousAgent1->name, infectiousAgent2->name) != 0) {
        return false;
    }
    if (infectiousAgent1->r0 != infectiousAgent2->r0) {
        return false;
    }

    return true;
}

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent *dest, tInfectiousAgent *src) {

    // PR1_EX2
    assert(dest != NULL);
    assert(src != NULL);

    infectiousAgent_free(dest);

    return infectiousAgent_init(dest, src->name, src->r0, src->medium, src->date, src->city, src->reservoirList);
}

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable *table) {

    // PR1_EX3
    assert(table != NULL);

    table->size = 0;
    table->elements = NULL;
}

// Remove the memory used by infectious agent table structure
void infectiousAgentTable_free(tInfectiousAgentTable *object) {

    // PR1_EX3
    assert(object != NULL);

    if (object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    object->size = 0;
}

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable *table, tInfectiousAgent *infectiousAgent) {

    // PR1_EX3
    assert(table != NULL);
    assert(infectiousAgent != NULL);

    if (infectiousAgentTable_find(table, infectiousAgent->name))
        return ERR_DUPLICATED;

    table->size++;
    if (table->size == 0) {
        // Empty table
        table->elements = (tInfectiousAgent *) malloc(table->size * sizeof(tInfectiousAgent));
    } else {
        // table with 1 or more elements
        table->elements = (tInfectiousAgent *) realloc(table->elements, table->size * sizeof(tInfectiousAgent));
    }

    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Adds a new initialized infectiousAgent with the given params in the last location of table->elements
    return infectiousAgent_init(&(table->elements[table->size - 1]), infectiousAgent->name, infectiousAgent->r0,
                                infectiousAgent->medium, infectiousAgent->date, infectiousAgent->city,
                                infectiousAgent->reservoirList);
}

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable *table, tInfectiousAgent *infectiousAgent) {

    // PR1_EX3
    assert(table != NULL);
    assert(infectiousAgent != NULL);

    int i;
    bool found;

    // It will relocate all items after the one to be removed to one less position
    found = false;
    for (i = 0; i < table->size; i++) {
        if (found) {
            // Copy element into its previous position
            if (infectiousAgent_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR)
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
        } else if (infectiousAgent_equals(&table->elements[i], infectiousAgent)) {
            // The current element is the element we want to remove. Set found flag to true to start element relocating.
            found = true;
        }
    }

    if (found) {
        // Modify size and used memory for elements
        table->size--;

        if (table->size == 0) {
            table->elements = NULL;
        } else {
            table->elements = (tInfectiousAgent *) realloc(table->elements, table->size * sizeof(tInfectiousAgent));
            if (table->elements == NULL)
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
        }
    } else {
        // The element was not found in the table
        return ERR_NOT_FOUND;
    }

    return OK;
}

// Get infectious agent by infectious agent name
tInfectiousAgent *infectiousAgentTable_find(tInfectiousAgentTable *table, const char *infectiousAgentName) {

    // PR1_EX3
    assert(table != NULL);

    int i;

    for (i = 0; i < table->size; i++) {
        if (strcmp(table->elements[i].name, infectiousAgentName) == 0) {
            return &(table->elements[i]);
        }
    }

    // The element has not been found
    return NULL;
}

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable *table) {

    // PR1_EX3
    assert(table != NULL);

    return table->size;
}