#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test_suit.h"

void waitKey() {
    printf("Press enter to end...");
    getchar();
}

void help(const char* name) {
    printf("%s\t =>\t Run all tests and show results on screen\n", name);
    printf("%s -h\t =>\t Show this help\n", name);
    printf("%s -e [<file_path>]\t =>\t Run all tests and save results on file (default test_result.json)\n", name);
}

int main(int argc, char **argv)
{
    char output_filename[512];
    tTestSuite test_suite;
    FILE* fout = NULL;
    
    if(argc == 1) {
        // Run tests and show results on screen        
        run_all(&test_suite);
        testSuite_print(&test_suite);        
        waitKey();
    } else if(argc > 1) {
        if(strcmp(argv[1], "-h") == 0) {
            // Show help message
            help(argv[0]);
            exit(EXIT_SUCCESS);
        } else if(strcmp(argv[1], "-e") == 0) {            
            // Run tests and export the resultin JSON format
            if(argc > 2) {
                // Output file is provided
                strncpy(output_filename, argv[2], 512);
            } else {
                // Use default filename
                strncpy(output_filename, "test_result.json", 512);
            }                        
            run_all(&test_suite);
            fout = fopen(output_filename, "w");
            assert(fout != NULL);
            testSuite_export(&test_suite, fout);
            fclose(fout);
        } else {
            // Invalid parameters
            printf("Invalid parameters\n");
            help(argv[0]);
            exit(EXIT_FAILURE);
        }
    } 
	exit(EXIT_SUCCESS);
}