#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

// Initialize a test Suite
void testSuite_init(tTestSuite* object) {
    assert(object!=NULL);    
    object->numSections = 0;
    object->sections = NULL;    
}

// Remove a test Suite
void testSuite_free(tTestSuite* object) {
    int i;
    assert(object!=NULL);
    if(object->sections != NULL) {
        for(i=0; i<object->numSections;i++) {
            testSection_free(&(object->sections[i]));
        }
        free(object->sections);
    }
}

// Add a test Section
void testSuite_addSection(tTestSuite* object, const char* code, const char* title) {
    assert(object!=NULL);
    object->numSections++;
    if(object->sections == NULL) {
        object->sections = (tTestSection*)malloc(object->numSections*sizeof(tTestSection));        
    } else {
        object->sections = (tTestSection*)realloc(object->sections, object->numSections*sizeof(tTestSection));        
    }
    assert(object->sections != NULL);
    testSection_init(&(object->sections[object->numSections-1]), code, title);
}

// Add a test
void testSuite_addTest(tTestSuite* object, const char* section_code, const char* code, const char* description, tTestResult result) {
    tTestSection* section = NULL;
    assert(object!=NULL);
    assert(section_code!=NULL);
    assert(code != NULL);
    assert(description != NULL);
    
    section = testSuite_getSection(object, section_code);
    assert(section != NULL);
    
    testSection_addTest(section, code, description, result);    
}

// Update a test result
void testSuite_updateTest(tTestSuite* object, const char* section_code, const char* test_code, tTestResult result) {
    tTestSection* section = NULL;
    
    assert(object!=NULL);
    assert(section_code!=NULL);
    assert(test_code != NULL);    
    
    section = testSuite_getSection(object, section_code);
    assert(section != NULL);
    
    testSection_updateTest(section, test_code, result);
}

// Get a pointer to a section
tTestSection* testSuite_getSection(tTestSuite* object, const char* section_code) {
    int i;
    
    assert(object!=NULL);
    assert(section_code!=NULL);
    for(i=0; i<object->numSections;i++) {
        if(strcmp(object->sections[i].code, section_code) == 0) {
            return &(object->sections[i]);
        }
    }
    return NULL;
}

// Get a pointer to a test
tTest* testSuite_getTest(tTestSuite* object, const char* section_code, const char* test_code) {
    tTestSection* section = NULL;
    
    assert(object!=NULL);
    assert(section_code!=NULL);
    assert(test_code!=NULL);
    section = testSuite_getSection(object, section_code);
    assert(section!=NULL);
    
    if (section != NULL) {
        return testSection_getTest(section, test_code);
    }
    
    return NULL;
}

// Get test statistics
void testSuite_getStats(tTestSuite* object, int* total, int* passed, int* failed, int* not_implemented) {    
    int i;    
    int s_total, s_passed, s_failed, s_not_implemented; 
    assert(object!=NULL);
    assert(total!=NULL);
    assert(passed!=NULL);
    assert(failed!=NULL);
    assert(not_implemented!=NULL);
    
    *total = 0;
    *passed = 0;
    *failed = 0;
    *not_implemented = 0;
    for(i=0; i<object->numSections;i++) {
        testSection_getStats(&(object->sections[i]), &s_total, &s_passed, &s_failed, &s_not_implemented);
        *total += s_total;
        *passed += s_passed;
        *failed += s_failed;
        *not_implemented += s_not_implemented;
    }    
}

// Print test suite
void testSuite_print(tTestSuite* object) {
    int i;
    int total, passed, failed, not_implemented;
    
    assert(object!=NULL);    
    
    testSuite_getStats(object, &total, &passed, &failed, &not_implemented);
    
    printf("\n=========================================================================\n");
    printf("\t TEST RESULTS\n");
    printf("=========================================================================\n");
    if(object->numSections == 0) {
        printf("NO TEST DEFINED\n");
    } else {
        for(i=0; i < object->numSections; i++) {
            testSection_print(&(object->sections[i]));
        }
    }
    printf("\n=========================================================================\n");
    if(total>0) {
        printf("Total Tests: %d\n", total);
        printf("Passed Tests: %d ( %2.02f %% )\n", passed, ((float)passed/(float)total)*100.0);
        printf("Failed Tests: %d ( %2.02f %% )\n", failed, ((float)failed/(float)total)*100.0);
        //printf("Not Implemented: %d ( %2.02f %% )\n", not_implemented, ((float)not_implemented/(float)total)*100.0);
        printf("=========================================================================\n");
    }    
}

// Export a test suite
void testSuite_export(tTestSuite* object, FILE* fout) {
    int i;
    int total, passed, failed, not_implemented;
    
    assert(object!=NULL);
    assert(fout!=NULL);
    
    testSuite_getStats(object, &total, &passed, &failed, &not_implemented);
    
    fprintf(fout, "{ \"total\": %d, \"passed\": %d, \"failed\": %d, \"not_implemented\": %d, \"sections\": [", total, passed, failed, not_implemented);    
        
    for(i=0; i < object->numSections; i++) {
        if(i>0) {
            fprintf(fout, ", ");
        }
        testSection_export(&(object->sections[i]), fout);
    }
    
    fprintf(fout, "]}");
}


// Initialize a test Section
void testSection_init(tTestSection* object, const char* code, const char* title) {
    assert(object!=NULL);
    object->code = (char*) malloc((strlen(code) + 1) * sizeof(char));
    assert(object->code!=NULL);    
    strcpy(object->code, code);    
    object->title = (char*) malloc((strlen(title) + 1) * sizeof(char));
    assert(object->title!=NULL);    
    strcpy(object->title, title);    
    object->numTests = 0;
    object->tests = NULL;    
}

// Remove a test Section
void testSection_free(tTestSection* object) {
    int i;
    assert(object!=NULL);
    assert(object->code!=NULL);
        
    free(object->code);    
    if(object->tests != NULL) {
        for(i=0; i<object->numTests; i++) {
            test_free(&(object->tests[i]));
        }
        free(object->tests);
    }
}

// Add a test to the Section
void testSection_addTest(tTestSection* object, const char* code, const char* description, tTestResult result) {
    assert(object!=NULL);
    object->numTests++;
    if(object->tests == NULL) {
        object->tests = (tTest*)malloc(object->numTests*sizeof(tTest));        
    } else {
        object->tests = (tTest*)realloc(object->tests, object->numTests*sizeof(tTestSection));        
    }
    assert(object->tests != NULL);
    test_init(&(object->tests[object->numTests-1]), code, description, result);
}

// Update a test result
void testSection_updateTest(tTestSection* object, const char* test_code, tTestResult result) {
    tTest* test = NULL;
    
    assert(object!=NULL);
    test = testSection_getTest(object, test_code);
    
    assert(test != NULL);
    test_updateTest(test, result);
}

// Get a pointer to a test
tTest* testSection_getTest(tTestSection* object, const char* test_code) {
    int i;
    assert(object!=NULL);
    assert(test_code!=NULL);
    for(i=0; i<object->numTests;i++) {
        if(strcmp(object->tests[i].code, test_code) == 0) {
            return &(object->tests[i]);
        }
    }
    return NULL;
}

// Get test statistics
void testSection_getStats(tTestSection* object, int* total, int* passed, int* failed, int* not_implemented) {
    int i;    
    assert(object!=NULL);
    assert(total!=NULL);
    assert(passed!=NULL);
    assert(failed!=NULL);
    assert(not_implemented!=NULL);
    
    *total = object->numTests;
    *passed = 0;
    *failed = 0;
    *not_implemented = 0;
    for(i=0; i<object->numTests;i++) {
        if(object->tests[i].result == TEST_PASSED) {
            (*passed)++;
        } else if(object->tests[i].result == TEST_FAILED) {
            (*failed)++;
        } else if(object->tests[i].result == TEST_FAILED) {
            (*not_implemented)++;
        }
    }    
}

// Print test section
void testSection_print(tTestSection* object) {
    int i;
    int total, passed, failed, not_implemented;
    
    assert(object!=NULL);
    
    testSection_getStats(object, &total, &passed, &failed, &not_implemented);
    
    printf("\n\t=================================================================\n");
    printf("\t%s\n", object->title);
    printf("\t=================================================================\n");
    if(object->numTests == 0) {
        printf("\tNO TEST DEFINED\n");
    } else {
        for(i=0; i < object->numTests; i++) {
            test_print(&(object->tests[i]));
        }
    }
    printf("\t=================================================================\n");
    if(total>0) {
        printf("\tTotal Tests: %d\n", total);
        printf("\tPassed Tests: %d ( %2.2f %% )\n", passed, ((float)passed/(float)total)*100.0);
        printf("\tFailed Tests: %d ( %2.2f %%)\n", failed, ((float)failed/(float)total)*100.0);
        //printf("\tNot Implemented: %d ( %2.2f %%)\n", not_implemented, ((float)not_implemented/(float)total)*100.0);
        printf("\t=================================================================\n");
    }    
}

// Export a test section
void testSection_export(tTestSection* object, FILE* fout) {
    int i;
    int total, passed, failed, not_implemented;
    
    assert(object!=NULL);
    assert(fout!=NULL);
    
    testSection_getStats(object, &total, &passed, &failed, &not_implemented);
    
    fprintf(fout, "{ \"code\": \"%s\", \"title\": \"%s\", \"total\": %d, \"passed\": %d, \"failed\": %d, \"not_implemented\": %d, \"tests\": [", object->code, object->title, total, passed, failed, not_implemented);    
        
    for(i=0; i < object->numTests; i++) {
        if(i>0) {
            fprintf(fout, ", ");
        }
        test_export(&(object->tests[i]), fout);
    }
    
    fprintf(fout, "]}");
}


// Initialize a test
void test_init(tTest* object, const char* code, const char* description, tTestResult result) {
    assert(object!=NULL);
    object->code = (char*) malloc((strlen(code) + 1) * sizeof(char));
    assert(object->code!=NULL);
    object->description = (char*) malloc((strlen(description) + 1) * sizeof(char));
    assert(object->description!=NULL);
    strcpy(object->code, code);
    strcpy(object->description, description);
    object->result = TEST_RUNNING;
}

// Remove a test
void test_free(tTest* object) {
    assert(object!=NULL);
    assert(object->code!=NULL);
    assert(object->description!=NULL);
    free(object->code);
    free(object->description);
}

// Update a test result
void test_updateTest(tTest* object, tTestResult result) {
    assert(object!=NULL);
    object->result = result;
}

// Print test
void test_print(tTest* object) {    
    assert(object!=NULL);
    printf("\t\t");
    if(object->result == TEST_RUNNING) {
        printf("[%s]", "RUNNING");
    } else if (object->result == TEST_NOT_IMPLEMENTED) {
        printf("[%s]", "NOT IMPLEMENTED");
    } else if (object->result == TEST_PASSED) {
        printf("[%s]", "OK");
    } else if (object->result == TEST_FAILED) {
        printf("[%s]", "FAIL");
    }         
    printf(":\t [%s] %s\n", object->code, object->description);
}

// Export a test
void test_export(tTest* object, FILE* fout) {
    assert(object!=NULL);
    assert(fout!=NULL);
    
    fprintf(fout, "{ \"code\": \"%s\", \"description\": \"%s\", \"result\": ",object->code, object->description);
    if(object->result == TEST_RUNNING) {
        fprintf(fout, "\"%s\"}", "RUNNING");
    } else if (object->result == TEST_NOT_IMPLEMENTED) {
        fprintf(fout, "\"%s\"}", "NOT IMPLEMENTED");
    } else if (object->result == TEST_PASSED) {
        fprintf(fout, "\"%s\"}", "OK");
    } else if (object->result == TEST_FAILED) {
        fprintf(fout, "\"%s\"}", "FAIL");
    }             
}


// Start a test
void start_test(tTestSection* section, const char* code, const char* description) {
    tTest* test = NULL;
    
    assert(section!=NULL);
    assert(code!=NULL);
    assert(description!=NULL);
    #ifdef PRINT_TEST_PROGRESS 
    printf("\n[START] ==> Running test [%s] - %s\n", code, description);
    #endif // PRINT_TEST_PROGRESS
    testSection_addTest(section, code, description, TEST_RUNNING);
    
    test = testSection_getTest(section, code);
    assert(test!=NULL);
}

// Finish a test
void end_test(tTestSection* section, const char* code, bool passed) {
    tTest* test = NULL;
    assert(section!=NULL);
    assert(code!=NULL);
    
    test = testSection_getTest(section, code);
    assert(test!=NULL);
    
    if(passed) {
        #ifdef PRINT_TEST_PROGRESS 
        printf("\n[OK] ==> Finished test [%s] - %s\n", test->code, test->description);
        #endif // PRINT_TEST_PROGRESS
        test_updateTest(test, TEST_PASSED);
    } else {
        #ifdef PRINT_TEST_PROGRESS 
        printf("\n[FAIL] ==> Finished test [%s] - %s\n", test->code, test->description);
        #endif // PRINT_TEST_PROGRESS
        test_updateTest(test, TEST_FAILED);
    }    
}



