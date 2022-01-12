/*   CONSTRUIR LAS FUNCIONES  :        */
/*
/*   int EQUIPO::GASTOS()       QUE RETORNE EL TOTAL DE SUELDOS DEL EQUIPO       */
/*   void EQUIPO::DEPURA()      QUE ELIMINE JUGADORES (COMENZANDO POR LOS        */
/*                              MAS CAROS) HASTA QUE LOS SUELDOS SEAN MENORES    */
/*                              QUE EL PRESUPUESTO DEL EQUIPO                    */
/*   void GUIRNALDA::DEPURA()   QUE PRODUZCA LA DEPURACION DE TODOS LOS EQUIPOS  */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <iostream>

using namespace std;

class JUGADOR {
		public :
			char NOM[20] ;
			int SUELDO ;
			JUGADOR * SIG ;
			JUGADOR(char *);
			~JUGADOR();
};

JUGADOR::JUGADOR(char * S)
{
		strcpy ( NOM , S ) ;
		int VAL = 10*(rand()%40000);
		SUELDO = 200000 + VAL ;
		SIG = NULL ;
}
JUGADOR::~JUGADOR()
{
		cout << "\n\n   MATANDO A ... " << NOM << "\n\n";
		//getchar();
}


class EQUIPO {
		public :
			char NOM[20] ;
			int PRESUPUESTO ;
			JUGADOR * PUNJU ;
			EQUIPO * SIG ;
			EQUIPO ( char * , JUGADOR * ) ;
			~EQUIPO() ;
			int GASTOS();
			void DEPURA();
			JUGADOR * max_salary_player();
			void delete_node(JUGADOR *);
};


EQUIPO::EQUIPO ( char * S , JUGADOR * CAPITAN )
{
		strcpy ( NOM , S ) ;
		PRESUPUESTO = 1000000 + rand()%2000000 ;
		PUNJU = CAPITAN ;
}

EQUIPO::~EQUIPO()
{
		JUGADOR * scan_ptr=PUNJU, * del_ptr;

		cout << "\n\n   MATANDO A ... TODOS LOS JUGADORES DE "<<NOM<<"\n\n";
		while(scan_ptr){
            del_ptr=scan_ptr;
            scan_ptr=scan_ptr->SIG;
            delete del_ptr;
		}
		getchar();
}

int EQUIPO :: GASTOS()
{
    int total_spending=0;
    JUGADOR * scan_ptr=PUNJU;

    while (scan_ptr){
        total_spending+=scan_ptr->SUELDO;
        scan_ptr=scan_ptr->SIG;
    }

    return total_spending;
}

void EQUIPO :: DEPURA()
{
    while (GASTOS() > PRESUPUESTO){
        delete_node(max_salary_player());
    }
}

JUGADOR * EQUIPO :: max_salary_player()
{
    JUGADOR * scan_ptr=PUNJU, * max_salary_player_ptr=PUNJU;

    while (scan_ptr){
        if (scan_ptr->SUELDO > max_salary_player_ptr->SUELDO){
            max_salary_player_ptr=scan_ptr;
        }
        scan_ptr=scan_ptr->SIG;
    }

    return max_salary_player_ptr;
}

void EQUIPO :: delete_node(JUGADOR * del_ptr)
{
    JUGADOR * scan_ptr=PUNJU;

    if (PUNJU == del_ptr){
        PUNJU=del_ptr->SIG;
        delete del_ptr;
        return;
    }

    while (scan_ptr->SIG!=del_ptr && scan_ptr){
        scan_ptr=scan_ptr->SIG;
    }

    if (scan_ptr){
        scan_ptr->SIG=del_ptr->SIG;
        delete del_ptr;
    }
}



class GUIRNALDA {
		private :
			EQUIPO * INICIO ;
			EQUIPO * BUSCAR ( char * );
		public :
			GUIRNALDA() ;
			~GUIRNALDA() ;
			void ARREGLATE(char *);
			void MIRAR();
			void DEPURA();
};

GUIRNALDA::GUIRNALDA()
{
		INICIO = NULL ;
}


GUIRNALDA::~GUIRNALDA()
{
		EQUIPO * scan_ptr=INICIO, * del_ptr;
		cout << "\n\n   QUE SE VAYAN TODOS !!! DESTRUYENDO PARTIDOS" ;
		while(scan_ptr){
            del_ptr=scan_ptr;
            scan_ptr=scan_ptr->SIG;
            delete del_ptr;
		}
		getchar();
}


EQUIPO * GUIRNALDA::BUSCAR(char * S)
{
		EQUIPO * P ;
		P = INICIO ;

		while ( P ) {
				if ( ! strcmp(P->NOM,S) )
						return P ;
				P = P->SIG ;
		}
		return NULL ;
}



void GUIRNALDA::ARREGLATE ( char * S )
{
		char * GENERAEQUIPO() ;				/*  PROTOTIPO  */

		JUGADOR * PAL , * P ;
		EQUIPO * PEQUI ;
		char BUF[20] ;

		PAL = new JUGADOR(S) ;

		strcpy ( BUF, GENERAEQUIPO() );

		PEQUI = BUSCAR(BUF) ;

		if ( PEQUI ) {
				/*  PARTIDO EXISTENTE  */
				P = PEQUI->PUNJU ;
				while ( P->SIG )
						P = P->SIG ;  /* VOY HASTA EL ULTIMO ALUMNO */
				P->SIG = PAL ;
				return ;
		}
		/*   PARTIDO NUEVO    */
		PEQUI = new EQUIPO(BUF,PAL) ;
		PEQUI->SIG = INICIO ;
		INICIO = PEQUI ;
}

void GUIRNALDA::MIRAR()
{
		EQUIPO * PEQUI ;
		JUGADOR * PAL ;

		cout << "\n\n  CONTENIDO DE LA GUIRNALDA\n\n\n";
		PEQUI = INICIO ;
		while ( PEQUI ) {
					//printf("\n\n\n\n\t\t%-15s%20d\n" , PEQUI->NOM , PEQUI->PRESUPUESTO ) ;
					printf("\n\n\t\t%-15s%20d\n" , PEQUI->NOM , PEQUI->PRESUPUESTO ) ;

					PAL = PEQUI->PUNJU ;
					while ( PAL ) {
							//printf("\n\n\t\t%-15s%20d" , PAL->NOM , PAL->SUELDO ) ;
							printf("\n\t\t%-15s%20d" , PAL->NOM , PAL->SUELDO ) ;

							PAL = PAL->SIG ;
					}
					getchar();

					PEQUI = PEQUI->SIG ;
		}
}

void GUIRNALDA :: DEPURA()
{
    EQUIPO * scan_ptr=INICIO;

    while(scan_ptr){
        scan_ptr->DEPURA();
        scan_ptr=scan_ptr->SIG;
    }
}



char * GENERANOM();

int main()
{
		char BUF[20] ;
		GUIRNALDA G ;

		srand(105);

		strcpy( BUF , GENERANOM() ) ;
		while ( strcmp (BUF,"FIN") ) {
				G.ARREGLATE(BUF) ;

				strcpy( BUF , GENERANOM() ) ;
		}

		G.MIRAR() ;

		G.DEPURA() ;
		G.MIRAR() ;

		printf("\n\n      FIN DEL PROGRAMA");
		return 0 ;
}


char * GENERANOM()
{
		static char NOM[][20] = {"MARADONA","RONALDO","MESSI",
						  "PELE","MESSI","LABRUNA",
						  "ORTEGA","RIQUELME","ROMA","CARRIZO",
						  "LORENZO","BOBBY MOORE","RONALDINHO","ARMANI",
						  "TARANTINI","RATTIN","ROSSI","ONEGA",
						  "ARTIME","VARACKA","GALLARDO","TEVEZ",
						  "MORETE","ERICO","LABRUNA","MORENO",
						  "PEDERNERA","LOUSTEAU","CAVENAGHI","NAVARRO",
						  "PAVONI","VERON","MESSI","RONALDO",
						  "PERFUMO","MATOSAS","PELE",
						  "CUBILLA","SANTORO","MALBERNAT","BECKENBAUER",
						  "EUSEBIO","PASTORIZA","JAIRZINHO","ROJAS",
						  "MADURGA","PIANETTI","ANDRADA","MARIN",
						  "ROMERO","ALONSO","FRANCESCOLI","DOMINGUEZ",
						  "MAYADA","MORA","MASCHERANO","KRANEVITER",
						  "SOLARI","MATURANA","BOBY MOORE",
						  "HIGUITA","BASILE","FRANCESCOLI",
						  "SARNARI","BILARDO","BATISTUTA","VALENTIM",
						  "CRISTIANO","ZAMORANO","SALAS","ARDILES",
						  "KEMPES","ZANABRIA","OLGUIN","PALACIOS",
						  "MESSI","VERON","FIN"};
		static int I = 0 ;
		return NOM[I++] ;
}


char * GENERAEQUIPO()
{
		static char NOM[][20] = {"BARCELONA","RIVER","BOCA","JUVENTUS",
						  		 "MILAN","REAL MADRID","DYNAMO",
								 "BOTAFOGO","COLO COLO","PEÑAROL",
								 "RACING","INDEPENDIENTE"  };
		return NOM[rand()%12] ;
}
