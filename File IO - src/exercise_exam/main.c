#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Se cuenta con un archivo ATLETAS, conteniendo información de un Juego Olímpico en registros con esta forma:

struct atleta {
		char NOMBRE[50];
		char DISCIPLINA[30];
		int ORO;
		int PLATA;
		int BRONCE;
};

Este archivo indica las medallas obtenidas por los atletas en cada disciplina.
ORO, PLATA y BRONCE tienen un 1 si el atleta la obtuvo, ó 0 en caso contrario.
Un atleta, en una disciplina, puede ganar una de estas medallas o bien ninguna.

Por otro lado, se cuenta con un archivo DISCIPLINAS, con registros de esta forma:

struct disciplina {
		char NOMBRE[30];
		char ORO[50];
};

El archivo DISCIPLINAS solamente tiene los nombres de ellas, el campo ORO está vacio.


Se pide, en un solo programa:

1) Imprimir en pantalla los ATLETAS, para verificar que la lectura del archivo es correcta y visualizar los datos.

2) Actualizar el archivo DISCIPLINAS para que contenga en el campo ORO el nombre del atleta que lo obtuvo.

3) Mostrar en pantalla el archivo DISCIPLINAS para corroborar los resultados.

4) Mostrar en pantalla los nombres de los atletas sin repetir.
No modificar el archivo ATLETAS original.
En el ejemplo proporcionado Pepe Gomez y Maria Perez compitieron en varias disciplinas (no deben verse repetidos).
*/

struct atleta{
    char NOMBRE[50];
    char DISCIPLINA[30];
    int ORO;
    int PLATA;
    int BRONCE;
};

struct disciplina{
    char NOMBRE[30];
    char ORO[50];
};

///Note (14/1/2022): This program has been transcrypted from a handwritten notebook. Minor errors were fixed.

int main()
{
    FILE * athletes_file_ptr, * disciplines_file_ptr, * names_file_ptr;
    struct atleta athlete_buffer;
    struct disciplina discipline_buffer;
    char name_buf[50];
    int name_flag=0;

    if (!(athletes_file_ptr=fopen("ATLETAS", "r+b"))){
        printf("Error en la apertura del archivo ATLETAS.\n");
        exit(1);
    }
    if (!(disciplines_file_ptr=fopen("DISCIPLINAS", "r+b"))){
        printf("Error en la apertura del archivo DISCIPLINAS.\n");
        exit(1);
    }

    fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    while (!feof(athletes_file_ptr)){
        printf("%-30s %-50s ORO: %d PLATA: %d BRONCE: %d\n", athlete_buffer.DISCIPLINA, athlete_buffer.NOMBRE, athlete_buffer.ORO, athlete_buffer.PLATA, athlete_buffer.BRONCE);
        fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    }
    rewind(athletes_file_ptr);


    fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    while (!feof(athletes_file_ptr)){
       fread(&discipline_buffer, sizeof(struct disciplina), 1, disciplines_file_ptr);
       while (!feof(disciplines_file_ptr)){
        if (!strcmp(discipline_buffer.NOMBRE, athlete_buffer.DISCIPLINA) && (athlete_buffer.ORO==1)){
            strcpy(discipline_buffer.ORO, athlete_buffer.NOMBRE);
            break;
        }
        fread(&discipline_buffer, sizeof(struct disciplina), 1, disciplines_file_ptr);
       }
       rewind(disciplines_file_ptr);
       fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    }
    rewind(athletes_file_ptr);

    fread(&discipline_buffer, sizeof(struct disciplina), 1, disciplines_file_ptr);
    while (!feof(disciplines_file_ptr)){
        printf("%-30s ORO: %-50s\n", discipline_buffer.NOMBRE, discipline_buffer.ORO);
        fread(&discipline_buffer, sizeof(struct disciplina), 1, disciplines_file_ptr);
    }
    rewind(disciplines_file_ptr);

    if(!(names_file_ptr=fopen("athletes_names", "w+b"))){
        printf("Error, no se pudo abrir un archivo auxiliar.\n");
        exit(1);
    }

    fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    while (!feof(athletes_file_ptr)){
        fread(&name_buf, 50, 1, names_file_ptr); //The first time we read the file it's empty, we will be reading outside the file so feof()==0
        //printf("%d\n", !feof(names_file_ptr));
        while (!feof(names_file_ptr)){
            if (!strcmp(name_buf, athlete_buffer.NOMBRE)){
                name_flag=1;
                break;
            }
            fread(&name_buf, 50, 1, names_file_ptr);
        }
        if (!name_flag){
            fseek(names_file_ptr, 0, SEEK_END);
            strcpy(name_buf, athlete_buffer.NOMBRE);
            fwrite(&name_buf, 50, 1, names_file_ptr);
        }
        rewind(names_file_ptr);
        name_flag=0;
        fread(&athlete_buffer, sizeof(struct atleta), 1, athletes_file_ptr);
    }

    fread(&name_buf, 50, 1, names_file_ptr);
    while (!feof(names_file_ptr)){
        printf("%-50s\n", name_buf);
        fread(&name_buf, 50, 1, names_file_ptr);
    }

    fclose(names_file_ptr);
    fclose(athletes_file_ptr);
    fclose(disciplines_file_ptr);

    return 0;
}
