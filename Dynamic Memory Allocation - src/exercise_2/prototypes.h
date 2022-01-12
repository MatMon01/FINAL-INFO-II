#define MAX_NAME_LENGTH 50
#define TOTAL_EXAMS 4

typedef struct student_data_s {
    char name[MAX_NAME_LENGTH];
    float exam_score[TOTAL_EXAMS];
} student_data;



void main_menu(void);

void select_command(char  command[], student_data **record_ptr, int *record_size_ptr);

void new_record(student_data **record_ptr, int *record_size_ptr);
void add(student_data **record_ptr, int *record_size_ptr);
void search_student(student_data **record_ptr, int *record_size_ptr);
void change_marks(student_data **record_ptr, int *record_size_ptr);
void average(student_data **record_ptr, int *record_size_ptr);
void sort_record(student_data **record_ptr, int *record_size_ptr);
void append_student(student_data **record_ptr, int *record_size_ptr);
void bubble_sort(student_data **record_ptr, int *record_size_ptr);
student_data* find_student(student_data **record_ptr, int *record_size_ptr, char name[]);
