#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototypes.h"

#define MAX_SUPPLIER_LENGTH 15
#define TRUE 1
#define FALSE 0

void print_database(FILE *db_ptr)
{
    article buffer;

    fread(&buffer, sizeof(article), 1, db_ptr);
    while(!feof(db_ptr)) // feof!=0 when eof indicator is set. This happens when trying to read at or past the end of file
    {
        printf("%d %-20s %d %-15s %f\n", buffer.id, buffer.description, buffer.stock, buffer.supplier, buffer.cost);
        fread(&buffer, sizeof(article), 1, db_ptr);
    }

    printf("\n");
    rewind(db_ptr);
}

void print_suppliers(FILE *db_ptr)
{
    FILE *suppliers_list;
    article buffer;
    int supplier_found = FALSE, total_suppliers = 0;
    char supplier_name[MAX_SUPPLIER_LENGTH];

    if (!(suppliers_list = fopen("SUPPLIERS", "w+b"))) //I would have used a tmpfile but windows won't let me
    {
        printf("ERROR: couldn't open SUPPLIERS file.");
        exit(1);
    }

    fread(&buffer, sizeof(article), 1, db_ptr);
    while(!feof(db_ptr))
    {
        fseek(suppliers_list, (long) 0, SEEK_END);
        total_suppliers = ftell(suppliers_list)/MAX_SUPPLIER_LENGTH;
        rewind(suppliers_list);

        fread(&supplier_name, MAX_SUPPLIER_LENGTH, 1, suppliers_list);
        while(!feof(suppliers_list) && (total_suppliers!=0)) //If the list is empty we will write into it directly
        {
            if(!(strcmp(buffer.supplier, supplier_name)))//If the supplier is in the list we raise a flag
            {
                supplier_found = TRUE;
                break;
            }
            fread(&supplier_name, MAX_SUPPLIER_LENGTH, 1, suppliers_list);
        }

        if(!supplier_found)// If the flag hasn't being raised we include the supplier in the list
        {
            fseek(suppliers_list, (long) 0, SEEK_END);
            fwrite(&buffer.supplier, MAX_SUPPLIER_LENGTH, 1, suppliers_list);
            printf("%-15s\n", buffer.supplier);
        }

        supplier_found = FALSE;
        fread(&buffer, sizeof(article), 1, db_ptr);
    }

    rewind(db_ptr);
    fclose(suppliers_list);
    remove("SUPPLIERS");
}

void increase_price(FILE *db_ptr, char supplier[], float percentage)
{
    article buffer;

    fread(&buffer, sizeof(article), 1, db_ptr); //We read before and at the end of the loop to prevent double reading the last article, which would cause an infinite loop since the eof indicator resets due to fseek so feof==0 always for the last article
    while(!feof(db_ptr))
    {
        if(!strcmp(buffer.supplier, supplier))
        {
            printf("OLD %d %-15s %f %d\n", buffer.id, buffer.supplier, buffer.cost, ftell(db_ptr)/sizeof(article));
            buffer.cost+=buffer.cost * (percentage/100);
            fseek(db_ptr, (long) -1 * (long)sizeof(article), SEEK_CUR);
            printf("NEW %d %-15s %f %d\n", buffer.id, buffer.supplier, buffer.cost, ftell(db_ptr)/sizeof(article));
            fwrite(&buffer, sizeof(article), 1, db_ptr);
            fseek(db_ptr, (long) 0, SEEK_CUR);
            getchar();
        }
       fread(&buffer, sizeof(article), 1, db_ptr);
    }
    getchar();
    rewind(db_ptr);
}

void alphabetical_index(FILE *db_ptr)
{
    FILE *index_ptr;
    article article_buffer;
    index_item index_buffer;

    if(!(index_ptr = fopen("INDEX_AZ", "w+b")))
    {
        printf("ERROR: couldn't open an alphabetical index file.");
        exit(1);
    }

    fread(&article_buffer, sizeof(article), 1, db_ptr);
    while(!feof(db_ptr))
    {
        index_buffer.id = article_buffer.id;
        index_buffer.pos = ftell(db_ptr)/sizeof(article)-1; //We subtract one so that the first article has position 0
        fwrite(&index_buffer, sizeof(index_item), 1, index_ptr);
        fread(&article_buffer, sizeof(article), 1, db_ptr);
    }

    rewind(index_ptr);
    bubble_sort(db_ptr, index_ptr);

    fclose(index_ptr);
}

void low_stock_index(FILE *db_ptr)
{
    FILE *index_ptr;
    article article_buffer;
    index_item index_buffer;

    if(!(index_ptr = fopen("INDEX_LS", "w+b")))
    {
        printf("ERROR: couldn't open a low stock index file.");
        exit(1);
    }

    fread(&article_buffer, sizeof(article), 1, db_ptr);
    while(!feof(db_ptr))
    {
        if(article_buffer.stock < 5)
        {
            index_buffer.id = article_buffer.id;
            index_buffer.pos = ftell(db_ptr)/sizeof(article)-1; //We subtract one so that the first article has position 0. If we don't, accessing the article using fseek and pos returns a different article
            fwrite(&index_buffer, sizeof(index_item), 1, index_ptr);
        }
        fread(&article_buffer, sizeof(article), 1, db_ptr);
    }

    fclose(index_ptr);
}

void print_sorted_db(FILE *db_ptr)
{
    FILE *index_ptr;
    article article_buffer;
    index_item index_buffer;

    if(!(index_ptr = fopen("INDEX_AZ", "r+b")))
    {
        printf("ERROR: couldn't open a low stock index file.");
        exit(1);
    }

    fread(&index_buffer, sizeof(index_item), 1, index_ptr);
    while(!feof(index_ptr))
    {
        fseek(db_ptr, (long) index_buffer.pos * sizeof(article), SEEK_SET);
        fread(&article_buffer, sizeof(article), 1, db_ptr);
        printf("%d %-20s %d %-15s %f %d\n", article_buffer.id, article_buffer.description, article_buffer.stock, article_buffer.supplier, article_buffer.cost, index_buffer.pos);
        fread(&index_buffer, sizeof(index_item), 1, index_ptr);
    }
    rewind(db_ptr);
}

void print_low_stock_db(FILE *db_ptr)
{
    FILE *index_ptr;
    article article_buffer;
    index_item index_buffer;

    if(!(index_ptr = fopen("INDEX_LS", "r+b")))
    {
        printf("ERROR: couldn't open a low stock index file.");
        exit(1);
    }

    fread(&index_buffer, sizeof(index_item), 1, index_ptr);
    while(!feof(index_ptr))
    {
        fseek(db_ptr, (long) index_buffer.pos * sizeof(article), SEEK_SET);
        fread(&article_buffer, sizeof(article), 1, db_ptr);
        printf("%d %-20s %d %-15s %f\n", article_buffer.id, article_buffer.description, article_buffer.stock, article_buffer.supplier, article_buffer.cost);
        fread(&index_buffer, sizeof(index_item), 1, index_ptr);
    }
    rewind(db_ptr);
}

void bubble_sort(FILE *db_ptr, FILE *index_ptr)
{
    index_item buffer, item1, item2;
    article article1, article2;
    int counter1, counter2, total_articles;

    fseek(db_ptr, (long) 0, SEEK_END);
    total_articles = ftell(db_ptr)/sizeof(article);
    rewind(db_ptr);

    for(counter1=0;counter1<total_articles-1;counter1++)
    {
        for(counter2=0;counter2<total_articles-counter1-1;counter2++)
        {
            fseek(index_ptr, (long) counter2 * sizeof(index_item), SEEK_SET);
            fread(&item1, sizeof(index_item), 1, index_ptr);
            fread(&item2, sizeof(index_item), 1, index_ptr);

            fseek(db_ptr, (long) item1.pos * sizeof(article), SEEK_SET);
            fread(&article1, sizeof(article), 1, db_ptr);
            fseek(db_ptr, (long) item2.pos * sizeof(article), SEEK_SET);
            fread(&article2, sizeof(article), 1, db_ptr);
            if(strcmp(article1.description, article2.description) > 0) //If the first article goes after the second alphabetically we have to swap
            {
                buffer = item1;
                item1 = item2;
                item2 = buffer;

                fseek(index_ptr, (long) -2 * (long) sizeof(index_item), SEEK_CUR);
                fwrite(&item1, sizeof(index_item), 1, index_ptr);
                fwrite(&item2, sizeof(index_item), 1, index_ptr);
            }
        }
    }
    rewind(index_ptr);
    rewind(db_ptr);
}

