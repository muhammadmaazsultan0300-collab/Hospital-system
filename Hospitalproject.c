#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOSPITALS 100
#define MAX_PATIENTS 200

// -----------------Structures of patient and hospitals-----------------
// -----------------Hospital Structure----------------
struct HospitalData
{
    char HospitalName[40];
    char hospitalCity[40];
    int ID;
    int availableBeds;
    float BedpriceperDay;
    float Rating; // 0-5 scale
    int Reviews;
};

// -----------------Patient Structure----------------
struct PatientData
{
    char PatientName[40];
    int Age;
    int PatientID;
    char Disease[50];
    int HospitalID;
};

struct HospitalData hospitals[MAX_HOSPITALS];
struct PatientData patients[MAX_PATIENTS];

int hospitalscount = 0; // for counting numbers
int patientscount = 0;

// -----------------Function Prototypes / Declarations-----------------
void loadHospitalData();
void saveHospitalData(); // save and load data
void loadPatientData();
void savePatientData();

void addhospitals(); // add and display hospitals
void displayhospitals();
void displayhospitalsbycity();

void addpatients(); // add and display patients
void displaypatients();

void sortbyBedprice(); // sorts
void sortbyBeds();
void sortbyhospitalName();
void sortbyRatingandReviews();

void deleteHospitalData();
void deletePatientData();
float discountprice(float price, float discount);

void loadingScreen(); // loading animation

// Function to check if a hospital ID already exists
int hospitalIDExists(int id)
{
    for (int i = 0; i < hospitalscount; i++)
    {
        if (hospitals[i].ID == id)
            return 1; // ID already exists
    }
    return 0; // ID is unique
}

// Function to check if a patient ID already exists
int patientIDExists(int id)
{
    for (int i = 0; i < patientscount; i++)
    {
        if (patients[i].PatientID == id)
            return 1; // ID already exists
    }
    return 0; // ID is unique
}

int main()
{
    printf("\n");
    loadingScreen();
    printf("\n");
    // =================for login page=================
    char name[30];
    char pass[8];
    int choice;
    printf("=================================================\n");
    printf("\tWelcome to Hospital Management System\n");
    printf("=================================================\n\n");
    printf("Please Choose an Option:\n");
    printf("-------------------------------------------------\n");
    printf("1. Sign in\t2. Sign up\n");
    printf("Choose for further process: ");
    scanf("%d", &choice);

    // ============for choice 1=============
    if (choice == 1)
    {
        printf("---------------Sign In Page-------------\n");
        printf("Enter username: ");
        scanf("%s", name);
        printf("Enter password: ");
        scanf("%s", pass);
        printf("Sign In Successfully!\n");
        printf("---------------------------------------\n");
    }

    // ============for choice 2=============
    else
    {
        printf("---------------Sign Up Page-------------\n");
        printf("Enter your first name: ");
        scanf("%s", name);
        printf("Enter your last name: ");
        scanf("%s", name);
        printf("Enter your username: ");
        scanf("%s", name);
        printf("Chose your password: ");
        scanf("%s", pass);
        printf("Sign Up Successfully!\n");
        printf("---------------------------------------\n");
    }

    loadHospitalData();
    loadPatientData();

    //================ MENU OF HOSPITAL===============
    do
    {
        printf("\n==============================================\n");
        printf("\tHospital Management System Menu\n");
        printf("==============================================\n\n");
        printf("----------------------------------------------\n");
        printf("\t1.Add Hospital Data\n");
        printf("\t2.Display Hospital \n");
        printf("\t3.Display Hospital BY City\n");
        printf("\t4.Add Patient Data\n");
        printf("\t5.Display Patient Data\n");
        printf("\t6.Sort By Beds\n");
        printf("\t7.Sort By Bed Price\n");
        printf("\t8.Sort By Hospital Name\n");
        printf("\t9.Sort By Rating and Reveiws\n");
        printf("\t10. Delete Hospital Data\n");
        printf("\t11. Delete Patient Data\n");
        printf("\t0.Exit\n");
        printf("----------------------------------------------\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        printf("----------------------------------------------\n");

        switch (choice)
        {
        case 1:
            addhospitals();
            break;
        case 2:
            displayhospitals();
            break;
        case 3:
            displayhospitalsbycity();
            break;
        case 4:
            addpatients();
            break;
        case 5:
            displaypatients();
            break;
        case 6:
            sortbyBeds();
            break;
        case 7:
            sortbyBedprice();
            break;
        case 8:
            sortbyhospitalName();
            break;
        case 9:
            sortbyRatingandReviews();
            break;
        case 10:
            deleteHospitalData();
            break;
        case 11:
            deletePatientData();
            break;
        case 0:
            saveHospitalData();
            savePatientData();
            printf("Data Saved Successfully.\n");
            printf("Exiting the Program. Goodbye!\n");
            break;

        default:
            printf("Invalid Choice!\n Please Try Again!\n");
            break;
        }
    } while (choice != 0);
    return 0;
}
// ===============file Handling to store data===============

//================loading data of hospitals==================
void loadHospitalData()
{
    FILE *fp = fopen("hospital.txt", "r");

    // If file does not exist, create it and return silently
    if (fp == NULL)
    {
        fp = fopen("hospital.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "0\n"); // no hospitals yet
            fclose(fp);
        }
        hospitalscount = 0;
        return;
    }

    fscanf(fp, "%d\n", &hospitalscount);

    for (int i = 0; i < hospitalscount; i++)
    {
        fscanf(fp, "%d\n", &hospitals[i].ID);
        fgets(hospitals[i].HospitalName, 40, fp);
        fgets(hospitals[i].hospitalCity, 40, fp);

        hospitals[i].HospitalName[strcspn(hospitals[i].HospitalName, "\n")] = 0;
        hospitals[i].hospitalCity[strcspn(hospitals[i].hospitalCity, "\n")] = 0;

        fscanf(fp, "%d\n", &hospitals[i].availableBeds);
        fscanf(fp, "%f\n", &hospitals[i].BedpriceperDay);
        fscanf(fp, "%f\n", &hospitals[i].Rating);
        fscanf(fp, "%d\n", &hospitals[i].Reviews);
    }

    fclose(fp);
}

//======writing and saving data of hospitals from count=============
void saveHospitalData()
{
    FILE *fp = fopen("hospital.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving hospital data!\n");
        return;
    }

    fprintf(fp, "%d\n", hospitalscount);

    for (int i = 0; i < hospitalscount; i++)
    {
        fprintf(fp, "%d\n%s\n%s\n%d\n%f\n%f\n%d\n",
                hospitals[i].ID,
                hospitals[i].HospitalName,
                hospitals[i].hospitalCity,
                hospitals[i].availableBeds,
                hospitals[i].BedpriceperDay,
                hospitals[i].Rating,
                hospitals[i].Reviews);
    }

    fclose(fp);
}

//========loading patient data==============
void loadPatientData()
{
    FILE *fp = fopen("patients.txt", "r");

    //  If file does not exist, create it and return silently
    if (fp == NULL)
    {
        fp = fopen("patients.txt", "w");
        if (fp != NULL)
        {
            fprintf(fp, "0\n"); // no patients yet
            fclose(fp);
        }
        patientscount = 0;
        return;
    }

    fscanf(fp, "%d\n", &patientscount);

    for (int i = 0; i < patientscount; i++)
    {
        fscanf(fp, "%d\n", &patients[i].PatientID);
        fgets(patients[i].PatientName, 40, fp);
        fscanf(fp, "%d\n", &patients[i].Age);
        fgets(patients[i].Disease, 50, fp);
        fscanf(fp, "%d\n", &patients[i].HospitalID);

        patients[i].PatientName[strcspn(patients[i].PatientName, "\n")] = 0;
        patients[i].Disease[strcspn(patients[i].Disease, "\n")] = 0;
    }

    fclose(fp);
}

//==========saving patients in file===========
void savePatientData()
{
    FILE *fp = fopen("patients.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving patient data!\n");
        return;
    }

    fprintf(fp, "%d\n", patientscount);

    for (int i = 0; i < patientscount; i++)
    {
        fprintf(fp, "%d\n%s\n%d\n%s\n%d\n",
                patients[i].PatientID,
                patients[i].PatientName,
                patients[i].Age,
                patients[i].Disease,
                patients[i].HospitalID);
    }

    fclose(fp);
}

//========adding hospitals===========
void addhospitals()
{

    if (hospitalscount >= MAX_HOSPITALS)
    {
        printf("Limit Reached!");
        return;
    }

    struct HospitalData h;
    int id;

    while (1)
    {
        printf("Enter Hospital ID: ");
        scanf("%d", &id);

        if (hospitalIDExists(id))
        {
            printf("ID already exists! Try again.\n");
            break;
        }
        else
        {
            break;
        }
    }

    h.ID = id;

    printf("Enter Hospital Details:\n");
    printf("===============================================\n");
    printf("Hospital Name: ");
    scanf(" %[^\n]", h.HospitalName);
    printf("Hospital City: ");
    scanf(" %[^\n]", h.hospitalCity);
    printf("Number of Available Beds: ");
    scanf("%d", &h.availableBeds);
    printf("Bed price per Day: ");
    scanf("%f", &h.BedpriceperDay);
    printf("Rating of Hospital: ");
    scanf("%f", &h.Rating);
    printf("Number Of Reviews: ");
    scanf("%d", &h.Reviews);
    printf("===============================================\n");

    hospitals[hospitalscount++] = h;
    saveHospitalData();
    printf("=================================================\n");
    printf(" \tHospital is added successfully.\n");
    printf("=================================================\n\n");
}

//======Display Hospital data========
void displayhospitals()
{
    float finalPrice;
    if (hospitalscount == 0)
    {
        printf("No Record Found!");
        return;
    }

    for (int i = 0; i < hospitalscount; i++)
    {
        printf("------------------------------------------------\n");
        printf("\tHospital:%d\n", i + 1);
        printf("\tName:%s\n", hospitals[i].HospitalName);
        printf("\tCity:%s\n", hospitals[i].hospitalCity);
        printf("\tHospital ID:%d\n", hospitals[i].ID);
        printf("\tAvailable Beds:%d\n", hospitals[i].availableBeds);

        printf("\tOriginal Bed Price: %.2f\n", hospitals[i].BedpriceperDay);
        printf("\tDiscount Applied: 10%%\n");
        printf("\tAfter discount Bed Price: %.2f\n", discountprice(hospitals[i].BedpriceperDay, 10));
        printf("\tRating of Hospital:%0.1f\n", hospitals[i].Rating);
        printf("\tNumber of Reviews:%d\n", hospitals[i].Reviews);

        printf("------------------------------------------------\n");
    }
}

//=====----Display Hospital By City------=========
void displayhospitalsbycity()
{
    if (hospitalscount == 0)
    {
        printf("No Record Found!\n");
        return;
    }

    char city[40];
    int found = 0;

    printf("Enter Your City Name: ");
    scanf(" %[^\n]", city);

    printf("\nCity Name: %s\n", city);
    printf("----------------------------------------\n");

    for (int i = 0; i < hospitalscount; i++)
    {
        if (strcmp(hospitals[i].hospitalCity, city) == 0)
        {
            printf("Hospital Name        : %s\n", hospitals[i].HospitalName);
            printf("Hospital ID          : %d\n", hospitals[i].ID);
            printf("Available Beds       : %d\n", hospitals[i].availableBeds);
            printf("Hospital Rating      : %.1f\n", hospitals[i].Rating);
            printf("Bed Price per Day    : %.2f\n", hospitals[i].BedpriceperDay);
            printf("----------------------------------------\n");
            found = 1;
        }
    }

    if (!found)
    {
        printf("No hospitals found in this city.\n");
    }
}

//=========Adding patient in file==========

void addpatients()
{

    struct PatientData p;
    int id;

    while (1)
    {
        printf("Enter Patient ID: ");
        scanf("%d", &id);

        if (patientIDExists(id))
            printf("❌ Patient ID already exists! Enter a unique ID.\n");
        else
            break;
    }

    p.PatientID = id;

    if (patientscount >= MAX_PATIENTS)
    {
        printf("limit is Reached!\n");
        return;
    }
    printf("Enter Patient Details:\n");
    printf("===============================================\n");
    printf("Enter Patient Name: ");
    scanf("%s", p.PatientName);
    printf("Enter patient Disease: ");
    scanf(" %[^\n]", p.Disease);
    printf("Enter patient Age: ");
    scanf("%d", &p.Age);
    printf("Enter Addmitted Hospital ID: ");
    scanf("%d", &p.HospitalID);
    printf("===============================================\n");

    patients[patientscount++] = p;
    savePatientData();
    printf("-----------------------------------------------------\n");
    printf("\tPatient Data is added Successfully.\n");
    printf("-----------------------------------------------------\n\n");
}

//============Display Patient============
void displaypatients()
{
    if (patientscount == 0)
    {
        printf("No patient's record!\n");
        return;
    }

    for (int i = 0; i < patientscount; i++)
    {
        printf("------------------------------------------------\n");
        printf("\tPatient Name:%s\n", patients[i].PatientName);
        printf("\tPatient ID:%d\n", patients[i].PatientID);
        printf("\tPatient Age:%d\n", patients[i].Age);
        printf("\tPatient Disease:%s\n", patients[i].Disease);
        printf("\tAdmitted Hospital ID:%d\n", patients[i].HospitalID);

        for (int j = 0; j < hospitalscount; j++)
        {
            if (hospitals[j].ID == patients[i].HospitalID)
            {
                printf("\tHospital Name      : %s\n", hospitals[j].HospitalName);

                float finalPrice = hospitals[j].BedpriceperDay;

                printf("\tHospital Name      : %s\n", hospitals[j].HospitalName);

                printf("\tOriginal Bed Price : %.2f\n", hospitals[j].BedpriceperDay);
                printf("\tDiscount Applied   : 10%%\n");
                printf("\tFinal Bed Price    : %.2f\n", finalPrice);

                printf("------------------------------------------------\n");
            }

            printf("------------------------------------------------\n");
        }
    }
}

//=========Sort by Bed Price===========

void sortbyBedprice()
{
    for (int i = 0; i < hospitalscount - 1; i++)
    {
        for (int j = i + 1; j < hospitalscount; j++)
        {
            if (hospitals[i].BedpriceperDay < hospitals[j].BedpriceperDay)
            {
                struct HospitalData temp = hospitals[i];
                hospitals[i] = hospitals[j];
                hospitals[j] = temp;
            }
        }
    }
    displayhospitals();
}

//============Sort by Beds==========
void sortbyBeds()
{

    for (int i = 0; i < hospitalscount - 1; i++)
    {

        for (int j = i + 1; j < hospitalscount; j++)
        {
            if (hospitals[i].availableBeds < hospitals[j].availableBeds)
            {
                struct HospitalData temp = hospitals[i];
                hospitals[i] = hospitals[j];
                hospitals[j] = temp;
            }
        }
    }

    displayhospitals();
}

//===============Sort BY Hospital Name==================
void sortbyhospitalName()
{
    for (int i = 0; i < hospitalscount - 1; i++)
    {
        for (int j = i + 1; j < hospitalscount; j++)
        {
            if (strcmp(hospitals[i].HospitalName, hospitals[j].HospitalName) > 0)
            {
                struct HospitalData temp = hospitals[i];
                hospitals[i] = hospitals[j];
                hospitals[j] = temp;
            }
        }
    }
    displayhospitals();
}

//=============Sort By Rating and Reviews==================
void sortbyRatingandReviews()
{
    for (int i = 0; i < hospitalscount - 1; i++)
    {
        for (int j = i + 1; j < hospitalscount; j++)
        {
            if (hospitals[i].Rating == hospitals[j].Rating || hospitals[i].Rating < hospitals[j].Rating && hospitals[i].Reviews < hospitals[j].Reviews)
            {
                struct HospitalData temp = hospitals[i];
                hospitals[i] = hospitals[j];
                hospitals[j] = temp;
            }
        }
    }

    displayhospitals();
}

//=============Delete Hospital Data==================
void deleteHospitalData()
{
    int id;
    printf("Enter Hospital ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < hospitalscount; i++)
    {
        if (hospitals[i].ID == id)
        {
            found = 1;
            for (int j = i; j < hospitalscount - 1; j++)
            {
                hospitals[j] = hospitals[j + 1];
            }
            hospitalscount--;
            saveHospitalData();
            printf("========================================================\n");
            printf("\tHospital with ID %d deleted successfully.\n", id);
            printf("========================================================\n");
            break;
        }
    }

    if (!found)
    {
        printf("=================================================\n");
        printf("\tHospital with ID %d not found.\n", id);
        printf("=================================================\n");
    }
}

//=============Delete Patient Data==================
void deletePatientData()
{
    int id;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < patientscount; i++)
    {
        if (patients[i].PatientID == id)
        {
            found = 1;
            for (int j = i; j < patientscount - 1; j++)
            {
                patients[j] = patients[j + 1];
            }
            patientscount--;
            savePatientData();
            printf("=======================================================\n");
            printf("\tPatient with ID %d deleted successfully.\n", id);
            printf("=======================================================\n");
            break;
        }
    }

    if (!found)
    {
        printf("=================================================\n");
        printf("\tPatient with ID %d not found.\n", id);
        printf("=================================================\n");
    }
}

//=============Loading Animation==================
void loadingScreen()
{
    printf("\n\n");
    printf("\tLoading ");
    for (int i = 0; i <= 6; i++)
    {
        for (long int j = 0; j < 100000000; j++)
            ;
        printf("*");
    }
    printf("\n");
}

float discountprice(float price, float discount)
{
    return price - (price * discount / 100);
}
