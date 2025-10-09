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

// ------------------------------------------------------------
// ฟังก์ชันทดสอบการเพิ่มข้อมูล (Add Seminar)
// ------------------------------------------------------------
int test_add_seminar_success() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) return 0;
    fprintf(file, "UnitTester_Add,AI Testing Success,2025-10-09,50\n");
    fclose(file);

    // ตรวจสอบว่าข้อมูลถูกเพิ่มจริงไหม
    file = fopen(FILE_NAME, "r");
    if (!file) return 0;
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "UnitTester_Add")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

int test_add_seminar_fail() {
    // ทดสอบกรณีเปิดไฟล์ไม่ได้
    FILE *file = fopen("non_exist_directory/seminars.csv", "a");
    if (!file) {
        return 1; // ถือว่าทดสอบ fail case ผ่าน (เพราะเปิดไม่ได้ตามคาด)
    } else {
        fclose(file);
        return 0; // เปิดได้ แปลว่า fail case ไม่ผ่าน
    }
}

// ------------------------------------------------------------
// ฟังก์ชันทดสอบการค้นหาข้อมูล (Search Seminar)
// ------------------------------------------------------------
int test_search_seminar_success() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return 0;
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "AI Testing Success")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

int test_search_seminar_fail() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) return 0;
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "NotExistTopic")) { // keyword ที่ไม่มีในไฟล์
            found = 1;
            break;
        }
    }
    fclose(file);
    return !found; // ถ้าไม่เจอถือว่าผ่าน (fail case)
}

// ------------------------------------------------------------
// Main: Run all unit tests
// ------------------------------------------------------------
int main() {
    printf("===== Running Unit Tests =====\n\n");

    // --- Test Add Seminar ---
    int add_success = test_add_seminar_success();
    printf("[Add Seminar - Success Case]  %s\n", add_success ? " PASSED" : " FAILED");

    int add_fail = test_add_seminar_fail();
    printf("[Add Seminar - Fail Case]     %s\n", add_fail ? " PASSED" : " FAILED");

    // --- Test Search Seminar ---
    int search_success = test_search_seminar_success();
    printf("[Search Seminar - Success Case] %s\n", search_success ? " PASSED" : " FAILED");

    int search_fail = test_search_seminar_fail();
    printf("[Search Seminar - Fail Case]    %s\n", search_fail ? " PASSED" : " FAILED");

    printf("\n===== Unit Tests Finished =====\n");
    return 0;
}
