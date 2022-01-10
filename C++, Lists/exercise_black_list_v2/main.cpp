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
		void count_vote(char*);
		void drop();
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

void LISTA :: count_vote(char name[])
{
    CANDI * scan_ptr=INICIO;

    while(scan_ptr)
    {
        if(!strcmp(scan_ptr->NOM, name))
            scan_ptr->VOTOS-=1;
        scan_ptr=scan_ptr->SIG;
    }
}

void LISTA :: drop()
{
    CANDI * scan_ptr=INICIO;

    while(scan_ptr)
    {
        if(scan_ptr->VOTOS<=0)
            delete_node(scan_ptr);
        scan_ptr=scan_ptr->SIG;
    }
}

void LISTA :: delete_node(CANDI * del_ptr)
{
    CANDI * scan_ptr=INICIO;

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
		void count_votes_against(LISTA *);
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

void LISTANEGRA :: count_votes_against(LISTA * candidate_list)
{
    PERSONA * scan_ptr=INICIO;

    while(scan_ptr)
    {
        candidate_list->count_vote(scan_ptr->NOM);
        scan_ptr=scan_ptr->SIG;
    }

    candidate_list->drop();
}

/*  PROTOTIPO  */
void IMPUGNA ( LISTA & , LISTANEGRA & );

void IMPUGNA ( LISTA & candidate_list, LISTANEGRA & black_list)
{
    black_list.count_votes_against(&candidate_list);
}

///NOTE (9/1/2022): The difference between this program and the previous is that in this version the process is done within
///                 a LISTANEGRA method, which allows us direct access to it's private members, saving us trouble when
///                 recovering the names of the list since jumping from one node to the next is easy. Names are read from the
///                 LISTANEGRA object and then votes against are counted in the LISTA object, reducing the votes of a candidate one by one.
///
///                 The only reason the pointer to the LISTA object (could have passed it by reference too) is passed to the LISTANEGRA
///                 object is because there we can walk through the PERSONA list easily. The same effect could have been achieved with
///                 a getter method to obtain INICIO and then work within IMPUGNA, however I think this doesn't match with
///                 the idea of encapsulation.

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
