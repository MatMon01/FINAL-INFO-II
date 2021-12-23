#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Realizar un programa que busque una palabra en un archivo de texto. Indique la cantidad
de ocurrencias de la palabra, o bien su ausencia. El usuario ingresará el nombre del archivo
en donde buscar y la palabra que será buscada. La palabra puede tener un máximo de 10
caracteres.
**/

///NOTE: this implementation of a solution strongly depends on strtok, a string.h function, to work.
///      I might explore making a program that works without such tool, working directly on the text string
///      since the heavy reliance of this implementation on knowledge of strtok somehow makes it counterintuitive
///      (for instance: in the loop that detects the word searched it was necessary
///      to use an extra variable (buf_start) for the loop condition since strcpy does not work if given a NULL pointer,
///      something which I never had to think about. There might be a different, less obscure solution)

#define MAX_PATH_LENGTH 50
#define MAX_WORD_LENGTH 15

int main()
{
    char path[MAX_PATH_LENGTH], word[MAX_WORD_LENGTH], buffer[MAX_WORD_LENGTH], * dynamic_string, character, * buf_start;
    FILE * file_pointer;
    int character_counter = 0, file_size = 0, word_counter = 0;

    printf("Enter the filename: ");
    gets(path); //the problem with gets is that the program is vulnerable to buffer overflows

    if(!(file_pointer = fopen(strtok(path, ""), "r"))) //strtok tokenizes the path string using the null character as a delimiter, we remove \0 at the end thus making the str look like a const str
    {
        printf("ERROR: couldn't open file %s", path);
        exit(1);
    }

    fseek(file_pointer, (long) 0, SEEK_END); //we obtain the number of characters in the file
    file_size = ftell(file_pointer);
    fseek(file_pointer, (long) 0, SEEK_SET);

    dynamic_string = (char *) malloc(file_size * sizeof(char));
    character=fgetc(file_pointer);
    while((character)!=EOF)
    {
        dynamic_string[character_counter] = character;
        putchar(dynamic_string[character_counter]);
        character=fgetc(file_pointer);
        character_counter++;
    }


    printf("\nInput word to count: ");
    gets(word);

    buf_start = strtok(dynamic_string, ", .");
    while(buf_start!=NULL)
    {
        strcpy(buffer, buf_start); //the reason behind calling strtok with a null pointer in subsequent calls is in it's documentation.
        if(!strcmp(word, buffer))
            word_counter++;
        printf("%d %s\n", word_counter, buffer);
        buf_start = strtok(NULL, ", .");
        printf("A\n");
    }

    printf("The number of times the word %s appears in the file %s is %d", word, path, word_counter);

    if(file_pointer)
        fclose(file_pointer);
    if(dynamic_string)
        free(dynamic_string);

    return 0;
}
