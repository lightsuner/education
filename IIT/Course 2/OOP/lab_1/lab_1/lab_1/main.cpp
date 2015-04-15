//
//  main.cpp
//  lab_1
//
//  Created by Alex Kuk on 25.02.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <iostream>
#include "pairs.h"

int main(int argc, const char * argv[]) {
    
    Pairs * pairs;
    pairs = InitPairs();
    int tmp_val;
    
    printf("Search for ALEX\n");
    
    if (GetValue(pairs, "alex", tmp_val)) {
        printf("ALEX's value is: %d\n", tmp_val);
    } else {
        printf("ALEX's value not found\n");
    }
    
    printf("try to set ALEX's value to 7\n");
    
    SetValue(pairs, "alex", 7);
    
    if (GetValue(pairs, "alex", tmp_val)) {
        printf("ALEX's value is: %d\n", tmp_val);
    } else {
        printf("ALEX's value not found\n");
    }
    SetValue(pairs, "alex", 8);
           
    SetValue(pairs, "bob", 1);
    
    SetValue(pairs, "tom", 6);
    
    PrintPairs(pairs);
           
    return 0;
}
