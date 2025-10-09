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

void run_e2e_test() {
    printf("===== Running End-to-End Test =====\n");

    // 1️⃣ เพิ่มข้อมูล
    FILE *file = fopen(FILE_NAME, "a");
    fprintf(file, "E2E_User,Deep Learning 101,2025-10-15,80\n");
    fclose(file);
    printf("[Add] Added E2E_User successfully.\n");

    // 2️⃣ ค้นหา
    file = fopen(FILE_NAME, "r");
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "E2E_User")) {
            printf("[Search] Found record: %s", line);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("[Search] ❌ Record not found after adding.\n");
        return;
    }

    // 3️⃣ แก้ไขข้อมูล (จำลอง)
    FILE *temp = fopen("temp.csv", "w");
    file = fopen(FILE_NAME, "r");
    fgets(line, sizeof(line), file);
    fprintf(temp, "%s", line);
    while (fgets(line, sizeof(line), file)) {
        Seminar s;
        sscanf(line, "%[^,],%[^,],%[^,],%d",
               s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);
        if (strcmp(s.participantName, "E2E_User") == 0) {
            strcpy(s.seminarTitle, "Deep Learning Advanced");
            s.participantsCount = 99;
        }
        fprintf(temp, "%s,%s,%s,%d\n",
                s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);
    printf("[Edit] Edited E2E_User successfully.\n");

        // 4️⃣ ลบข้อมูล
    file = fopen(FILE_NAME, "r");
    temp = fopen("temp.csv", "w");
    fgets(line, sizeof(line), file);
    fprintf(temp, "%s", line);
    while (fgets(line, sizeof(line), file)) {
        Seminar s;
        sscanf(line, "%[^,],%[^,],%[^,],%d",
           s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);
    if (strcmp(s.participantName, "E2E_User") != 0) {  // ✅ เทียบตรงๆ
        fprintf(temp, "%s,%s,%s,%d\n",
                s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
    }
    }
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);
    printf("[Delete] Deleted E2E_User successfully.\n");

        // 5️⃣ ตรวจสอบว่าลบจริงไหม
    file = fopen(FILE_NAME, "r");
    found = 0;
    while (fgets(line, sizeof(line), file)) {
    // ตัด newline
        line[strcspn(line, "\r\n")] = 0;
        if (strstr(line, "E2E_User"))
            found = 1;
    }
    fclose(file);
    printf(found ? "[Check]  Delete failed.\n" : "[Check]  Delete verified.\n");
    }

int main() {
    run_e2e_test();
    return 0;
}
