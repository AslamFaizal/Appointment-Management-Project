/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name   : Faizal Aslam
Student ID# : 152121216
Email       : faizal-aslam@myseneca.ca
Section     : IPC144 ZEE

Authenticity Declaration :
I declare this submission is the r of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
* ***************************************************************************
*/




// +---------------------------------------------------------+
// | *** The contents of this file is NOT to be modified *** |
// +---------------------------------------------------------+
//
// ############################################################################


#include <stdio.h>

// include the user library "clinic" where the data types are declared
#include "clinic.h"

#define MAX_PETS 7

int main(void)
{
    struct Patient pets[MAX_PETS] = {
        {1024, "Shaggy Yanson", {"CELL","3048005191"} },
        {1032, "Puglsey Yanson", {"CELL","3048005191"} },
        {1040, "Beans Maulin", {"HOME","3649155831"} },
        {1048, "Banjo Codi", {"TBA",{'\0'}} },
        {1056, "Rover Davidov", {"WORK","7934346809"} }
    };
    struct ClinicData data = { pets, MAX_PETS };

    // Entry point to the application logic:
    menuMain(&data);

    return 0;
}