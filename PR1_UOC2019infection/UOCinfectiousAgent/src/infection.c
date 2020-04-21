#include "error.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "commons.h"
#include "infection.h"
#include <stdio.h>

// Initialize the Infection structure
tError
infection_init(tInfection *object, tInfectiousAgent *infectiousAgent, const char *country, tDate *date, int cases,
               int deaths) {

    // PR1_EX4
    assert(object != NULL);
    assert(infectiousAgent != NULL);
    assert(date != NULL);

    // memory allocation
    object->infectiousAgent = (tInfectiousAgent *) calloc(1, sizeof(tInfectiousAgent));
    object->country = (char *) malloc(strlen(country) + 1 * sizeof(char));
    object->date = (tDate *) malloc(sizeof(tDate));

    // checking for memory errors
    if (object->infectiousAgent == NULL ||
        object->country == NULL ||
        object->date == NULL) {
        return ERR_MEMORY_ERROR;
    }

    // deep copy of values
    strcpy(object->country, country);
    object->date->day = date->day;
    object->date->month = date->month;
    object->date->year = date->year;
    object->cases = cases;
    object->deaths = deaths;

    // abort if the copy of infectiousAgent fails (if not, returns OK)
    return infectiousAgent_cpy(object->infectiousAgent, infectiousAgent);
}

// Remove the memory used by Infection structure
void infection_free(tInfection *object) {

    // PR1_EX4

    assert(object != NULL);

    if (object->infectiousAgent != NULL) {
        infectiousAgent_free(object->infectiousAgent);
        object->infectiousAgent = NULL;
    }
    if (object->country != NULL) {
        free(object->country);
        object->country = NULL;
    }
    if (object->date != NULL) {
        free(object->date);
        object->date = NULL;
    }
    object->cases = 0;
    object->deaths = 0;
}

// Update cases and deaths of an Infection
void infection_update(tInfection *infection, int cases, int deaths) {

    // PR1_EX4
    assert(infection != NULL);

    infection->cases += cases;
    infection->deaths += deaths;
}

// Compare two infections
bool infection_equals(tInfection *infection1, tInfection *infection2) {

    // PR1_EX4
    assert(infection1 != NULL);
    assert(infection2 != NULL);

    if (strcmp(infection1->infectiousAgent->name, infection2->infectiousAgent->name) != 0) {
        return false;
    }
    if (strcmp(infection1->country, infection2->country) != 0) {
        return false;
    }

    return true;
}

// Get the size of the table
unsigned int infectionTable_size(tInfectionTable *table) {

    // PR1_EX4
    assert(table != NULL);

    return table->size;
}

// Initialize the Table of infections
void infectionTable_init(tInfectionTable *table) {

    // PR1_EX4
    assert(table != NULL);

    table->size = 0;
    table->elements = NULL;
}

// Remove the memory used by InfectionTable structure
void infectionTable_free(tInfectionTable *object) {

    // PR1_EX4
    assert(object != NULL);

    if (object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    object->size = 0;
}

// Add a new Infection to the table
tError infectionTable_add(tInfectionTable *table, tInfection *infection) {

    // PR1_EX4
    assert(table != NULL);
    assert(infection != NULL);

    if (infectionTable_find(table, infection->infectiousAgent->name, infection->country))
        return ERR_DUPLICATED;

    table->size++;
    if (table->size == 0) {
        // Empty table
        table->elements = (tInfection *) malloc(table->size * sizeof(tInfection));
    } else {
        // table with 1 or more elements
        table->elements = (tInfection *) realloc(table->elements, table->size * sizeof(tInfection));
    }

    if (table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Adds a new initialized infection with the given params in the last location of table->elements
    return infection_init(&(table->elements[table->size - 1]), infection->infectiousAgent, infection->country,
                          infection->date, infection->cases, infection->deaths);
}

// Get Infection by Infection and country name
tInfection *infectionTable_find(tInfectionTable *table, const char *infectiousAgentName, const char *country) {

    // PR1_EX4
    assert(table != NULL);

    int i;

    for (i = 0; i < table->size; i++) {
        if (strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0 &&
            strcmp(table->elements[i].country, country) == 0)
            return &(table->elements[i]);
    }

    // The element has not been found
    return NULL;
}

// Compare two Table of infections
bool infectionTable_equals(tInfectionTable *infectionTable1, tInfectionTable *infectionTable2) {

    // PR1_EX4
    assert(infectionTable1 != NULL);
    assert(infectionTable2 != NULL);

    unsigned int i, j;
    bool found;

    if (infectionTable1->size != infectionTable2->size)
        // having different sizes is considered as not equal
        return false;

    // Search over the table and return once we found the element.
    for (i = 0; i < infectionTable1->size; i++) {
        found = false;
        for (j = 0; j < infectionTable2->size; j++) {
            if (infection_equals(&infectionTable1->elements[i], &infectionTable2->elements[j])) {
                found = true;
                break;
            }
        }
        if (!found)
            // the second table doesn't have the [i] element of first table, so they're not equal
            return false;
    }

    return true;
}

// Copy the data of a Infection to another Infection
tError infection_cpy(tInfection *dst, tInfection *src) {

    // PR1_EX4
    assert(dst != NULL);
    assert(src != NULL);

    infection_free(dst);

    return infection_init(dst, src->infectiousAgent, src->country, src->date, src->cases, src->deaths);
}

// Remove a Infection from the table
tError infectionTable_remove(tInfectionTable *table, tInfection *infection) {

    // PR1_EX4
    assert(table != NULL);
    assert(infection != NULL);

    int i;
    bool found;

    // It will relocate all items after the one to be removed to one less position
    found = false;
    for (i = 0; i < table->size; i++) {
        if (found) {
            // Copy element into its previous position
            if (infection_cpy(&(table->elements[i - 1]), &(table->elements[i])) == ERR_MEMORY_ERROR)
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
        } else if (infection_equals(&table->elements[i], infection)) {
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
            table->elements = (tInfection *) realloc(table->elements, table->size * sizeof(tInfection));

            if (table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }
        }
    } else {
        // The element was not found in the table
        return ERR_NOT_FOUND;
    }

    return OK;
}

// Given an infectious agent and a table of type tinfectionTable, 
// it performs a search of the country with the largest infected population, 
// offering us a pointer to it. In case of a tie, the country that is first on the list will be returned. 
// In case of not finding the infectious agent in the list, it will return NULL.
tInfection *infectionTable_getMaxInfection(tInfectionTable *table, const char *infectiousAgentName) {

    // PR1_EX4
    assert(table != NULL);

    int i, max_cases_found;
    tInfection *max_infection;

    max_cases_found = -1;
    max_infection = NULL;
    for (i = 0; i < table->size; i++) {
        if (strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0) {
            // only cases of infections with the same name as infectiousAgentName are considered
            if ((table->elements[i].cases > max_cases_found) ||
                (table->elements[i].cases == max_cases_found && table->elements[i].deaths > max_infection->deaths)) {
                // max_infection will only change if the infection of the current iteration has more cases or if it has
                // the same number of cases but more deaths. In case of a tie, the earlier will remain
                max_cases_found = table->elements[i].cases;
                max_infection = &table->elements[i];
            }
        }
    }
    return max_infection;
}

// Given an infectious agent and a tinfectionTable type table, 
// calculate the mortality rate of an infectious agent worldwide, 
// adding all the deceased and dividing it by the number of affected.
float infectionTable_getMortalityRate(tInfectionTable *table, const char *infectiousAgentName) {

    // PR1_EX4
    assert(table != NULL);

    int i;
    float total_cases, total_deaths;

    total_cases = 0;
    total_deaths = 0;
    for (i = 0; i < table->size; i++) {
        if (strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0) {
            // only cases and deaths of infections with the same name as infectiousAgentName are counted
            total_cases += (float) table->elements[i].cases;
            total_deaths += (float) table->elements[i].deaths;
        }
    }

    return total_deaths / total_cases;
}