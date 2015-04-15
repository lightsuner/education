//
//  pairs.cpp
//  lab_1
//
//  Created by Alex Kuk on 25.02.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include "pairs.h"
#include <string.h>

Pairs * InitPairs()
{
    Pairs * pairs;
    pairs = new Pairs;
    pairs->count = 0;
    
    return pairs;
}

int GetValue(Pairs * pairs, const char * name, int &value)
{
    for(int i = 0; i < pairs->count; i++) {
        if (strcmp(pairs->pairs[i].name, name) == 0) {
            value = pairs->pairs[i].value;
            return 1;
        }
    }
    return 0;
}

void SetValue(Pairs * pairs, const char * name, int value)
{
    
    for(int i = 0; i < pairs->count; i++) {
        if (strcmp(pairs->pairs[i].name, name) == 0) {
            pairs->pairs[i].value = value;
            return;
        }
    }
    //pairs->pairs[pairs->count] = Pair();
    pairs->pairs[pairs->count].name = new char[strlen(name)+1];
    strcpy(pairs->pairs[pairs->count].name, name);
    pairs->pairs[pairs->count].value = value;
    pairs->count++;
    
    return;
}

void PrintPairs(Pairs * pairs)
{
    printf("Pairs:\n");
    printf("Total: %d\n", pairs->count);
    for(int i = 0; i < pairs->count; i++) {
       printf("%d) name: %s value: %d\n", (i+1), pairs->pairs[i].name, pairs->pairs[i].value);
    }
    printf("\n");
}