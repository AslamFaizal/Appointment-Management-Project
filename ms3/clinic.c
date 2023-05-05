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
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n");
    printf("----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM) {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->patient_name, patient->patient_number);
        displayFormattedPhone(patient->patient_phone.number);
        printf(" (%s)\n", patient->patient_phone.description);
    }
    else {
        printf("%05d %-15s ", patient->patient_number, patient->patient_name);
        displayFormattedPhone(patient->patient_phone.number);
        printf(" (%s)\n", patient->patient_phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient, const struct Appointment* appointment, int includeDateField)
{
    if (includeDateField) {
        printf("%04d-%02d-%02d ", appointment->date.year, appointment->date.month, appointment->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appointment->time.hour, appointment->time.min, patient->patient_number, patient->patient_name);

    displayFormattedPhone(patient->patient_phone.number);

    printf(" (%s)\n", patient->patient_phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* clinic)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n");
        printf("=========================\n");
        printf("1) PATIENT     Management\n");
        printf("2) APPOINTMENT Management\n");
        printf("-------------------------\n");
        printf("0) Exit System\n");
        printf("-------------------------\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        switch (selection) {
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
            menuPatient(clinic->patients, clinic->maxPatient);
            break;
        case 2:
            menuAppointment(clinic);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n");
        printf("=========================\n");
        printf("1) VIEW   Patient Data\n");
        printf("2) SEARCH Patients\n");
        printf("3) ADD    Patient\n");
        printf("4) EDIT   Patient\n");
        printf("5) REMOVE Patient\n");
        printf("-------------------------\n");
        printf("0) Previous menu\n");
        printf("-------------------------\n");
        printf("Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');

        switch (selection) {
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patient_number, patient->patient_name);

        displayFormattedPhone(patient->patient_phone.number);

        printf("\n");
        printf("-------------------------\n");
        printf("0) Previous menu\n");
        printf("-------------------------\n");
        printf("Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1) {
            printf("Name  : ");
            inputCString(patient->patient_name, 1, NAME_LEN, NULL);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2) {
            inputPhoneData(&patient->patient_phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;
    do {
        printf("Appointment Management\n");
        printf("==============================\n");
        printf("1) VIEW   ALL Appointments\n");
        printf("2) VIEW   Appointments by DATE\n");
        printf("3) ADD    Appointment\n");
        printf("4) REMOVE Appointment\n");
        printf("------------------------------\n");
        printf("0) Previous menu\n");
        printf("------------------------------\n");
        printf("Selection: ");

        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection) {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointment, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointment, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    int displayedNo = 0;
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patient_number != 0)
        {
            displayPatientData(&patient[i], fmt);
            displayedNo++;
        }
    }
    if (displayedNo == 0)
    {
        printf("*** No records found ***");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = -1;
    do
    {
        printf("Search Options\n==========================\n1) By patient number\n2) By phone number\n..........................\n0) Previous menu\n..........................\nSelection: ");
        selection = inputInt(0, 2);
        putchar('\n');
        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
        }
        if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();
        }

    } while (selection != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int i = 0;
    int index = -1;
    for (i = 0; i < max && index == -1; i++)
    {
        if (patient[i].patient_number == 0)
        {
            index = i;
        }
    }
    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[index].patient_number = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patientNum = inputInt();
    putchar('\n');
    int index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patientNum = inputInt();

    int index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index == -1)
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    else
    {
        putchar('\n');
        displayPatientData(&patient[index], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        int result = inputCharOption("yn");
        if (result == 'y')
        {
            patient[index].patient_number = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}

int dateGreat(const struct Date* d, const struct Time* t)
{
    return d->year * 100000 + d->month * 10000 + d->day * 1000 + t->hour * 100 + t->min; // this
}
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void sortAppointments(struct ClinicData* value)
{
    int i, j;
    struct Appointment temp;

    for (i = value->maxAppointments - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (dateGreat(&value->appointment[j].date, &value->appointment[j].time) > dateGreat(&value->appointment[j + 1].date, &value->appointment[j + 1].time) && value->appointment[j].patient_number > 0 && value->appointment[j + 1].patient_number > 0) {
                temp = value->appointment[j];
                value->appointment[j] = value->appointment[j + 1];
                value->appointment[j + 1] = temp;
            }
        }
    }
}

int isEqual(const struct Date* d1, const struct Date* d2)
{
    return d1->year == d2->year && d1->month == d2->month && d1->day == d2->day;
}

void viewAllAppointments(struct ClinicData* value) {
    struct Date d;
    displayScheduleTableHeader(&d, 1);
    sortAppointments(value);
    int i = 0;

    for (i = 0; i < value->maxAppointments; i++) {
        if (value->appointment[i].patient_number > 0) {
            displayScheduleData(&value->patients[findPatientIndexByPatientNum(value->appointment[i].patient_number, value->patients, value->maxPatient)], &value->appointment[i], 1);
        }
    }
    putchar('\n');
}
// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* value) {
    struct Date d;
    int i = 0;
    sortAppointments(value);
    printf("Year        : ");
    d.year = inputIntPositive();

    int febdays = d.year % 4 == 0 ? 29 : 28;
    int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    printf("Month (1-12): ");
    d.month = inputIntRange(1, 12);

    printf("Day (1-%d)  : ", months[d.month - 1]);
    d.day = inputIntRange(1, months[d.month - 1]);
    putchar('\n');

    displayScheduleTableHeader(&d, 0);
    for (i = 0; i < value->maxAppointments; i++) {
        if (value->appointment[i].patient_number > 0) {
            if (isEqual(&d, &value->appointment[i].date)) {
                displayScheduleData(&value->patients[findPatientIndexByPatientNum(value->appointment[i].patient_number, value->patients, value->maxPatient)], &value->appointment[i], 0);
            }
        }
    }
    putchar('\n');
}


// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* patients, int maxPatient) {
    int Date_booked = 0;
    int Time_booked = 0;
    int number = 0;
    int Appointment_same = 0;
    int i = 0;
    int final = 0;
    int Appointment_available = 0;
    int done = 0;
    int patient_done = 0;

    struct Date d;
    struct Time t;

    for (i = 0; i < maxAppointments && !Appointment_available; i++) {
        if (appointment[i].patient_number < 1) {
            Appointment_available = i;
        }
    }
    while (!done && Appointment_available) {
        while (!patient_done) {
            printf("Patient Number: ");
            number = inputIntPositive();
            int result = findPatientIndexByPatientNum(number, patients, maxPatient);

            if (result > -1) {
                patient_done = 1;
            }
            else {
                printf("Invalid Entry, try again: \n");
            }
        }

        while (!Date_booked) {
            printf("Year        : ");
            d.year = inputIntPositive();
            int febdays = d.year % 4 == 0 ? 29 : 28;
            int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

            printf("Month (1-12): ");
            d.month = inputIntRange(1, 12);

            printf("Day (1-%d)  : ", months[d.month - 1]);
            d.day = inputIntRange(1, months[d.month - 1]);

            Date_booked = 1;
        }

        while (!Time_booked) {
            final = 0;
            printf("Hour (0-23)  : ");
            t.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            t.min = inputIntRange(0, 59);

            if (t.hour == TIME_END_HOUR) {
                if (t.min != 0) {
                    final = 1;
                }
            }

            if (t.hour >= TIME_START_HOUR && t.hour <= TIME_END_HOUR && (t.min % TIME_INTERVAL == 0) && !final) {
                Time_booked = 1;
            }
            else {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", TIME_START_HOUR, TIME_END_HOUR, TIME_INTERVAL);
            }
        }
        Appointment_same = 0;

        for (i = 0; i < maxAppointments && !Appointment_same; i++) {
            if (isEqual(&d, &appointment[i].date) && appointment[i].time.hour == t.hour && appointment[i].time.min == t.min) {
                Appointment_same = 1;
            }
        }

        if (Appointment_same) {
            printf("\nERROR: Appointment timeslot is not available!\n\n");
            Date_booked = 0;
            Time_booked = 0;
        }
        else {
            done = 1;
            appointment[Appointment_available].date = d;
            appointment[Appointment_available].time = t;
            appointment[Appointment_available].patient_number = number;
            printf("\n*** Appointment scheduled! ***\n\n");
        }
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int i = 0;
    printf("Patient Number: ");
    int number = inputIntPositive();
    int result = findPatientIndexByPatientNum(number, patients, maxPatient);
    if (result == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        struct Date d;
        printf("Year        : ");
        d.year = inputIntPositive();
        int febdays = d.year % 4 == 0 ? 29 : 28;

        int months[12] = { 31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        printf("Month (1-12): ");

        d.month = inputIntRange(1, 12);
        printf("Day (1-%d)  : ", months[d.month - 1]);
        d.day = inputIntRange(1, months[d.month - 1]);

        int found = 0;
        int newindex = 0;
        for (i = 0; i < maxAppointments && !found; i++) {
            if ((appointment[i].patient_number == number) && isEqual(&d, &appointment[i].date)) {
                found = 1;
                newindex = i;
                // printf("the index is : %d\n", i);
            }
            // printf("value of i is now %d\n", i);
        }
        putchar('\n');
        displayPatientData(&patients[result], FMT_FORM);
        printf("Are you sure you want to remove this appointment (y,n): ");
        char option = inputCharOption("yn");

        if (option == 'y') {
            appointment[newindex].patient_number = 0;
            appointment[newindex].date.year = 0;
            appointment[newindex].date.month = 0;
            appointment[newindex].date.day = 0;
            printf("\nAppointment record has been removed!\n");
        }
        else {
            printf("\n Operation Aborted!\n");
        }

        putchar('\n');
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    printf("Search by patient number: ");
    int patient_number = inputInt();
    putchar('\n');

    int patient_index = findPatientIndexByPatientNum(patient_number, patient, max);
    if (patient_index == -1) {
        printf("*** No records found ***\n");
    }
    else {
        displayPatientData(&patient[patient_index], FMT_FORM);
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    char phone_entry[11] = { 0 };
    int displayed_no = 0;
    int i = 0;

    printf("Search by phone number: ");
    inputCString(phone_entry, 10, 10, NULL);
    putchar('\n');

    displayPatientTableHeader();

    for (i = 0; i < max; i++) {
        if (strcmp(phone_entry, patient[i].patient_phone.number) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);
            displayed_no++;
        }
    }

    if (displayed_no == 0) {
        printf("\n*** No records found ***\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int i = 0;
    int maximum = patient[i].patient_number;


    for (i = 1; i < max; i++) {
        if (patient[i].patient_number > maximum)
            maximum = patient[i].patient_number;
    }
    return maximum + 1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patient_no, const struct Patient patient[], int max) {
    int result = -1;
    int i = 0;

    for (i = 0; i < max && result == -1; i++) {
        if (patient_no == patient[i].patient_number) {
            result = i;
        }
    }

    return result;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\nName  : ", patient->patient_number);
    inputCString(patient->patient_name, 1, NAME_LEN, NULL);
    putchar('\n');
    inputPhoneData(&patient->patient_phone);
    printf("*** New patient record added ***\n\n");
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\nSelection: ");

    int selection = inputInt(1, 4);
    putchar('\n');

    if (selection == 4) {
        strcpy(phone->description, "TBD");
        phone->number[0] = 0;
    }
    else {
        if (selection == 1) {
            strcpy(phone->description, "CELL");
        }

        if (selection == 2) {
            strcpy(phone->description, "HOME");
        }

        if (selection == 3) {
            strcpy(phone->description, "WORK");
        }

        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, 10, NULL);

        putchar('\n');
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    int read = 0;
    if (fp != NULL) {
        while (!feof(fp) && read < max) {
            fscanf(fp, "%d|%29[^|]|%4[^|]|", &patients[read].patient_number, patients[read].patient_name, patients[read].patient_phone.description);

            if (!(strcmp(patients[read].patient_phone.description, "TBD") == 0)) {
                fscanf(fp, "%[^\n]%*c", patients[read].patient_phone.number);
            }
            read++;
        }
        fclose(fp);
    }
    return read;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appointment[], int max) {

    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    int read = 0;
    if (fp != NULL) {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appointment[read].patient_number, &appointment[read].date.year, &appointment[read].date.month, &appointment[read].date.day, &appointment[read].time.hour, &appointment[read].time.min) == 6 && read < max) {
            read++;
        }
        fclose(fp);
    }
    return read;
}