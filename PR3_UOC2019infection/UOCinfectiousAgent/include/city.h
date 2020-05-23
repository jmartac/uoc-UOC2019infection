#ifndef __CITY_H__
#define __CITY_H__

#include "error.h"
#include "commons.h"
#include <stdbool.h>
#include <limits.h>
#include "city.h"

// Definition of a City
typedef struct {
    char * name;
    tDate * last_update;
    long population;
    int cases;
    int critical_cases;
    int deaths;
    int recovered;
    int medical_beds;
} tCity;


// Definition of the city list node
typedef struct tCityNode {
    tCity * city;
    struct tCityNode * next;
} tCityNode;

// Definition of the city list
typedef struct {
    tCityNode * first;
} tCityList;

// Initialize the City structure
tError city_init(tCity * city, char * name, tDate * date, long population, int cases, int critical_cases, int deaths, int recovered, int medical_beds);
   
// Compare two cities
bool city_equal(tCity * city1, tCity * city2);

// Create a list of cities
void cityList_create(tCityList * cities);

// Free a city
void city_free(tCity * city);

// Insert a city at index position
tError cityList_insert(tCityList * cities, tCity * city, int index);

// Delete the city at index position
bool cityList_delete(tCityList * cities, int index);

// Get the city at index position
tCity * cityList_get(tCityList * cities, int index);

// Returns true if the list is empty
bool cityList_empty(tCityList * cities);

// Find cities by name
tCity * cityList_find(tCityList * cities, char * cityName);

// Update the city data
tCity * cityList_update(tCityList * cities, char * cityName, tDate * date, int cases, int critical_cases, int deaths, int recovered);

// Delete all cities
void cityList_free(tCityList * cities);

// Gets the number of elements in the list
int cityList_size(tCityList * cities);

// print the city list in console
void cityList_print(tCityList * cities) ;

// Calculate the total population by going through all the items on the list.
long cityList_populationIterative(tCityNode * cityNode);

// Calculate recursively the total population by going through all the items on the list.
long cityList_populationRecursive(tCityNode * cityNode);

// Calculate recursively the total  cases by going through all the items on the list.
int cityList_casesRecursive(tCityNode * cityNode);

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_criticalCasesRecursive(tCityNode * cityNode);

// Calculate recursively the total deaths by going through all the items on the list.
int cityList_deathsRecursive(tCityNode * cityNode);
    
// Calculate recursively the total Recovered by going through all the items on the list.
int cityList_recoveredRecursive(tCityNode * cityNode);

#endif // __CITY_H__