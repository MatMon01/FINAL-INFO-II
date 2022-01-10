#define MAX_DESCRIPTION_LENGTH 20
#define MAX_SUPPLIER_LENGTH 15

typedef struct article_s{
    int id;
    char description[MAX_DESCRIPTION_LENGTH];
    int stock;
    char supplier[MAX_SUPPLIER_LENGTH];
    float cost;
} article;

typedef struct index_item_s{
    int id;
    int pos;
}   index_item;

void print_database(FILE *db_ptr);
void print_suppliers(FILE *db_ptr);
void increase_price(FILE *db_ptr, char supplier[], float percentage);
void alphabetical_index(FILE *db_ptr);
void low_stock_index(FILE *db_ptr);
void print_sorted_db(FILE *db_ptr);
void print_low_stock_db(FILE *db_ptr);
void bubble_sort(FILE *db_ptr, FILE *index_ptr);
