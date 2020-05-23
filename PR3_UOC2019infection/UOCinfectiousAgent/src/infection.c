#include "error.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "commons.h"
#include "infection.h"
#include <stdio.h>

// Initialize the Infection structure
tError infection_init(tInfection* object, tInfectiousAgent* infectiousAgent, tCountry* country, tDate* date){
    // Verify pre conditions
    assert(object != NULL);
    assert(infectiousAgent != NULL);
    assert(country != NULL);
    assert(date != NULL);

    // Allocate the memory for all the fields. To allocate memory we use the malloc command.
    object->country = (tCountry*)malloc(sizeof(tCountry));

    // Allocate the memory for the date field. We use the malloc command.
    object->date = (tDate*)malloc(sizeof(tDate));

    object->infectiousAgent = (tInfectiousAgent*)malloc(sizeof(tInfectiousAgent));


    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (object->country == NULL || object->date == NULL || object->infectiousAgent == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.
    country_cpy(object->country, country);

    infectiousAgent_cpy(object->infectiousAgent, infectiousAgent);

    // As the field date is a struct, we need to copy all fields.
    object->date->day = date->day;
    object->date->month = date->month;
    object->date->year = date->year;

    object->totalCases = 0;
    object->totalCriticalCases = 0;
    object->totalDeaths = 0;
    object->totalRecovered = 0;

    return OK;
}

// Remove the memory used by Infection structure
void infection_free(tInfection* object){
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if (object->country != NULL) {
        country_free(object->country);
        free(object->country);
        object->country = NULL;
    }
    if (object->date != NULL) {
        free(object->date);
        object->date = NULL;
    }

    if (object->infectiousAgent != NULL) {
        infectiousAgent_free(object->infectiousAgent);
        free(object->infectiousAgent);
        object->infectiousAgent = NULL;
    }

}

// Update cases and deaths of an Infection
void infection_update(tInfection* infection, int cases, int deaths, int criticalCases, int recovered){
    // Verify pre conditions
    assert(infection != NULL);
    assert(cases >= 0);
    assert(deaths >= 0);
    assert(criticalCases >= 0);
    assert(recovered >= 0);

    infection->totalCases += cases;
    infection->totalDeaths += deaths;
    infection->totalCriticalCases += criticalCases;
    infection->totalRecovered += recovered;
}

// Update cases and deaths of an Infection rescursively
void infection_update_recursive(tInfection* infection){
    assert(infection != NULL);

    int totalCases = country_totalCases(infection->country);
    infection->totalCases = totalCases;
    infection->totalDeaths = country_totalDeaths(infection->country);
    infection->totalCriticalCases = country_totalCriticalCases(infection->country);
    infection->totalRecovered = country_totalRecovered(infection->country);

}

// Compare two infections
bool infection_equals(tInfection* infection1, tInfection* infection2) {

    // Verify pre conditions
    assert(infection1 != NULL);
    assert(infection2 != NULL);

    // To see if two infections are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared  as  " infection1->country == infection2->country ". We need to use a string comparison function    

    if (strcmp(infection1->infectiousAgent->name, infection2->infectiousAgent->name) != 0) {
        // infectious Agents are different
        return false;
    }

    if (!country_equal(infection1->country, infection2->country)) {
        // countries are different
        return false;
    }

    // All fields have the same value
    return true;
}

// Initialize the Table of infections
void infectionTable_init(tInfectionTable* table){
    // Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated). This is the main difference with respect to the reservoir of static memory, were data was allways initialized (tInfection elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Remove the memory used by InfectionTable structure
void infectionTable_free(tInfectionTable* object){
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if (object->elements != NULL) {
        for (int i = 0; i < object->size; i++) {
            infection_free(&object->elements[i]);
        }
        free(object->elements);
        object->elements = NULL;
        // As the table is now empty, assign the size to 0.
        object->size = 0;
    }

}

// Add a new Infection to the table
tError infectionTable_add(tInfectionTable* table, tInfection* infection){
    // Verify pre conditions
    assert(table != NULL);
    assert(infection != NULL);

    // Check if reservoirs already is on the table
    if (infectionTable_find(table, infection->infectiousAgent->name, infection->country))
        return ERR_DUPLICATED;

    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc). Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory block, we have to use malloc. The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type). In this case the type is tInfection.
        table->elements = (tInfection*)malloc(table->size * sizeof(tInfection));
    }
    else {
        // table with elements

        // Increase the number of elements of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command. The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type). In this case the type is tInfection. We provide the previous block of memory.
        table->elements = (tInfection*)realloc(table->elements, table->size * sizeof(tInfection));
    }

    // Check that the memory has been allocated
    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Once we have the block of memory, which is an array of tInfection elements, we initialize the new element (which is the last one). The last element is " table->elements[table->size - 1] " (we start counting at 0)
    return infection_init(&(table->elements[table->size - 1]), infection->infectiousAgent, infection->country, infection->date);

}

// Get the size of the table
unsigned int infectionTable_size(tInfectionTable* table){
    // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Get Infection by Infection and country name
tInfection* infectionTable_find(tInfectionTable* table, const char* infectiousAgentName, tCountry* country){
    int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);
    assert(country != NULL);

    // Search over the table and return once we found the element.
    for (i = 0; i<table->size; i++) {
        if ((strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0)) {
            if (country_equal(table->elements[i].country, country)) {
                // We return the ADDRESS (&) of the element, which is a pointer to the element
                return &(table->elements[i]);
            }
        }
    }

    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Compare two Table of infections
bool infectionTable_equals(tInfectionTable* infectionTable1, tInfectionTable* infectionTable2){
    // Verify pre conditions
    assert(infectionTable1 != NULL);
    assert(infectionTable2 != NULL);

    int i;
    if (infectionTable1->size != infectionTable2->size){
        return false;
    }

    for (i = 0; i< infectionTable1->size; i++)
    {
        // Uses "find" because the order of reservoirs could be different
        if (!infectionTable_find(infectionTable1, infectionTable2->elements[i].infectiousAgent->name, infectionTable2->elements[i].country)) {
            // names are different
            return false;
        }
    }

    return true;
}

// Copy the data of a Infection to another Infection
tError infection_cpy(tInfection* dst, tInfection* src){
    // Verify pre conditions
    //assert(dst != NULL);
    assert(src != NULL);

    // Free the space used by destination object. 
    if (dst != NULL)
        infection_free(dst);

    // Initialize the element with the new data
    return infection_init(dst, src->infectiousAgent, src->country, src->date);

}

// Remove a Infection from the table
tError infectionTable_remove(tInfectionTable* table, tInfection* infection){
    int i;
    bool found;

    // Verify pre conditions
    assert(table != NULL);
    assert(infection != NULL);

    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for (i = 0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if (found) {
            // Check the return code to detect memory allocation errors
            if (infection_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        }
        else if (infection_equals(&table->elements[i], infection)){
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
            infectionTable_free(table);
        }
        else {
            infection_free(&table->elements[table->size - 1]);
            // Modify the used memory. As we are modifying a previously 
            // allocated block, we need to use the realloc command.
            table->elements = (tInfection*)realloc(table->elements, table->size * sizeof(tInfection));

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

// Given an infectious agent and a table of type tinfectionTable, 
// it performs a search of the country with the largest infected population, 
// offering us a pointer to it. In case of a tie, the country that is first on the list will be returned. 
// In case of not finding the infectious agent in the list, it will return NULL.

tInfection* infectionTable_getMaxInfection(tInfectionTable* table, const char* infectiousAgentName){
    int maxCases = 0;
    int maxDeaths = 0;
    int i;
    tInfection * infection = NULL;

    for (i = 0; i<table->size; i++) {
        if (strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0){
            if (table->elements[i].totalCases > maxCases){
                infection = &table->elements[i];
                maxCases = table->elements[i].totalCases;
            }
            if (table->elements[i].totalCases == maxCases && table->elements[i].totalDeaths > maxDeaths){
                infection = &table->elements[i];
                maxDeaths = table->elements[i].totalDeaths;

            }
        }
    }




    return infection;

}

// Given an infectious agent and a tinfectionTable type table, 
// calculate the mortality rate of an infectious agent worldwide, 
// adding all the deceased and dividing it by the number of affected.

float infectionTable_getMortalityRate(tInfectionTable* table, const char* infectiousAgentName){
    int cases = 0;
    int deaths = 0;
    float mortalityRate = 0;
    int i;

    for (i = 0; i<table->size; i++) {
        if (strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0){
            cases += table->elements[i].totalCases;
            deaths += table->elements[i].totalDeaths;

        }
    }

    mortalityRate = (float)deaths / (float)cases;

    return mortalityRate;
}