#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Se tiene un archivo lista.dat que contiene la base de datos de artículos de un negocio:
número de artículo (int), descripción (string de 30 caracteres), precio (float), proveedor
(string de 30) y stock (int). Actualizar esta base de datos aplicando un 20% de aumento a
todos los artículos del proveedor “PEREZ”. Para probar el funcionamiento deberá crear
primero el archivo con un programa auxiliar.
**/

///NOTE (27/12/2022): The database file used to solve this exercise was created with a different program and it doesn't contain
///                   any supplier named PEREZ. Instead this program lists the all the suppliers and asks the user to decide
///                   whose articles will have a percentage increase in price. This is done in memory and then written to a
///                   different file, BD_INCREASE. Also, the length of the strings is 20 for the description and 15 for the supplier.
///                   In order to list the suppliers once without repetitions it was necessary to use a dynamic array of strings of
///                   size MAX_SUPPLIER_LENGTH and store first-seen names there, checking for each article if the supplier associated is
///                   is in the array.  If it isn't, a flag is raised and then the name is added. While this analysis is done the new names
///                   are displayed to the user.
///                   In the last step of the program the modified data is dumped into a file named BD_AUMENTO.

#define MAX_PATH_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 20
#define MAX_SUPPLIER_LENGTH 15

typedef struct article_s{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    int stock;
    char supplier[MAX_SUPPLIER_LENGTH];
    float cost;
} article;

int main()
{
    int db_size = 0, counter = 0, counter1 = 0, counter2 = 0, supplier_flag = 0;
    char buffer[MAX_PATH_LENGTH], **suppliers;
    FILE * db_ptr, * db_increase_ptr;
    article * articles_database = NULL, art;

    printf("Input the to the database file: \n");
    gets(buffer);

    if(!(db_ptr = fopen(buffer, "r+b")))
    {
        printf("ERROR: couldn't open the database file. \n");
        exit(1);
    }

    fseek(db_ptr, (long) 0, SEEK_END);
    db_size = ftell(db_ptr)/sizeof(article);
    fseek(db_ptr, (long) 0, SEEK_SET);

    articles_database = (article*) malloc(db_size * sizeof(article));

    suppliers = (char**) malloc(db_size * sizeof(char*)); //The maximum number of suppliers is equal to the number of articles
    for(counter=0;counter<db_size;counter++)              //We allocate memory for each string in the dynamic array of strings (char pointers)
        suppliers[counter] = (char*) malloc(MAX_SUPPLIER_LENGTH * sizeof(char));

    fread(articles_database, sizeof(article), db_size, db_ptr); //We dump the entire database into memory in one line

    for(counter1=0;counter1<db_size;counter1++) //In this loop we copy the names of the different suppliers to an array and print them on screen
    {
        for(counter2=0;counter2<counter1;counter2++)
        {
            if(!strcmp(articles_database[counter1].supplier, suppliers[counter2]))
            {
                supplier_flag = 1;
                break;
            }
        }

        if(!supplier_flag)
        {
            strcpy(suppliers[counter2], articles_database[counter1].supplier);
            printf("%s \n", suppliers[counter2]);
        }
        supplier_flag = 0;
    }

    printf("\nChoose the supplier whose articles's price will increase: ");
    gets(buffer);

    for(counter1=0;counter1<db_size;counter1++)
    {
        if(!strcmp(buffer, articles_database[counter1].supplier))
        {
            printf("%f\n", articles_database[counter1].cost);
            articles_database[counter1].cost += (articles_database[counter1].cost * 0.2);
        }

    }

    if(!(db_increase_ptr = fopen("BD_AUMENTO", "w+b")))
    {
        printf("ERROR: couldn't open the database file. \n");
        exit(1);
    }

    fwrite(articles_database, sizeof(article), db_size, db_increase_ptr); //We dump the database in memory into a binary file
    rewind(db_increase_ptr); // We set the position indicator at the beginning of the file

    printf("\n\nFinal data:\n");

    fread(&art, sizeof(article), 1, db_increase_ptr);
    while(!feof(db_increase_ptr))//We check the data written to the file
    {
        printf("%d\n%s\n%d\n%s\n%f\n\n", art.id, art.description, art.stock, art.supplier, art.cost);
        fread(&art, sizeof(article), 1, db_increase_ptr);
    }

    if(db_ptr)
        fclose(db_ptr);
    if(db_increase_ptr)
        fclose(db_increase_ptr);
    if(articles_database)
        free(articles_database);
    if(suppliers)
    {
        for(counter=0;counter<db_size;counter++)
        {
            if(suppliers[counter])
                free(suppliers[counter]);
        }
        free(suppliers);
    }

    return 0;
}
