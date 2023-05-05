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



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

#include "clinic.h"

void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


void menuMain(struct ClinicData* data)
{
    int selection;

    do
    {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}


void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}


void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do
    {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


void displayAllPatients(const struct Patient patient[], int max, int fmt)
{

    int i;
    int flag = 0;
    
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
         
            flag = 1;
       
            break;
        }
    }
    if (flag == 0)
    {
        printf("*** No records found ***\n");
    }
    else
    {
  
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
          
            if (patient[i].patientNumber != 0)
                displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');
}



void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
       
        selection = inputIntRange(0, 2);
        putchar('\n');
   
        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection);
}


void addPatient(struct Patient patient[], int max)
{
    int i;
    int freeIndex;
    int flag = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            flag = 1;
            freeIndex = i;
        
            break;
        }
    }
  
    if (flag == 0)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }

    else
    {
        patient[freeIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[freeIndex]);
        printf("*** New patient record added ***\n");
    }
    putchar('\n');
}


void editPatient(struct Patient patient[], int max)
{

    printf("Enter the patient number: ");
    int num = inputInt();
  
    int index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');
  
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
      
        menuPatientEdit(&patient[index]);
    }
}


void removePatient(struct Patient patient[], int max)
{
  
    printf("Enter the patient number: ");
    int num = inputInt();

    int index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');
   
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)\n", patient[index].phone.description);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        char answer;
        answer = inputCharOption("yn");
        if (answer == 'n')
        {
            printf("Operation aborted.\n");
        }
        else
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n");
        }
    }
    putchar('\n');
}



void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
   
    printf("Search by patient number: ");
    int num = inputInt();
    
    int index = findPatientIndexByPatientNum(num, patient, max);
    putchar('\n');
 
    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');

}


void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNum[11];
    
    printf("Search by phone number: ");
    inputCString(phoneNum, 10, 10);
    putchar('\n');
    int flag = 0;
    int i;
    for (i = 0; i < max; i++)
    {
      
        if (strcmp(phoneNum, patient[i].phone.number) == 0)
        {
            flag = 1;
            break;
        }
    }
    displayPatientTableHeader();
    if (flag == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    else
    {
        for (i = 0; i < max; i++)
        {
         
            if (strcmp(phoneNum, patient[i].phone.number) == 0)
                displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    putchar('\n');
}


int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int next = -1;
    
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > next)
        {
            next = patient[i].patientNumber;
        }
    }

    ++next;
    return next;

}


int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;
 
    int ret = -1;
  
    for (i = 0; i < max; i++)
    {
 
        if (patient[i].patientNumber == patientNumber)
        {
            ret = i;
            break;
        }
    }
    return ret;
}



void inputPatient(struct Patient* patient)
{
   
    printf("Patient Data Input\n"
        "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&(patient->phone));
}



void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n"
        "-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    if (selection == 1)
    {
        printf("Contact: ");
        puts("CELL");
        strcpy(phone->description, "CELL");
    }
    if (selection == 2)
    {
        printf("Contact: ");
        puts("HOME");
        strcpy(phone->description, "HOME");
    }
    if (selection == 3)
    {
        printf("Contact: ");
        puts("WORK");
        strcpy(phone->description, "WORK");
    }
    if (selection == 4)
    {
        strcpy(phone->description, "TBD");
    }
    else
    {
        printf("Number : ");
        inputCString(phone->number, 10, 10);
        putchar('\n');
    }
}