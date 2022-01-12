#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

/**
Se tiene un archivo lista.dat que contiene la base de datos de artículos de un negocio:
número de artículo (int), descripción (string de 30 caracteres), precio (float), proveedor
(string de 30) y stock (int). Actualizar esta base de datos aplicando un 20% de aumento a
todos los artículos del proveedor “PEREZ”. Para probar el funcionamiento deberá crear
primero el archivo con un programa auxiliar.
Dado el archivo con artículos del punto 3, cree dos índices que permitan ver los artículos
ordenados alfabéticamente por descripción, y el otro ver los artículos con stock menor a 5.
**/

///NOTE (2/1/2022): The database file used to solve this exercise was created with a different program and it doesn't contain
///                 any supplier named PEREZ. Instead this program lists the all the suppliers and asks the user to decide
///                 whose articles will have a percentage increase in price. The length of the strings is different too.

#define MAX_SUPPLIER_LENGTH 15

int main()
{
    FILE *db_ptr;
    char supplier[MAX_SUPPLIER_LENGTH];
    float percentage;

    if(!(db_ptr = fopen("BD", "r+b")))
    {
        printf("ERROR: couldn't open database file.");
        exit(1);
    }

    print_database(db_ptr);

    print_suppliers(db_ptr);

    printf("Type the name of the supplier whose products have increased in price: ");
    gets(supplier);
    printf("Input the percentage increase of the price of %s's articles: ", supplier);
    scanf("%f", &percentage);

    increase_price(db_ptr, supplier, percentage);
    print_database(db_ptr);

    printf("Creating sorted index file...\n");
    alphabetical_index(db_ptr);
    printf("Creating low stock index file...\n");
    low_stock_index(db_ptr);

    printf("\nSorted database:\n");
    print_sorted_db(db_ptr);

    printf("\nArticles low on stock:\n");
    print_low_stock_db(db_ptr);

    fclose(db_ptr);

    return 0;
}
