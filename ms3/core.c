/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name   : Faizal Aslam
Student ID# : 152121216
Email       : faizal-aslam@myseneca.ca
Section     : IPC144 ZEE

Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
* ***************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"
#include <string.h>
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

int inputInt() {
    int keep_going = 1;
    char next_char = '\0';
    int result = -1;

    do {
        scanf("%d%c", &result, &next_char);
        if (next_char != '\n') {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else {
            keep_going = 0;
        }
    } while (keep_going);
    return result;
}

int inputIntPositive() {
    int result = -1;
    do {
        result = inputInt();
    } while (result < 0 && printf("ERROR! Value must be > 0: "));
    return result;
}

int inputIntRange(int min, int max) {
    int result = min - 1;

    do {
        result = inputInt();
    } while ((result < min || result > max) && printf("ERROR! Value must be between %d and %d inclusive: ", min, max));
    return result;
}

char inputCharOption(const char* char_str) {
    char result = '\0';
    char next_char = '\0';
    int i = 0;
    int length = strlen(char_str);
    int keep_going = 1;

    do {
        scanf("%c%c", &result, &next_char);

        if (next_char == '\n') {
            for (i = 0; i < length && keep_going; i++) {
                if (char_str[i] == result) {
                    keep_going = 0;
                }
            }
        }
        else {
            clearInputBuffer();
        }

    } while (keep_going && printf("ERROR: Character must be one of [%s]: ", char_str));

    return result;
}

void inputCString(char* chr_str, int min, int max, const char* prompt)
{
    char input[100] = { '\0' };
    int done = 0;
    int i = 0;
    //int j = 0;
    do
    {
        scanf("%99[^\n]%*c", input);
        for (i = 1; input[i]; i++)
            ; // this will calculate the length of the string that is required
        if (min == max) {
            if (i == min) {
                strcpy(chr_str, input);
                done = 1;
            }
        }
        else {
            if (i >= min && i <= max) {
                strcpy(chr_str, input);
                done = 1;
            }
        }
        if (!done) {
            if (!prompt) {
                if (min == max) {
                    printf("Invalid %d-digit number! Number: ", min);
                }
                else if (min == 0 || i > max) {
                    printf("ERROR: String length must be no more than %d chars: ", max);
                }
                else {
                    printf("ERROR: String length must be between %d and %d chars: ", min, max);
                }
            }
            else {
                printf(prompt);
            }
        }

    } while (!done);
}
void displayFormattedPhone(const char* chr_str) {
    int is_valid = 1;
    int i = 0;
    if (chr_str != NULL) {
        for (i = 0; chr_str[i] && is_valid; i++) {
            if (chr_str[i] < 48 || chr_str[i] > 57) {
                is_valid = 0;
            }
        }
    }

    if (is_valid && i == 10) {
        printf("(");
        for (i = 0; i < 3; i++) {
            printf("%c", chr_str[i]);
        }

        printf(")");
        for (i = 3; i < 6; i++) {
            printf("%c", chr_str[i]);
        }
        printf("-");
        for (i = 6; i < 10; i++) {
            printf("%c", chr_str[i]);
        }
    }
    else {
        printf("(___)___-____");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

