#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/*
enum sex_t {man=1, woman=2};

typedef struct student_s{
    char name[MAX_NAME_LENGTH];
    int age;
    sex_t sex;
} student;
*/

#define MAX_NAME_LENGTH 30
#define NOT_FOUND -1

void new_database(void)
{
    char names[10][MAX_NAME_LENGTH] = {"Marcus", "Leeroy", "David", "Gregory", "William", "Janette", "Lucy", "Mary", "Sasha", "Angela"};
    student buffer;
    int counter;
    FILE *file_ptr;

    if(!(file_ptr=fopen("DB_STUDENTS", "w+b")))
    {
        printf("ERROR: database creation failed.");
        exit(1);
    }

    for(counter=0;counter<10;counter++)
    {
        strcpy(buffer.name, names[counter]);
        buffer.age = 30 - (rand() % 12 + 1);
        if(counter<5)
            buffer.sex = man;
        else
            buffer.sex = woman;

        fwrite(&buffer, sizeof(student), 1, file_ptr);
    }

    rewind(file_ptr);
    if(file_ptr)
        fclose(file_ptr);
}

void bubble_sort(FILE *db_pointer)
{
    student buffer, student1, student2;
    int counter1, counter2, total_students;

    fseek(db_pointer, (long) 0, SEEK_END);
    total_students = ftell(db_pointer)/sizeof(student);
    rewind(db_pointer);

    for(counter1=0;counter1<total_students-1;counter1++)
    {
        for(counter2=0;counter2<total_students-counter1-1;counter2++)
        {
            fseek(db_pointer, (long) counter2 * sizeof(student), SEEK_SET); //We first fix the position indicator pointing to the student in position counter2
            fread(&student1, sizeof(student), 1, db_pointer);
            fread(&student2, sizeof(student), 1, db_pointer);

            if(strcmp(student1.name, student2.name) > 0) //buffer1.name goes after buffer2.name alphabetically
            {
                buffer = student1;
                student1 = student2;
                student2 = buffer;

                fseek(db_pointer, (long) -2 * sizeof(student), SEEK_CUR);
                fwrite(&student1, sizeof(student), 1, db_pointer);
                fwrite(&student2, sizeof(student), 1, db_pointer);
            }
        }
    }
    rewind(db_pointer);
}

int search_student(FILE *db_pointer, char name[])
{
    student buffer;
    int total_students, l_bound, h_bound, middle;

    fseek(db_pointer, (long) 0, SEEK_END);
    total_students = ftell(db_pointer)/sizeof(student);
    rewind(db_pointer);

    l_bound = 0;
    h_bound = total_students-1;

    rewind(db_pointer);
    while(l_bound<=h_bound)
    {
        middle = (l_bound + h_bound)/2;

        fseek(db_pointer, middle * sizeof(student), SEEK_SET);
        fread(&buffer, sizeof(student), 1, db_pointer);
        if(!(strcmp(buffer.name, name)))
            return middle; //We return the position of the student in the file
        if(strcmp(buffer.name, name)>0)
            h_bound = middle - 1;
        else
            l_bound = middle + 1;
    }

    return NOT_FOUND;
}
