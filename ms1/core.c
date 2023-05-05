

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void clearInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ;
    }
}


void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}
int inputInt()
{

    int result = -1;
    char nextChar = '\0';
    int keepgoing = 1;
    do
    {
        scanf("%d%c", &result, &nextChar);
        if (nextChar != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else
        {
            keepgoing = 0;
        }

    } while (keepgoing);
    return result;
}

int inputIntPositive()
{
    int result = -1;
    do
    {
        result = inputInt();
    } while (result < 0 && printf("ERROR! Value must be > 0: "));
    return result;
}

int inputIntRange(int min, int max)
{
    int result = min - 1;
    do
    {
        result = inputInt();

    } while ((result < min || result > max) && printf("ERROR! Value must be between %d and %d inclusive: ", min, max));
    return result;
}

char inputCharOption(const char* cString)
{
    char result = '\0';
    char nextChar = '\0';
    int i = 0;
    int length = 0;
    for (length = 1; cString[length]; length++)
        ;
    int keepgoing = 1;
    do
    {
        scanf("%c%c", &result, &nextChar);

        if (nextChar == '\n')
        {
            for (i = 0; i < length && keepgoing; i++)
                if (cString[i] == result)
                    keepgoing = 0;
        }

    } while (keepgoing && printf("ERROR: Character must be one of [%s]: ", cString));

    return result;
}

void inputCString(char* cString, int min, int max)
{
    char largeInput[100] = { '\0' };
    int done = 0;
    int i = 0;
    int j = 0;
    do
    {
        scanf("%99[^\n]%*c", largeInput);
        for (i = 1; largeInput[i]; i++)
            ;
        if (min == max)
        {
            if (i == min)
            {
                for (j = 0; largeInput[j]; cString[j] = largeInput[j], j++)
                    ;
                cString[j] = '\0';
                done = 1;
            }
        }
        else
        {
            if (i >= min && i <= max)
            {
                for (j = 0; largeInput[j]; cString[j] = largeInput[j], j++)
                    ;
                cString[j] = '\0';
                done = 1;
            }
        }
        if (!done)
        {
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (min == 0 || i > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }

    } while (!done);
}
void displayFormattedPhone(const char* cString)
{
    int isValid = 1;
    int i = 0;
    if (cString != NULL)
    {
        for (i = 0; cString[i] && isValid; i++)
        {

            if (cString[i] < 48 || cString[i] > 57)
            {
                isValid = 0;
            }
        }
    }
    if (isValid && i == 10)
    {
        printf("(");
        for (i = 0; i < 3; i++)
            printf("%c", cString[i]);
        printf(")");
        for (i = 3; i < 6; i++)
            printf("%c", cString[i]);
        printf("-");
        for (i = 6; i < 10; i++)
            printf("%c", cString[i]);
    }
    else
    {
        printf("(___)___-____");
    }
}