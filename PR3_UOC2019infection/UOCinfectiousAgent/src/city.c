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
void cityList_create(tCityList *cities)
{
	// Verify pre conditions
	assert(cities != NULL);

	cities->first = NULL;
}

// Insert a city at index position
tError cityList_insert(tCityList *cities, tCity *city, int index)
{
	tCityNode * prev;
	tCityNode * newCity;
    int i = 0;

	// Verify pre conditions
	assert(cities != NULL);
	assert(city != NULL);
	assert(index >= 0);

	// If city exists return ERR_DUPLICATED
	if (cityList_find(cities, city->name) != NULL){
		return ERR_DUPLICATED;
	}

	// Create new city
	newCity = (tCityNode*) malloc(sizeof(tCityNode));
	// Check that memory has been allocated
	if (newCity == NULL){
		return ERR_MEMORY_ERROR;
	}
	else{
		newCity->city = (tCity*) malloc(sizeof(tCity));
		// Check that memory has been allocated
		if (newCity->city == NULL)
		{
            free(newCity);
			return ERR_MEMORY_ERROR;
		}
		city_init(newCity->city, city->name, city->last_update, city->population, city->cases, 
				  city->critical_cases, city->deaths, city->recovered, city->medical_beds);

		if (index == 0)	{
			// no previous element
			newCity->next = cities->first;
			cities->first = newCity;
		}
		else{
            if (index > cityList_size(cities)) {
				city_free(newCity->city);
				free(newCity->city);
				free(newCity);			
                return ERR_INVALID;
			}
                
			// move prev to index -1 position
			prev = cities->first;
			while (i < index -1 && prev->next != NULL)	{
				prev = prev->next;
				i++;
			}

			if (prev != NULL){
				// standard case 
				newCity->next = prev->next;
				prev->next = newCity;
			}
			else{
				city_free(newCity->city);
				free(newCity->city);
				free(newCity);		
				return ERR_INVALID;
			}
		}
	}

	return OK;
}

// Delete the city at index position
bool cityList_delete(tCityList * cities, int index) {
    int num_elements;
    int i;
    tCityNode * ptr;
    tCityNode * ptr_del;

    // Verify pre conditions
    assert(cities != NULL);
    assert(index >= 0);

    // Out of range
    num_elements = cityList_size(cities);
    if (num_elements == 0 || index > num_elements) return false;

    // Find element at index-1 position
    i = 0;
    ptr = cities->first;
    while (i < index - 1) {
        ptr = ptr->next;
        i++;
    }
    // Now ptr points to element at index-1 position    

    // ptr_del points to element to be deleted
    if (index == 0){
        ptr_del = ptr;
        cities->first = ptr_del->next;
    }
    else {
        ptr_del = ptr->next;
    }


    // Element at index-1 position points to element at index+1 position
    if (ptr_del != NULL){
        ptr->next = ptr_del->next;
    }
    else {
        ptr->next = NULL;
    }

    // Delete element
    city_free(ptr_del->city);
    free(ptr_del->city);
    free(ptr_del);


    return true;
}

// Get the city at index position
tCity * cityList_get(tCityList * cities, int index) {
    int num_elements;
    int i;
    tCityNode * ptr;

    // Verify pre conditions
    assert(cities != NULL);
    assert(index >= 0);

    // Out of range
    num_elements = cityList_size(cities);
    if (num_elements == 0 || index > num_elements) return NULL;

    // Find element at index position
    i = 0;
    ptr = cities->first;
    while (i < index) {
        ptr = ptr->next;
        i++;
    }
    // Now ptr points to element at index position
    if (ptr != NULL)
        return ptr->city;
    else return NULL;
}

// Returns true if the list is empty
bool cityList_empty(tCityList * cities) {
    // Verify pre conditions
    assert(cities != NULL);

    if (cities->first == NULL) return true;
    else return false;
}

// Find cities by name
tCity * cityList_find(tCityList * cities, char * cityName) {
    int num_elements;
    tCityNode * ptr;
    bool findCity = false;

    // Verify pre conditions
    assert(cities != NULL);
    assert(cityName != NULL);

    // Out of range
    num_elements = cityList_size(cities);
    if (num_elements == 0) return NULL;

    // Find element with city-name = cityName
    ptr = cities->first;
    while (ptr != NULL) {
        if (strcmp(ptr->city->name, cityName) == 0) {
            // Now ptr points to element with city-name = cityName  
            findCity = true;
            break;
        }
        ptr = ptr->next;
    }

    if (findCity)
        return ptr->city;
    else return NULL;
}

// Update the city data
tCity * cityList_update(tCityList * cities, char * cityName, tDate * date, int cases, int critical_cases, int deaths, int recovered) {
    tCity * city;

    // Verify pre conditions
    assert(cities != NULL);
    assert(cityName != NULL);
    assert(date != NULL);
    assert(cases >= 0);
    assert(critical_cases >= 0);
    assert(deaths >= 0);
    assert(recovered >= 0);

    // If City don't exists return NULL
    city = cityList_find(cities, cityName);

    if (city == NULL)
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
    tCityNode * ptrCity;
    tCityNode * ptrDeleteCity;

    // Verify pre conditions
    assert(cities != NULL);

    ptrCity = cities->first;

    while (ptrCity != NULL) {
        ptrDeleteCity = ptrCity;
        ptrCity = ptrCity->next;

        city_free(ptrDeleteCity->city);
        free(ptrDeleteCity->city);
        free(ptrDeleteCity);

    }
    //free(ptr);
    cities->first = NULL;
}

// Gets the number of elements in the list
int cityList_size(tCityList * cities) {
    int num_elements = 0;
    tCityNode * ptr;

    ptr = cities->first;

    while (ptr != NULL) {
        num_elements++;
        ptr = ptr->next;
    }

    return num_elements;
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
    if (cityNode == NULL){
        return 0;
    }
    return cityList_casesRecursive(cityNode->next) + cityNode->city->cases;

}

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_criticalCasesRecursive(tCityNode * cityNode){
    if (cityNode == NULL){
        return 0;
    }
    return cityList_criticalCasesRecursive(cityNode->next) + cityNode->city->critical_cases;

}

// Calculate recursively the total deaths by going through all the items on the list.
int cityList_deathsRecursive(tCityNode * cityNode){
    if (cityNode == NULL){
        return 0;
    }
    return cityList_deathsRecursive(cityNode->next) + cityNode->city->deaths;
}


// Calculate recursively the total Recovered by going through all the items on the list.
int cityList_recoveredRecursive(tCityNode * cityNode){
    if (cityNode == NULL){
        return 0;
    }
    return cityList_recoveredRecursive(cityNode->next) + cityNode->city->recovered;

}