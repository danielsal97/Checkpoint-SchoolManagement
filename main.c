#include <stdio.h>
#include "menu.h"
#include "avl_tree.h"

int main() {
    AVLNode* root = NULL;

    // Initialize grade map (clear totals and counts for each grade level)
    for (int i = 1; i <= 12; i++) {
        for (int j = 0; j < MAX_COURSES; j++) {
            gradeMap[i].totalScores[j] = 0;
            gradeMap[i].studentCounts[j] = 0;
        }
    }

    root = readStudentsFromFile("/Users/danielsa/CLionProjects/untitled6/students_with_class.txt", root);
    menu(&root);
    freeAVLTree(root);

    return 0;
}