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
///                   of switch-case statements.

#define MAX_COMMAND_LENGTH 10

int main()
{
    char command[MAX_COMMAND_LENGTH] = {0};

    main_menu;
    gets(command);
    while(!strcmp("exit", command))
    {
        select_command(command);
        system(cls);
        main_menu();
        gets(command);
    }

    return 0;
}

