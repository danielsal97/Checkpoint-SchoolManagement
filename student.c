#include "student.h"
GradeEntry gradeMap[13];
// Add a new student to the linked list of an existing class/grade
void addStudentToList(Student* existingStudent, Student* newStudent) {
    Student* current = existingStudent;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newStudent;
    newStudent->next = NULL;
}

// Update the grade map when a new student is added
void updateGradeMap(Student* student) {
    GradeEntry* entry = &gradeMap[student->gradeLevel];  // Get entry for the student's grade level

    for (int i = 0; i < MAX_COURSES; i++) {
        entry->totalScores[i] += student->grades[i];  // Add the student's grade to the total
        entry->studentCounts[i]++;  // Increment the number of students for this course
    }
}
void printAverageScores() {
    for (int grade = 1; grade <= 12; grade++) {
        GradeEntry* entry = &gradeMap[grade];
        printf("Grade %d averages:\n", grade);
        for (int i = 0; i < MAX_COURSES; i++) {
            if (entry->studentCounts[i] > 0) {
                double average = (double)entry->totalScores[i] / entry->studentCounts[i];
                printf("  Course %d: Average = %.2f, Students = %d\n", i + 1, average, entry->studentCounts[i]);
            } else {
                printf("  Course %d: No students enrolled\n", i + 1);
            }
        }
    }
}