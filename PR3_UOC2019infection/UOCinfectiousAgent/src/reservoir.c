#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "reservoir.h"
#include <stdio.h>

// Initialize the reservoir structure
tError reservoir_init(tReservoir* object, const char* name, const char* species) {

    // Verify pre conditions
    assert(object != NULL);
    assert(name != NULL);
    assert(species != NULL);

    // Allocate the memory for all the fields, using the length of the provided text plus 1 space for the "end of string" char '\0'. To allocate memory we use the malloc command.
    object->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    object->species = (char*)malloc((strlen(species) + 1) * sizeof(char));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (object->name == NULL || object->species == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data. As the fields are strings, we need to use the string copy function strcpy. 
    strcpy(object->name, name);
    strcpy(object->species, species);

    return OK;
}

// Remove the memory used by reservoir structure
void reservoir_free(tReservoir* object) {

    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if (object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
    if (object->species != NULL) {
        free(object->species);
        object->species = NULL;
    }
}

// Compare two reservoirs
bool reservoir_equals(tReservoir* reservoir1, tReservoir* reservoir2) {

    // Verify pre conditions
    assert(reservoir1 != NULL);
    assert(reservoir2 != NULL);

    // To see if two reservoirs are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared  as  " reservoir1->reservoirname == reservoir2->reservoirname ". We need to use a string comparison function    

    if (strcmp(reservoir1->name, reservoir2->name) != 0) {
        // names are different
        return false;
    }

    if (strcmp(reservoir1->species, reservoir2->species) != 0) {
        // species are different
        return false;
    }

    // All fields have the same value
    return true;
}

// Compare two Table of reservoirs. There are equals if they have the same number of reservoir, they have the same reservoirname. The order of reservoirs of two tables could be different
bool reservoirTable_equals(tReservoirTable* reservoirTable1, tReservoirTable* reservoirTable2){
    // Verify pre conditions
    assert(reservoirTable1 != NULL);
    assert(reservoirTable2 != NULL);

    int i;
    if (reservoirTable1->size != reservoirTable2->size){
        return false;
    }

    for (i = 0; i< reservoirTable1->size; i++)
    {
        // Uses "find" because the order of reservoirs could be different
        if (!reservoirTable_find(reservoirTable1, reservoirTable2->elements[i].name)) {
            // names are different
            return false;
        }
    }

    return true;
}

// Copy the data of a reservoir to another reservoir
tError reservoir_cpy(tReservoir* dst, tReservoir* src) {

    // Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);

    // Free the space used by destination object. An initialized object is assumed.
    reservoir_free(dst);

    // Initialize the element with the new data
    reservoir_init(dst, src->name, src->species);

    return OK;
}

// Initialize the table of reservoirs
void reservoirTable_init(tReservoirTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated). This is the main difference with respect to the reservoir of static memory, were data was allways initialized (tReservoir elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Remove the memory used by reservoirTable structure
void reservoirTable_free(tReservoirTable* object) {
    // Verify pre conditions
    assert(object != NULL);
    tReservoir * ptr;
    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if (object->elements != NULL) {
        for (int i = 0; i < object->size; i++) {
            ptr = &object->elements[i];
            reservoir_free(ptr);
        }
        free(object->elements);
        object->elements = NULL;

    }
    // As the table is now empty, assign the size to 0.
    object->size = 0;
}

// Add a new reservoir to the table
tError reservoirTable_add(tReservoirTable* table, tReservoir* reservoir) {
    // Verify pre conditions
    assert(table != NULL);
    assert(reservoir != NULL);

    // Check if reservoirs already is on the table
    if (reservoirTable_find(table, reservoir->name))
        return ERR_DUPLICATED;

    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc). Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory block, we have to use malloc. The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type). In this case the type is tReservoir.
        table->elements = (tReservoir*)malloc(table->size * sizeof(tReservoir));
    }
    else {
        // table with elements

        // Increase the number of elements of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command. The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type). In this case the type is tReservoir. We provide the previous block of memory.
        table->elements = (tReservoir*)realloc(table->elements, table->size * sizeof(tReservoir));
    }

    // Check that the memory has been allocated
    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array of tReservoir elements, we initialize the new element (which is the last one). The last element is " table->elements[table->size - 1] " (we start counting at 0)
    reservoir_init(&(table->elements[table->size - 1]), reservoir->name, reservoir->species);

    return OK;
}

// Remove a reservoir from the table
tError reservoirTable_remove(tReservoirTable * table, tReservoir * reservoir) {
    int i;
    bool found;

    // Verify pre conditions
    assert(table != NULL);
    assert(reservoir != NULL);

    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for (i = 0; i < table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if (found) {
            // Check the return code to detect memory allocation errors
            if (reservoir_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }

        }
        else if (strcmp(table->elements[i].name, reservoir->name) == 0) {
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
            reservoirTable_free(table);
        }
        else {
            reservoir_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously 
            // allocated block, we need to use the realloc command.
            table->elements = (tReservoir*)realloc(table->elements, table->size * sizeof(tReservoir));

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

// Get reservoir by reservoirname
tReservoir* reservoirTable_find(tReservoirTable* table, const char* name) {
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(name != NULL);

    // Search over the table and return once we found the element.
    for (i = 0; i<table->size; i++) {
        if (strcmp(table->elements[i].name, name) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of a the table
unsigned int reservoirTable_size(tReservoirTable* table) {
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

void reservoirTable_print(tReservoirTable * table) {
    // Verify pre conditions
    assert(table != NULL);

    for (int i = 0; i< table->size; i++)   {
        printf("%s %s \n ", table->elements[i].name, table->elements[i].species);

    }
    printf("\n ");
}