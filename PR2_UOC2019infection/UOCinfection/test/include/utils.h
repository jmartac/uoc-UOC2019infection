#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>
#include <stdio.h>

// #define PRINT_TEST_PROGRESS

// Status of a test
typedef enum {
    TEST_RUNNING,
    TEST_NOT_IMPLEMENTED,
    TEST_PASSED,
    TEST_FAILED
} tTestResult;

// A single test
typedef struct {
    // Code of the test
    char* code;
    // Description of the test
    char* description;
    // Result of the test
    tTestResult result;
} tTest;

// Grup of tests
typedef struct {
    // Code of the test section
    char* code;
    // Title of the section
    char* title;
    // Number of tests
    int numTests;    
    // Array of tests
    tTest* tests;
} tTestSection;

// Test suit with multiple sections
typedef struct {
    // Number of sections
    int numSections;    
    // Array of sections
    tTestSection* sections;
} tTestSuite;

// Initialize a test Suite
void testSuite_init(tTestSuite* object);

// Remove a test Suite
void testSuite_free(tTestSuite* object);

// Add a test Section
void testSuite_addSection(tTestSuite* object, const char* code, const char* title);

// Add a test
void testSuite_addTest(tTestSuite* object, const char* section_code, const char* code, const char* description, tTestResult result);

// Update a test result
void testSuite_updateTest(tTestSuite* object, const char* section_code, const char* test_code, tTestResult result);

// Get a pointer to a section
tTestSection* testSuite_getSection(tTestSuite* object, const char* section_code);

// Get a pointer to a test
tTest* testSuite_getTest(tTestSuite* object, const char* section_code, const char* test_code);

// Get test statistics
void testSuite_getStats(tTestSuite* object, int* total, int* passed, int* failed, int* not_implemented);

// Print test suite
void testSuite_print(tTestSuite* object);

// Export a test suite
void testSuite_export(tTestSuite* object, FILE* fout);



// Initialize a test Section
void testSection_init(tTestSection* object, const char* code, const char* title);

// Remove a test Section
void testSection_free(tTestSection* object);

// Add a test to the Section
void testSection_addTest(tTestSection* object, const char* code, const char* description, tTestResult result);

// Update a test result
void testSection_updateTest(tTestSection* object, const char* test_code, tTestResult result);

// Get a pointer to a test
tTest* testSection_getTest(tTestSection* object, const char* test_code);

// Get test statistics
void testSection_getStats(tTestSection* object, int* total, int* passed, int* failed, int* not_implemented);

// Print test section
void testSection_print(tTestSection* object);

// Export a test section
void testSection_export(tTestSection* object, FILE* fout);



// Initialize a test
void test_init(tTest* object, const char* code, const char* description, tTestResult result);

// Remove a test
void test_free(tTest* object);

// Update a test result
void test_updateTest(tTest* object, tTestResult result);

// Print test
void test_print(tTest* object);

// Export a test
void test_export(tTest* object, FILE* fout);


// Start a test
void start_test(tTestSection* section, const char* code, const char* description);

// Finish a test
void end_test(tTestSection* section, const char* code, bool passed);


#endif // __UTILS_H__