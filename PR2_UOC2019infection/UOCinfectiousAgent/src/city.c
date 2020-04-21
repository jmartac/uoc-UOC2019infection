#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "city.h"
#include <stdbool.h>
#include <limits.h>
#include "error.h"

// Initialize the City structure
tError city_init(tCity * city, char * name, tDate * date, long population, int cases, int critical_cases, int deaths, int recovered, int medical_beds) {
    // Verify pre conditions
    assert(city != NULL);
    assert(name != NULL);
    assert(date != NULL);
    assert(population > 0);
    assert(cases >= 0);
    assert(critical_cases >= 0);
    assert(deaths >= 0);
    assert(recovered >= 0);
    assert(medical_beds > 0);

    // Allocate the memory for the string fields, using the length of the provided text plus 1 space
    //for the "end of string" char '\0'. To allocate memory we use the malloc command.
    city->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Allocate the memory for the last_update field. We use the malloc command.
    city->last_update = (tDate*)malloc(sizeof(tDate));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (city->name == NULL || city->last_update == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Copy params to City fields
    strcpy(city->name, name);

    city->last_update->day = date->day;
    city->last_update->month = date->month;
    city->last_update->year = date->year;

    city->population = population;
    city->cases = cases;
    city->critical_cases = critical_cases;
    city->deaths = deaths;
    city->recovered = recovered;
    city->medical_beds = medical_beds;

    return OK;
}

// Free a city
void city_free(tCity * city){
    assert(city != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if (city->name != NULL) {
        free(city->name);
        city->name = NULL;
    }

    if (city->last_update != NULL) {
        free(city->last_update);
        city->last_update = NULL;
    }
}

bool city_equal(tCity * city1, tCity * city2){
    // Verify pre conditions
    assert(city1 != NULL);
    assert(city2 != NULL);

    // To see if two cities are equals, we need to compare only their names

    if (strcmp(city1->name, city2->name) != 0) {
        // cities are different
        return false;
    }

    return true;

}

// Create a list of cities
void cityList_create(tCityList * cities) {
    // PR2_EX1
    assert(cities != NULL);

    // initialize a cityList means setting it to an empty state with 0 elements. That is, First pointer should be NULL
    cities->first = NULL;
}

// Insert a city at index position
tError cityList_insert(tCityList * cities, tCity * city, int index) {
    // PR2_EX1
    assert(cities != NULL);
    assert(city != NULL);

    int i, size, limit;
    tCityNode *node;
    tCityNode *new_node;
    tError error;

    size = cityList_size(cities);
    if (index > size && index != 0 && index != INT_MAX)
        // index is greater than the citylist size and is not equal to 0 or INT_MAX
        return ERR_INVALID;
    if (cityList_find(cities, city->name))
        // the city is already present in the citylist
        return ERR_DUPLICATED;

    // allocate space for a new node which will contain the given city
    new_node = (tCityNode*)malloc(sizeof(tCityNode));
    if (new_node == NULL)
        return ERR_MEMORY_ERROR;

    // allocate space for the city inside the new node
    new_node->city = (tCity*)malloc(sizeof(tCity));
    if (new_node->city == NULL)
        return ERR_MEMORY_ERROR;

    error = city_init(new_node->city, city->name, city->last_update, city->population, city->cases, city->critical_cases, city->deaths, city->recovered,city->medical_beds);

    // an error occurred during the new_node->city initialization
    if (error != OK)
        return error;

    if ((index == 0 || index == INT_MAX) && size == 0) {
        // the new node will be the first one in the list if index equals 0 or INT_MAX with an empty list
        new_node->next = NULL;
        cities->first = new_node;
    } else {
        if (index == 0) {
            // place the new node at the top of the list moving the rest one position forward
            new_node->next = cities->first;
            cities->first = new_node;
        } else {
            // place the new node somewhere in the middle of the list or at the bottom

            // we need the previous node of the given index (index - 1) or the last one in the list (size - 1) to place the new one in its Next pointer
            limit = (index == INT_MAX) ? size - 1 : index - 1;

            i = 0;
            node = cities->first;
            while (i != limit) {
                i++;
                node = node->next;
            }

            // the new node will point to the current node at the given index position
            new_node->next = node->next;
            // and the previous node will point to the new node
            node->next = new_node;
        }
    }

    return OK;
}

// Delete the city at index position
bool cityList_delete(tCityList * cities, int index) {
    // PR2_EX2
    assert(cities != NULL);

    // empty cityList
    if (cityList_empty(cities))
        return false;

    int i;
    tCityNode *node;
    tCityNode *node_to_delete;

    node_to_delete = cities->first;
    if (index == 0) {
        if (cities->first->next == NULL) {
            // node_to_delete is the first one in a list of 1 elements
            cities->first = NULL;
        } else {
            // node_to_delete is the first one in a list of 2 or more elements
            cities->first = cities->first->next;
        }
    } else {
        // node_to_delete is somewhere in the middle of the list or at the bottom (size > index > 0)
        i = 0;
        node = cities->first;
        while (i != index - 1) {
            i++;

            if (node->next == NULL)
                // index is greater than number of elements
                return false;

            node = node->next;
        }

        node_to_delete = node->next;

        node->next = node_to_delete->next;
    }

    city_free(node_to_delete->city);
    node_to_delete->city = NULL;
    free(node_to_delete);

    return true;
}

// Get the city at index position
tCity * cityList_get(tCityList * cities, int index) {
    // PR2_EX2
    assert(cities != NULL);

    // empty cityList
    if (cityList_empty(cities))
        return NULL;

    int i;
    tCityNode *node;

    i = 0;
    node = cities->first;
    while (i != index) {
        i++;

        if (node->next == NULL)
            // index is greater than number of elements
            return NULL;
        node = node->next;
    }

    return node->city;
}

// Returns true if the list is empty
bool cityList_empty(tCityList * cities) {
    // PR2_EX1
    assert(cities != NULL);

    return cities->first == NULL;
}

// Find cities by name
tCity * cityList_find(tCityList * cities, char * cityName) {
    // PR2_EX2
    assert(cities != NULL);

    tCityNode *node;

    node = cities->first;
    while (node != NULL) {
        if (strcmp(node->city->name, cityName) == 0) {
            // both names match
            return node->city;
        }
        node = node->next;
    }

    // city not found
    return NULL;
}

// Update the city data
tCity * cityList_update(tCityList * cities, char * cityName, tDate * date, int cases, int critical_cases, int deaths, int recovered) {
    // PR2_EX2
    assert(cities != NULL);

    tCity *city;

    city = cityList_find(cities, cityName);

    if (city == NULL)
        // city not found
        return NULL;

    city->last_update->day = date->day;
    city->last_update->month = date->month;
    city->last_update->year = date->year;
    city->cases += cases;
    city->critical_cases += critical_cases;
    city->deaths += deaths;
    city->recovered += recovered;
    city->population -= deaths;

    return city;
}

// Delete all cities
void cityList_free(tCityList * cities) {
    // PR2_EX2
    assert(cities != NULL);

    // removes the city at the top of the list until its first node points to NULL (which means there are no more cities in the list)
    while (cities->first != NULL) {
        cityList_delete(cities, 0);
    }
}

// Gets the number of elements in the list
int cityList_size(tCityList * cities) {
    // PR2_EX1
    assert(cities != NULL);

    int sum;
    tCityNode *node;

    sum = 0;
    node = cities->first;
    while (node != NULL) {
        sum++;
        node = node->next;
    }

    return sum;
}

// Create a list of cities
void cityList_print(tCityList * cities) {
    // Verify pre conditions
    assert(cities != NULL);
    int num_elements = 0;
    tCityNode * ptr;
    ptr = cities->first;
    while (ptr != NULL) {
        printf("%d %s \n ", num_elements, ptr->city->name);
        printf("\tpopulation:%li medical_beds:%d updated:%d/%d/%d \n ",
            ptr->city->population,
            ptr->city->medical_beds,
            ptr->city->last_update->day,
            ptr->city->last_update->month,
            ptr->city->last_update->year);
        printf("\tcases:%d critical:%d deaths:%d recovered:%d \n ", ptr->city->cases, ptr->city->critical_cases, ptr->city->deaths, ptr->city->recovered);

        ptr = ptr->next;
        num_elements++;
    }
    printf("\n ");
}

long cityList_populationIterative(tCityNode * ptr){
    assert(ptr != NULL);
    long total_population = 0;
    while (ptr != NULL) {
        total_population += ptr->city->population;
        ptr = ptr->next;
    }
    return total_population;
}

long cityList_populationRecursive(tCityNode * ptr){
    if (ptr == NULL){
        return 0;
    }
    return cityList_populationRecursive(ptr->next) + ptr->city->population;

}

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_casesRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL)
        return 0;
    return cityList_casesRecursive(cityNode->next) + cityNode->city->cases;
}

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_criticalCasesRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL)
        return 0;
    return cityList_criticalCasesRecursive(cityNode->next) + cityNode->city->critical_cases;
}

// Calculate recursively the total deaths by going through all the items on the list.
int cityList_deathsRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL)
        return 0;
    return cityList_deathsRecursive(cityNode->next) + cityNode->city->deaths;
}

// Calculate recursively the total Recovered by going through all the items on the list.
int cityList_recoveredRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL)
        return 0;
    return cityList_recoveredRecursive(cityNode->next) + cityNode->city->recovered;
}
