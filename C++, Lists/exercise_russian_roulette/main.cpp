/*  LA RULETA RUSA GENERA UNA LISTA CERRADA DE 16 COMPETIDORES */
/*  LA FUNCION DISPARAR() CUYO PROTOTIPO SE ADJUNTA, RECIBE UN ENTERO   */
/*  Y DEBE HACER AVANZAR EL PUNTERO AL INICIO TANTOS NODO COMO INDICA  */
/*  EL ENTERO RECIBIDO.  */
/*  CON POSTERIORIDAD DEBE ELIMINAR ESE NODO DE LA LISTA. SU DESTRUCTOR */
/*  SE ENCARGARA DE INDICAR QUIEN ES.  */
/*  AL EJECUTAR LA FUNCION 15 VECES SOLO QUEDARA EL GANADOR  */
/*  SE PIDE CONSTRUIR LA FUNCION DISPARAR() */

/* MODIFIQUE LA CLASE A FIN DE PERMITIR ACTUAR A DISPARAR()  */

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define NUM 16

using namespace std;

class CANDI {
	public :
		char NOM[20];
		CANDI * SIG ;
		~CANDI() ;
};

CANDI::~CANDI()
{
	printf("\n\n   MATANDO A ... %s " , NOM );
	getch() ;
}


class RUSA {
	private :
		CANDI * INICIO ;
		void delete_candidate(CANDI *);
	public :
		RUSA() ;
		void MIRAR() ;
		void kill(int) ;
};

RUSA :: RUSA ()
{
	int I ;
	CANDI * P ;
	char NOM[][20] = { "PEPE" , "LOLA" , "LAURA" , "CACHO" ,
			   "ANSELMO" , "MARIANO" , "MONICA" , "ANA" ,
			   "EDELMIRO" , "JOSE" , "MIRTA" , "SUSANA" ,
			   "FELIPE" , "ENZO" , "BETO" , "PACO" } ;
	INICIO = NULL ;
	for ( I=0 ; I<NUM ; I++ ) {
		P = new CANDI ;
		strcpy ( P->NOM , NOM [ I ] ) ;
		P->SIG = INICIO ;
		INICIO = P ;
	}
	/* CERRANDO LA RULETA */        //The list forms a closed loop
	P = INICIO ;
	while ( P->SIG ) P = P->SIG ;
	P->SIG = INICIO ;
}

void RUSA :: MIRAR ()
{
	int I ;
	cout << "\n\n\n" ;
	for ( I = 0 ; I < NUM ; I++ ) {
		printf ( "\n     %-10s  %p-> %-10s" , INICIO->NOM, INICIO , INICIO->SIG->NOM) ;
		INICIO = INICIO->SIG ;
	}
	getch();
}

void RUSA :: kill(int position)
{
    int counter;
    CANDI * scan_ptr=INICIO;

    cout<<"\n INICIO: "<<INICIO->NOM<<" "<<INICIO;

    for(counter=0;counter<position;counter++)
    {
        scan_ptr=scan_ptr->SIG;
        //cout<<"\n "<<scan_ptr<<" ("<<scan_ptr->NOM<<") "<<" -> "<<scan_ptr->SIG<<" "<<counter;
    }

    delete_candidate(scan_ptr);
}

void RUSA :: delete_candidate(CANDI * del_ptr) //Since the list forms a closed loop we have to solve two links in case the pointer is at the start of the list
{
    CANDI * scan_ptr=INICIO;

    /*
    if(INICIO==del_ptr)
    {
        INICIO=del_ptr->SIG;
        printf("%p * %p\n", del_ptr, INICIO);
        delete del_ptr;
        return;
    }
    */
    while(scan_ptr->SIG!=del_ptr && scan_ptr)
    {
        scan_ptr=scan_ptr->SIG;
    }

    if(scan_ptr)
    {
        printf("\n%p * %p\n", del_ptr, scan_ptr);
        scan_ptr->SIG=del_ptr->SIG;
        if(INICIO==del_ptr)         //Even though all links are solved the same way, we still have too update INICIO
            INICIO=INICIO->SIG;
        //printf("%p\n", INICIO);
        delete del_ptr;
    }
}


void DISPARAR(RUSA,int) ;

void DISPARAR(RUSA table, int random_number)
{
    int position=random_number%NUM;
    //scanf("%d", &position);
    printf(" %d", position);

    table.kill(position);
}

///NOTE (8/1/2022):
///For some reason, MIRAR shows the wrong value for INICIO, probably because DISPARAR has the object R as an argument passed instead of a pointer.
///The modifications made on members of R wouldn't be reflected on MIRAR since it works on the original object, the other is removed after
///DISPARAR ends. However changes made to the list are saved since the links are determined by pointers to CANDI objects from R

int main()
{
	int I ;
	//clrscr();
	RUSA R ;
	R.MIRAR() ;

	for ( I = 0 ; I < NUM-1 ; I++ ) {

            DISPARAR(R , rand()%100);

        	R.MIRAR() ;
	}

	cout << "\n\n\nFIN DEL PROGRAMA  " ;
	getch();
}
