//
//  pairs.h
//  lab_1
//
//  Created by Alex Kuk on 25.02.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#ifndef __lab_1__pairs__
#define __lab_1__pairs__

#include <stdio.h>

#define MAX_PAIRS 100

struct Pair
{
    char * name;	//имя
    int value;	//значение
};

struct Pairs
{
    Pair pairs[MAX_PAIRS];
    int count;
};

Pairs * InitPairs();
int GetValue(Pairs * pairs, const char * name, int &value);
void SetValue(Pairs * pairs, const char * name, int value);
void PrintPairs(Pairs * pairs);

#endif /* defined(__lab_1__pairs__) */
