#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_MODEL_LENGTH 30
#define MAX_NAME_LENGTH 30
#define MAX_NUMBER_LENGTH 20

class Auto{
public:
    char cModel[MAX_MODEL_LENGTH];
    int cYear;
    Auto * next;
    Auto(char*, int);
    ~Auto();
};

Auto :: Auto(char model[], int year)
{
    cYear=year;
    strcpy(cModel, model);
}

Auto :: ~Auto()
{
    printf("\t\tDestruyendo auto modelo %s año %d\n", cModel, cYear);
}

//------------------------------------------------------------------------

class Cliente{
public:
    char cName[MAX_NAME_LENGTH];
    char phoneNumber[MAX_NUMBER_LENGTH];
    Auto * start;
    Cliente * next;
    Cliente(char *, char *);
    ~Cliente();
    void agregarAuto(char*, int);
    int cantAutos();
    void vaciarAutos();
};

Cliente :: Cliente(char name[], char number[])
{
    strcpy(cName, name);
    strcpy(phoneNumber, number);
    start=NULL;
}

Cliente :: ~Cliente()
{
    Auto *scan_ptr=start, *del_ptr;

    printf("\tDestruyendo Cliente %s\n", cName);
    while (scan_ptr){
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next;
        delete del_ptr;
    }
}

void Cliente :: agregarAuto(char model[], int year)
{
    Auto *car_ptr=new Auto(model, year);
    car_ptr->next=start;
    start=car_ptr;
}

int Cliente :: cantAutos()
{
    Auto *scan_ptr=start;
    int counter=0;

    while (scan_ptr){
        counter++;
        scan_ptr=scan_ptr->next;
    }
    return counter;
}

void Cliente :: vaciarAutos()
{
    Auto *scan_ptr=start, *del_ptr;

    while (scan_ptr){
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next;
        delete del_ptr;
    }
    start=NULL;
}

//------------------------------------------------------------------------

class ListaClientes{
    public:
        ListaClientes();
        ~ListaClientes();
        Cliente * buscar(char*);
        void agregar(char*, char*);
        int cantClientes();
    private:
        Cliente *start;
};

ListaClientes :: ListaClientes()
{
    start=NULL;
}

ListaClientes :: ~ListaClientes()
{
    Cliente *scan_ptr=start, *del_ptr;

    printf("Destruyendo cliente\n");
    while (scan_ptr){
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next;
        delete del_ptr;
    }
}

/*
Cliente * ListaClientes :: buscar(char name[])
{
    Cliente *scan_ptr=start;

    while (strcmp(name, scan_ptr->cName) && scan_ptr){
        scan_ptr=scan_ptr->next;
    }
    if (!strcmp(name, scan_ptr->cName)){
        return scan_ptr;
    }
    return NULL;
}
*/

Cliente * ListaClientes :: buscar(char name[])
{
    Cliente *scan_ptr=start;

    while (scan_ptr){
        if (!strcmp(name, scan_ptr->cName)){
            return scan_ptr;
        }
        scan_ptr=scan_ptr->next;
    }
    return NULL;
}

void ListaClientes :: agregar(char name[], char number[])
{
    Cliente *client_ptr;

    if(buscar(name)){
        return;
    }

    client_ptr=new Cliente(name, number);
    client_ptr->next=start;
    start=client_ptr;
}

int ListaClientes :: cantClientes()
{
    Cliente *scan_ptr=start;
    int counter=0;

    while (scan_ptr){
        counter++;
        scan_ptr=scan_ptr->next;
    }
    return counter;
}

//------------------------------------------------------------------------

///NOTE (11/01/2022): This program has been transcrypted from a handwritten notebook, it had errors in some methods which were fixed.
///                   A warning shown in the console indicates "ISO C++ forbids converting a string constant to 'char*'". This appears because
///                   in the main function functions which are expecting strings (non constant strings) are given string literals as
///                   arguments.

int main() {
    ListaClientes * lc = new ListaClientes;  // la guirnalda en sí

    lc->agregar("Pepe", "4555-6565");  //agrega Cliente (lista principal)
    lc->agregar("Maria", "4444-3232");
    lc->agregar("Carlos", "5460-1111");

    lc->buscar("Pepe")->agregarAuto("Renault 12", 1980);  //agrega Auto a un Cliente (lista secundaria)
    lc->buscar("Pepe")->agregarAuto("Renault Fluence", 2013);

    printf("\n Pepe tiene %d autos\n" , lc->buscar("Pepe")->cantAutos() );  //debe dar 2

    lc->buscar("Pepe")->vaciarAutos();

    printf("\n Pepe tiene %d autos\n" , lc->buscar("Pepe")->cantAutos() );  //debe dar 0

    printf("\n La guirnalda tiene %d clientes\n" , lc->cantClientes() );  //debe dar 3

    delete lc;
}
