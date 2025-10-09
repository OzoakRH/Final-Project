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
    printf("\n=== Add New Seminar ===\n");

    // ---- Input Name ----
    char first[50], middle[50], last[50];
    printf("Enter first name: ");
    scanf(" %[^\n]", first);
    getchar();

    printf("Enter middle name (or '-' if none): ");
    scanf(" %[^\n]", middle);
    getchar();

    printf("Enter last name: ");
    scanf(" %[^\n]", last);
    getchar();

    // Combine name
    if (strcmp(middle, "-") == 0 || strlen(middle) == 0)
        sprintf(s.participantName, "%s %s", first, last);
    else
        sprintf(s.participantName, "%s %s %s", first, middle, last);

    // ---- Seminar Topics ----
    printf("\n---Available Seminar Topics---\n");
    printf("1. Artificial Intelligence\n");
    printf("2. Data Science & Analytics\n");
    printf("3. Cybersecurity Fundamentals\n");
    printf("4. Cloud Computing & DevOps\n");
    printf("5. Digital Marketing\n");
    printf("6. Others\n");
    printf("-------------------------------\n");

    int topicChoice;
    printf("Select a topic (1-6): ");
    scanf("%d", &topicChoice);
    getchar();

    switch (topicChoice) {
        case 1: strcpy(s.seminarTitle, "Artificial Intelligence"); break;
        case 2: strcpy(s.seminarTitle, "Data Science & Analytics"); break;
        case 3: strcpy(s.seminarTitle, "Cybersecurity Fundamentals"); break;
        case 4: strcpy(s.seminarTitle, "Cloud Computing & DevOps"); break;
        case 5: strcpy(s.seminarTitle, "Digital Marketing"); break;
        case 6:
            printf("Enter custom seminar title: ");
            fgets(s.seminarTitle, sizeof(s.seminarTitle), stdin);
            s.seminarTitle[strcspn(s.seminarTitle, "\n")] = '\0';
            break;
        default:
            printf("Invalid choice. Defaulting to 'General Seminar'.\n");
            strcpy(s.seminarTitle, "General Seminar");
    }

    // ---- Date Validation ----
    int validDate = 0;
    do {
        printf("Enter seminar date (YYYY-MM-DD): ");
        scanf(" %[^\n]", s.seminarDate);
        getchar();

        if (strlen(s.seminarDate) == 10 &&
            s.seminarDate[4] == '-' &&
            s.seminarDate[7] == '-')
            validDate = 1;
        else
            printf("Invalid date format! Please use YYYY-MM-DD.\n");
    } while (!validDate);

    // ---- Participant Count ----
    printf("Enter number of participants: ");
    scanf("%d", &s.participantsCount);

    // ---- Save to CSV ----
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s,%s,%s,%d\n",
            s.participantName, s.seminarTitle,
            s.seminarDate, s.participantsCount);
    fclose(file);

    printf("\n Seminar added successfully!\n");
}



