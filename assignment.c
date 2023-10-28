#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a student
typedef struct Student {
    int number;
    char name[50];
    int age;
    int recordID;
    struct Student* next;
} Student;

// Initialize a list with a dummy head node
Student* head = NULL;
Student* tail = NULL;

// Function to add a student to the end of the list
void addStudent(int number, const char* name, int age) {
    // Create a new student node
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->number = number;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->next = NULL;

    // Assign a unique record ID
    newStudent->recordID = 1;
    if (tail != NULL) {
        newStudent->recordID = tail->recordID + 1;
        tail->next = newStudent;
    } else {
        head = newStudent;
    }

    // Update the tail pointer
    tail = newStudent;
}

// Function to print all student information
void printStudentInfo() {
    Student* current = head;
    int count = 0;

    while (current != NULL) {
        printf("%d - %s %d %d\n", current->number, current->name, current->age, current->recordID);
        current = current->next;
        count++;
    }

    printf("Total students: %d\n", count);
}

// Function to search for a student by name
Student* searchStudentByName(const char* name) {
    Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Function to delete the next node from a node with the given student name
void deleteNextNode(const char* name) {
    Student* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->next != NULL) {
                Student* next = current->next;
                current->next = next->next;
                free(next);
                break;
            }
        }
        current = current->next;
    }
}

// Function to find and print the record with the longest name
void printLongestNameRecord() {
    Student* current = head;
    char longestName[50] = "";
    int maxLength = 0;

    while (current != NULL) {
        int currentLength = strlen(current->name);
        if (currentLength > maxLength) {
            maxLength = currentLength;
            strcpy(longestName, current->name);
        }
        current = current->next;
    }

    printf("The longest name in the list: %s\nLength: %d\n", longestName, maxLength);
}

int main() {
    char name[50];
    int number, age;

    while (1) {
        printf("Enter student number (-1 to exit): ");
        scanf("%d", &number);
        if (number == -1) {
            break;
        }

        printf("Enter student name: ");
        scanf("%s", name);

        printf("Enter student age: ");
        scanf("%d", &age);

        addStudent(number, name, age);
    }

    // Print all student information
    printStudentInfo();

    // Search for a student by name
    printf("Enter a student name to search: ");
    scanf("%s", name);
    Student* foundStudent = searchStudentByName(name);
    if (foundStudent != NULL) {
        printf("Student found: %d - %s %d %d\n", foundStudent->number, foundStudent->name, foundStudent->age, foundStudent->recordID);
    } else {
        printf("Student not found.\n");
    }

    // Delete the next node from a node with the given student name
    printf("Enter a student name to delete the next node: ");
    scanf("%s", name);
    deleteNextNode(name);

    // Print the record with the longest name
    printLongestNameRecord();

    return 0;
}
