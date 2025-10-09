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

//ฟังชั่น เพิ่มข้อมูลผู้สัมมนา
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
    int topicChoice;
    int validChoice = 0;

    do {
        printf("\n--- Available Seminar Topics ---\n");
        printf("1. Artificial Intelligence\n");
        printf("2. Data Science & Analytics\n");
        printf("3. Cybersecurity Fundamentals\n");
        printf("4. Cloud Computing & DevOps\n");
        printf("5. Digital Marketing\n");
        printf("6. Others\n");
        printf("--------------------------------\n");
        printf("Select a topic (1-6): ");

        if (scanf("%d", &topicChoice) != 1) {
            printf("Invalid input! Please enter a number between 1 and 6.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); // clear newline
        switch (topicChoice) {
            case 1: strcpy(s.seminarTitle, "Artificial Intelligence"); validChoice = 1; break;
            case 2: strcpy(s.seminarTitle, "Data Science & Analytics"); validChoice = 1; break;
            case 3: strcpy(s.seminarTitle, "Cybersecurity Fundamentals"); validChoice = 1; break;
            case 4: strcpy(s.seminarTitle, "Cloud Computing & DevOps"); validChoice = 1; break;
            case 5: strcpy(s.seminarTitle, "Digital Marketing"); validChoice = 1; break;
            case 6:
                printf("Enter custom seminar title: ");
                fgets(s.seminarTitle, sizeof(s.seminarTitle), stdin);
                s.seminarTitle[strcspn(s.seminarTitle, "\n")] = '\0';
                validChoice = 1;
                break;
            default:
                printf("Invalid choice! Please select between 1-6.\n");
                validChoice = 0;
        }
    } while (!validChoice);
    // ---- Date Validation ----
    int validDate = 0;
    char dateInput[20];
    int year, month, day;
    
    do {
        printf("Enter seminar date (YYYY-MM-DD): ");
        scanf(" %19s", dateInput);
        getchar();
        
        if (sscanf(dateInput, "%d-%d-%d", &year, &month, &day) != 3) {
            printf("Invalid format! Please use YYYY-MM-DD.\n");
            continue;
        }
        if (year < 2025 || year > 2028) {
            printf("Invalid year! Must be between 2025 and 2028.\n");
            continue;
        }
        if (month < 1 || month > 12) {
            printf("Invalid month! Must be 1-12.\n");
            continue;
        }
        int max_day = 31;
        switch (month) {
            case 4: case 6: case 9: case 11:
                max_day = 30; break;
            case 2:
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                    max_day = 29;
                else
                    max_day = 28;
                break;
        }

        if (day < 1 || day > max_day) {
            printf("Invalid day! For %d/%d, day must be 1-%d.\n", month, year, max_day);
            continue;
        }
        validDate = 1;
        sprintf(s.seminarDate, "%04d-%02d-%02d", year, month, day);

    } while (!validDate);
    // ---- Participant Count ----
    printf("Enter number of participants: ");
    scanf("%d", &s.participantsCount);
    getchar();

    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s,%s,%s,%d\n", s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
    fclose(file);
    printf("Seminar added successfully!\n");
}

// function แสดงตารางข้อมูลทั้งหมด
void display_all() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char line[256];
    int count = 0;
    // อ่าน header
    fgets(line, sizeof(line), file);

    printf("\n=== All Seminar Records ===\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| No | %-20s | %-20s | %-12s | %-5s |\n", 
           "Participant", "Seminar Title", "Date", "Count");
    printf("--------------------------------------------------------------------------\n");

    // อ่านข้อมูลทั้งหมดจากไฟล์และพิมพ์ออกมา
    while (fgets(line, sizeof(line), file)) {
        Seminar s;
        sscanf(line, "%[^,],%[^,],%[^,],%d",
               s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);
        count++;

        printf("| %2d | %-20s | %-20s | %-12s | %-5d |\n", 
               count,
               s.participantName,
               s.seminarTitle,
               s.seminarDate,
               s.participantsCount);
    }
    printf("--------------------------------------------------------------------------\n");
    if (count == 0) {
        printf("No seminar records found.\n");
    } else {
        printf("Total records: %d\n", count);
    }
    fclose(file);
}

//ฟังชั่น ค้นหาข้อมูล
void search_seminar() {
    int choice;
    char keyword[100];
    char again;

    do {
        printf("\n=== Search Seminar ===\n");
        printf("Search by:\n");
        printf("1. Participant Name\n");
        printf("2. Seminar Title\n");
        printf("Choose (1 or 2): ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        if (choice != 1 && choice != 2) {
            printf("Invalid choice! Please select 1 or 2.\n");
            continue;
        }

        printf("Enter keyword: ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // remove newline

        FILE *file = fopen(FILE_NAME, "r");
        if (!file) {
            printf("Error: Cannot open file.\n");
            return;
        }
        char line[256];
        fgets(line, sizeof(line), file); // skip header
        int found = 0;
        
        printf("\n--------------------------------------------------------------\n");
        printf("| %-20s | %-20s | %-10s | %-5s |\n", "Participant Name", "Seminar Title", "Date", "Count");
        printf("--------------------------------------------------------------\n");
        
        while (fgets(line, sizeof(line), file)) {
            Seminar s;
            sscanf(line, "%[^,],%[^,],%[^,],%d", 
                   s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);
            int match = 0;
            if (choice == 1 && strstr(s.participantName, keyword)) match = 1;
            if (choice == 2 && strstr(s.seminarTitle, keyword)) match = 1;

            if (match) {
                printf("| %-20s | %-20s | %-10s | %-5d |\n", 
                       s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
                found++;
            }
        }
        fclose(file);
        printf("--------------------------------------------------------------\n");
        if (found == 0)
            printf("No matching record found.\n");
        else
            printf("Found %d record(s).\n", found);
        printf("\nDo you want to search again? (y/n): ");
        scanf(" %c", &again);
        getchar();
    } while (again == 'y' || again == 'Y');
}

void edit_seminar() {
    // --- Display all records before editing ---
    display_all();
    printf("\n");

    char keyword[100];
    printf("Enter participant name to edit: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // remove newline

    if (strlen(keyword) == 0) {
        printf("No input provided. Returning to menu.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) {
        perror("Error opening file");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);
    fprintf(temp, "%s", line); // copy header

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        Seminar s;
        sscanf(line, "%[^,],%[^,],%[^,],%d", 
               s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);

        if (strcmp(s.participantName, keyword) == 0) {
            found = 1;
            printf("\nEditing record for: %s\n", s.participantName);

            printf("Enter new seminar title: ");
            fgets(s.seminarTitle, sizeof(s.seminarTitle), stdin);
            s.seminarTitle[strcspn(s.seminarTitle, "\n")] = '\0';

            // --- ตรวจสอบวันเดือนปี ---
            int year, month, day;
            while (1) {
                printf("Enter new date (YYYY-MM-DD): ");
                char input[20];
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                if (sscanf(input, "%d-%d-%d", &year, &month, &day) != 3) {
                    printf("Invalid format! Please use YYYY-MM-DD.\n");
                    continue;
                }

                if (year < 2025 || year > 2028) {
                    printf("Invalid year! Year must be between 2025 and 2028.\n");
                    continue;
                }
                if (month < 1 || month > 12) {
                    printf("Invalid month! Month must be between 1 and 12.\n");
                    continue;
                }
                
                int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                    days_in_month[1] = 29; // leap year

                if (day < 1 || day > days_in_month[month - 1]) {
                    printf("Invalid day! This month has only %d days.\n", days_in_month[month - 1]);
                    continue;
                }
                
                // ✅ valid date
                sprintf(s.seminarDate, "%04d-%02d-%02d", year, month, day);
                break;
            }
            
            printf("Enter new participant count: ");
            scanf("%d", &s.participantsCount);
            getchar();

            // --- ยืนยันก่อนบันทึก ---
            char confirm;
            printf("\nConfirm update? (y/n): ");
            scanf(" %c", &confirm);
            getchar();
            
            if (confirm == 'y' || confirm == 'Y') {
                fprintf(temp, "%s,%s,%s,%d\n", 
                        s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
                printf("Record updated successfully!\n");
            } else {
                fprintf(temp, "%s,%s,%s,%d\n", 
                        s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
                printf("Update cancelled. Original record retained.\n");
            }
        } else {
            fprintf(temp, "%s,%s,%s,%d\n", 
                    s.participantName, s.seminarTitle, s.seminarDate, s.participantsCount);
        }
    }

    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    if (!found)
        printf("No matching record found.\n");
}
//ฟังชั่น ลบข้อมูลสัมมนา
void delete_seminar() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Seminar list[200];
    int total = 0;
    char line[256];

    fgets(line, sizeof(line), file); // skip header

    // อ่านข้อมูลทั้งหมด
    while (fgets(line, sizeof(line), file)) {
        Seminar s;
        sscanf(line, "%[^,],%[^,],%[^,],%d",
               s.participantName, s.seminarTitle, s.seminarDate, &s.participantsCount);
        list[total++] = s;
    }
    fclose(file);

    if (total == 0) {
        printf("\nNo seminar data found.\n");
        return;
    }

    // ✅ แสดงตารางข้อมูลทั้งหมดก่อน
    printf("\n=== All Seminar Records ===\n");
    printf("--------------------------------------------------------------\n");
    printf("| No | %-20s | %-20s | %-10s | %-5s |\n", "Participant", "Seminar Title", "Date", "Count");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("| %2d | %-20s | %-20s | %-10s | %-5d |\n",
               i + 1,
               list[i].participantName,
               list[i].seminarTitle,
               list[i].seminarDate,
               list[i].participantsCount);
    }
    printf("--------------------------------------------------------------\n");

    // ✅ ให้ผู้ใช้พิมพ์ keyword เพื่อค้นหาที่จะลบ
    char keyword[100];
    printf("\nEnter participant name or seminar title to search for deletion: ");
    scanf(" %[^\n]", keyword);
    getchar();

    int matchIndexes[200];
    int matchCount = 0;

    // ค้นหาตรง keyword
    for (int i = 0; i < total; i++) {
        if (strstr(list[i].participantName, keyword) || strstr(list[i].seminarTitle, keyword)) {
            matchIndexes[matchCount++] = i;
        }
    }

    if (matchCount == 0) {
        printf("No matching seminar found.\n");
        return;
    }

    // ✅ แสดงรายการที่ตรงกับ keyword
    printf("\nFound %d record(s):\n", matchCount);
    printf("--------------------------------------------------------------\n");
    printf("| No | %-20s | %-20s | %-10s | %-5s |\n", "Participant", "Seminar Title", "Date", "Count");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < matchCount; i++) {
        int idx = matchIndexes[i];
        printf("| %2d | %-20s | %-20s | %-10s | %-5d |\n",
               i + 1,
               list[idx].participantName,
               list[idx].seminarTitle,
               list[idx].seminarDate,
               list[idx].participantsCount);
    }
    printf("--------------------------------------------------------------\n");

    // ✅ ให้ผู้ใช้เลือกว่าจะลบแถวไหน
    int delChoice;
    printf("Enter record number to delete (1-%d): ", matchCount);
    scanf("%d", &delChoice);
    getchar();

    if (delChoice < 1 || delChoice > matchCount) {
        printf("Invalid selection. Cancelled.\n");
        return;
    }

    int deleteIndex = matchIndexes[delChoice - 1];

    // ✅ ยืนยันก่อนลบ
    char confirm;
    printf("Are you sure you want to delete this record? (y/n): ");
    scanf(" %c", &confirm);
    getchar();

    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }

    // ✅ เขียนกลับเฉพาะข้อมูลที่ไม่ถูกลบ
    FILE *temp = fopen("temp.csv", "w");
    fprintf(temp, "ParticipantName,SeminarTitle,SeminarDate,ParticipantsCount\n");
    for (int i = 0; i < total; i++) {
        if (i != deleteIndex)
            fprintf(temp, "%s,%s,%s,%d\n",
                    list[i].participantName,
                    list[i].seminarTitle,
                    list[i].seminarDate,
                    list[i].participantsCount);
    }
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    printf("✅ Record deleted successfully!\n");
}

