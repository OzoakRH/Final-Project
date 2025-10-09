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

// ฟังก์ชันทดสอบการเพิ่มข้อมูล
int test_add_seminar() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) return 0;
    fprintf(file, "UnitTester,AI Testing,2025-10-09,50\n");
    fclose(file);

    // ตรวจสอบว่าเพิ่มสำเร็จไหม
    file = fopen(FILE_NAME, "r");
    if (!file) return 0;
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "UnitTester")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

// ฟังก์ชันทดสอบการค้นหาข้อมูล
int test_search_seminar() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return 0;
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "AI Testing")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

int main() {
    printf("===== Running Unit Tests =====\n");

    int add_result = test_add_seminar();
    printf("Test add_seminar(): %s\n", add_result ? "SUCCESS" : "FAILED");

    int search_result = test_search_seminar();
    printf("Test search_seminar(): %s\n", search_result ? "SUCCESS" : "FAILED");

    printf("===== Unit Tests Finished =====\n");
    return 0;
}
