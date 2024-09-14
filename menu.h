#ifndef MENU_H
#define MENU_H

#include "avl_tree.h"

// Function prototypes for menu operations
void menu(AVLNode** root);
void editStudentDetails(AVLNode* root, char* first_name, char* last_name);

#endif