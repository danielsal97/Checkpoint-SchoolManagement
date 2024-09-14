#include <stdio.h>
#include "menu.h"
#include "avl_tree.h"

void menu(AVLNode** root) {
    int choice;
    while (1) {
        printf("\n========== Student Management System ==========\n");
        printf("1. Add new student\n");
        printf("2. Print all students\n");
        printf("3. Print average scores\n");
        printf("4. Search student by name\n");
        printf("5. Delete student\n");
        printf("6. Print the top 10 in grade and class\n");
        printf("7. Select candidates for departure\n");
        printf("8. Edit student details\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Add new student
                Student* student = (Student*)malloc(sizeof(Student));
                printf("Enter first name: ");
                scanf("%s", student->name);
                printf("Enter last name: ");
                scanf("%s", student->last_name);
                printf("Enter phone number: ");
                scanf("%s", student->phone);
                printf("Enter grade level: ");
                scanf("%d", &student->gradeLevel);
                printf("Enter class number: ");
                scanf("%d", &student->classNumber);
                for (int i = 0; i < MAX_COURSES; i++) {
                    printf("Enter grades for course %d: ", i + 1);
                    scanf("%d", &student->grades[i]);
                }
                *root = insertStudent(*root, student);
                break;
            }
            case 2:
                // Print all students
                inOrderTraversal(*root);
                break;
            case 3:
                // Print average scores
                printAverageScores();
                break;
            case 4: {
                // Search for a student by first and last name
                char first_name[50], last_name[50];
                printf("Enter first name: ");
                scanf("%s", first_name);
                printf("Enter last name: ");
                scanf("%s", last_name);
                printStudentIfMatch(*root, first_name, last_name);
                break;
            }
            case 5: {
                char first_name[50], last_name[50];

                printf("Enter first name of the student to delete: ");
                scanf("%s", first_name);
                printf("Enter last name of the student to delete: ");
                scanf("%s", last_name);
                deleteStudentIfMatch(*root, first_name, last_name);
                break;
            }
            case 6: {
                int gradeLevel;
                printf("Enter the grade level (1-12): ");
                scanf("%d", &gradeLevel);
                selectTopPerformers(*root, gradeLevel);
                break;
            }
            case 7: {
                int minGradeThreshold;
                printf("Enter the minimum grade threshold: ");
                scanf("%d", &minGradeThreshold);
                selectCandidatesForDeparture(*root, minGradeThreshold);
                break;
            }
            case 8: {
                char first_name[50], last_name[50];
                printf("Enter first name of the student to edit: ");
                scanf("%s", first_name);
                printf("Enter last name of the student to edit: ");
                scanf("%s", last_name);
                editStudentDetails(*root, first_name, last_name);
                break;
            }
            case 9:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
                break;
        }
    }
}