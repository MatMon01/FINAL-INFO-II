#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ARTI{
    short int ART;
    char COD[50];
    char DESC[100];
    char FAB[50];
    short int STOCK;
};

typedef struct index_item_s{
    short int ART;
    int POS;
} index_item;

void print_articles(FILE * file_ptr);
void print_low_stock(FILE * file_ptr);
void find_supplier(FILE * file_ptr);
void search_article(FILE * file_ptr);
void index_file(FILE * file_ptr, FILE * index_file_ptr);
void bubble_sort(FILE * file_ptr, FILE * index_file_ptr);
int binary_search_article(FILE * file_ptr, FILE * index_file_ptr, int ART);

///NOTE (5/1/2022): Exercise from https://www.youtube.com/watch?v=fo8acVsMgpE . Should test the algorithm that finds the manufacturer
///                 that makes the most products.

void print_articles(FILE * file_ptr)
{
    struct ARTI buffer;

    printf("ARTICLE %-50s %-100s %-50s STOCK\n", "CODE", "DESCRIPTION", "MANUFACTURER");
    fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
    while(!feof(file_ptr))
    {
        printf("%d %-50s %-100s %-50s %d\n",
                buffer.ART, buffer.COD, buffer.DESC, buffer.FAB, buffer.STOCK);
        fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
    }
    printf("\n");
}
void print_low_stock(FILE * file_ptr)
{
    struct ARTI buffer;

    printf("ARTICLE %-50s %-100s %-50s STOCK\n", "CODE", "DESCRIPTION", "MANUFACTURER");
    fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
    while(!feof(file_ptr))
    {
        if(buffer.STOCK<8)
            printf("%d %-50s %-100s %-50s %d\n", buffer.ART, buffer.COD, buffer.DESC, buffer.FAB, buffer.STOCK);
        fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
    }
    printf("\n");
}
void find_supplier(FILE * file_ptr)
{
    FILE * extra_file_ptr;
    struct ARTI buffer;
    int total_suppliers, counter1, counter2, total_articles, article_counter, manuf_articles;
    char manufacturer[50], flag_supplier_found = 0, most_prod_manuf[50];

    if(!(extra_file_ptr = fopen("extra_file", "w+b")))
    {
        printf("Couldn't open extra file.");
        exit(1);
    }

    fseek(file_ptr, (long) 0, SEEK_END);
    total_articles = ftell(file_ptr)/sizeof(struct ARTI);
    rewind(file_ptr);

    total_suppliers=0;article_counter=0;manuf_articles=0;

    for(counter1=0;counter1<total_articles;counter1++)
    {
        fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
        for(counter2=0;counter2<counter1;counter2++)
        {
            fread(&manufacturer, 50, 1, extra_file_ptr);
            if(!strcmp(manufacturer, buffer.FAB))
            {
                flag_supplier_found=1;
                break;
            }
        }

        if(flag_supplier_found==0 || counter2==0)
        {
            strcpy(manufacturer, buffer.FAB);
            printf("%-50s \n", manufacturer);
            fseek(extra_file_ptr, (long) 0, SEEK_END);
            fwrite(&manufacturer, 50, 1, extra_file_ptr);
            total_suppliers++;
        }
        flag_supplier_found=0;
        rewind(extra_file_ptr);
    }
    rewind(file_ptr);

    for(counter1=0;counter1<total_suppliers;counter1++)
    {
        fread(&manufacturer, 50, 1, extra_file_ptr);
        for(counter2=0;counter2<total_articles;counter2++)
        {
            fread(&buffer, sizeof(struct ARTI), 1, file_ptr);

            if(!strcmp(buffer.FAB, manufacturer))
                article_counter++;
        }

        if(article_counter>manuf_articles)
        {
            manuf_articles=article_counter;
            strcpy(most_prod_manuf, manufacturer);
        }
        rewind(file_ptr);
    }

    printf("The manufacturer that produces the most products is %s"
           " with %d products\n", most_prod_manuf, manuf_articles);
    fclose(extra_file_ptr);
    remove("extra_file");
}
void search_article(FILE * file_ptr)
{
    int article_number, flag_found = 0;
    struct ARTI buffer;

    printf("ARTICLE SEARCH: Input an article number. Input zero to continue:\n");
    scanf("%d", &article_number);

    while(article_number!=0)
    {

        fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
        while(!feof(file_ptr))
        {
            if(buffer.ART==article_number)
            {
                printf("Article found\n"
                       "ARTICLE %-50s %-100s %-50s STOCK\n", "CODE", "DESCRIPTION", "MANUFACTURER");
                printf("%d %-50s %-100s %-50s %d\n",
                       buffer.ART, buffer.COD, buffer.DESC, buffer.FAB, buffer.STOCK);
                flag_found=1;
            }
            fread(&buffer, sizeof(struct ARTI), 1, file_ptr);
        }

        if(flag_found==0)
            printf("Article not found\n");

        flag_found=0;
        rewind(file_ptr);

        printf("ARTICLE SEARCH: Input an article number. Input zero to continue:\n");
        scanf("%d", &article_number);
    }
}
void index_file(FILE * file_ptr, FILE * index_file_ptr)
{
    index_item index_buffer;
    struct ARTI article_buffer;

    fread(&article_buffer, sizeof(struct ARTI), 1, file_ptr);
    while(!feof(file_ptr))
    {
        index_buffer.ART=article_buffer.ART;
        index_buffer.POS=ftell(file_ptr)/sizeof(struct ARTI) - 1;

        fwrite(&index_buffer, sizeof(index_item), 1, index_file_ptr);
        fread(&article_buffer, sizeof(struct ARTI), 1, file_ptr);
    }
}
void bubble_sort(FILE * file_ptr, FILE * index_file_ptr)
{
    int total_articles, counter1, counter2;
    struct ARTI article1, article2;
    index_item item1, item2, buffer;

    fseek(file_ptr, (long) 0, SEEK_END);
    total_articles=ftell(file_ptr)/sizeof(struct ARTI);
    rewind(file_ptr);

    for(counter1=0;counter1<total_articles-1;counter1++)
    {
        for(counter2=0;counter2<total_articles-counter1-1;counter2++)
        {
            fseek(index_file_ptr, (long) counter2 * sizeof(index_item), SEEK_SET);

            fread(&item1, sizeof(index_item), 1, index_file_ptr);
            fseek(file_ptr, (long) item1.POS * sizeof(struct ARTI), SEEK_SET);
            fread(&article1, sizeof(struct ARTI), 1, file_ptr);

            fread(&item2, sizeof(index_item), 1, index_file_ptr);
            fseek(file_ptr, (long) item2.POS * sizeof(struct ARTI), SEEK_SET);
            fread(&article2, sizeof(struct ARTI), 1, file_ptr);

            if(article1.ART>article2.ART)
            {
                buffer=item1;
                item1=item2;
                item2=buffer;

                fseek(index_file_ptr, (long) -2 * (long) sizeof(index_item), SEEK_CUR);
                fwrite(&item1, sizeof(index_item), 1, index_file_ptr);
                fwrite(&item2, sizeof(index_item), 1, index_file_ptr);
            }
        }
    }

    rewind(file_ptr);
    rewind(index_file_ptr);
}
int binary_search_article(FILE * file_ptr, FILE * index_file_ptr, int ART)
{
    int h_bound, l_bound, middle, total_articles;
    index_item index_buffer;
    struct ARTI article_buffer;

    fseek(file_ptr, (long) 0, SEEK_END);
    total_articles=ftell(file_ptr)/sizeof(struct ARTI);
    rewind(file_ptr);

    l_bound=0;
    h_bound=total_articles-1;

    while(l_bound<=h_bound)
    {
        middle=(l_bound+h_bound)/2;
        fseek(index_file_ptr, (long) middle * sizeof(index_item), SEEK_SET);
        fread(&index_buffer, sizeof(index_item), 1, index_file_ptr);
        fseek(file_ptr, (long) index_buffer.POS * sizeof(struct ARTI), SEEK_SET);
        fread(&article_buffer, sizeof(struct ARTI), 1, file_ptr);
        printf("\n%d %d %d\n", l_bound, middle, h_bound);
        if(article_buffer.ART==ART)
        {
            printf("Article found\n" "ARTICLE %-50s %-100s %-50s STOCK\n",
                                                "CODE", "DESCRIPTION", "MANUFACTURER");
            printf("%d %-50s %-100s %-50s %d\n",
                       article_buffer.ART, article_buffer.COD, article_buffer.DESC, article_buffer.FAB, article_buffer.STOCK);
            return middle;
        }
        if(article_buffer.ART>ART)
            h_bound=middle-1;
        if(article_buffer.ART<ART)
            l_bound=middle+1;
    }

    return -1;
}

int main()
{
    FILE * file_ptr, * index_file_ptr;
    int ART;

    if(!(file_ptr=fopen("BDARTICULOS", "r+b")))
    {
        printf("ERROR: couldn't open database file.");
        exit(1);
    }
    if(!(index_file_ptr=fopen("BDINDEX", "w+b")))
    {
        printf("ERROR: couldn't open index file.");
        exit(1);
    }

    print_articles(file_ptr);

    print_low_stock(file_ptr);

    find_supplier(file_ptr);

    search_article(file_ptr);

    index_file(file_ptr, index_file_ptr);
    printf("\nSORTING...\n");
    bubble_sort(file_ptr, index_file_ptr);

    int A;
    index_item index_buf;
    struct ARTI art_buf;
    fread(&index_buf, sizeof(index_item), 1, index_file_ptr);
    while(!feof(index_file_ptr))
    {
        A=fseek(file_ptr, (long) index_buf.POS * sizeof(struct ARTI), SEEK_SET);
        fread(&art_buf, sizeof(struct ARTI), 1, file_ptr);
        printf("%d %s %s %s %d %d %d\n",
                       art_buf.ART, art_buf.COD, art_buf.DESC, art_buf.FAB, art_buf.STOCK, index_buf.POS, A);
        fread(&index_buf, sizeof(index_item), 1, index_file_ptr);
    }

    rewind(index_file_ptr);
    rewind(file_ptr);

    printf("ARTICLE SEARCH: Input an article number. Input zero to continue:\n");
    scanf("%d", &ART);
    while(ART!=0)
    {
        //printf("%d\n", binary_search_article(file_ptr, index_file_ptr, ART));
        if(binary_search_article(file_ptr, index_file_ptr, ART) == -1)
            printf("Article not found.\n");

        printf("ARTICLE SEARCH: Input an article number. Input zero to continue:\n");
        scanf("%d", &ART);
    }

    return 0;
}
