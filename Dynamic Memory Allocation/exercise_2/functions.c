#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

#define TOTAL_COMMANDS 6
#define MAX_COMMAND_LENGTH 15
#define FALSE 0
#define TRUE 1
#define MAX_RECORD_NAME_LENGTH 50
#define MAX_NAME_LENGTH 50
#define TOTAL_EXAMS 4

///Prints the main menu on screen
void main_menu(void)
{
    printf("*-*-*-*-*-*-*-*-*-*-*-*STUDENT MARKS RECORD*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*MAIN  MENU*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n\n");
    printf("new - Create a new student record.\n\n");
    printf("add - Add a new student and his 4 exam results to the record.\n\n");
    printf("search - Search for a student's data.\n\n");
    printf("change_marks - Change a student's marks.\n\n");
    printf("average - View the total average of the students.\n\n");
    printf("sort - Sort the record in alphabetical order.\n\n");
    printf("exit - End the program.\n\n");
    printf("Type a valid command and press ENTER: ");
}

///Calls the function associated with certain command
void select_command(char command[], student_data **record_ptr, int *record_size_ptr)
{
    char valid_commands[TOTAL_COMMANDS][MAX_COMMAND_LENGTH] = {"new", "add", "search", "change_marks", "average", "sort"};
    void (*function_ptrs[TOTAL_COMMANDS])(student_data**, int*) = {new_record, add, search_student, change_marks, average, sort_record};
    int counter, command_found = FALSE;

    for(counter=0;counter<TOTAL_COMMANDS;counter++)
    {
        if(!strcmp(command, valid_commands[counter]))
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

    function_ptrs[counter](record_ptr, record_size_ptr);
}

///Asks the user for data for the new record
void new_record(student_data **record_ptr, int *record_size_ptr)
{
    char record_name[MAX_RECORD_NAME_LENGTH];
    int students_to_record = 0, counter;

    if((*record_ptr)!=NULL)
    {
        printf("There is already a record stored in memory. Overwrite? (Y/N): ");
        if(getchar()=='N')
        {
            fflush(stdin);
            return;
        }
        free(*record_ptr);
        *record_ptr = NULL;
        *record_size_ptr = 0;
        fflush(stdin);
    }
    printf("Enter the name of the record to be created: ");//this is useless in this implementation unless multiple records are kept. If files where used instead we could name the file with this input
    gets(record_name);

    printf("Enter the number of students to be recorded initially: ");
    scanf("%d", &students_to_record);
    fflush(stdin);

    if(!students_to_record)
    {
        printf("ERROR: record creation failed. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    for(counter=0;counter<students_to_record;counter++)
    {
        append_student(record_ptr, record_size_ptr);
    }

    printf("Record created successfully, %d students added. Press ENTER to return to the main menu.\n", students_to_record);
    getchar();

}

void add(student_data **record_ptr, int *record_size_ptr)
{
    int students_to_record = 0, counter;

    if(*record_ptr==NULL)
    {
        printf("ERROR: no record found. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    printf("Enter the number of students to be recorded: ");
    scanf("%d", &students_to_record);
    fflush(stdin);

    if(!students_to_record)
    {
        printf("ERROR: record creation failed. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    for(counter=0;counter<students_to_record;counter++)
    {
        append_student(record_ptr, record_size_ptr);
    }

    printf("%d students added. Press ENTER to return to the main menu.\n", students_to_record);
    getchar();
}

///Asks user for a student to search
void search_student(student_data **record_ptr, int *record_size_ptr)
{
    char buffer[MAX_NAME_LENGTH];
    student_data *student_ptr;

    if(*record_ptr==NULL)
    {
        printf("ERROR: no record found. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    bubble_sort(record_ptr, record_size_ptr);

    printf("Name of a student. Type \"exit\" to return to the main menu: ");
    gets(buffer);

    while(strcmp(buffer, "exit"))
    {
        student_ptr = find_student(record_ptr, record_size_ptr, buffer);

        if(!student_ptr)
        {
            printf("ERROR: no student found. Press ENTER to return to the main menu.\n");
            getchar();
            return;
        }

        printf("Student found: \n");
        printf("Name: %s.\n1°: %f.\n2°: %f.\n3°: %f.\n4°: %f.\n\n", student_ptr->name, student_ptr->exam_score[0], student_ptr->exam_score[1], student_ptr->exam_score[2], student_ptr->exam_score[3]);

        printf("Name of a student. Type \"exit\" to return to the main menu: ");
        gets(buffer);
    }
}

void change_marks(student_data **record_ptr, int *record_size_ptr)
{
    char buffer[MAX_NAME_LENGTH];
    student_data *student_ptr;
    int exam_number;

    if(*record_ptr==NULL)
    {
        printf("ERROR: no record found. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    bubble_sort(record_ptr, record_size_ptr);

    printf("Name of a student. Type \"exit\" to return to the main menu: ");
    gets(buffer);

    while(strcmp(buffer, "exit"))
    {
        student_ptr = find_student(record_ptr, record_size_ptr, buffer);

        if(!student_ptr)
        {
            printf("ERROR: no student found. Press ENTER to return to the main menu.\n");
            getchar();
            return;
        }

        printf("Student found: \n");
        printf("Name: %s.\n1°: %f.\n2°: %f.\n3°: %f.\n4°: %f.\n\n", student_ptr->name, student_ptr->exam_score[0], student_ptr->exam_score[1], student_ptr->exam_score[2], student_ptr->exam_score[3]);

        printf("Number of exam score which will be changed: ");
        scanf("%d", &exam_number);
        fflush(stdin);

        printf("Type the score: ");
        scanf("%f",&(student_ptr->exam_score[exam_number-1]));
        fflush(stdin);

        printf("Name of a student. Type \"exit\" to return to the main menu: ");
        gets(buffer);
    }
}

///Calculates the average score of each student and the total average
void average(student_data **record_ptr, int *record_size_ptr)
{
    float average_score = 0, total_score = 0, total_average = 0;
    int counter;

    if(*record_ptr==NULL)
    {
        printf("ERROR: no record found. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    printf("|-----------------------NAME-----------------------|--1°--|--2°--|--3°--|--4°--|-AVG-|\n");
    for(counter=0;counter<*record_size_ptr;counter++)
    {
        average_score =  ((*record_ptr)[counter].exam_score[0]+(*record_ptr)[counter].exam_score[1]+(*record_ptr)[counter].exam_score[2]+(*record_ptr)[counter].exam_score[3])/4;
        total_score += ((*record_ptr)[counter].exam_score[0]+(*record_ptr)[counter].exam_score[1]+(*record_ptr)[counter].exam_score[2]+(*record_ptr)[counter].exam_score[3]);
        printf("|%-50s|-%-4.2f-|-%-4.2f-|-%-4.2f-|-%-4.2f-|-%-3.2f-|\n", (*record_ptr)[counter].name, (*record_ptr)[counter].exam_score[0], (*record_ptr)[counter].exam_score[1], (*record_ptr)[counter].exam_score[2], (*record_ptr)[counter].exam_score[3], average_score);
    }
    total_average=total_score/((*record_size_ptr)*4);

    printf("The total average is %.2f .\n Press ENTER to return to the main menu.\n", total_average);
    getchar();

}

///Display the record sorted alphabetically using the bubble sort algorithm
void sort_record(student_data **record_ptr, int *record_size_ptr)
{
    int counter;

    if(*record_ptr==NULL)
    {
        printf("ERROR: no record found. Press ENTER to return to the main menu.\n");
        getchar();
        return;
    }

    bubble_sort(record_ptr, record_size_ptr);

    printf("|-----------------------NAME-----------------------|--1°--|--2°--|--3°--|--4°--|\n");
    for(counter=0;counter<*record_size_ptr;counter++)
    {
        printf("|%-50s|-%-4.2f-|-%-4.2f-|-%-4.2f-|-%-4.2f-|\n", (*record_ptr)[counter].name, (*record_ptr)[counter].exam_score[0], (*record_ptr)[counter].exam_score[1], (*record_ptr)[counter].exam_score[2], (*record_ptr)[counter].exam_score[3]);
    }

    printf("Press ENTER to return to the main menu.\n");
    getchar();
}

///Receives student data and allocates the memory necessary for a dynamic student array
void append_student(student_data **record_ptr, int *record_size_ptr) //we use a pointer to a pointer because we need to rebuild the record and that information should be visible to every other function
{
    student_data student;

    printf("\nEnter the name of the student: ");
    gets(student.name);
    printf("\nEnter the score of the first exam: ");
    scanf("%f", &student.exam_score[0]);
    printf("\nEnter the score of the second exam: ");
    scanf("%f", &student.exam_score[1]);
    printf("\nEnter the score of the third exam: ");
    scanf("%f", &student.exam_score[2]);
    printf("\nEnter the score of the fourth exam: ");
    scanf("%f", &student.exam_score[3]);

    *record_size_ptr+=1;

    *record_ptr = (student_data*) realloc(*record_ptr, (*record_size_ptr ) * sizeof(student_data)); //If provided a null pointer, realloc behaves like malloc
    //In the line above the record (accessed through record_ptr) is being relocated to a block with more space
    (*record_ptr)[*record_size_ptr-1] = student;
    fflush(stdin);
}

///Binary search
student_data* find_student(student_data **record_ptr, int *record_size_ptr, char name[])
{
    int h_bound = *record_size_ptr-1, l_bound = 0, medium;

    while(l_bound <= h_bound)
    {
        medium = (l_bound+h_bound)/2;
        if(!strcmp((*record_ptr)[medium].name, name))
        {
            return &(*record_ptr)[medium]; //We return the adress to the student element in the record
        }

        if(strcmp((*record_ptr)[medium].name, name) > 0)//the name in med goes after the name we are looking for
            h_bound = medium-1;
        else
            l_bound = medium+1;
    }

    return NULL;
}

///Bubble Sort
void bubble_sort(student_data **record_ptr, int *record_size_ptr)
{
    int counter1, counter2;
    student_data student_buffer;

    for(counter1=0;counter1<*record_size_ptr-1;counter1++)
    {
       for(counter2=0;counter2<*record_size_ptr-1-counter1;counter2++)
       {
           if(strcmp((*record_ptr)[counter2].name, (*record_ptr)[counter2+1].name) > 0) //if the name of the first goes after the name of the second, we have to swap (see ascii code and strcmp)
           {
                student_buffer = (*record_ptr)[counter2];
                (*record_ptr)[counter2] = (*record_ptr)[counter2+1];
                (*record_ptr)[counter2+1] = student_buffer;
           }
       }
    }
}
