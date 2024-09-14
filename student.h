#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_COURSES 10
#define NAME_LENGTH 50
#define PHONE_NUMBER 10

// Student structure definition with the 'next' pointer
typedef struct Student {
    char name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    char phone[PHONE_NUMBER];
    int gradeLevel;
    int classNumber;
    int grades[MAX_COURSES];
    struct Student* next;  // Pointer to next student (for linked list)
} Student;

typedef struct GradeEntry {
    int totalScores[MAX_COURSES];
    int studentCounts[MAX_COURSES];
} GradeEntry;

extern GradeEntry gradeMap[13];  // Declare gradeMap globally

// Function declarations
void addStudentToList(Student* existingStudent, Student* newStudent);
void updateGradeMap(Student* student);
void printAverageScores();

#endif // STUDENT_H