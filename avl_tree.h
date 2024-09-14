#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "student.h"

typedef struct AVLNode {
    int gradeLevel;
    int classNumber;
    Student* studentList;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

AVLNode* readStudentsFromFile(const char* filename, AVLNode* root);
AVLNode* insertStudent(AVLNode* root, Student* student);
AVLNode* createAVLNode(Student* student);
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
int getBalance(AVLNode* node);
int getHeight(AVLNode* node);
void freeAVLTree(AVLNode* root);
void printStudentIfMatch(AVLNode* root, char* first_name, char* last_name);
void inOrderTraversal(AVLNode* root);
void deleteStudentIfMatch(AVLNode* root, char* first_name, char* last_name);
void selectTopPerformers(AVLNode* root, int gradeLevel);
void selectCandidatesForDeparture(AVLNode* root, int minGradeThreshold);

#endif // AVL_TREE_H