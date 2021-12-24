#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

#define TOTAL_COMMANDS 7
#define FALSE 0
#define TRUE 1
#define MAX_RECORD_NAME_LENGTH 50
#define MAX_NAME_LENGTH 50
#define TOTAL_EXAMS 4

///Prints the main menu on screen
void main_menu(void)
{
    printf("*-*-*-*-*-*-*-*-*-*-*-*STUDENT MARKS RECORD*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*MAIN  MENU*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n");
    printf("new - Create a new student record.\n");
    printf("add - Add a new student and his 4 exam results to the record.\n");
    printf("search - Search for a student's data.\n");
    printf("change_marks - Change a student's marks.\n");
    printf("average - View the total average of the students.\n");
    printf("sort - Sort the record in alphabetical order.\n");
    printf("exit - End the program.\n");
    printf("Type a valid command and press ENTER: ");
}

///Calls the function associated with certain command
void select_command(char command[])
{
    char valid_commands[TOTAL_COMMANDS] = {"new", "add", "search", "change_marks", "average", "sort"};
    void *function_ptrs[TOTAL_COMMANDS]() = {new_record, add, search_student, change_marks, average, sort_record};
    int counter, command_found = FALSE;

    for(counter=0;counter<TOTAL_COMMANDS;counter++)
    {
        if(!strcmp(command, valid_commands))
        {
            command_found = TRUE;
            break;
        }
    }

    if(!command_found)
    {
        printf("\a\n ERROR: invalid command. Press ENTER to write a new command.");
        getchar();
        return;
    }

    function_ptrs[counter];
}

void new_record(student_data record[])
{
    char record_name[MAX_RECORD_NAME_LENGTH];
    int students_to_record = 0;
    if(record)
    {
        printf("There is already a record stored in memory. Overwrite? (Y/N): ");
        if(getc(stdin)=='N')
            return;
    }
    printf("Enter the name of the record to be created: ");//this is useless in this implementation unless multiple records are kept. If files where used instead we could name the file with this input
    gets(record_name);

    printf("Enter the number of students to be recorded initially: ");
    scanf("%d", &students_to_record);

    if(!students_to_record)
    {
        printf("ERROR: record creation failed. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    for(counter=0;counter<students_to_record;counter++)
    {
        append_student();
    }

    printf("Record created successfully, %d students added. Press ENTER to return to the main menu.\n", students_to_record);
    getchar();

}

void add(student_data record[])
{

}

void search_student(student_data record[])
{

}

void change_marks(student_data record[])
{

}

void average(student_data record[])
{

}

void sort_record(student_data record[])
{

}

void append_student(student_data record[])
{
    char student_name[MAX_NAME_LENGTH];
    float score[TOTAL_EXAMS];

    printf("\nEnter the name of the student: ");
    gets(student_name);
    printf("\nEnter the score of the first exam: ");
    scanf("%f", score[0]);
}
