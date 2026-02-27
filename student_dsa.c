#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[50];
    int roll;
    float marks;
};

struct Student students[MAX];
int count = 0;

void addStudent() {
    if (count >= MAX) {
        printf("Array full! Cannot add more students.\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Roll Number: ");
    scanf("%d", &students[count].roll);

    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);

    count++;
    printf("Student Added Successfully!\n");
}

void displayStudents() {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s | Roll: %d | Marks: %.2f\n",
               students[i].name,
               students[i].roll,
               students[i].marks);
    }
}

void searchByRoll() {
    int roll, found = 0;

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("Record Found!\n");
            printf("Name: %s | Marks: %.2f\n",
                   students[i].name,
                   students[i].marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record Not Found.\n");
}

void searchByName() {
    char name[50];
    int found = 0;

    printf("Enter Name to Search: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Record Found!\n");
            printf("Roll: %d | Marks: %.2f\n",
                   students[i].roll,
                   students[i].marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Record Not Found.\n");
}

void sortByMarks() {
    struct Student temp;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Sorted by Marks (Descending).\n");
}

void sortByRoll() {
    struct Student temp;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].roll > students[j + 1].roll) {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("Sorted by Roll Number (Ascending).\n");
}

void findTopper() {
    if (count == 0) {
        printf("No records available.\n");
        return;
    }

    int topperIndex = 0;

    for (int i = 1; i < count; i++) {
        if (students[i].marks > students[topperIndex].marks) {
            topperIndex = i;
        }
    }

    printf("Topper Details:\n");
    printf("Name: %s | Roll: %d | Marks: %.2f\n",
           students[topperIndex].name,
           students[topperIndex].roll,
           students[topperIndex].marks);
}

int main() {
    int choice;

    do {
        printf("\n==== Student DSA Project ====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search by Roll Number\n");
        printf("4. Search by Name\n");
        printf("5. Sort by Marks\n");
        printf("6. Sort by Roll Number\n");
        printf("7. Find Topper\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: sortByMarks(); break;
            case 6: sortByRoll(); break;
            case 7: findTopper(); break;
            case 0: printf("Exiting Program...\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while (choice != 0);

    return 0;
}
