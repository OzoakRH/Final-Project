#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "seminars.csv"

typedef struct {
    char participantName[100];
    char seminarTitle[100];
    char seminarDate[20];
    int participantsCount;
} Seminar;

void open_file() {
    FILE *file = fopen(FILE_NAME, "a+");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "ParticipantName,SeminarTitle,SeminarDate,ParticipantsCount\n");
    }
    fclose(file);
}

// การเพิ่มผู้เข้าร่วมสัมมนา
void add_seminar() {
    Seminar s;
    char firstName[50], middleName[50], lastName[50];
    int validDate = 0;

    // --- Get Name Parts ---
    printf("Enter first name: ");
    scanf(" %[^\n]", firstName);
    printf("Enter middle name (or press Enter / '-' if none): ");
    getchar(); // Clear buffer for safety
    fgets(middleName, sizeof(middleName), stdin);
    middleName[strcspn(middleName, "\n")] = '\0'; // Remove newline
    if (strlen(middleName) == 0) strcpy(middleName, "-");
    printf("Enter last name: ");
    scanf(" %[^\n]", lastName);

    snprintf(s.participantName, sizeof(s.participantName), "%s %s %s", firstName, middleName, lastName);

    // --- Get Seminar Info ---
    printf("Enter seminar title: ");
    scanf(" %[^\n]", s.seminarTitle);

    // --- Validate Date Format ---
    do {
        printf("Enter seminar date (YYYY-MM-DD): ");
        scanf(" %[^\n]", s.seminarDate);

        if (strlen(s.seminarDate) != 10 ||
            s.seminarDate[4] != '-' ||
            s.seminarDate[7] != '-' ||
            !isdigit(s.seminarDate[0]) || !isdigit(s.seminarDate[1]) ||
            !isdigit(s.seminarDate[2]) || !isdigit(s.seminarDate[3]) ||
            !isdigit(s.seminarDate[5]) || !isdigit(s.seminarDate[6]) ||
            !isdigit(s.seminarDate[8]) || !isdigit(s.seminarDate[9])) {
            printf("Invalid date format! Please use YYYY-MM-DD.\n");
        } else {
            validDate = 1;
        }
    } while (!validDate);

    printf("Enter number of participants: ");
    scanf("%d", &s.participantsCount);

    // --- Write to CSV ---
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s,%s,%s,%d\n", s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
    fclose(file);

    printf("Seminar added successfully!\n");
}



