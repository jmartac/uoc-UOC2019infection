#include <assert.h>
#include <string.h>
#include "test_pr3.h"
#include "research.h"
#include "infectiousAgent.h"
#include "infection.h"
#include "country.h"
#include "city.h"

// Run all tests for PR3
bool run_pr3(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");

    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);

    ok = run_pr3_ex1(section) && ok;
    ok = run_pr3_ex2(section) && ok;
    ok = run_pr3_ex3(section) && ok;

    return ok;
}

// Run tests for PR3 exercice 1
bool run_pr3_ex1(tTestSection* test_section) {

    bool passed = true, failed = false;
    int i;
    tError err;
    tCityList  cities;
    tCity cityComo, cityAsuncion, cityLisbon;
    tCountry italy, paraguay, portugal;
    tResearch researchItaly, researchParaguay, researchPortugal;
    tDate date;

    failed = false;
    start_test(test_section, "PR3_EX1_1", "Initizalize Research");

    cityList_create(&cities);


    date.day = 1;
    date.month = 2;
    date.year = 2020;
    city_init(&cityComo, "Como", &date, 507500, 5800, 250, 80, 100, 100);

    date.day = 1;
    date.month = 3;
    date.year = 2020;
    city_init(&cityAsuncion, "Asuncion", &date, 7000000, 220, 6, 9, 60, 1000);

    date.day = 12;
    date.month = 12;
    date.year = 2019;
    city_init(&cityLisbon, "Lisbon", &date, 9000000, 220, 10, 9, 60, 1000);


    country_init(&italy, "Italy");
    country_init(&paraguay, "Paraguay");
    country_init(&portugal, "Lisbon");

    country_addCity(&italy, &cityComo);
    err = research_init(&researchItaly, &italy);
    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX1_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_1", true);
    }

    // TEST 2: research stats compare 1st is high
    failed = false;
    country_addCity(&paraguay, &cityAsuncion);
    country_addCity(&portugal, &cityLisbon);

    err = research_init(&researchParaguay, &paraguay);
    err = research_init(&researchPortugal, &portugal);

    start_test(test_section, "PR3_EX1_2", "Research Stats Compare High Infectivity");

    i = research_compare(researchItaly.stats, researchParaguay.stats);
    if (i != 1) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX1_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_2", true);
    }

    // TEST 3: research stats compare 2nd is high
    failed = false;

    start_test(test_section, "PR3_EX1_3", "Research Stats Compare High Severity");

    i = research_compare(researchParaguay.stats, researchPortugal.stats);
    if (i != -1) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX1_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_3", true);
    }


    // TEST 4: research stats compare 2nd is high
    failed = false;

    start_test(test_section, "PR3_EX1_4", "Research Stats Compare High Lethality");

    date.day = 1;
    date.month = 3;
    date.year = 2020;
    cityList_update(&cities, "Lisbon", &date, 220, 6, 9, 658);

    i = research_compare(researchParaguay.stats, researchPortugal.stats);
    if (i != -1) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX1_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_4", true);
    }

    // TEST 5: research stats compare 2nd is high
    failed = false;

    start_test(test_section, "PR3_EX1_5", "Research Stats Compare both equals");

    i = research_compare(researchItaly.stats, researchItaly.stats);
    if (i != 0) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX1_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX1_5", true);
    }

    // Remove used memory

    cityList_free(&cities);

    city_free(&cityComo);
    city_free(&cityAsuncion);
    city_free(&cityLisbon);

    country_free(&italy);
    country_free(&paraguay);
    country_free(&portugal);

    research_free(&researchItaly);
    research_free(&researchParaguay);
    research_free(&researchPortugal);

    return passed;
}


// Run tests for PR3 exercice 2
bool run_pr3_ex2(tTestSection* test_section) {

    bool passed = true, failed = false;
    tError err;
    tCityList  cities;
    tCity cityComo, cityAsuncion, cityBarcelona;
    tCountry italy, spain, paraguay;
    tResearch researchItaly, researchSpain, researchParaguay;
    tResearchList researchWorld;
    tResearchListNode * watch;
    tDate date;

    cityList_create(&cities);

    date.day = 1;
    date.month = 2;
    date.year = 2020;
    city_init(&cityComo, "Como", &date, 507500, 5800, 250, 80, 100, 100);

    date.day = 1;
    date.month = 3;
    date.year = 2020;
    city_init(&cityAsuncion, "Asuncion", &date, 7000000, 220, 6, 9, 60, 1000);

    date.day = 11;
    date.month = 12;
    date.year = 2019;
    city_init(&cityBarcelona, "Barcelona", &date, 507500, 38590, 9000, 450, 890, 800);

    country_init(&italy, "Italy");
    country_init(&spain, "Spain");
    country_init(&paraguay, "Paraguay");

    country_addCity(&italy, &cityComo);
    country_addCity(&spain, &cityBarcelona);
    country_addCity(&paraguay, &cityAsuncion);

    err = research_init(&researchItaly, &italy);
    err = research_init(&researchSpain, &spain);
    err = research_init(&researchParaguay, &paraguay);

    researchList_create(&researchWorld);

    // TEST 1: Insert a Country to ResearchList
    failed = false;
    start_test(test_section, "PR3_EX2_1", "Insert a Country to ResearchList Head");

    err = researchList_insert(&researchWorld, &researchItaly, 1);


    if (err == OK) {
        watch = researchList_get(&researchWorld, 1);
        if (watch != NULL) {
            if (strcmp(watch->e->country->name, "Italy") != 0) failed = true;
        }
    }
    else
        failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_1", true);
    }

    // TEST 2: check researchList Invalid Index
    failed = false;
    start_test(test_section, "PR3_EX2_2", "check researchList Invalid Index");

    err = researchList_insert(&researchWorld, &researchParaguay, 6);
    if (err != ERR_INVALID_INDEX) failed = true;
    if (failed) {
        end_test(test_section, "PR3_EX2_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_2", true);
    }


    // TEST 3: Insert a Country to ResearchList Middle
    failed = false;
    start_test(test_section, "PR3_EX2_3", "Insert a Country to ResearchList Middle");

    err = researchList_insert(&researchWorld, &researchParaguay, 2);
    if (err == OK) {
        err = researchList_insert(&researchWorld, &researchItaly, 3);
        if (err == OK) {
            err = researchList_insert(&researchWorld, &researchItaly, 2);
        }
    }

    if (err == OK) {
        watch = researchList_get(&researchWorld, 2);
        if (watch != NULL){
            if (strcmp(watch->e->country->name, "Italy") != 0) failed = true;
        }
        else
            failed = true;
    }
    else
        failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_3", true);
    }


    // TEST 4: Delete a Country from ResearchList
    failed = false;
    start_test(test_section, "PR3_EX2_4", "Delete a Country from ResearchList");
    err = researchList_delete(&researchWorld, 1);
    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_4", true);
    }

    // TEST 5: Delete a Country from ResearchList
    failed = false;
    start_test(test_section, "PR3_EX2_5", "Delete an invalid index from ResearchList");
    err = researchList_delete(&researchWorld, 4);
    if (err != ERR_INVALID_INDEX) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_5", true);
    }


    // TEST 6: ResearchList is empty?
    failed = false;
    start_test(test_section, "PR3_EX2_6", "Check researchList free");
    researchList_free(&researchWorld);

    if (!researchList_empty(&researchWorld)) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_6", true);
    }


    // TEST 7: Get a stat from ResearchList
    failed = false;
    start_test(test_section, "PR3_EX2_7", "Get a stat from ResearchList through index");
    err = researchList_insert(&researchWorld, &researchItaly, 1);
    if (err == OK){
        err = researchList_insert(&researchWorld, &researchSpain, 2);
        if (err == OK){
            err = researchList_insert(&researchWorld, &researchParaguay, 3);
        }
    }

    if (err == OK){
        watch = researchList_get(&researchWorld, 2);
        if (watch != NULL){
            if (strcmp(watch->e->country->name, "Spain") != 0)
                failed = true;
        }
        else
            failed = true;
    }
    else
        failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX2_7", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX2_7", true);
    }

    // Remove used memory

    cityList_free(&cities);

    city_free(&cityComo);
    city_free(&cityAsuncion);
    city_free(&cityBarcelona);

    country_free(&italy);
    country_free(&spain);
    country_free(&paraguay);

    research_free(&researchItaly);
    research_free(&researchSpain);
    research_free(&researchParaguay);

    researchList_free(&researchWorld);

    return passed;
}

// Run tests for PR3 exercice 3
bool run_pr3_ex3(tTestSection* test_section) {

    bool passed = true, failed = false;
    int i;
    tError err;
    tCityList  cities;
    tCity cityBergamo, cityMilan, cityBrescia, cityComo, cityAsuncion, cityMadrid, cityBarcelona, cityConcepcion, cityLisbon, cityPorto;
    tCountry italy, spain, paraguay, portugal, nonExist;
    tResearch researchItaly, researchSpain, researchParaguay, researchPortugal;
    tResearchList researchWorld;
    tDate date;

    cityList_create(&cities);

    date.day = 23;
    date.month = 1;
    date.year = 2020;
    city_init(&cityMilan, "Milan", &date, 1390000l, 15000, 2500, 5000, 300, 1100);

    date.day = 18;
    date.month = 1;
    date.year = 2020;
    city_init(&cityBergamo, "Bergamo", &date, 1114590l, 23000, 7000, 4500, 200, 800);

    date.day = 23;
    date.month = 1;
    date.year = 2020;
    city_init(&cityBrescia, "Brescia", &date, 1109841l, 3400, 200, 55, 8, 850);

    date.day = 1;
    date.month = 2;
    date.year = 2020;
    city_init(&cityComo, "Como", &date, 507500, 5800, 250, 80, 100, 100);

    date.day = 1;
    date.month = 3;
    date.year = 2020;
    city_init(&cityAsuncion, "Asuncion", &date, 7000000, 220, 6, 9, 60, 1000);

    date.day = 18;
    date.month = 2;
    date.year = 2020;
    city_init(&cityConcepcion, "Concepcion", &date, 1114590l, 10, 0, 5, 1, 810);

    date.day = 24;
    date.month = 3;
    date.year = 2020;
    city_init(&cityMadrid, "Madrid", &date, 1109841l, 24500, 5200, 480, 1500, 975);

    date.day = 11;
    date.month = 12;
    date.year = 2019;
    city_init(&cityBarcelona, "Barcelona", &date, 507500, 38590, 9000, 450, 890, 800);

    date.day = 11;
    date.month = 12;
    date.year = 2019;
    city_init(&cityLisbon, "Lisbon", &date, 87500, 3480, 1300, 440, 290, 800);

    date.day = 11;
    date.month = 12;
    date.year = 2019;
    city_init(&cityPorto, "Porto", &date, 127500, 590, 910, 50, 590, 800);


    country_init(&italy, "Italy");
    country_init(&spain, "Spain");
    country_init(&paraguay, "Paraguay");
    country_init(&portugal, "Portugal");

    country_init(&nonExist, "nonExist");
    country_addCity(&italy, &cityMilan);
    country_addCity(&italy, &cityBrescia);
    country_addCity(&italy, &cityBergamo);
    country_addCity(&italy, &cityComo);
    country_addCity(&spain, &cityMadrid);
    country_addCity(&spain, &cityBarcelona);
    country_addCity(&paraguay, &cityAsuncion);
    country_addCity(&paraguay, &cityConcepcion);
    country_addCity(&portugal, &cityLisbon);
    country_addCity(&portugal, &cityPorto);

    err = research_init(&researchItaly, &italy);
    err = research_init(&researchSpain, &spain);
    err = research_init(&researchParaguay, &paraguay);
    err = research_init(&researchPortugal, &portugal);

    researchList_create(&researchWorld);

    researchList_insert(&researchWorld, &researchItaly, 1);

    researchList_insert(&researchWorld, &researchSpain, 2);

    researchList_insert(&researchWorld, &researchParaguay, 3);



    // TEST 1: Get a country position in the research list Recursively
    failed = false;
    start_test(test_section, "PR3_EX3_1", "Get a country position Recursively");

    i = researchList_getPosByCountry(&researchWorld, &spain);
    if (i != 2) failed = true;
    if (failed) {
        end_test(test_section, "PR3_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_1", true);
    }

    // TEST 2: Get a country position in the research list Recursively
    failed = false;
    start_test(test_section, "PR3_EX3_2", "Get a non-existent country position ");

    i = researchList_getPosByCountry(&researchWorld, &nonExist);
    if (i != -1) failed = true;
    if (failed) {
        end_test(test_section, "PR3_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_2", true);
    }

    // TEST 3: Sort the ResearchList to put the tops first
    failed = false;
    start_test(test_section, "PR3_EX3_3", "Sort ResearchList");

    err = researchList_bubbleSort(&researchWorld);

    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX3_3", false);
        passed = false;
    }
    else {
        i = researchList_getPosByCountry(&researchWorld, &spain);
        if (i != 1){
            end_test(test_section, "PR3_EX3_3", false);
        }
        else end_test(test_section, "PR3_EX3_3", true);
    }

    // TEST 4: Sort the ResearchList to put the tops first
    failed = false;
    start_test(test_section, "PR3_EX3_4", "ReSort a sorted ResearchList");
    err = researchList_bubbleSort(&researchWorld);

    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX3_4", false);
        passed = false;
    }
    else {
        i = researchList_getPosByCountry(&researchWorld, &spain);
        if (i != 1){
            end_test(test_section, "PR3_EX3_4", false);
        }
        else end_test(test_section, "PR3_EX3_4", true);
    }



    // TEST 5: Sort the ResearchList to put the tops first
    failed = false;
    start_test(test_section, "PR3_EX3_5", "Add new country and sort");
    researchList_insert(&researchWorld, &researchPortugal, 4);

    err = researchList_bubbleSort(&researchWorld);

    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX3_5", false);
        passed = false;
    }
    else {
        i = researchList_getPosByCountry(&researchWorld, &portugal);
        if (i != 3){
            end_test(test_section, "PR3_EX3_5", false);
        }
        else end_test(test_section, "PR3_EX3_5", true);
    }

    research_free(&researchItaly);
    research_free(&researchSpain);
    research_free(&researchParaguay);


    researchList_free(&researchWorld);

    // TEST 6: Sort the ResearchList to put the tops first
    failed = false;
    start_test(test_section, "PR3_EX3_6", "Sort an empty ResearchList");
    err = researchList_bubbleSort(&researchWorld);

    if (err != OK) failed = true;

    if (failed) {
        end_test(test_section, "PR3_EX3_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR3_EX3_6", true);
    }

    // Remove used memory

    city_free(&cityBergamo);
    city_free(&cityMilan);
    city_free(&cityBrescia);
    city_free(&cityComo);
    city_free(&cityAsuncion);
    city_free(&cityMadrid);
    city_free(&cityBarcelona);
    city_free(&cityConcepcion);
    city_free(&cityLisbon);
    city_free(&cityPorto);

    cityList_free(&cities);

    country_free(&italy);
    country_free(&spain);
    country_free(&paraguay);
    country_free(&portugal);
    country_free(&nonExist);

    research_free(&researchItaly);
    research_free(&researchSpain);
    research_free(&researchParaguay);
    research_free(&researchPortugal);
    researchList_free(&researchWorld);

    return passed;
}
