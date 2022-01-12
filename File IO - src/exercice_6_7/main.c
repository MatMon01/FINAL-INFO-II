#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/**
6) Hacer un programa que ordene un archivo binario que contiene los datos de los alumnos
de un curso (nombre, edad, sexo) en forma alfabética aplicando burbujeo simple,
directamente sobre el archivo.
7) Dado el archivo ya ordenado del ejercicio anterior, ingresar un nombre por teclado,
buscarlo en el archivo utilizando un algoritmo de búsqueda binaria y mostrar en pantalla los
datos que le correspondan si es encontrado, o bien un mensaje de error en su ausencia.
**/

///NOTE (30/12/2021): Since I don't have a database with students already created I will make one and use it.

#define MAX_NAME_LENGTH 30
#define NOT_FOUND -1

int main()
{
    FILE * db_pointer;
    student buffer;
    char name[MAX_NAME_LENGTH];
    int student_index;

    new_database();


    if(!(db_pointer = fopen("DB_STUDENTS", "r+b")))
    {
        printf("ERROR: couldn't open file.");
        exit(1);
    }

    fread(&buffer, sizeof(student), 1, db_pointer);
    while(!feof(db_pointer))
    {
        if(buffer.sex==man)
            printf("%-30s %-2d %s\n", buffer.name, buffer.age, "Man");
        else
            printf("%-30s %-2d %s\n", buffer.name, buffer.age, "Woman");
        fread(&buffer, sizeof(student), 1, db_pointer);
    }
    rewind(db_pointer);

    bubble_sort(db_pointer);

    rewind(db_pointer);

    printf("\nAfter sorting:\n");
    fread(&buffer, sizeof(student), 1, db_pointer);
    while(!feof(db_pointer))
    {
        if(buffer.sex==man)
            printf("%-30s %-2d %s\n", buffer.name, buffer.age, "Man");
        else
            printf("%-30s %-2d %s\n", buffer.name, buffer.age, "Woman");
        fread(&buffer, sizeof(student), 1, db_pointer);
    }
    printf("\n");

    printf("Enter the name of a student. Type \"exit\" to end the program: ");
    while(strcmp(gets(name), "exit"))
    {
        student_index = search_student(db_pointer, name);
        if(student_index!=NOT_FOUND)
        {
            fseek(db_pointer, (long) student_index * sizeof(student), SEEK_SET);
            fread(&buffer, sizeof(student), 1, db_pointer);

            if(buffer.sex == man)
                printf("Student found:\n%-30s %-2d %s \n", buffer.name, buffer.age, "Man");
            else
                printf("Student found:\n%-30s %-2d %s \n", buffer.name, buffer.age, "Woman");

            rewind(db_pointer);
        }
        else
        {
            printf("ERROR: student not found.\n");
        }

        printf("Enter the name of a student. Type \"exit\" to end the program: ");
    }

    if(db_pointer)
        fclose(db_pointer);

    return 0;
}
