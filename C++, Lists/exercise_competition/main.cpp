/*   COMPETENCIA   */

/*   SE DESARROLLARA UN TORNEO POR DISCIPLINAS.                  */
/*   CADA UNA DE ESTAS TIENE UN DETERMINADO HANDICAP             */
/*   POR CADA DISCIPLINA SE DISPONE DE LA LISTA DE COMPETIDORES  */
/*   EN EL ORDEN EN QUE CLASIFICARON                             */
/*   SEGUN LA POSICION OBTENIDA SE ASIGNA EL SIGUIENTE PUNTAJE : */
/*   		PRIMERO     10 PUNTOS                                */
/*   		SEGUNDO      9 PUNTOS                                */
/*   		TERCERO      8 PUNTOS                                */
/*   		CUARTO       7 PUNTOS                                */
/*   		QUINTO       6 PUNTOS                                */
/*   		EL RESTO     2 PUNTOS                                */
/*   EL COMPETIDOR (QUE PUEDE ESTAR INSCRIPTO VARIAS VECES EN    */
/*   CADA DISCIPLINA) OBTIENE EL PUNTAJE DE SU POSICION MULTI    */
/*   PLICADO POR EL HANDICAP DE LA DISCIPLINA CONSIDERADA        */
/*   EL GANADOR ES EL QUE SUMA MAYOR PUNTAJE TOTAL               */
/*   LA INSCRIPCION EN CADA PARTICIPACION CUESTA 1000 $ POR      */
/*   EL HANDICAP DE LA DISCIPLINA EN QUE SE INSCRIBE             */

/*   SE PIDE :                                                   */
/*			1. DETERMINAR EL GANADOR Y SU PUNTAJE                */
/*          2. INDICAR QUE COMPETIDOR GASTO MAS DINERO Y CUANTO  */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std ;

class COMPETIDOR {
	public :
			COMPETIDOR(char *) ;
			~COMPETIDOR() ;
			char NOM[20] ;
			COMPETIDOR * SIG ;
};


COMPETIDOR::COMPETIDOR(char * S)
{
		strcpy ( NOM , S );
		SIG = NULL ;
}

COMPETIDOR::~COMPETIDOR()
{
		cout << "\n\n   MATANDO A ... " << NOM ;
		getchar();
}




class DISCIPLINA {
	public :
			char NOM[20] ;
			int HANDICAP ;
			COMPETIDOR * PALUM ;
			DISCIPLINA * SIG ;
			DISCIPLINA(char * , COMPETIDOR *) ;
			~DISCIPLINA() ;
			int points(char *);
			int money_spent(char *);
};


DISCIPLINA::DISCIPLINA(char * S , COMPETIDOR * PRIMERO)
{
		strcpy ( NOM , S );
		HANDICAP = 5 + rand()%30 ;
		PALUM = PRIMERO ;
}

DISCIPLINA::~DISCIPLINA()
{
		COMPETIDOR * scan_ptr=PALUM, * del_ptr;

		cout << "\n\n   MATANDO A ... TODOS LOS COMPETIDORES" ;
		while(scan_ptr)
        {
            del_ptr=scan_ptr;
            scan_ptr=scan_ptr->SIG;
            delete del_ptr;
        }

		getchar();
}

int DISCIPLINA :: points(char competitor_name[])
{
    COMPETIDOR * scan_ptr=PALUM;
    int position=0, total_points=0, place_points=0;

    while(scan_ptr)
    {
        if(!strcmp(competitor_name, scan_ptr->NOM))
        {
            if(position<=4)
                place_points=10-position; //Position zero corresponds to the first place, two to the second and so on,
            else
                place_points=2;

            total_points+=place_points*HANDICAP;
        }
        scan_ptr=scan_ptr->SIG;
        position++;
    }

    return total_points;
}

int DISCIPLINA :: money_spent(char competitor_name[])
{
    COMPETIDOR * scan_ptr=PALUM;
    int counter=0;

    while(scan_ptr)
    {
        if(!strcmp(scan_ptr->NOM, competitor_name))
            counter++;
        scan_ptr=scan_ptr->SIG;
    }

    return counter*1000*HANDICAP;
}



class TORNEO {
	private :
			DISCIPLINA * INICIO ;
			DISCIPLINA * BUSCAR(char *);
	public :
			TORNEO() ;
			~TORNEO() ;
			void ARREGLATE(char *);
			void MIRAR() ;
			void GANADOR();
			void MAYOR_INVERSION();
};


TORNEO::TORNEO()
{
		INICIO = NULL ;
}

TORNEO::~TORNEO()
{
        DISCIPLINA * scan_ptr=INICIO, * del_ptr;

		cout << "\n\n   DESTRUYENDO TODAS LAS DISCIPLINAS " ;
		while(scan_ptr)
        {
            del_ptr=scan_ptr;
            scan_ptr=scan_ptr->SIG;
            delete del_ptr;
        }
		getchar();
}

void TORNEO::ARREGLATE(char * S)
{
		/*   PROTOTIPO  */
		char * GENERADISCIPLINA();

		char BUF[20] ;
		COMPETIDOR * PAL , * P ;
		DISCIPLINA * PPAR ;

		PAL = new COMPETIDOR(S) ;

		strcpy ( BUF , GENERADISCIPLINA() ) ;

		PPAR = BUSCAR(BUF) ;

		if ( PPAR ) {
				/*  DISCIPLINA EXISTENTE  */
				P = PPAR->PALUM ;		/*  APUNTO AL PRIMERO  */
				while ( P->SIG )
						P = P->SIG ; 	/*  AVANZO AL ULTIMO COMPETIDOR  */ //The competitor is added at the end of the discipline list
				P->SIG = PAL ;
				return ;
		}
		/*  NUEVA DISCIPLINA  */
		PPAR = new DISCIPLINA(BUF,PAL) ;
		PPAR->SIG = INICIO ;
		INICIO = PPAR ;
}

DISCIPLINA * TORNEO::BUSCAR(char * S)
{
		DISCIPLINA * P ;
		P = INICIO ;

		while (P) {
				if ( ! strcmp ( P->NOM , S ) )
						return P ;
				P = P->SIG ;
		}
		return NULL ;
}


void TORNEO::MIRAR()
{
		DISCIPLINA * PPAR ;
		COMPETIDOR * PAL ;

		fflush(stdin);
		system("cls");
		cout << "\n\n\n\n\t\t    CONTENIDO DEL TORNEO \n\n" ;
		PPAR = INICIO ;
		while ( PPAR ) {
				cout << "\n\n\n\n\t\t    DISCIPLINA   :   " << PPAR->NOM ;
				cout << "\n\n\t\t    HANDICAP     :   " << PPAR->HANDICAP ;
				cout << "\n\n" ;

				PAL = PPAR->PALUM ;
				while ( PAL ) {
						cout << "\n\t\t    " << PAL->NOM ;
						PAL = PAL->SIG ;
				}
				getchar();

				PPAR = PPAR->SIG ;
		}
}

void TORNEO :: GANADOR()
{
    DISCIPLINA * scan_ptr1=INICIO;
    COMPETIDOR * scan_ptr2, * winner;
    int winner_points=0;

    while(scan_ptr1)
    {
        scan_ptr2=winner=scan_ptr1->PALUM;
        winner_points=0;    //We reset the winner and it's points for each new discipline
        while(scan_ptr2)
        {
            if(scan_ptr1->points(scan_ptr2->NOM) > winner_points)
            {
                winner = scan_ptr2;
                winner_points = scan_ptr1->points(scan_ptr2->NOM);
            }
            scan_ptr2=scan_ptr2->SIG;
        }
        printf("%-20s -> %-15s %d\n", scan_ptr1->NOM, winner->NOM, winner_points);
        scan_ptr1=scan_ptr1->SIG;
    }
}

void TORNEO :: MAYOR_INVERSION()
{
    DISCIPLINA * scan_ptr1=INICIO;
    COMPETIDOR * scan_ptr2, * highest_spender;
    int money_spent=0;

    while(scan_ptr1)
    {
        scan_ptr2=highest_spender=scan_ptr1->PALUM;
        money_spent=0;
        while(scan_ptr2)
        {
            if(scan_ptr1->money_spent(scan_ptr2->NOM) > money_spent)
            {
                highest_spender=scan_ptr2;
                money_spent=scan_ptr1->money_spent(scan_ptr2->NOM);
            }
            scan_ptr2=scan_ptr2->SIG;
        }
        printf("%-20s -> %-15s %d\n", scan_ptr1->NOM, highest_spender->NOM, money_spent);
        scan_ptr1=scan_ptr1->SIG;
    }
}

char * GENERANOM();

///NOTE (9/1/2022): Started and finished the exercise. I counted total money spent on each discipline, not overall.
///                 In order to do that I would need to somehow keep a record of the competitors names in all competitions,
///                 then count the money a particular competitor spends in all disciplines, add it up and compare it to the
///                 one that spent the most. If greater, then our competitor becomes the highest spender. We keep comparing until
///                 there are no competitors left. Since we can't assume that all competitors participate in every competition,
///                 to obtain every possible competitor we must look through every discipline.
///
///                 Remember to always read the text and understand what's required before starting to
///                 save time spent on corrections.

int main( )
{
		TORNEO T ;
		char BUF[20];

		srand(65);

		strcpy ( BUF , GENERANOM() );
		while ( strcmp(BUF,"FIN") ) {
				T.ARREGLATE(BUF) ;

				strcpy ( BUF , GENERANOM() );
		}

		T.MIRAR() ;

		T.GANADOR() ;
        T.MAYOR_INVERSION() ;

		printf("\n\n");
		return 0 ;
}


char * GENERANOM()
{
	static int I = 0 ;
	static char NOM[][20] = {"DARIO","CAROLINA","PEPE","LOLA",
						     "PACO","LUIS","MARIA","ANSELMO",
						  	 "ANA","LAURA","PEDRO","ANIBAL",
						     "PABLO","ROMUALDO","ALICIA","MARTA",
						     "MARTIN","TOBIAS","SAUL","LORENA",
							 "ANDRES","KEVIN","LUCRECIA","RAUL",
							 "ENZO","BETO","HERMINDO","FELIPE",
							 "GUILLERMO","TATO","KARINA","AQUILES",
							 "MINERVA","OLGA","LALO","TATIANA",
							 "LILO","STICH","EMA","THELMA",
							 "LOUISE","BONNIE","CLYDE","ROMEO",
							 "JULIETA","VERONICA","JORGE","ALEJANDRO",
							 "ROCIO","LUJAN","LIBORIO","CONAN","FIN"};
	if ( ++I < 250 )
		return NOM[rand()%52] ;
	else
		return NOM[52] ;
}


char * GENERADISCIPLINA()
{
	static char NOM[][20] = {"TRIATLON","PENTATLON","MARTILLO","JABALINA",
						     "GARROCHA","SALTO TRIPLE","SALTO EN LARGO",
							 "MARATON","CARRERA 100 MTS","DISCO","MEDIA MARATON","PESAS" };
	return NOM[rand()%12] ;
}
