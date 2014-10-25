//
//  main.c
//  c-lab2
//
//  Created by Alex Kuk on 23.10.14.
//  Copyright (c) 2014 alexkuk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct NUM_COUNTER {
 int num;
 unsigned int count;
} NUM_COUNTER;

NUM_COUNTER *create_num_counter(int number) {
    NUM_COUNTER *c = (NUM_COUNTER *) malloc (sizeof (NUM_COUNTER));
    c->num = number;
    c->count = 1;
    return c;
}

void push(NUM_COUNTER *num_counter[], int number) {
    int i = 0;
    while (num_counter[i] != NULL) {
        if (num_counter[i]->num == number) {
            num_counter[i]->count++;
            return;
        }
        i++;
    }

    num_counter[i] = create_num_counter(number);

}

void print_num_counter(NUM_COUNTER *num_counter[]) {
    int i = 0;
    printf("num - count\n");
    while (num_counter[i] != NULL) {
        printf("%2d  - %d\n", num_counter[i]->num, num_counter[i]->count);
        i++;
    }

}

int main(int argc, const char * argv[]) {

    int matrix[6][6] = {
            {1,2,3,4,5,6}, {2,3,4,5,6,7}, {3,4,5,6,7,8,9}, {4,5,6,7,8,9,0}, {5,6,7,8,9,0,1}, {6,7,8,9,0,1,2}
    };


    NUM_COUNTER *counter[36] = {NULL};

    for (int i=0; i < 6; i++) {
        for (int j=0; j < 6; j++) {
            printf("%3d", matrix[i][j]);
            push(&counter, matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    print_num_counter(counter);

    return 0;
}

