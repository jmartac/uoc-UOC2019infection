#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include "research.h"
#include "infection.h"
#include "country.h"
#include "commons.h"
#include "error.h"


// Creates a research element out of a country and a stats
tError research_init(tResearch* object, tCountry* country) {
    // PR3_EX1

    // Verify pre conditions
    assert(object != NULL);
    assert(country != NULL);

    // Allocate the memory for all the fields. Since 'stats' is not a pointer, we can't allocate memory for it
    object->country = (tCountry*) malloc(sizeof(tCountry));

    // Check that memory has been correctly allocated for all fields. Pointer must be different from NULL
    if (object->country == NULL) {
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.
    object->stats.Infectivity = country_totalCases(country);
    object->stats.Severity    = country_totalCriticalCases(country);
    object->stats.Lethality   = country_totalDeaths(country);

    country_cpy(object->country, country);

    return OK;
}

// Releases data pointed by research element
void research_free(tResearch* object) {
    // PR3_EX1

    // Verify pre conditions
    assert(object != NULL);

    object->stats.Infectivity = 0;
    object->stats.Severity    = 0;
    object->stats.Lethality   = 0;

    if (object->country != NULL) {
        country_free(object->country);
        free(object->country);
        object->country = NULL;
    }
}

// Compare stats of two countries, 1 if s1 wins, -1 if s2 wins, 0 if tie
int research_compare(tInfectionStats s1, tInfectionStats s2) {
    // PR3_EX1

    int result = 0;
    if (s1.Infectivity != s2.Infectivity)
        result = (s1.Infectivity > s2.Infectivity)? 1 : -1;

    if (result == 0 && s1.Lethality != s2.Lethality)
        result = (s1.Lethality > s2.Lethality)? 1 : -1;

    if (result == 0 && s1.Severity != s2.Severity)
        result = (s1.Severity > s2.Severity)? 1 : -1;

    return result;
}

// Create the research list
void researchList_create(tResearchList* list) {
    // PR3_EX2

    // Verify pre conditions
    assert(list != NULL);

    list->first = NULL;
    list->last  = NULL;
    list->size  = 0;
}

// Insert/adds a new research to the research list
tError researchList_insert(tResearchList* list, tResearch* research, int index) {
    // PR3_EX2

    tResearchListNode* new_node;
    tResearchListNode* old_node;
    tResearchListNode* prev_node;

    // Verify pre conditions
    assert(list != NULL);
    assert(research != NULL);

    // Index will be considered invalid if it's not between 1 and (list size + 1), both included, except when the list is empty and index is 1 (first insertion)
    if ( (index != 1 && !researchList_empty(list)) && (index > list->size + 1 || index < 1) )
        return ERR_INVALID_INDEX;

    // Create new node with given research and check if memory's correctly allocated
    new_node = (tResearchListNode*) malloc(sizeof(tResearchListNode));
    if (new_node == NULL)
        return ERR_MEMORY_ERROR;

    new_node->e = (tResearch*) malloc(sizeof(tResearch));
    if (new_node->e == NULL)
        return ERR_MEMORY_ERROR;

    research_init(new_node->e, research->country);
    new_node->next = NULL;
    new_node->prev = NULL;

    if (researchList_empty(list)) {
        // First insertion in empty list
        list->first = new_node;
        list->last  = new_node;
    } else {
        // old node is the last one listed if given index is (size + 1) or the node in the given index position
        if (index == list->size + 1) {
            old_node        = list->last;
            old_node->next  = new_node;
            new_node->prev  = old_node;
            list->last      = new_node;
        } else {
            old_node  = researchList_get(list, index);
            prev_node = old_node->prev;

            // Check if we are dealing with the first node
            if (index != 1) {
                // Previous node now points to the new node and vice versa
                prev_node->next = new_node;
                new_node->prev  = prev_node;
            } else
                list->first = new_node;

            // New node now points to the old node (should now be relocated to a later position) and vice versa
            new_node->next = old_node;
            old_node->prev = new_node;
        }
    }

    list->size++;
    return OK;
}

// Deletes a research from the research list
tError researchList_delete(tResearchList* list, int index) {
    // PR3_EX2

    tResearchListNode* node_to_delete;
    tResearchListNode* prev_node;
    tResearchListNode* next_node;

    // Verify pre conditions
    assert(list != NULL);

    // List is empty
    if (researchList_empty(list))
        return ERR_EMPTY_LIST;

    node_to_delete = researchList_get(list, index);

    // Node has not been found with the given index, so it's an invalid index
    if (node_to_delete == NULL)
        return ERR_INVALID_INDEX;

    next_node = node_to_delete->next;
    prev_node = node_to_delete->prev;

    // Update list references if node to be deleted is the first or last one
    if (index == 1)
        list->first = next_node;

    if (index == list->size)
        list->last = prev_node;

    // Link previous node to next node reference if there exist previous node
    if (prev_node != NULL)
        prev_node->next = next_node;

    // Link next node to previous node reference if there exist next node
    if (next_node != NULL)
        next_node->prev = prev_node;

    // Free memory of the research and it's node
    research_free(node_to_delete->e);
    free(node_to_delete->e);
    free(node_to_delete);
    list->size--;

    return OK;
}

// Gets research from given position, NULL if out of bounds
tResearchListNode* researchList_get(tResearchList* list, int index) {
    // PR3_EX2

    tResearchListNode* node;
    int i;

    // Verify pre conditions
    assert(list != NULL);

    // index out of ranges or empty list
    if (index > list->size || index < 1 || researchList_empty(list))
        return NULL;

    if (index == list->size)
        return list->last;

    i = 1;
    node = list->first;
    while (i < index) {
        node = node->next;
        i++;
    }

    return node;
}

// Gets true if list is empty
bool researchList_empty(tResearchList* list) {
    // PR3_EX2

    // Verify pre conditions
    assert(list != NULL);

    return (list->size == 0)? true : false;
}

// Remove all data for a research list
void researchList_free(tResearchList* list) {
    // PR3_EX2

    tResearchListNode* node;
    tResearchListNode* next_node;

    // Verify pre conditions
    assert(list != NULL);

    node = list->first;

    // Free memory of every node
    while (node != NULL) {
        next_node = node->next;

        // Free memory of the research and it's node
        research_free(node->e);
        free(node->e);
        free(node);

        node = next_node;
    }

    list->size  = 0;
    list->first = NULL;
    list->last  = NULL;
}

// given a list of country' research, returns the position of the country in the list
int researchList_getPosByCountryRecursive(tResearchListNode* first, tCountry *country, int pos) {
    // PR3_EX3

    if (!country_equal(first->e->country, country)) {
        if (first->next != NULL)
            pos = researchList_getPosByCountryRecursive(first->next, country, pos + 1);
        else
            pos = -1;
    }

    return pos;
}

// given a list of country' research, returns the position of the country in the list
int researchList_getPosByCountry(tResearchList* list, tCountry *country) {
    // PR3_EX3

    // Verify pre conditions
    assert(list != NULL);
    assert(country != NULL);

    return researchList_getPosByCountryRecursive(list->first, country, 1);
}

// Swap two elements in the list
tError researchList_swap(tResearchList* list, int index_dst, int index_src) {
    // PR3_EX3

    tResearchListNode* src;
    tResearchListNode* src_next;
    tResearchListNode* src_prev;
    tResearchListNode* dst;
    tResearchListNode* dst_next;
    tResearchListNode* dst_prev;

    // Verify pre conditions
    assert(list != NULL);

    // Index out of range or indexes are equal
    if (index_dst < 1 || index_dst > list->size || index_src < 1 || index_src > list->size)
        return ERR_INVALID_INDEX;
    if (index_src == index_dst)
        return OK;

    src      = researchList_get(list, index_src);
    src_prev = src->prev;
    src_next = src->next;

    dst      = researchList_get(list, index_dst);
    dst_prev = dst->prev;
    dst_next = dst->next;

    // src is one position before dst
    if (index_src + 1 == index_dst){
        dst->next = src;
        dst->prev = src_prev;
        src->next = dst_next;
        src->prev = dst;

        if (dst_next != NULL)
            dst_next->prev = src;

        if (src_prev != NULL)
            src_prev->next = dst;
    }

    // src is one position after dst
    if (index_dst + 1 == index_src) {
        dst->next = src_next;
        dst->prev = src;
        src->next = dst;
        src->prev = dst_prev;

        if (dst_prev != NULL)
            dst_prev->next = src;

        if (src_next != NULL)
            src_next->prev = dst;
    }

    // src and dst are separated by 1 or more nodes
    if (index_dst + 1 != index_src && index_src + 1 != index_dst) {
        dst->next = src_next;
        dst->prev = src_prev;
        src->next = dst_next;
        src->prev = dst_prev;

        if (dst_prev != NULL)
            dst_prev->next = src;

        if (dst_next != NULL)
            dst_next->prev = src;

        if (src_next != NULL)
            src_next->prev = dst;

        if (src_prev != NULL)
            src_prev->next = dst;
    }

    // Update list references if required
    if (index_src == list->size || index_dst == list->size)
        list->last = (index_src == list->size) ? dst : src;
    if (index_src == 1 || index_dst == 1)
        list->first = (index_src == 1) ? dst : src;

    return OK;
}

// Sorts input list using bubbleSort algorithm
tError researchList_bubbleSort(tResearchList *list) {
    // PR3_EX3

    int i, j;
    tResearchListNode* further_node;
    tResearchListNode* nearest_node;

    // Verify pre conditions
    assert(list != NULL);

    // Compare nodes from last to first position, sorting by statistics in descending order
    for (i = list->size; i > 1; i--) {
        for (j = i; j > 1; j--) {
            further_node = researchList_get(list, j);
            nearest_node = researchList_get(list, j - 1);

            // Swap nodes when the furthest node has better statistics than the nearest one
            if (research_compare(further_node->e->stats, nearest_node->e->stats) == 1) {
                researchList_swap(list, j, j - 1);
            }
        }
    }

    return OK;
}

// Helper function, print list contents
void researchList_print(tResearchList list) {
    tResearchListNode *pLNode;

    printf("===== List Contents:\n\n");

    for (int i = 0; i < list.size; i++) {
        pLNode = researchList_get(&list, i + 1);
        printf("\tElemPos: %d:\tInfectivity: %d;\tSeverity: %d;\tLethality: %d;\tCountry_Name: \"%s\"\n",
            i + 1,
            pLNode->e->stats.Infectivity,
            pLNode->e->stats.Severity,
            pLNode->e->stats.Lethality,
            pLNode->e->country->name
            );

    }

    printf("\n===== End Of List: %d elems\n", list.size);
}
