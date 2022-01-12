#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Realizar un programa que busque una palabra en un archivo de texto. Indique la cantidad
de ocurrencias de la palabra, o bien su ausencia. El usuario ingresará el nombre del archivo
en donde buscar y la palabra que será buscada. La palabra puede tener un máximo de 10
caracteres.
**/

///NOTE(23/12/2021): In this implementation I try limiting the number of functions from string.h used to operate on the strings and
///                  detect the words within the text.
///                  I found out by accident that fopen accepts null terminated strings as arguments.

#define MAX_PATH_LENGTH 50
#define MAX_WORD_LENGTH 15

///Function that was intended to remove the null terminator, although it did so wrong and wasn't necessary in the end
/*
void null_terminator_remover(char src[], char dst[], int str_length);

void null_terminator_remover(char src[], char dst[], int str_length) //The function requires dst to be of size str_length-1
{
    int character_counter;

    for(character_counter = 0;character_counter<str_length-1;character_counter++)
    {
        dst[character_counter] = src[character_counter];
    }
}
*/
int main()
{
    char path[MAX_PATH_LENGTH], word[MAX_WORD_LENGTH], * dynamic_string, word_buffer[MAX_WORD_LENGTH];
    FILE * file_pointer;
    int character_counter = 0, file_size, counter, word_counter = 0;

    printf("Enter file path: ");
    gets(path);

    //null_terminator_remover(path, path_buffer, MAX_PATH_LENGTH);

    if(!(file_pointer=fopen(path, "r")))
    {
        printf("ERROR: couldn't open file %s", path);
        exit(1);
    }

    fseek(file_pointer, (long) 0, SEEK_END);
    file_size = ftell(file_pointer);
    fseek(file_pointer, (long) 0, SEEK_SET);

    dynamic_string = (char *) malloc(file_size * sizeof(char));

    while(!feof(file_pointer)) //This is a different way to load the text in dynamic memory and show it
    {
        dynamic_string[character_counter] = fgetc(file_pointer);
        fputc(dynamic_string[character_counter], stdout);
        character_counter++;
    }

    printf("\n\nFile opened successfully. Enter the word to be searched for: ");
    gets(word);

    for(character_counter=0;character_counter<(file_size * sizeof(char));character_counter++) //this loop parses the text into words
    {
        if(dynamic_string[character_counter]!=' ' && dynamic_string[character_counter]!=',' && dynamic_string[character_counter]!='.')
        {
            for(counter=0;counter<MAX_WORD_LENGTH-1;counter++)
            {
                if(dynamic_string[character_counter+counter]==' ' || dynamic_string[character_counter+counter]==',' ||
                   dynamic_string[character_counter+counter]=='.')
                    break;
                word_buffer[counter] = dynamic_string[character_counter+counter];
                //printf("%c", word_buffer[counter]);
            }
            word_buffer[counter]='\0';
            character_counter+=counter; //We take into account the characters that have been analyzed
            printf(" *%s* ", word_buffer);
            if(!strcmp(word_buffer, word))
                word_counter++;
        }
    }

    printf("\n The word %s was found %d times in the text file.", word, word_counter);


    if(file_pointer)
        fclose(file_pointer);

    if(dynamic_string)
        free(dynamic_string);

    return 0;
}
