# Checkpoint-SchoolManagement
# Student Management System with AVL Tree

## Project Overview
This project implements a **Student Management System** using an **AVL Tree** for efficient student data storage and retrieval. The system allows adding, removing, and searching students, and provides various functionalities such as grade management and data exporting.

## Features
- Add new students
- Remove students
- Search for students by name
- Manage student grades
- Data stored using an AVL Tree for efficient lookups and balancing
- Export student data to a file

## Files Structure
- **student.h / student.c**: Manages student-related operations such as creating, managing, and displaying student data.
- **menu.h / menu.c**: Provides the user interface for navigating the options, managing students, and viewing statistics.
- **avl_tree.h / avl_tree.c**: Implements the AVL Tree data structure to efficiently manage and balance the student data.
- **main.c**: The main entry point of the program, orchestrates the system by calling the necessary functions from the other files.

## How to Compile
To compile the project, use the following command:

```bash
gcc -o student_management main.c student.c menu.c avl_tree.c -lm