#ifndef __RESEARCH_H__
#define __RESEARCH_H__

#include "infection.h"
#include "commons.h"

typedef struct {
    unsigned int Infectivity;
    unsigned int Severity;
    unsigned int Lethality;
} tInfectionStats;

// Definition of research element
typedef struct {
    tCountry* country;
    tInfectionStats stats;
} tResearch;

// Definition of a node for a double-linked list
typedef struct _tResearchListNode {
    tResearch* e;
    struct _tResearchListNode* next;
    struct _tResearchListNode* prev;
} tResearchListNode;

// Definition of a list of ratings
typedef struct {
    tResearchListNode* first;
    tResearchListNode* last;
    int size;
} tResearchList;


// Creates a research element out of a country and a stats
tError research_init(tResearch* object, tCountry* country);

// Releases data pointed by research element
void research_free(tResearch* object);

// Compare stats of two countries, 1 if s1 wins, -1 if s2 wins, 0 if tie
int research_compare(tInfectionStats s1, tInfectionStats s2);

// Create the research list
void researchList_create(tResearchList* list);

// Insert/adds a new research to the research list
tError researchList_insert(tResearchList* list, tResearch* research, int index);

// Deletes a research from the research list
tError researchList_delete(tResearchList* list, int index);

// Gets research from given position, NULL if out of bounds
tResearchListNode* researchList_get(tResearchList* list, int index);

// Gets true if list is empty
bool researchList_empty(tResearchList* list);

// Remove all data for a popularity list
void researchList_free(tResearchList* list);

// given the head list (first), returns the position of the country in the list recursively
int researchList_getPosByCountryRecursive(tResearchListNode* first, tCountry *country, int pos);

// given a list of infections, returns the position of the infection in the list recursively calling researchList_getPosByCountryRecursive
int researchList_getPosByCountry(tResearchList* list, tCountry *country);

// Swap two elements in the list
tError researchList_swap(tResearchList* list, int index_dst, int index_src);

// Sorts input list using bubbleSort algorithm
tError researchList_bubbleSort(tResearchList *list);

// Helper function, print list contents
void researchList_print(tResearchList list);

#endif // __RESEARCH_H__
