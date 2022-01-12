#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
Dado el mismo archivo con artículos lista.dat, mostrar en pantalla y almacenar en un
archivo la “nota de pedido” para completar el stock mínimo de artículos. El stock mínimo de
cada artículo está almacenado en un archivo llamado SM.dat estructurado como nº de
artículo (int) y cantidad mínima (int). Se pide armar una lista de productos que son
necesarios reponer y cuántos deben comprarse de cada uno (como mínimo) para alcanzar
el nivel de stock mínimo. El archivo con la nota de pedido debe poder abrirse con un editor
de texto normal.
**/

///NOTE (28/12/2021): Instead of a file named lista.dat I will use an article database which I made previously, BD. Each article in
///                   that file contains information which is not really necessary to solve the exercise. The file containing
///                   the minimum stock for each article is created in this program.
///                   Since I want to practice dynamic memory allocation I won't create a text document with a list of articles
///                   to buy, the data will be saved in memory. However, I plan on solving this exercise using only files later on.
///                   It isn't specified whether the database file contains different articles with the same description.
///                   I will consider that this may be the case so when counting the total stock of certain article I will
///                   take into consideration the sum of the stocks of all articles with the same description.
///
///                   REREADING THE EXERCISE I RELIZED THAT THE MINIMUM STOCK LIST SHOULD CONTAIN AN ARTICLE ID AND THE MINIMUM AMOUNT,
///                   WHICH MIGHT MEAN THAT WE SHOULD DIFFERENTIATE ARTICLES BASED ON THEI IDS RATHER THAN DESCRIPTION. IF THAT'S THE CASE
///                   THE APPROACH TAKEN IN THIS PROGRAM WOULD BE WRONG AND SINCE EVERY ARTICLE LSITED IN THE DATABASE USED HAS A
///                   DIFFERENT ID, THEN THE MINIMUM STOCK LIST WOULD HAVE AS MANY ARTICLES AS THE ORIGINAL DATABASE.

#define MAX_ARTICLE_LENGTH 20
#define MAX_SUPPLIER_LENGTH 15

typedef struct article_s{
    int id;
    char description[MAX_ARTICLE_LENGTH];
    int stock;
    char supplier[MAX_SUPPLIER_LENGTH];
    float price;
} article;


int main()
{
    FILE *db_file_ptr;
    article *article_db, *ms_list, *required_stock_list;
    int counter, counter1, counter2, total_elements, stock_difference = 0, total_stock = 0, flag_article = 0, ms_list_size = 0;

    if(!(db_file_ptr = fopen("BD", "r+b")))
    {
        printf("ERROR: couldn't open the database file.");
        exit(1);
    }

    fseek(db_file_ptr, (long) 0, SEEK_END);
    total_elements = ftell(db_file_ptr)/sizeof(article);
    rewind(db_file_ptr);

    article_db = (article*) malloc(total_elements * sizeof(article));
    ms_list = (article*) malloc(total_elements * sizeof(article)); //From the approach taken at the beginning, there could be as many as total_elements different articles. If there are less, then we wasted memory
                                   //This array will be used to create the minimum stock list, so it must contain the same articles as BD

    fread(article_db, sizeof(article), total_elements, db_file_ptr);//We dump the entire file into memory in one line

    for(counter1=0;counter1<total_elements;counter1++) //We make the minimum stock list using this loop
    {
        for(counter2=0;counter2<counter1;counter2++)
        {
            if(!strcmp(article_db[counter1].description, ms_list[counter2].description))
            {
                flag_article = 1;
                break;
            }
        }
        if(!flag_article) //If the article isn't already in the list we add it
        {
            ms_list[counter2]=article_db[counter1];
            printf("Description: %-20s ", ms_list[counter2].description);
            ms_list[counter2].stock=rand() % 25 + 1;
            printf("Min. Stock: %d\n", ms_list[counter2].stock);
            ms_list_size = counter2 + 1; //+1 since counter2 would be the index of the array
        }
        flag_article = 0;
    }



    required_stock_list = (article*) malloc((ms_list_size) * sizeof(article)); //This array is of size equal to the amount of articles in ms_list

    for(counter=0;counter<ms_list_size;counter++)
    {
        required_stock_list[counter]=ms_list[counter];
        required_stock_list[counter].stock=0;
    }


    for(counter1=0;counter1<ms_list_size;counter1++) //We fill the list of the required amount of articles to reach the minimum stock
    {
        for(counter2=0;counter2<total_elements;counter2++)
        {
            if(!strcmp(required_stock_list[counter1].description, article_db[counter2].description))
            {
                total_stock+=article_db[counter2].stock;
            }
        }

        stock_difference = ms_list[counter1].stock - total_stock;

        if(stock_difference>0)
            required_stock_list[counter1].stock = stock_difference;
        total_stock = 0; //We reset total_stock for the next article
    }

    printf("\nProducts to buy:\n");
    for(counter=0;counter<ms_list_size;counter++)
    {
        printf("Description: %-20s ", required_stock_list[counter].description);
        printf("Stock: %-2d \n", required_stock_list[counter].stock);
    }

    if(db_file_ptr)
        fclose(db_file_ptr);
    if(article_db)
        free(article_db);
    if(ms_list)
        free(ms_list);
    if(required_stock_list)
        free(required_stock_list);

    return 0;
}

/*  On line 96 we start going through the array required_stock_list rather then article_db, like it was done in line 64.
    thats because we are now interested in calculating the total stock in the database for each article, we require the value
    of the index of the required_stock_list. The easiest way to keep that value is using the counter of the outside loop,
    otherwise it would be necessary to store it in an extra variable since counter2 is always ms_list_size when leaving the inner loop
    because we don't break the loop like we did before in this case.
    We could implement this system differently with the loops, whats important is that the result must be the same. It takes some
    thinking to realize what will happen without doing trial and error using the compiler.
*/
