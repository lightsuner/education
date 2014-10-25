//
//  main.c
//  c-lab1
//
//  Created by Alex Kuk on 23.10.14.
//  Copyright (c) 2014 alexkuk. All rights reserved.
//

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    double sum = 0;

    for (unsigned int i = 1; i <= 50; i++) {
        sum += 1/pow(i, 3);
    }

    printf("The result is - %.10f\n", sum);

    return 0;
}