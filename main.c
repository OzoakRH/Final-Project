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

void add_seminar() {
    Seminar s;
    printf("Enter participant name: ");
    scanf(" %[^\n]", s.participantName);
    printf("Enter seminar title: ");
    scanf(" %[^\n]", s.seminarTitle);
    printf("Enter seminar date (YYYY-MM-DD): ");
    scanf(" %[^\n]", s.seminarDate);
    printf("Enter number of participants: ");
    scanf("%d", &s.participantsCount);

    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s,%s,%s,%d\n", s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
    fclose(file);
    printf("Seminar added successfully!\n");
}

