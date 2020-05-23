#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "infectiousAgent.h"

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent* object, char* name, float r0, char* medium, tDate* date, char* city, tReservoirTable* reservoirList) {
    tReservoir element;

    // Verify pre conditions
    assert(object != NULL);
    assert(name != NULL);
    assert(r0 > 0);
    assert(medium != NULL);
    assert(date != NULL);
    assert(city != NULL);
    assert(reservoirList != NULL);

    // Allocate the memory for all the string fields, using the length of the provided text plus 1 space for the "end of string" char '\0'.
    // To allocate memory we use the malloc command.
    object->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    object->medium = (char*)malloc((strlen(medium) + 1) * sizeof(char));
    object->city = (char *)malloc((strlen(city) + 1) * sizeof(char));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (object->name == NULL || object->medium == NULL || object->city == NULL) {
        // Some of the string fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Allocate the memory for the date field. We use the malloc command.
    object->date = (tDate*)malloc(sizeof(tDate));

    // Check that memory has been allocated.
    if (object->date == NULL) {
        // We found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Allocate the memory for the reservoir list field. We use the malloc command.
    // First we need to allocate the memory for the tReservoirTable and init the strucutre.
    // After this, we copy all the elements.
    object->reservoirList = (tReservoirTable*)malloc(sizeof(tReservoirTable));
    //object->reservoirList->elements = (tReservoir*) malloc(reservoirList->size * sizeof(tReservoir));
    reservoirTable_init(object->reservoirList);

    for (int i = 0; i < reservoirList->size; i++) {
        reservoir_init(&element, reservoirList->elements[i].name, reservoirList->elements[i].species);
        reservoirTable_add(object->reservoirList, &element);
        reservoir_free(&element);
    }

    // Check that memory has been allocated.
    if (object->reservoirList == NULL) { //|| object->reservoirList->elements == NULL) {
        // We found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.

    // As the fields are strings, we need to use the string copy function strcpy. 
    strcpy(object->name, name);
    strcpy(object->medium, medium);
    strcpy(object->city, city);

    // As the field date is a struct, we need to copy all fields.
    object->date->day = date->day;
    object->date->month = date->month;
    object->date->year = date->year;

    // Create all the elements of the reservoir list.
    /*
    object->reservoirList->size = reservoirList->size;
    for(int i; i < reservoirList->size; i++) {
    initReservoirError = reservoir_init(&object->reservoirList->elements[i],
    reservoirList->elements[i].name,
    reservoirList->elements[i].species);
    if(initReservoirError != OK) {
    return initReservoirError;
    }
    }
    */
    // Copy the basic reproductive rate R0 data
    object->r0 = r0;

    return OK;
}

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent* object) {

    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc to allocate the fields, we have to free them


    object->r0 = 0;

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
        free(object->reservoirList);
        object->reservoirList = NULL;
    }



}

// Get the reservoirs list of an infectious agent
tReservoirTable* infectiousAgent_getReservoirs(tInfectiousAgent* object) {
    // Verify pre conditions
    assert(object != NULL);

    return object->reservoirList;
}

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent* infectiousAgent1, tInfectiousAgent* infectiousAgent2) {

    // Verify pre conditions
    assert(infectiousAgent1 != NULL);
    assert(infectiousAgent2 != NULL);

    // To see if two infectious agents are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared as "infectiousAgent1->name == infectiousAgent2->name".
    // We need to use a string comparison function.

    if (strcmp(infectiousAgent1->name, infectiousAgent2->name) != 0) {
        // names are different
        return false;
    }

    if (infectiousAgent1->r0 != infectiousAgent2->r0) {
        // basic reproductive ratio r0 are different
        return false;
    }

    if (strcmp(infectiousAgent1->medium, infectiousAgent2->medium) != 0) {
        // transmission medium
        return false;
    }

    if (infectiousAgent1->date->day != infectiousAgent2->date->day ||
        infectiousAgent1->date->month != infectiousAgent2->date->month ||
        infectiousAgent1->date->year != infectiousAgent2->date->year) {
        // date of first infection
        return false;
    }

    if (strcmp(infectiousAgent1->city, infectiousAgent2->city) != 0) {
        // city of first infection
        return false;
    }

    if (!reservoirTable_equals(infectiousAgent1->reservoirList, infectiousAgent2->reservoirList)) {
        // infectious agent reservoir list
        return false;
    }

    return true;
}

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent* dest, tInfectiousAgent* src) {
    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);


    // Initialize the element with the new data
    infectiousAgent_init(dest, src->name, src->r0, src->medium, src->date, src->city, src->reservoirList);

    return OK;
}

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated).
    // This is the main difference with respect to the infectious agents of static memory, were data was allways initialized (tInfectiousAgent elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Remove the memory used by infectious agent table structure
void infectiousAgentTable_free(tInfectiousAgentTable* object) {
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
    // In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if (object->elements != NULL) {
        for (int i = 0; i < object->size; i++) {
            infectiousAgent_free(&object->elements[i]);
        }
        free(object->elements);
        object->elements = NULL;
        // As the table is now empty, assign the size to 0.
        object->size = 0;
    }


}

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgent != NULL);

    // Check if reservoirs already is on the table
    if (infectiousAgentTable_find(table, infectiousAgent->name))
        return ERR_DUPLICATED;

    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc).
    // Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory block, we have to use malloc.
        // The amount of memory we need is the number of elements (will be 1) times the size of one element,
        // which is computed by sizeof(type). In this case the type is tInfectiousAgent.
        table->elements = (tInfectiousAgent*)malloc(table->size * sizeof(tInfectiousAgent));
    }
    else {
        // table with elements

        // Increase the number of elements of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. We need to modify the size of this block,
        // using the realloc command. The amount of memory we need is the number of elements times the size of one element,
        // which is computed by sizeof(type). In this case the type is tInfectiousAgent. We provide the previous block of memory.
        table->elements = (tInfectiousAgent*)realloc(table->elements, table->size * sizeof(tInfectiousAgent));
    }

    // Check that the memory has been allocated
    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array of tInfectiousAgent elements, we initialize the new element (which is the last one).
    // The last element is " table->elements[table->size - 1] " (we start counting at 0)
    infectiousAgent_init(&(table->elements[table->size - 1]), infectiousAgent->name, infectiousAgent->r0,
        infectiousAgent->medium, infectiousAgent->date, infectiousAgent->city, infectiousAgent->reservoirList);

    return OK;
}

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    bool found;

    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgent != NULL);

    // To remove an element of a table, we will move all elements after this element one position, 
    // to fill the space of the removed element.
    found = false;
    for (int i = 0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element 
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) 
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if (found) {
            // Check the return code to detect memory allocation errors
            if (infectiousAgent_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }

        }
        else if (strcmp(table->elements[i].name, infectiousAgent->name) == 0) {
            // The current element is the element we want to remove. Set found flag to true to start element movement.
            found = true;
        }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if (found) {
        // If we are removing the last element, we will free 
        // the last/remaining element in table / assign pointer 
        // to NULL
        if (table->size <= 1) {
            infectiousAgentTable_free(table);
        }
        else {
            infectiousAgent_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously 
            // allocated block, we need to use the realloc command.
            table->elements = (tInfectiousAgent*)realloc(table->elements, table->size * sizeof(tInfectiousAgent));

            // Check that the memory has been allocated
            if (table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }
            else {
                // Succesfully allocated, set new table size
                table->size = table->size - 1;
            }
        }
    }
    else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }

    return OK;

}

// Get infectious agent by infectious agent name
tInfectiousAgent* infectiousAgentTable_find(tInfectiousAgentTable* table, const char* infectiousAgentName) {
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);

    // Search over the table and return once we found the element.
    for (i = 0; i<table->size; i++) {
        if (strcmp(table->elements[i].name, infectiousAgentName) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    return table->size;
}

void infectiousAgentTable_print(tInfectiousAgentTable * table) {
    // Verify pre conditions
    assert(table != NULL);

    for (int i = 0; i< table->size; i++)   {
        printf("%s %s \n ", table->elements[i].name, table->elements[i].city);

    }
    printf("\n ");
}