#ifndef __COUNTRY_H__
#define __COUNTRY_H__

#include "error.h"
#include "city.h"

// Definition of a country
typedef struct {
    char * name;
    bool health_collapse;
    tCityList * cities;
} tCountry;

// Initialize the Country structure
tError country_init(tCountry * country, char * name);

// Copy the data of a Country to another Country
tError country_cpy(tCountry * dest, tCountry * src);

// Add new City to Country
tError country_addCity(tCountry * country, tCity * city);

// Compare two Countries
bool country_equal(tCountry * country1, tCountry * country2);

// Remove the memory used by tCountry structure
tError country_free(tCountry * country);

// Calculate the total population by going through all the items on the list.
long country_totalPopulation(tCountry * country);

// Calculate the total cases by going through all the items on the list.
int country_totalCases(tCountry * country);

// Calculate the total Critical Cases by going through all the items on the list.
int country_totalCriticalCases(tCountry * country);

// Calculate the total deaths by going through all the items on the list.
int country_totalDeaths(tCountry * country);

// Calculate the total Recovered by going through all the items on the list.
int country_totalRecovered(tCountry * country);


#endif // __COUNTRY_H__