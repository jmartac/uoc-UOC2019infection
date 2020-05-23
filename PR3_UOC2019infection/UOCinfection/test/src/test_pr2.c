#include <assert.h>
#include <string.h>
#include "test_pr2.h"
#include "reservoir.h"
#include "infectiousAgent.h"
#include "infection.h"
#include "country.h"
#include "city.h"

// Run all tests for PR2
bool run_pr2(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");

    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);

    ok = run_pr2_ex1(section) && ok;
    ok = run_pr2_ex2(section) && ok;
    ok = run_pr2_ex3(section) && ok;

    return ok;
}

// Run tests for PR1 exercice 1
bool run_pr2_ex1(tTestSection* test_section) {

    bool passed = true, failed = false;
    tError err;
    tCityList cities;
    tCity cityNewYok, cityMilan, cityFoo;
    tDate date;

    // TEST 1: Create List
    failed = false;
    start_test(test_section, "PR2_EX1_1", "Create a list of cities");

    cityList_create(&cities);

    if (cityList_size(&cities) != 0) {
        failed = true;
    }

    if (cities.first != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_1", true);
    }

    // TEST 2: Empty List
    failed = false;
    start_test(test_section, "PR2_EX1_2", "Validate if a list is empty");

    if (!cityList_empty(&cities)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_2", true);
    }

    // TEST 3: Size of the List
    failed = false;
    start_test(test_section, "PR2_EX1_3", "Return the size of the list");

    if (cityList_size(&cities) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_3", true);
    }

    // TEST 4: Insert a City
    failed = false;
    start_test(test_section, "PR2_EX1_4", "Insert a element in the list");

    date.day = 3;
    date.month = 4;
    date.year = 2020;
    err = city_init(&cityNewYok, "New York", &date, 8350000ul, 0, 0, 0, 0, 50000);

    if (err == OK) {
        err = cityList_insert(&cities, &cityNewYok, 0);
        if (err == OK) {
            if (cityList_size(&cities) != 1) {
                failed = true;
            }
        }
        else {
            failed = true;
        }
    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_4", true);
    }

    // TEST 5: Insert multiple cities
    failed = false;
    start_test(test_section, "PR2_EX1_5", "Insert multiple cities in the list");

    date.day = 23;
    date.month = 1;
    date.year = 2020;
    err = city_init(&cityMilan, "Milan", &date, 1390000l, 0, 0, 0, 0, 1100);

    if (err == OK) {
        err = cityList_insert(&cities, &cityMilan, 1);
        if (err == OK) {
            if (cityList_size(&cities) != 2) {
                failed = true;
            }
        }
        else {
            failed = true;
        }
    }
    else {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX1_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_5", true);
    }

    // TEST 5: Insert multiple cities
    failed = false;
    start_test(test_section, "PR2_EX1_6", "Insert wrong city index");

    date.day = 1;
    date.month = 1;
    date.year = 2020;
    city_init(&cityFoo, "Foo", &date, 1, 0, 0, 0, 0, 1);

    err = cityList_insert(&cities, &cityFoo, 3);
    if (err == OK) {
        failed = true;
    }

    err = cityList_insert(&cities, &cityFoo, 4);
    if (err == OK) {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX1_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX1_6", true);
    }

    // Remove used memory
    cityList_free(&cities);


    city_free(&cityMilan);
    city_free(&cityNewYok);
    city_free(&cityFoo);


    return passed;
}

// Run tests for PR1 exercice 2
bool run_pr2_ex2(tTestSection* test_section) {

    bool passed = true, failed = false;
    tCityList  cities, emptyCities;
    tCity cityNewYok, cityMilan, cityLondon, cityFoo;
    tCity * city;
    tDate date;

    cityList_create(&cities);
    cityList_create(&emptyCities);

    date.day = 3;
    date.month = 4;
    date.year = 2020;
    city_init(&cityNewYok, "New York", &date, 8350000l, 1, 2, 3, 4, 50000);
    cityList_insert(&cities, &cityNewYok, 0);

    date.day = 23;
    date.month = 1;
    date.year = 2020;
    city_init(&cityMilan, "Milan", &date, 1390000l, 0, 0, 0, 0, 1100);
    cityList_insert(&cities, &cityMilan, 1);

    date.day = 20;
    date.month = 2;
    date.year = 2020;
    city_init(&cityLondon, "London", &date, 9700000ul, 0, 0, 0, 0, 60000);
    cityList_insert(&cities, &cityLondon, 1);

    // TEST 1: find a city
    failed = false;
    start_test(test_section, "PR2_EX2_1", "Find a city");

    city = cityList_find(&cities, "London");

    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityLondon)){
        failed = true;
    }

    city = cityList_find(&cities, "Milan");
    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityMilan)){
        failed = true;
    }

    city = cityList_find(&cities, "New York");
    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityNewYok)){
        failed = true;
    }

    city = cityList_find(&cities, "Bar");

    if (city != NULL) {
        failed = true;
    }

    city = cityList_find(&emptyCities, "London");

    if (city != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_1", true);
    }

    // TEST 2: get a city from an empty list
    failed = false;
    start_test(test_section, "PR2_EX2_2", "Get a city from an empty city list");

    city = cityList_get(&emptyCities, 0);

    if (city != NULL) {
        failed = true;
    }

    city = cityList_get(&cities, 3);

    if (city != NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX2_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_2", true);
    }

    // TEST 3: Get a city from a city list
    failed = false;
    start_test(test_section, "PR2_EX2_3", "Get a city from a city list");

    city = cityList_get(&cities, 0);

    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityNewYok)) {
        failed = true;
    }

    city = cityList_get(&cities, 1);

    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityLondon)) {
        failed = true;
    }

    city = cityList_get(&cities, 2);

    if (city == NULL) {
        failed = true;
    }
    else if (!city_equal(city, &cityMilan)) {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_3", true);
    }


    // TEST 4:Delete a city from a city list
    failed = false;
    start_test(test_section, "PR2_EX2_4", "Delete a city from a city list");

    date.day = 1;
    date.month = 1;
    date.year = 2020;
    city_init(&cityFoo, "Foo", &date, 1, 0, 0, 0, 0, 1);
    cityList_insert(&cities, &cityFoo, 3);
    // delete end list
    if (cityList_delete(&cities, 3)) {
        if (cityList_size(&cities) != 3)
            failed = true;
    }
    else {
        failed = true;
    }

    cityList_insert(&cities, &cityFoo, 0);
    // delete first list
    if (cityList_delete(&cities, 0)) {
        if (cityList_size(&cities) != 3)
            failed = true;
    }
    else {
        failed = true;
    }

    // delete middle list
    cityList_insert(&cities, &cityFoo, 2);
    if (cityList_delete(&cities, 2)) {
        if (cityList_size(&cities) != 3)
            failed = true;
    }
    else {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX2_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_4", true);
    }



    // TEST 5: delete from a list with only one city
    failed = false;
    start_test(test_section, "PR2_EX2_5", "delete a non exist city from a list ");
    if (cityList_delete(&emptyCities, 1)) {
        failed = true;
    }

    if (cityList_delete(&cities, 4)) {
        failed = true;
    }
    city = cityList_get(&cities, 1);

    if (failed) {
        end_test(test_section, "PR2_EX2_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_5", true);
    }

    // TEST 6: update a city from a list
    failed = false;
    start_test(test_section, "PR2_EX2_6", "update a city from a list");

    date.day = 6;
    date.month = 3;
    date.year = 2020;
    city = cityList_update(&cities, "London", &date, 8, 1, 0, 0);

    if (city != NULL) {
        if (city->cases != 8 || city->critical_cases != 1) {
            failed = true;
        }
    }
    else{
        failed = true;
    }

    date.day = 2;
    date.month = 4;
    date.year = 2020;
    city = cityList_update(&cities, "London", &date, 9283, 500, 1000, 100);

    if (city != NULL) {
        if (city->cases != 9291 || city->critical_cases != 501 || city->deaths != 1000 || city->recovered != 100) {
            failed = true;
        }
    }
    else{
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX2_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_6", true);
    }

    // TEST 7: update a non existing city from a list
    failed = false;
    start_test(test_section, "PR2_EX2_7", "update a non existing city from a list");


    city = cityList_update(&cities, "Bar", &date, 1, 1, 1, 1);

    if (city != NULL) {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX2_7", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX2_7", true);
    }

    // Remove used memory

    city_free(&cityMilan);
    city_free(&cityLondon);
    city_free(&cityNewYok);
    city_free(&cityFoo);
    cityList_free(&cities);
    cityList_free(&emptyCities);

    return passed;
}

// Run tests for PR1 exercice 3
bool run_pr2_ex3(tTestSection* test_section) {

    bool passed = true, failed = false;
    tError err;
    tCity cityBergamo, cityMilan, cityBrescia, cityComo;
    tCountry italy;
    tInfectiousAgent COVID_19;
    tInfection COVID_19_Italy = { 0 };
    long country_population = 0;
    int country_cases, country_critical_cases, country_recovered, country_deaths;
    tDate date, dateOutbreak;
    tReservoirTable reservoirList;
    tReservoir pangolin, bat;



    date.day = 23;
    date.month = 1;
    date.year = 2020;
    city_init(&cityMilan, "Milan", &date, 1390000l, 0, 0, 0, 0, 1100);

    date.day = 18;
    date.month = 1;
    date.year = 2020;
    city_init(&cityBergamo, "Bergamo", &date, 1114590l, 0, 0, 0, 0, 800);

    date.day = 23;
    date.month = 1;
    date.year = 2020;
    city_init(&cityBrescia, "Brescia", &date, 1109841l, 0, 0, 0, 0, 850);

    date.day = 1;
    date.month = 2;
    date.year = 2020;
    city_init(&cityComo, "Como", &date, 507500, 0, 0, 0, 0, 100);

    // TEST 0: calculate country population
    failed = false;
    start_test(test_section, "PR2_EX3_0", "calculate country population");

    err = country_init(&italy, "Italy");

    if (err != OK){
        failed = true;
    }

    err = country_addCity(&italy, &cityMilan);

    if (err != OK){
        failed = true;
    }
    country_addCity(&italy, &cityBrescia);
    country_addCity(&italy, &cityBergamo);
    country_addCity(&italy, &cityComo);

    if (err == OK){
        country_population = country_totalPopulation(&italy);

        if (country_population != 4121931l){
            failed = true;
        }
    }
    else {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR2_EX3_0", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_0", true);
    }

    // TEST 1: calculate country total cases
    failed = false;
    start_test(test_section, "PR2_EX3_1", "calculate country total cases");

    date.day = 5;
    date.month = 4;
    date.year = 2020;
    cityList_update(italy.cities, "Milan", &date, 20000, 50, 3000, 5000);
    cityList_update(italy.cities, "Bergamo", &date, 10000, 30, 2000, 2500);
    cityList_update(italy.cities, "Brescia", &date, 10000, 30, 2200, 2000);
    cityList_update(italy.cities, "Como", &date, 5000, 15, 500, 1000);

    country_cases = country_totalCases(&italy); // 45000 

    if (country_cases != 45000){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_1", true);
    }

    // TEST 2: calculate country total critical cases
    failed = false;
    start_test(test_section, "PR2_EX3_2", "calculate country total critical cases");

    country_critical_cases = country_totalCriticalCases(&italy);

    if (country_critical_cases != 125){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_2", true);
    }

    // TEST 3: calculate country total deaths
    failed = false;
    start_test(test_section, "PR2_EX3_3", "calculate country total deaths");

    country_deaths = country_totalDeaths(&italy);

    if (country_deaths != 7700){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_3", true);
    }

    // TEST 4: calculate country total cases
    failed = false;
    start_test(test_section, "PR2_EX3_4", "calculate country total cases");

    country_recovered = country_totalRecovered(&italy);

    if (country_recovered != 10500){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_4", true);
    }

    // TEST 5: update infection totals
    failed = false;
    start_test(test_section, "PR2_EX3_5", "update infection totals");

    reservoir_init(&pangolin, "pangolin ", "Manis pentadactyla");
    reservoir_init(&bat, "bat", "Rhinolophus FerrumEquinum");
    dateOutbreak.day = 1; dateOutbreak.month = 12; dateOutbreak.year = 2019;
    reservoirTable_init(&reservoirList);
    reservoirTable_add(&reservoirList, &pangolin);
    reservoirTable_add(&reservoirList, &bat);
    infectiousAgent_init(&COVID_19, "SARS-CoV-2", 1.3, "Air", &dateOutbreak, "Wuhan", &reservoirList);

    date.day = 31; date.month = 1; date.year = 2020;
    infection_init(&COVID_19_Italy, &COVID_19, &italy, &date);
    // infection_update(&COVID_19_Italy, country_cases, country_deaths, country_critical_cases, country_recovered);
    infection_update_recursive(&COVID_19_Italy);
    if (COVID_19_Italy.totalCases != 45000 || COVID_19_Italy.totalDeaths != 7700 || COVID_19_Italy.totalCriticalCases != 125 || COVID_19_Italy.totalRecovered != 10500){
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR2_EX3_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR2_EX3_5", true);
    }


    // Remove used memory
    city_free(&cityMilan);
    city_free(&cityBergamo);
    city_free(&cityBrescia);
    city_free(&cityComo);

    infection_free(&COVID_19_Italy);
    infectiousAgent_free(&COVID_19);
    reservoirTable_free(&reservoirList);
    reservoir_free(&pangolin);
    reservoir_free(&bat);

    country_free(&italy);

    return passed;
}
