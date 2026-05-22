#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000

typedef struct {
    char firstName[50];
    char lastName[50];
    char studentID[20];
    float grade;
} Student;

int compare(Student *a, Student *b) {
    if (a->grade != b->grade) {
        return (a->grade > b->grade) ? 1 : -1;
    }
    return strcmp(a->firstName, b->firstName);
}

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Student arr[], int low, int high) {
    Student pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(&arr[j], &pivot) <= 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int readStudents(const char *filename, Student arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ERROR: Could not open file '%s'\n", filename);
        return -1;
    }

    int count = 0;
    while (count < MAX_STUDENTS &&
           fscanf(fp, "%49s %49s %19s %f",
                  arr[count].firstName,
                  arr[count].lastName,
                  arr[count].studentID,
                  &arr[count].grade) == 4) {
        count++;
    }

    fclose(fp);
    return count;
}

void writeStudents(const char *filename, Student arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("ERROR: Could not write to file '%s'\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s %s %.2f\n",
                arr[i].firstName,
                arr[i].lastName,
                arr[i].studentID,
                arr[i].grade);
    }

    fclose(fp);
}

int main() {
    Student students[MAX_STUDENTS];

    int n = readStudents("students.txt", students);
    if (n <= 0) {
        printf("No records found or file error.\n");
        return 1;
    }
    printf("Read %d student records.\n", n);

    quickSort(students, 0, n - 1);
    printf("Sorting complete.\n");

    writeStudents("sorted_students.txt", students, n);
    printf("Sorted records written to sorted_students.txt\n");

    return 0;
}
