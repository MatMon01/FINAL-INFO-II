#define MAX_NAME_LENGTH 50
#define TOTAL_EXAMS 4

typedef struct student_data_s {
    char name[MAX_NAME_LENGTH];
    float exam_score[TOTAL_EXAMS];
} student_data;



void main_menu(void);

void select_command(char  command[]);

void new_record(student_data record[]);
void add(student_data record[]);
void search_student(student_data record[]);
void change_marks(student_data record[]);
void average(student_data record[]);
void sort_record(student_data record[]);
