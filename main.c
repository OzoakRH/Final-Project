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

