#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

typedef enum sex_t {man=1, woman=2} sex_t;

typedef struct student_s{
    char name[MAX_NAME_LENGTH];
    int age;
    sex_t sex;
} student;

void new_database(void);
void bubble_sort(FILE *db_pointer);
int search_student(FILE *db_pointer, char name[]);
