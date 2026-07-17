Student Management System (C)

Objective: A console-based student record management system implemented in C using a singly linked list, supporting CRUD operations and basic statistics on student records.

What's Covered


Data structure: each student record (ID, name, age, GPA) stored as a node in a dynamically allocated singly linked list
Add student — inserts a new student at the end of the list, checking for duplicate IDs first
Display students — prints all student records currently in the list
Search student — looks up and displays a student's info by ID
Update student — modifies an existing student's name, age, and GPA by ID
Delete student — removes a student record by ID, handling head-node and mid-list deletion cases
Calculate average GPA — computes the mean GPA across all students
Find highest GPA — scans the list to report the student with the top GPA
Menu-driven main() — loops on a numbered menu (add/display/search/update/delete/average/highest) until exit


Tools

C (standard library: stdio.h, stdlib.h, string.h)
