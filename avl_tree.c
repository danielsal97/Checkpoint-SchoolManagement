#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

AVLNode* readStudentsFromFile(const char* filename, AVLNode* root) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return NULL;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Student* student = (Student*)malloc(sizeof(Student));

        // Use sscanf to parse the first part of the line (name, last name, phone, grade level, class number)
        sscanf(buffer, "%s %s %s %d %d", student->name, student->last_name, student->phone, &student->gradeLevel, &student->classNumber);

        // Use strtok to extract the grades
        char* token = strtok(buffer, " ");
        for (int i = 0; i < 5; i++) token = strtok(NULL, " ");  // Skip name, last_name, phone, gradeLevel, classNumber
        for (int i = 0; i < MAX_COURSES; i++) {
            student->grades[i] = atoi(token);
            token = strtok(NULL, " ");
        }

        student->next = NULL;  // Initialize the next pointer

        // Insert the student into the AVL Tree
        root = insertStudent(root, student);
    }

    fclose(file);
    return root;
}
void deleteStudentIfMatch(AVLNode* root, char* first_name, char* last_name) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    deleteStudentIfMatch(root->left, first_name, last_name);

    // Traverse the student list in the current node
    Student* currentStudent = root->studentList;
    Student* prevStudent = NULL;

    while (currentStudent != NULL) {
        // Compare first and last names (case-insensitive)
        if (strcasecmp(currentStudent->name, first_name) == 0 && strcasecmp(currentStudent->last_name, last_name) == 0) {
            // Found the student, now delete them
            if (prevStudent == NULL) {
                // The student is the head of the list
                root->studentList = currentStudent->next;
            } else {
                // The student is in the middle or at the end
                prevStudent->next = currentStudent->next;
            }

            // Update the GradeEntry to remove their grades
            for (int i = 0; i < MAX_COURSES; i++) {
                gradeMap[currentStudent->gradeLevel].totalScores[i] -= currentStudent->grades[i];
                gradeMap[currentStudent->gradeLevel].studentCounts[i]--;
            }

            // Free the memory of the student
            free(currentStudent);
            printf("Student %s %s deleted successfully.\n", first_name, last_name);
            return;  // Exit once the student is deleted
        }

        // Move to the next student
        prevStudent = currentStudent;
        currentStudent = currentStudent->next;
    }

    // Traverse the right subtree
    deleteStudentIfMatch(root->right, first_name, last_name);
}

void selectTopPerformers(AVLNode* root, int gradeLevel) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    selectTopPerformers(root->left, gradeLevel);

    Student* topStudent = NULL;
    int highestAverage = 0;

    // Traverse the student list in the current node
    Student* currentStudent = root->studentList;
    while (currentStudent != NULL) {
        if (currentStudent->gradeLevel == gradeLevel) {
            // Calculate the student's average grade
            int totalGrades = 0;
            for (int i = 0; i < MAX_COURSES; i++) {
                totalGrades += currentStudent->grades[i];
            }
            int averageGrade = totalGrades / MAX_COURSES;

            // Check if this student has the highest average so far
            if (averageGrade > highestAverage) {
                highestAverage = averageGrade;
                topStudent = currentStudent;
            }
        }
        currentStudent = currentStudent->next;
    }

    // Print the top student if found
    if (topStudent != NULL) {
        printf("Top Performer in Grade %d: %s %s, Average Grade: %d\n",
               gradeLevel, topStudent->name, topStudent->last_name, highestAverage);
    }

    // Traverse the right subtree
    selectTopPerformers(root->right, gradeLevel);
}
void selectCandidatesForDeparture(AVLNode* root, int minGradeThreshold) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    selectCandidatesForDeparture(root->left, minGradeThreshold);

    // Traverse the student list in the current node
    Student* currentStudent = root->studentList;
    while (currentStudent != NULL) {
        // Calculate the average grade for the student
        int totalGrades = 0;
        for (int i = 0; i < MAX_COURSES; i++) {
            totalGrades += currentStudent->grades[i];
        }
        int averageGrade = totalGrades / MAX_COURSES;

        // If the average grade is below the threshold, print the student
        if (averageGrade < minGradeThreshold) {
            printf("Student: %s %s, Phone: %s, Grade Level: %d, Class: %d, Average Grade: %d\n",
                   currentStudent->name, currentStudent->last_name, currentStudent->phone,
                   currentStudent->gradeLevel, currentStudent->classNumber, averageGrade);
        }
        currentStudent = currentStudent->next;
    }

    // Traverse the right subtree
    selectCandidatesForDeparture(root->right, minGradeThreshold);
}
// Function to edit a student's phone number or grade
void editStudentDetails(AVLNode* root, char* first_name, char* last_name) {
    if (root == NULL) {
        return;
    }

    // Traverse the left subtree
    editStudentDetails(root->left, first_name, last_name);

    // Traverse the student list in the current node
    Student* currentStudent = root->studentList;

    while (currentStudent != NULL) {
        // Compare first and last names (case-insensitive using strcasecmp)
        if (strcasecmp(currentStudent->name, first_name) == 0 && strcasecmp(currentStudent->last_name, last_name) == 0) {
            // Student found, now provide options to edit
            int choice;
            printf("Student found: %s %s, Phone: %s, Grade Level: %d, Class: %d\n",
                   currentStudent->name, currentStudent->last_name,
                   currentStudent->phone, currentStudent->gradeLevel, currentStudent->classNumber);
            printf("1. Edit Phone Number\n");
            printf("2. Edit Grades\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                // Edit phone number
                printf("Enter new phone number: ");
                scanf("%s", currentStudent->phone);
                printf("Phone number updated successfully.\n");
            } else if (choice == 2) {
                // Edit grades
                for (int i = 0; i < MAX_COURSES; i++) {
                    printf("Current grade for course %d: %d\n", i + 1, currentStudent->grades[i]);
                    printf("Enter new grade for course %d: ", i + 1);
                    scanf("%d", &currentStudent->grades[i]);
                }
                printf("Grades updated successfully.\n");
            } else {
                printf("Invalid choice. No changes were made.\n");
            }
            return;  // Exit once the student is found and edited
        }

        // Move to the next student in the list
        currentStudent = currentStudent->next;
    }

    // Traverse the right subtree
    editStudentDetails(root->right, first_name, last_name);
}
// Inorder traversal for AVL Tree (to get students sorted by grade level and class number)
void inOrderTraversal(AVLNode* root) {
    if (!root) return;

    // Traverse the left subtree
    inOrderTraversal(root->left);

    // Print the student list for this grade level and class
    Student* student = root->studentList;
    while (student != NULL) {
        printf("Student: %s %s, Phone: %s, Grade Level: %d, Class: %d, Grades: ",
               student->name, student->last_name, student->phone,
               student->gradeLevel, student->classNumber);
        for (int i = 0; i < MAX_COURSES; i++) {
            printf("%d ", student->grades[i]);
        }
        printf("\n");

        student = student->next;  // Go to the next student in the list
    }

    // Traverse the right subtree
    inOrderTraversal(root->right);
}
// Free the AVL Tree recursively
void freeAVLTree(AVLNode* root) {
    if (!root) return;

    // Free the student list in this node
    Student* current = root->studentList;
    while (current != NULL) {
        Student* next = current->next;
        free(current);
        current = next;
    }

    // Free left and right subtrees
    freeAVLTree(root->left);
    freeAVLTree(root->right);

    // Finally, free the current AVL node
    free(root);
}
// Insert a student into the AVL tree
AVLNode* insertStudent(AVLNode* root, Student* student) {
    if (!root) {
        updateGradeMap(student);  // Update map when adding a new student
        return createAVLNode(student);
    }

    // If gradeLevel and classNumber are the same, add the student to the existing node's list
    if (student->gradeLevel == root->gradeLevel && student->classNumber == root->classNumber) {
        addStudentToList(root->studentList, student);
        updateGradeMap(student);  // Update map when adding a new student
        return root;
    }

    // Insert in the left or right subtree based on gradeLevel and classNumber
    if (student->gradeLevel < root->gradeLevel ||
        (student->gradeLevel == root->gradeLevel && student->classNumber < root->classNumber)) {
        root->left = insertStudent(root->left, student);
    } else {
        root->right = insertStudent(root->right, student);
    }

    // Update height and balance the node
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    int balance = getBalance(root);

    // Rotate to balance the tree
    if (balance > 1 && (student->gradeLevel < root->left->gradeLevel ||
                        (student->gradeLevel == root->left->gradeLevel && student->classNumber < root->left->classNumber))) {
        return rotateRight(root);
    }
    if (balance < -1 && (student->gradeLevel > root->right->gradeLevel ||
                         (student->gradeLevel == root->right->gradeLevel && student->classNumber > root->right->classNumber))) {
        return rotateLeft(root);
    }
    if (balance > 1 && (student->gradeLevel > root->left->gradeLevel ||
                        (student->gradeLevel == root->left->gradeLevel && student->classNumber > root->left->classNumber))) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && (student->gradeLevel < root->right->gradeLevel ||
                         (student->gradeLevel == root->right->gradeLevel && student->classNumber < root->right->classNumber))) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
void printStudentIfMatch(AVLNode* root, char* first_name, char* last_name) {
    if (root == NULL) {
        return;
    }

    // Traverse left subtree
    printStudentIfMatch(root->left, first_name, last_name);

    // Traverse the student list in the current node
    Student* currentStudent = root->studentList;
    while (currentStudent != NULL) {
        // Compare first and last names (case-insensitive using strcasecmp)
        if (strcasecmp(currentStudent->name, first_name) == 0 && strcasecmp(currentStudent->last_name, last_name) == 0) {
            // Print student details if names match
            printf("Student: %s %s, Phone: %s, Grade Level: %d, Class: %d, Grades: ",
                   currentStudent->name, currentStudent->last_name, currentStudent->phone,
                   currentStudent->gradeLevel, currentStudent->classNumber);
            for (int i = 0; i < MAX_COURSES; i++) {
                printf("%d ", currentStudent->grades[i]);
            }
            printf("\n");
        }
        // Move to the next student in the list
        currentStudent = currentStudent->next;
    }

    // Traverse right subtree
    printStudentIfMatch(root->right, first_name, last_name);
}
int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
// Utility function to get the height of an AVL node
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// Utility function to rotate right
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    return x;
}

// Utility function to rotate left
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    return y;
}
AVLNode* createAVLNode(Student* student) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->gradeLevel = student->gradeLevel;
    newNode->classNumber = student->classNumber;
    newNode->studentList = student;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;  // New node is initially added at leaf level
    return newNode;
}