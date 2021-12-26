#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/**
 Realizar un programa que maneje un archivo de longitud desconocida, donde cada
registro contiene el nombre de un alumno y cuatro notas. Hacerlo con un menú que permita
crear el archivo, calcular el promedio, mostrarlo, buscar un registro determinado, modificar
una nota, agregar registros y ordenar el archivo alfabéticamente.
**/

///NOTE (23/12/2021): This exercise was originally intended to be solved using files, however
///                   I am trying to practice dynamic memory allocation so I will use this and
///                   in the future I will take the file I/O approach.
///                   The implementation of a menu is done using a function pointer array instead
///                   of switch-case statements. This lead to some complications in the design of functions.
///NOTE (24/12/2021): In this implementation the students from the record are added to a dynamic vector.
///                   As a consequence of this, every time a new student is appended all of the previous
///                   entries have to be moved to a larger memory block. This is done used realloc. However
///                   another approach, and maybe a mo re intuitive one, would be to use linked lists.
///                   Using a function pointer array instead of switch-case statements lead to
///                   some complications in the design of functions.
///                   One reason why the code seems counterintuitive is because it was necessary to use a
///                   pointer to a pointer (record_ptr) to make it possible to reallocate the memory used
///                   for the record when adding students. The record itself is a dynamic array, it's type
///                   is student_data*. When appending a student, due to the approach taken it is necessary
///                   to move the entire record to a block of bigger size, thus changing the pointer to the
///                   start of that block, and that change should be visible to the rest of the program.
///                   This is the reason why I decided to use a pointer to a pointer, we are able to access the
///                   record from the different functions and also change it while keeping the data.
///                   Using a global variable might have been easier and probably would have kept the code cleaner.
///NOTE (25/12/2021): -
///NOTE (25/12/2021): Finished the program. A lack of planning at the beginning led to confusion during the development.
///                   The result feels poorly put together although it works. For the next time it would be better
///                   to solve it in one sitting, paying close attention to the relationship between the functions and
///                   thinking about future steps.S

#define MAX_COMMAND_LENGTH 15

int main()
{
    char command[MAX_COMMAND_LENGTH];
    student_data **record_ptr, *record;
    int *record_size_ptr, record_size;

    record_size_ptr = &record_size;
    *record_size_ptr = 0;
    record = NULL;
    record_ptr = &record;

    main_menu();
    gets(command);
    while(strcmp("exit", command))
    {
        select_command(command, record_ptr, record_size_ptr);
        system("cls");
        main_menu();
        gets(command);
    }

    return 0;
}

