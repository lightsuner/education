//
//  main.c
//  c-lab3
//
//  Created by Alex Kuk on 23.10.14.
//  Copyright (c) 2014 alexkuk. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * remove_all_parentheses(const char * input_string) {
           unsigned int open = 0,
                   closed = 0,
           string_length = strlen(input_string);
           char * output_string = NULL, * buffer = NULL;

    buffer = malloc(string_length);

    unsigned int new_str_cursor = 0;
    for (unsigned int i = 0; i < string_length; i++) {
        switch (input_string[i]) {
            case '(':
                open++;
                break;
            case ')':
                closed++;
                break;
            default:
                if (open == closed) {
                    buffer[new_str_cursor] =  input_string[i];
                    new_str_cursor++;
                }
                break;
        }
    }
    buffer[new_str_cursor] = '\0';
    output_string = malloc(strlen(buffer));
    strcpy(output_string, buffer);
    free(buffer);
    return output_string;
}

int main(int argc, const char * argv[]) {

    char base_string[] = "this is a test ((string form (we) should remove all) parentheses ()";

    printf("Prepared string - \"%s\"", remove_all_parentheses(base_string));

    return 0;
}