#include <assert.h>
#include <string.h>
#include "test_pr1.h"
#include "reservoir.h"
#include "infectiousAgent.h"
#include "infection.h"
#include "country.h"

// Run all tests for PR1
bool run_pr1(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;

    assert(test_suite != NULL);

    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");

    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);

    ok = run_pr1_ex1(section) && ok;
    ok = run_pr1_ex2(section) && ok;
    ok = run_pr1_ex3(section) && ok;
    ok = run_pr1_ex4(section) && ok;

    return ok;
}

// Run all tests for PR1
bool run_pr1_ex1(tTestSection* test_section) {

    bool passed = true, failed = false;
    tReservoir *reservoirAux, rat, bat, monkey, blackRat;
    tReservoirTable reservoirsTable;
    tError err;

    // TEST 1: Initialize the table of reservoirs
    failed = false;
    start_test(test_section, "PR1_EX1_1", "Initialize the table of reservoirs");
    reservoirTable_init(&reservoirsTable);

    if (reservoirTable_size(&reservoirsTable) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_1", true);
    }

    // TEST 2: Initialize a reservoir
    failed = false;
    start_test(test_section, "PR1_EX1_2", "Initialize a reservoir");

    reservoir_init(&rat, "rat", "Rattus rattus");
    reservoir_init(&blackRat, "rat", "Rattus rattus");

    if (!reservoir_equals(&rat, &blackRat)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_2", true);
    }

    // TEST 3: Add a new reservoir
    failed = false;
    start_test(test_section, "PR1_EX1_3", "Add a new reservoir");

    err = reservoirTable_add(&reservoirsTable, &rat);
    if (err != OK) {
        failed = true;
    }
    if (reservoirTable_size(&reservoirsTable) != 1) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "rat");
    if (reservoirAux == NULL) {
        failed = true;
    }
    else if (!reservoir_equals(reservoirAux, &rat)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_3", true);
    }

    // TEST 4: Add more reservoirs
    failed = false;
    start_test(test_section, "PR1_EX1_4", "Add more reservoirs");
    reservoir_init(&bat, "bat", "Rhinolophus FerrumEquinum");
    reservoir_init(&monkey, "monkey", "Macaca mulatta");

    err = reservoirTable_add(&reservoirsTable, &bat);
    if (err != OK) {
        failed = true;
    }
    if (reservoirTable_size(&reservoirsTable) != 2) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "bat");
    if (reservoirAux == NULL) {
        failed = true;
    }
    if (!reservoir_equals(reservoirAux, &bat)) {
        failed = true;
    }

    err = reservoirTable_add(&reservoirsTable, &monkey);
    if (err != OK) {
        failed = true;
    }
    if (reservoirTable_size(&reservoirsTable) != 3) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "monkey");
    if (reservoirAux == NULL) {
        failed = true;
    }
    else if (!reservoir_equals(reservoirAux, &monkey)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_4", true);
    }

    // TEST 5: Remove a reservoir
    failed = false;
    start_test(test_section, "PR1_EX1_5", "Remove a reservoir");

    reservoirAux = reservoirTable_find(&reservoirsTable, "bat");
    if (reservoirAux == NULL) {
        failed = true;
    }
    err = reservoirTable_remove(&reservoirsTable, &bat);
    if (err != OK) {
        failed = true;
    }
    if (reservoirTable_size(&reservoirsTable) != 2) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "bat");
    if (reservoirAux != NULL) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "rat");
    if (reservoirAux == NULL) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "monkey");
    if (reservoirAux == NULL) {
        failed = true;
    }

    err = reservoirTable_remove(&reservoirsTable, &monkey);
    if (err != OK) {
        failed = true;
    }
    reservoirAux = reservoirTable_find(&reservoirsTable, "rat");
    if (reservoirAux == NULL) {
        failed = true;
    }

    err = reservoirTable_remove(&reservoirsTable, &rat);
    if (err != OK) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX1_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_5", true);
    }

    // TEST 6: Remove a non existing reservoir
    failed = false;
    start_test(test_section, "PR1_EX1_6", "Remove a non existing reservoir");

    err = reservoirTable_remove(&reservoirsTable, &bat);
    if (err != ERR_NOT_FOUND) {
        failed = true;
    }

    if (reservoirTable_size(&reservoirsTable) != 0) {
        failed = true;
    }



    if (failed) {
        end_test(test_section, "PR1_EX1_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX1_6", true);
    }


    // Remove used memory
    reservoirTable_free(&reservoirsTable);

    reservoir_free(&rat);
    reservoir_free(&blackRat);
    reservoir_free(&bat);
    reservoir_free(&monkey);

    return passed;

}

// Run tests for PR1 exercise 2
bool run_pr1_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;
    tInfectiousAgent influenzaA1, influenzaB, infectiousAgent_copy;
    tDate date1, date2;
    tReservoirTable reservoirListA1, reservoirListB, *reservoirList_aux;
    tReservoir rat, bat, monkey;
    tError err;

    // PRE TEST: Create reservoirs elements
    reservoir_init(&rat, "rat", "Rattus rattus");
    reservoir_init(&bat, "bat", "Rhinolophus FerrumEquinum");
    reservoir_init(&monkey, "monkey", "Macaca mulatta");

    // TEST 1: Initialize a infectious agent
    failed = false;
    start_test(test_section, "PR1_EX2_1", "Initialize a infectious agent");

    date1.day = 17; date1.month = 11; date1.year = 2019;
    reservoirTable_init(&reservoirListA1);
    reservoirTable_add(&reservoirListA1, &rat);
    reservoirTable_add(&reservoirListA1, &bat);

    err = infectiousAgent_init(&influenzaA1, "Influenza H1N1", 0.2, "Air", &date1, "New York", &reservoirListA1);
    if (err != OK) {
        failed = true;
    }

    date2.day = 22; date2.month = 10; date2.year = 2019;
    reservoirTable_init(&reservoirListB);
    reservoirTable_add(&reservoirListB, &rat);
    reservoirTable_add(&reservoirListB, &monkey);
    err = infectiousAgent_init(&influenzaB, "Influenza Yamagata", 0.15, "Air", &date2, "London", &reservoirListB);
    if (err != OK) {
        failed = true;
    }

    if (infectiousAgent_equals(&influenzaA1, &influenzaB)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX2_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_1", true);
    }

    // TEST 2: Copy a infectious agent
    failed = false;
    start_test(test_section, "PR1_EX2_2", "Copy a infectious agent");

    infectiousAgent_cpy(&infectiousAgent_copy, &influenzaA1);
    if (!infectiousAgent_equals(&infectiousAgent_copy, &influenzaA1)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX2_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_2", true);
    }

    // TEST 3: Get the reservoirs list
    failed = false;
    start_test(test_section, "PR1_EX2_3", "Get the reservoirs list");

    reservoirList_aux = infectiousAgent_getReservoirs(&influenzaB);
    if (reservoirList_aux == NULL || !reservoirTable_equals(reservoirList_aux, &reservoirListB)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX2_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX2_3", true);
    }

    // Remove used memory

    infectiousAgent_free(&infectiousAgent_copy);
    infectiousAgent_free(&influenzaB);
    infectiousAgent_free(&influenzaA1);

    reservoirTable_free(&reservoirListA1);
    reservoirTable_free(&reservoirListB);

    reservoir_free(&rat);
    reservoir_free(&bat);
    reservoir_free(&monkey);

    return passed;
}

// Run tests for PR1 exercice 3
bool run_pr1_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;
    tInfectiousAgent *infectiousAgent_aux, influenzaA1, influenzaA2, influenzaB;
    tDate date1, date2, date3;
    tReservoirTable reservoirListA1, reservoirListA2, reservoirListB;
    tReservoir rat, bat, monkey;
    tInfectiousAgentTable infectiousAgentTable;
    tError err;

    // PRE TEST: Create reservoirs elements
    reservoir_init(&rat, "rat", "Rattus rattus");
    reservoir_init(&bat, "bat", "Rhinolophus FerrumEquinum");
    reservoir_init(&monkey, "monkey", "Macaca mulatta");

    date1.day = 17; date1.month = 11; date1.year = 2019;
    reservoirTable_init(&reservoirListA1);
    reservoirTable_add(&reservoirListA1, &rat);
    reservoirTable_add(&reservoirListA1, &bat);
    infectiousAgent_init(&influenzaA1, "Influenza H1N1", 0.2, "Air", &date1, "New York", &reservoirListA1);

    date2.day = 22; date2.month = 10; date2.year = 2019;
    reservoirTable_init(&reservoirListB);
    reservoirTable_add(&reservoirListB, &rat);
    reservoirTable_add(&reservoirListB, &monkey);
    infectiousAgent_init(&influenzaB, "Influenza Yamagata", 0.15, "Air", &date2, "London", &reservoirListB);

    date3.day = 3; date3.month = 1; date3.year = 2020;
    reservoirTable_init(&reservoirListA2);
    reservoirTable_add(&reservoirListA2, &rat);
    reservoirTable_add(&reservoirListA2, &bat);
    reservoirTable_add(&reservoirListA2, &monkey);
    infectiousAgent_init(&influenzaA2, "Influenza H3N2", 0.12, "Air", &date3, "Paris", &reservoirListA2);

    // TEST 1: Initialize the table of infectious agents
    failed = false;
    start_test(test_section, "PR1_EX3_1", "Initialize the table of infectious agents");
    infectiousAgentTable_init(&infectiousAgentTable);

    if (infectiousAgentTable_size(&infectiousAgentTable) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_1", true);
    }

    // TEST 2: Add a new infectious agent
    failed = false;
    start_test(test_section, "PR1_EX3_2", "Add a new infectious agent");

    err = infectiousAgentTable_add(&infectiousAgentTable, &influenzaA1); // Influenza H1N1

    if (err != OK) {
        failed = true;
    }

    if (infectiousAgentTable_size(&infectiousAgentTable) != 1) {
        failed = true;
    }

    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H1N1");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    else if (!infectiousAgent_equals(infectiousAgent_aux, &influenzaA1)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_2", true);
    }

    // TEST 3: Add more infectious agent
    failed = false;
    start_test(test_section, "PR1_EX3_3", "Add more infectious agent");

    err = infectiousAgentTable_add(&infectiousAgentTable, &influenzaA2); // Influenza H3N2
    if (err != OK) {
        failed = true;
    }
    if (infectiousAgentTable_size(&infectiousAgentTable) != 2) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H3N2");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    if (!infectiousAgent_equals(infectiousAgent_aux, &influenzaA2)) {
        failed = true;
    }

    err = infectiousAgentTable_add(&infectiousAgentTable, &influenzaB); // Influenza Yamagata
    if (err != OK) {
        failed = true;
    }
    if (infectiousAgentTable_size(&infectiousAgentTable) != 3) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza Yamagata");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    else if (!infectiousAgent_equals(infectiousAgent_aux, &influenzaB)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_3", true);
    }

    // TEST 4: Remove a infectious agent
    failed = false;
    start_test(test_section, "PR1_EX3_4", "Remove a infectious agent");

    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza Yamagata");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    err = infectiousAgentTable_remove(&infectiousAgentTable, &influenzaB); //influenzaB influenzaA2

    if (err != OK) {
        failed = true;
    }

    if (infectiousAgentTable_size(&infectiousAgentTable) != 2) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza Yamagata");
    if (infectiousAgent_aux != NULL) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H1N1");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H3N2");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_4", true);
    }

    // TEST 5: Remove a non existing infectious agent
    failed = false;
    start_test(test_section, "PR1_EX3_5", "Remove a non existing infectious agent");

    err = infectiousAgentTable_remove(&infectiousAgentTable, &influenzaB);
    if (err != ERR_NOT_FOUND) {
        failed = true;
    }
    if (infectiousAgentTable_size(&infectiousAgentTable) != 2) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza Yamagata");
    if (infectiousAgent_aux != NULL) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H1N1");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }
    infectiousAgent_aux = infectiousAgentTable_find(&infectiousAgentTable, "Influenza H3N2");
    if (infectiousAgent_aux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX3_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX3_5", true);
    }

    // Remove used memory
    infectiousAgentTable_free(&infectiousAgentTable);
    infectiousAgent_free(&influenzaA1);
    infectiousAgent_free(&influenzaA2);
    infectiousAgent_free(&influenzaB);
    reservoirTable_free(&reservoirListA1);
    reservoirTable_free(&reservoirListA2);
    reservoirTable_free(&reservoirListB);
    reservoir_free(&rat);
    reservoir_free(&bat);
    reservoir_free(&monkey);

    return passed;
}

// Run tests for PR1 exercice 4
bool run_pr1_ex4(tTestSection* test_section) {
    bool passed = true, failed = false;
    tInfectiousAgent COVID_19, ebola;
    tInfection COVID_19_China = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection COVID_19_SouthKorea = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection COVID_19_Italy = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection ebola_Sierra_Leone = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection ebola_Liberia = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection ebola_Guinea = { NULL, NULL, NULL, 0, 0, 0, 0 };
    tInfection COVID_19_copy = { NULL, NULL, NULL, 0, 0, 0, 0 };


    tInfection *infectionAux;
    tInfectionTable infectionsTable;
    tDate dateOutbreak, date;
    tReservoirTable reservoirList;
    tReservoir pangolin, bat;
    float mortalityRate;
    tError err;

    tCountry china, south_korea, italy, sierra_leone, liberia, guinea;

    // PRE TEST: 
    country_init(&china, "China");
    country_init(&south_korea, "South Korea");
    country_init(&italy, "Italy");
    country_init(&sierra_leone, "Sierra Leone");
    country_init(&liberia, "Liberia");
    country_init(&guinea, "Guinea");

    reservoir_init(&pangolin, "pangolin ", "Manis pentadactyla");
    reservoir_init(&bat, "bat", "Rhinolophus FerrumEquinum");


    dateOutbreak.day = 1; dateOutbreak.month = 12; dateOutbreak.year = 2019;
    reservoirTable_init(&reservoirList);
    reservoirTable_add(&reservoirList, &pangolin);
    reservoirTable_add(&reservoirList, &bat);
    infectiousAgent_init(&COVID_19, "SARS-CoV-2", 1.3, "Air", &dateOutbreak, "Wuhan", &reservoirList);



    // TEST 1: Initialize an infection
    failed = false;

    start_test(test_section, "PR1_EX4_1", "Initialize an infection");

    err = infection_init(&COVID_19_China, &COVID_19, &china, &dateOutbreak);

    if (err) {
        failed = true;
    }

    if (!infectiousAgent_equals(COVID_19_China.infectiousAgent, &COVID_19)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_1", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_1", true);
    }

    // TEST 2: Update an infection

    failed = false;

    start_test(test_section, "PR1_EX4_2", "Update an infection");

    infection_update(&COVID_19_China, 80711, 3042, 0, 0);
    if (COVID_19_China.totalCases != 80711 || COVID_19_China.totalDeaths != 3042) {
        failed = true;
    }

    infection_update(&COVID_19_China, 2000, 1000, 2002, 1001);
    if (COVID_19_China.totalCases != 82711 || COVID_19_China.totalDeaths != 4042 || COVID_19_China.totalCriticalCases != 2002 || COVID_19_China.totalRecovered != 1001) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_2", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_2", true);
    }


    // TEST 3: Initialize the table of infections
    failed = false;

    start_test(test_section, "PR1_EX4_3", "Initialize the table of infections");
    infectionTable_init(&infectionsTable);

    if (infectionTable_size(&infectionsTable) != 0) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_3", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_3", true);
    }

    // TEST 4: Add a new infection
    failed = false;
    start_test(test_section, "PR1_EX4_4", "Add a new infection");

    err = infectionTable_add(&infectionsTable, &COVID_19_China);

    if (err != OK) {
        failed = true;
    }
    if (infectionTable_size(&infectionsTable) != 1) {
        failed = true;
    }


    if (failed) {
        end_test(test_section, "PR1_EX4_4", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_4", true);
    }



    // TEST 5: Add more infections
    failed = false;
    start_test(test_section, "PR1_EX4_5", "Add more infections");

    date.day = 20; date.month = 1; date.year = 2020;
    err = infection_init(&COVID_19_SouthKorea, &COVID_19, &south_korea, &date);
    if (err) {
        failed = true;
    }
    date.day = 31; date.month = 1; date.year = 2020;
    err = infection_init(&COVID_19_Italy, &COVID_19, &italy, &date);
    if (err) {
        failed = true;
    }

    err = infectionTable_add(&infectionsTable, &COVID_19_SouthKorea);
    if (err != OK) {
        failed = true;
    }
    if (infectionTable_size(&infectionsTable) != 2) {
        failed = true;
    }
    infectionAux = infectionTable_find(&infectionsTable, "SARS-CoV-2", &south_korea);
    if (infectionAux == NULL) {
        failed = true;
    }


    err = infectionTable_add(&infectionsTable, &COVID_19_Italy);
    if (err != OK) {
        failed = true;
    }
    if (infectionTable_size(&infectionsTable) != 3) {
        failed = true;
    }
    infectionAux = infectionTable_find(&infectionsTable, "SARS-CoV-2", &italy);
    if (infectionAux == NULL) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_5", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_5", true);
    }

    // TEST 6: Copy an infection
    failed = false;
    start_test(test_section, "PR1_EX4_6", "Copy an infection");


    err = infection_cpy(&COVID_19_copy, &COVID_19_Italy);
    if (err != OK) {
        failed = true;
    }

    if (!infection_equals(&COVID_19_Italy, &COVID_19_copy)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_6", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_6", true);
    }


    // TEST 7: Add duplicated infection
    failed = false;
    start_test(test_section, "PR1_EX4_7", "Add duplicated infection");

    err = infectionTable_add(&infectionsTable, &COVID_19_copy);
    if (err != ERR_DUPLICATED) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_7", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_7", true);
    }

    // TEST 8: Remove infection
    failed = false;
    start_test(test_section, "PR1_EX4_8", "Remove infection");

    err = infectionTable_remove(&infectionsTable, &COVID_19_Italy);
    if (err != OK) {
        failed = true;
    }

    err = infectionTable_remove(&infectionsTable, &COVID_19_Italy);
    if (err != ERR_NOT_FOUND) {
        failed = true;
    }

    infectionAux = infectionTable_find(&infectionsTable, "SARS-CoV-2", &italy);
    if (infectionAux != NULL) {
        failed = true;
    }
    infectionTable_add(&infectionsTable, &COVID_19_Italy);
    if (err == ERR_DUPLICATED) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_8", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_8", true);
    }

    // TEST 9: getMaxInfection

    dateOutbreak.day = 1; dateOutbreak.month = 12; dateOutbreak.year = 2013;
    infectiousAgent_init(&ebola, "Ebola", 25, "Fluids", &dateOutbreak, "Meliandou", &reservoirList);
    infection_init(&ebola_Sierra_Leone, &ebola, &sierra_leone, &date);
    infection_init(&ebola_Liberia, &ebola, &liberia, &date);
    infection_init(&ebola_Guinea, &ebola, &guinea, &date);

    infectionTable_add(&infectionsTable, &ebola_Sierra_Leone);
    infection_update(infectionTable_find(&infectionsTable, ebola.name, &sierra_leone), 10000, 3956, 0, 6044);
    infectionTable_add(&infectionsTable, &ebola_Liberia);
    infection_update(infectionTable_find(&infectionsTable, ebola.name, &liberia), 10000, 4809, 0, 5191);
    infectionTable_add(&infectionsTable, &ebola_Guinea);
    infection_update(infectionTable_find(&infectionsTable, ebola.name, &guinea), 3800, 2500, 0, 1300);


    failed = false;
    start_test(test_section, "PR1_EX4_9", "Get Max Infection");

    infectionAux = infectionTable_getMaxInfection(&infectionsTable, "Ebola");
    if (infectionAux == NULL || !infection_equals(infectionAux, &ebola_Liberia)) {
        failed = true;
    }


    infection_update(infectionTable_find(&infectionsTable, "SARS-CoV-2", &china), 81639, 3326, 0, 76751);
    infection_update(infectionTable_find(&infectionsTable, "SARS-CoV-2", &italy), 119827, 14681, 0, 19758);


    infectionAux = infectionTable_getMaxInfection(&infectionsTable, "SARS-CoV-2");
    if (infectionAux == NULL || !infection_equals(infectionAux, &COVID_19_Italy)) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_9", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_9", true);
    }

    // TEST 10: get mortality rate
    failed = false;
    start_test(test_section, "PR1_EX4_10", "Get mortality rate");

    mortalityRate = infectionTable_getMortalityRate(&infectionsTable, "Ebola");

    if (mortalityRate != 0.473319322f) {
        failed = true;
    }

    mortalityRate = infectionTable_getMortalityRate(&infectionsTable, "SARS-CoV-2");

    if (mortalityRate != 0.089379847f) {
        failed = true;
    }

    if (failed) {
        end_test(test_section, "PR1_EX4_10", false);
        passed = false;
    }
    else {
        end_test(test_section, "PR1_EX4_10", true);
    }

    // Remove used memory   

    infectionTable_free(&infectionsTable);

    infection_free(&ebola_Sierra_Leone);
    infection_free(&ebola_Liberia);
    infection_free(&ebola_Guinea);
    infection_free(&COVID_19_China);
    infection_free(&COVID_19_SouthKorea);
    infection_free(&COVID_19_Italy);
    infection_free(&COVID_19_copy);
    infection_free(&COVID_19_China);

    infectiousAgent_free(&ebola);
    infectiousAgent_free(&COVID_19);

    reservoirTable_free(&reservoirList);
    reservoir_free(&pangolin);
    reservoir_free(&bat);


    country_free(&china);
    country_free(&south_korea);
    country_free(&italy);
    country_free(&sierra_leone);
    country_free(&liberia);
    country_free(&guinea);


    return passed;
}
