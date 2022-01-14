#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*

	UNA VEZ RESUELTO ENVIAR ESTE ARCHIVO CPP A ************


	Una empresa de transporte posee camiones que realizan envíos.

	Los camiones forman una lista enlazada y cada camión posee a
	su vez una lista de envíos.

	Se desea completar las clases para que funcionen las llamadas
	hechas en el main.

	Agregue los métodos necesarios para que se pueda ejecutar.

	El resultado esperado se menciona en los comentarios.
	Por supuesto, si se modifican los datos debe modificarse el resultado.


	---NO se pueden incorporar elementos del lenguaje NO vistos en clase---

*/

#define MAX_NAME_LENGTH 30
#define MAX_PLATE_LENGTH 8
#define MAX_PKG_CONTENT 50

using namespace std;

class Envio{
    public:
        Envio(char*, float);
        ~Envio();
        Envio * next;
        char content[MAX_PKG_CONTENT];
        float weight;
};

Envio :: Envio(char pkg_content[], float pkg_weight){
    strcpy(content, pkg_content);
    weight=pkg_weight;
}

Envio :: ~Envio(){
    cout<<"\nDestruyendo "<<content;
}
//------------------------------------------------------------------------------------------------------
class Camion{
    public:
        Camion(char*, char*);
        ~Camion();
        Envio * start;
        char driver[MAX_NAME_LENGTH];
        char plate[MAX_PLATE_LENGTH];
        Camion * next;
        float totalWeight();
        int totalPackages();
        int packageCount(char*);
        void addPackage(char*, float);
};

Camion :: Camion(char l_plate[], char t_driver[]){
    strcpy(plate, l_plate);
    strcpy(driver, t_driver);
    start=NULL;
}

Camion :: ~Camion(){
    Envio * scan_ptr=start, * del_ptr;

    while (scan_ptr){
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next;
        delete del_ptr;
    }
}

int Camion :: totalPackages(){
    Envio * scan_ptr=start;
    int counter=0;

    while (scan_ptr){
        counter++;
        scan_ptr=scan_ptr->next;
    }
    return counter;
}

int Camion :: packageCount(char content[]){
    Envio * scan_ptr =start;
    int counter=0;

    while (scan_ptr){
        if(!strcmp(scan_ptr->content, content)){
            counter++;
        }
        scan_ptr=scan_ptr->next;
    }
    return counter;
}

float Camion :: totalWeight(){
    Envio * scan_ptr=start;
    float total_weight=0;

    while (scan_ptr){
        total_weight+=scan_ptr->weight;
        scan_ptr=scan_ptr->next;
    }
    return total_weight;
}

void Camion :: addPackage(char content[], float weight){
    Envio * new_pkg_ptr=new Envio(content, weight);
    new_pkg_ptr->next=start;
    start=new_pkg_ptr;
}

//------------------------------------------------------------------------------------------------------
class Empresa{
    public:
        Empresa();
        ~Empresa();
        void nuevoCamion(char*, char*);
        void nuevoEnvio(char*, char*, float);
        char * masPeso();
        char * menosPeso();
        char * masEnvios();
        int cantEnvios(char*);
    private:
        Camion * start;
};

Empresa :: Empresa(){
    start=NULL;
}

Empresa :: ~Empresa(){
    Camion * scan_ptr=start, * del_ptr;

    while (scan_ptr){
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next;
        delete del_ptr;
    }
}

void Empresa :: nuevoCamion(char l_plate[], char t_driver[]){
    Camion * new_truck_ptr=new Camion(l_plate, t_driver);

    new_truck_ptr->next=start;
    start=new_truck_ptr;
}

void Empresa :: nuevoEnvio(char l_plate[], char content[], float weight){
    Camion * scan_ptr=start;

    while (scan_ptr){
        if(!strcmp(scan_ptr->plate, l_plate)){
            scan_ptr->addPackage(content, weight);
            return;
        }
        scan_ptr=scan_ptr->next;
    }
    printf("\nNo se encontró una camioneta con esa patente");
}

char * Empresa :: masPeso(){
    Camion * scan_ptr=start, * heaviest_ptr;

    heaviest_ptr=scan_ptr;
    while (scan_ptr){
        if(scan_ptr->totalWeight() > heaviest_ptr->totalWeight()){
            heaviest_ptr=scan_ptr;
        }
        scan_ptr=scan_ptr->next;
    }
    if(heaviest_ptr){
        return heaviest_ptr->plate;
    }
    //The only situation where we would get past this if statement is if the truck list is empty, which is possible
}

char * Empresa :: menosPeso(){
    Camion * scan_ptr=start, * lightest_ptr;

    lightest_ptr=scan_ptr;
    while (scan_ptr){
        if(scan_ptr->totalWeight() < lightest_ptr->totalWeight()){
            lightest_ptr=scan_ptr;
        }
        scan_ptr=scan_ptr->next;
    }
    if(lightest_ptr){
        return lightest_ptr->plate;
    }
}

char * Empresa :: masEnvios(){
    Camion * scan_ptr=start, * most_pkgs_ptr;

    most_pkgs_ptr=scan_ptr;
    while (scan_ptr){
        if(scan_ptr->totalPackages() > most_pkgs_ptr->totalPackages()){
            most_pkgs_ptr=scan_ptr;
        }
        scan_ptr=scan_ptr->next;
    }
    if(most_pkgs_ptr){
        return most_pkgs_ptr->plate;
    }
}

int Empresa :: cantEnvios(char content[]){
    Camion * scan_ptr=start;
    int total_pkgs=0;

    while (scan_ptr){
        total_pkgs+=scan_ptr->packageCount(content);
        scan_ptr=scan_ptr->next;
    }
    return total_pkgs;
}

//--------------------------------------------------------------------------------

///Note (14/1/2022): This program has been transcrypted from a handwritten notebook, it had errors in some methods which were fixed.
///                  A warning shown in the console indicates "ISO C++ forbids converting a string constant to 'char*'". This appears because
///                  in the main function functions which are expecting strings (non constant strings) are given string literals as
///                  arguments.

int main()
{

	Empresa * emp = new Empresa();

	emp->nuevoCamion("AA666EE", "Pepe"); //patente y nombre de chofer
	emp->nuevoCamion("AB111FF", "Juan");
	emp->nuevoCamion("AC222BB", "Roberto");

	emp->nuevoEnvio("AA666EE", "Cajón de manzanas", 23.2); //patente, descripción del envio y peso en kg
	emp->nuevoEnvio("AB111FF", "Modem", 0.75);
	emp->nuevoEnvio("AA666EE", "Bolsa de papas", 21);
	emp->nuevoEnvio("AB111FF", "Microprocesador Ryzen 5", 0.381);
	emp->nuevoEnvio("AB111FF", "Gforce RTX 2080", 1.32);
	emp->nuevoEnvio("AB111FF", "Bolsa de papas", 20.85);

	cout << "El camión que más peso transporta es: " << emp->masPeso(); // AA666EE

	cout << "\n El camión que menos peso transporta es: " << emp->menosPeso(); // AC222BB

	cout << "\n El camión que más envíos lleva es: " << emp->masEnvios(); // AB111FF

	cout << "\n Cantidad de envios que son 'Bolsa de papas': " << emp->cantEnvios("Bolsa de papas"); // 2
	cout << "\n Cantidad de envios que son 'Modem': " << emp->cantEnvios("Modem"); // 1
	cout << "\n Cantidad de envios que son 'ZZZZZ': " << emp->cantEnvios("ZZZZZ"); // 0

    return 0;
}
