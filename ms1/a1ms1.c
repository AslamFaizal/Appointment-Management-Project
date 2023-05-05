/*
****************************************************************************
                        Assignment 1 - Milestone 1
Full Name   : Faizal Aslam
Student ID# : 152121216
Email       : faizal-aslam@myseneca.ca
Section     : IPC144 ZEE

Authenticity Declaration :
I declare this submission is the r of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* **************************************************************************
*/



#include <stdio.h>
#include "core.h"


void Test1_inputInteger(void);
void Test2_inputIntPositive(void);
void Test3_inputIntRange(void);
void Test4_inputIntRange(void);
void Test5_inputCharOption(void);
void Test6_inputCString(void);
void Test7_inputCString(void);
void Test8_inputCString(void);
void Test9_displayFormattedPhone(void);

int main(void)
{
    printf("Assignment 1 Milestone 1: Tester\n");
    printf("================================\n\n");

    Test1_inputInteger();
    Test2_inputIntPositive();
    Test3_inputIntRange();
    Test4_inputIntRange();
    Test5_inputCharOption();
    Test6_inputCString();
    Test7_inputCString();
    Test8_inputCString();
    Test9_displayFormattedPhone();

    printf("Assignment #1 Milestone #1 testing completed!\n");

    return 0;
}

void Test1_inputInteger(void)
{
    int ValueofInteger = 0;

    printf("TEST #1 - Instructions:\n"
        "1) Enter the word 'error'  [ENTER]\n"
        "2) Enter the number '-100' [ENTER]\n"
        ":>");

    ValueofInteger = inputInt();

    printf("////////////////////////////////////////\n");
    printf("TEST #1 r: ");
    if (ValueofInteger == -100)
    {
        printf("* PASS * \n");
    }
    else
    {
        printf("### FAILED ###\n");
    }
    printf("////////////////////////////////////////\n\n");
}

void Test2_inputIntPositive(void)
{
    int ValueofInteger = -1;

    printf("TEST #2 - Instructions:\n"
        "1) Enter the number '-100' [ENTER]\n"
        "2) Enter the number '200'  [ENTER]\n"
        ":>");

    ValueofInteger = inputIntPositive();

    printf("////////////////////////////////////////\n");
    printf("TEST #2 r: ");
    if (ValueofInteger == 200)
    {
        printf("* PASS * \n");
    }
    else
    {
        printf("### FAILED ###\n");
    }
    printf("////////////////////////////////////////\n\n");
}

void Test3_inputIntRange(void)
{
    int ValueofInteger = 999;

    printf("TEST #3 - Instructions:\n"
        "1) Enter the word 'error' [ENTER]\n"
        "2) Enter the number '-4'  [ENTER]\n"
        "3) Enter the number '12'  [ENTER]\n"
        "4) Enter the number '-3'  [ENTER]\n"
        ":>");
    ValueofInteger = inputIntRange(-3, 11);

    printf("////////////////////////////////////////\n");
    printf("TEST #3 r: ");
    if (ValueofInteger == -3)
    {
        printf("* PASS * \n");
    }
    else
    {
        printf("### FAILED ###\n");
    }
    printf("////////////////////////////////////////\n\n");
}

void Test4_inputIntRange(void)
{
    int ValueofInteger = 999;

    printf("TEST #4 - Instructions:\n"
        "1) Enter the number '14' [ENTER]\n"
        ":>");

    ValueofInteger = inputIntRange(-40, 14);

    printf("////////////////////////////////////////\n");
    printf("TEST #4 r: ");
    if (ValueofInteger == 14)
    {
        printf("* PASS * \n");
    }
    else
    {
        printf("### FAILED ###\n");
    }
    printf("////////////////////////////////////////\n\n");
}

void Test5_inputCharOption(void)
{
    char CharValue = 'x';

    printf("TEST #5 - Instructions:\n"
        "1) Enter the character 'R' [ENTER]\n"
        "2) Enter the character 'e' [ENTER]\n"
        "3) Enter the character 'p' [ENTER]\n"
        "4) Enter the character 'r' [ENTER]\n"
        ":>");

    CharValue = inputCharOption("qwErty");

    printf("////////////////////////////////////////\n");
    printf("TEST #5 r: ");
    if (CharValue == 'r')
    {
        printf("* PASS * \n");
    }
    else
    {
        printf("### FAILED ###\n");
    }
    printf("////////////////////////////////////////\n\n");
}

void Test6_inputCString(void)
{
    char CStringValue[7] = { '\0' };

    printf("TEST #6: - Instructions:\n"
        "1) Enter the word 'horse'   [ENTER]\n"  
        "2) Enter the word 'chicken' [ENTER]\n"  
        "3) Enter the word 'SENECA'  [ENTER]\n"  
        ":>");

    inputCString(CStringValue, 6, 6);

    printf("////////////////////////////////////////\n");
    printf("TEST #6 r: ");
    printf("%s (expected r: SENECA)\n", CStringValue);
    printf("////////////////////////////////////////\n\n");
}

void Test7_inputCString(void)
{
    char CStringValue[7] = { '\0' };

    printf("TEST #7: - Instructions:\n"
        "1) Enter the words 'Seneca College' [ENTER]\n"
        "2) Enter the word 'CATS'            [ENTER]\n"
        ":>");

    inputCString(CStringValue, 4, 6);

    printf("////////////////////////////////////////\n");
    printf("TEST #7 r: ");
    printf("%s (expected r: CATS)\n", CStringValue);
    printf("////////////////////////////////////////\n\n");
}

void Test8_inputCString(void)
{
    char CStringValue[7] = { '\0' };

    printf("TEST #8: - Instructions:\n"
        "1) Enter the word 'dogs'  [ENTER]\n"
        "2) Enter the word 'HORSES' [ENTER]\n"
        ":>");

    inputCString(CStringValue, 5, 6);

    printf("////////////////////////////////////////\n");
    printf("TEST #8 r: ");
    printf("%s (expected r: HORSES)\n", CStringValue);
    printf("////////////////////////////////////////\n\n");
}

void Test9_displayFormattedPhone(void)
{
    char* Phone1 = NULL;
    char Phone2[10 + 1] = "";
    char Phone3[10 + 1] = "1";
    char Phone4[10 * 2] = "111333444499999999";
    char Phone5[10 + 1] = "111222444z";
    char Phone6[10 + 1] = "z112224444";
    char Phone7[10 + 1] = "4161114444";

    printf("////////////////////////////////////////\n");
    printf("TEST #9 r:\n");
    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone1);
    putchar('\n');

    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone2);
    putchar('\n');

    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone3);
    putchar('\n');

    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone4);
    putchar('\n');

    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone5);
    putchar('\n');

    printf("Expecting (___)___-____ => Your r: ");
    displayFormattedPhone(Phone6);
    putchar('\n');

    printf("Expecting (416)111-4444 => Your r: ");
    displayFormattedPhone(Phone7);
    printf("\n"
        "////////////////////////////////////////\n\n");
}

