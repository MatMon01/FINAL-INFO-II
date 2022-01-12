/*  LA CLASE LISTA TIENE NODOS CON NOMBRE Y PUNTAJE DE PERSONALIDADES  */
/*  QUE COMPITEN EN UN CONCURSO DE POPULARIDAD  */
/*  LA CLASE LISTA NEGRA, TIENE VOTOS NEGATIVOS SOBRE CADA UNO DE LOS  */
/*  CANDIDATOS  */
/*  SE DEBE ACTUALIZAR LISTA HACIENDO QUE POR CADA VOTO NEGATIVO EN    */
/*  LISTANEGRA, SE LE DESCUENTE UN PUNTO AL CANDIDATO. EN CASO QUE ESTE */
/*  NO POSEA MAS PUNTOS, SE LO DEBE DAR DE BAJA  */
/*  CONSTRUIR LA FUNCION IMPUGNA(), CUYO PROTOTIPO SE ADJUNTA, DE FORMA */
/*  QUE REALICE LO PEDIDO */
/*  REALIZAR EL AGREGADO EN LAS CLASES QUE CONSIDERE CONVENIENTE  */


#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_VOTOS 15

using namespace std ;

class CANDI {
	public :
		char NOM[20];
		int VOTOS ;
		CANDI * SIG ;
};

class LISTA {
	private :
		CANDI * INICIO ;
		void delete_node(CANDI *);
	public :
		LISTA() ;
		void MIRAR() ;
		void count_votes(char*, int);
		char* get_names();
		void drop();
		int get_list_size();
};

LISTA :: LISTA ()
{
	int I ;
	CANDI * P ;
	char NOM[][20] = { "PEPE" , "LOLA" , "LAURA" , "CACHO" ,
			   "ANSELMO" , "MARIANO" , "MONICA" , "ANA" ,
			   "EDELMIRO" , "JOSE" , "MIRTA" , "SUSANA" ,
			   "FELIPE" , "ENZO" , "BETO" , "PACO" } ;
	INICIO = NULL ;
	for ( I=0 ; I<16 ; I++ ) {
		P = new CANDI ;
		strcpy ( P->NOM , NOM [ I ] ) ;
		P->VOTOS = 1 + rand()% MAX_VOTOS ;
		P->SIG = INICIO ;
		INICIO = P ;
	}
}

void LISTA :: MIRAR ()
{
	CANDI * P ;
	P = INICIO ;
	cout << "\n\n\n" ;
	while ( P ) {
		printf ( "     %-10s%5d" , P->NOM , P->VOTOS) ;
		P = P->SIG ;
	}
	getch();
}

int LISTA :: get_list_size()
{
    CANDI * scan_ptr=INICIO;
    int counter=0;

    while(scan_ptr)
    {
        counter++;
        scan_ptr=scan_ptr->SIG;
    }

    return counter;
}

char * LISTA :: get_names() //If the function reaches the null pointer at the end it will return trash, so we rely on an outside mechanism to control this
{
    CANDI * scan_ptr=INICIO;
    static int position=0;
    int counter;

    for(counter=0;counter<position && scan_ptr;counter++)
        scan_ptr=scan_ptr->SIG;

    printf("%s %d\n", scan_ptr->NOM, position);
    position++;

    return scan_ptr->NOM;
}

void LISTA :: count_votes(char name[], int votes_against)
{
    CANDI * scan_ptr=INICIO;

    while(strcmp(scan_ptr->NOM, name))
        scan_ptr=scan_ptr->SIG;

    if(!strcmp(scan_ptr->NOM, name))
    {
        scan_ptr->VOTOS-=votes_against;
        printf("CONTEO: %s %d\n", scan_ptr->NOM, scan_ptr->VOTOS);
    }
}

void LISTA :: drop()
{
    CANDI * scan_ptr=INICIO;

    printf("Eliminando candidatos\n");
    while(scan_ptr)
    {
        if(scan_ptr->VOTOS<=0)
            delete_node(scan_ptr);
        scan_ptr=scan_ptr->SIG;
        //printf(" %s %p \n", scan_ptr->NOM, scan_ptr);
    }
}

void LISTA :: delete_node(CANDI * del_ptr)
{
    CANDI * scan_ptr=INICIO;

    printf(" %s %p \n", del_ptr->NOM, del_ptr);

    if(INICIO==del_ptr)
    {
        INICIO=del_ptr->SIG;
        delete del_ptr;
        return;
    }

    while(scan_ptr->SIG!=del_ptr && scan_ptr)
    {
        scan_ptr=scan_ptr->SIG;
    }
    if(scan_ptr)
    {
        scan_ptr->SIG=del_ptr->SIG;
        delete del_ptr;
    }
}





class PERSONA {
	public :
		char NOM[20];
		PERSONA * SIG ;
};

class LISTANEGRA {
	private :
		PERSONA * INICIO ;
	public :
		LISTANEGRA() ;
		void MIRAR() ;
		int votes_against(char *);
};

LISTANEGRA :: LISTANEGRA ()
{
	int I ;
	PERSONA * P ;
	char NOM[][20] = { "PEPE" , "LOLA" , "LAURA" , "CACHO" ,
			   "ANSELMO" , "MARIANO" , "MONICA" , "ANA" ,
			   "EDELMIRO" , "JOSE" , "MIRTA" , "SUSANA" ,
			   "FELIPE" , "ENZO" , "BETO" , "PACO" } ;
	INICIO = NULL ;
	for ( I=0 ; I<100 ; I++ ) {
		P = new PERSONA ;
		strcpy ( P->NOM , NOM [ rand()%16 ] ) ;
		P->SIG = INICIO ;
		INICIO = P ;
	}
}

void LISTANEGRA :: MIRAR ()
{
	PERSONA * P ;
	P = INICIO ;
	cout << "\n\n\n" ;
	while ( P ) {
		printf ( "%-10s" , P->NOM ) ;
		P = P->SIG ;
	}
	getch();
}

int LISTANEGRA :: votes_against(char name[])
{
    PERSONA * scan_ptr=INICIO;
    int votes_counter=0;

    while(scan_ptr)
    {
        if(!strcmp(name, scan_ptr->NOM))
            votes_counter++;
        scan_ptr=scan_ptr->SIG;
    }

    return votes_counter;
}


/*  PROTOTIPO  */
void IMPUGNA ( LISTA & , LISTANEGRA & );

void IMPUGNA ( LISTA & candidate_list, LISTANEGRA & black_list)
{
    char buffer[50];
    int counter, total_nodes=candidate_list.get_list_size();

    for(counter=0;counter<total_nodes;counter++)
    {
        strcpy(buffer, candidate_list.get_names());
        //printf("* %s \n", buffer);
        candidate_list.count_votes(buffer, black_list.votes_against(buffer));
    }

    candidate_list.drop();
}

///NOTE (9/1/2022): The solution which I found is to work within the function IMPUGNA. This involves the creation of a member function for
///                 the LISTA object that returns either a pointer to a candidate or it's name, some reference in order to count the number
///                 of votes against.
///                 The final program somehow feels counterintuitive, might re do later.

int main()
{
	LISTA L ;
	L.MIRAR() ;
	LISTANEGRA N ;
	N.MIRAR() ;

	IMPUGNA ( L , N );

	L.MIRAR() ;

	cout << "\n\n\nFIN DEL PROGRAMA  " ;
	getch();
	return 0 ;
}
