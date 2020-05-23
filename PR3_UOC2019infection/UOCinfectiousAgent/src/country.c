#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "country.h"
#include "city.h"

// Initialize the Country structure
tError country_init(tCountry * country, char * name) {
    // Verify pre conditions
    assert(country != NULL);
    assert(name != NULL);

    // Allocate the memory for the string fields, using the length of the provided text plus 1 space
    //for the "end of string" char '\0'. To allocate memory we use the malloc command.
    country->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Allocate the memory for the list of cities. We use the malloc command.
    country->cities = (tCityList*)malloc(sizeof(tCityList));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (country->name == NULL || country->cities == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Copy params to Country fields
    strcpy(country->name, name);
    country->health_collapse = false;

    // Create the list of cities
    cityList_create(country->cities);

    return OK;
}

// Copy the data of a Country to another Country
tError country_cpy(tCountry* dst, tCountry* src){
    tError err;
    tCityNode* ptr = NULL;
    // Verify pre conditions   
    assert(src != NULL);

    // Initialize the element with the new data
    err = country_init(dst, src->name);
    if (err != OK){
        free(dst);
        return err;
    }
    cityList_create(dst->cities);

    ptr = src->cities->first;
    while (ptr != NULL) {
        err = country_addCity(dst, ptr->city);
        if (err != OK){
            free(dst);
            return err;
        }
        ptr = ptr->next;
    }

    return OK;
}

// Add new City to Country
tError country_addCity(tCountry * country, tCity * city) {
    tError error;

    // Verify pre conditions
    assert(country != NULL);
    assert(city != NULL);

    error = cityList_insert(country->cities, city, cityList_size(country->cities));

    return error;
}

bool country_equal(tCountry * country1, tCountry * country2){
    // Verify pre conditions
    assert(country1 != NULL);
    assert(country2 != NULL);

    // To see if two countries are equals, we need to compare only their names   

    if (strcmp(country1->name, country2->name) != 0) {
        // countries are different
        return false;
    }


    // All fields have the same value
    return true;

}

// Remove the memory used by tCountry structure
tError country_free(tCountry * country){
    assert(country != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if (country->name != NULL) {
        free(country->name);
        country->name = NULL;
    }


    if (country->cities != NULL) {
        cityList_free(country->cities);
        free(country->cities);
        country->cities = NULL;
    }

    return OK;
}


long country_totalPopulation(tCountry * country){
    //return cityList_populationIterative(country->cities->first);
    return cityList_populationRecursive(country->cities->first);

}

// Calculate recursively the total  cases by going through all the items on the list.
int country_totalCases(tCountry * country){
    return cityList_casesRecursive(country->cities->first);
}

// Calculate recursively the total critical cases by going through all the items on the list.
int country_totalCriticalCases(tCountry * country){
    return cityList_criticalCasesRecursive(country->cities->first);
}

// Calculate recursively the total deaths by going through all the items on the list.
int country_totalDeaths(tCountry * country){
    return cityList_deathsRecursive(country->cities->first);
}

// Calculate recursively the total Recovered by going through all the items on the list.
int country_totalRecovered(tCountry * country){
    return cityList_recoveredRecursive(country->cities->first);
}