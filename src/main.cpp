/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Pablo Ernesto Angusto Delgado y Miguel Aréjula Aísa
 * Ultima revisión: ¡¡¡!!!
 * Resumen: ¡¡¡!!!
 * Nota: El código de este programa está repartido en varios módulos.
 *       Para compilarlo, hay que ejecutar el comando
 *           make all
 *       o, en Windows,
 *           mingw32-make all
 *       o ejecutar la tarea "Compilar «electricidad»" de VSC.
 * 
 *       Para ejecutarlo, una vez compilado, hay que ejecutar el comando
 *           bin/electricidad
 *       o, en Windows,
 *           bin\electricidad.exe
 *       o ejecutar la tarea "Ejecutar «electricidad»" de VSC.
\******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
//#include "fecha.hpp"
using namespace std;


/*
 * Pre:  «f» es «cout» o un flujo de la clase «ofstream» asociado con un fichero
 *       externo abierto para escritura. Las «numRegs» primeras componentes
 *       del vector «regDiarios» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: Ha escrito en el flujo «f» el informe sobre consumo eléctrico indicado
 *       en el enunciado de este trabajo.
 */
void escribirInforme(ostream& f,
                     const GastoDiario regDiarios[], const unsigned numRegs,
                     const string nombreCliente, 
                     const unsigned mesInicial, const unsigned mesFinal);

void pedirmes(int& mesinicio, int& mesfinal){
    
    cout << "Escriba el mes inicial y el final: ";   
    cin >> mesinicio >> mesfinal;

}
void pedirDatos(string& usuario,int& mesinicio, int& mesfinal){
    cout << "Escriba el nombre del usuario: ";
    
    cin >> usuario;
    cout << endl;
    
    
    pedirmes(mesinicio,mesfinal);
    while(mesinicio > mesfinal || mesinicio < 1 || mesfinal > 11){
        
        if(mesinicio > mesfinal){
            cout <<"El mes inicial tiene que ser menor o igual que el mes final."<<endl;
            
        }
        
        if( mesinicio<1 || mesinicio>11){
            cout <<"El mes inicial tiene que estar entre 1 y 11."<<endl;
        }
        
        if( mesfinal<1 || mesfinal > 11){
            cout << "El mes final tiene que estar entre 1 y 11" << endl;
            
        }

        pedirmes(mesinicio,mesfinal);
        
    }
}

string convRuta(string usuario, int mesinicio, int mesfinal){
    string rutainicio="datos/";
    string rutayear="-2021-";
    string rutafinal=".csv";
    
        string mes = (to_string(mesinicio));
        if(mesinicio<10){
            mes = "0" + mes;
        }
        return rutainicio + usuario + rutayear + mes + rutafinal;
        
}

void fichBucle(string usuario, int mesinicio, int mesfinal, string rutaFicheros[]){
    int n=0;
    for(int i=mesinicio; i<=mesfinal; i++){
        rutaFicheros[n]=convRuta(usuario, i, mesfinal);
        n++;
    }
}
bool pedirNombreFichero(string& nombreEscritura){

    cout << "Escribe el nombre del fichero del informe"<<endl; 
    cout << "(presione solo ENTRAR para escribirlo en la pantalla: ";
    cin >> nombreEscritura;
    if(nombreEscritura== "salto"){
        return true;
    }else{
        return false;
    }
            

}
bool leerFichero(string rutaFicheros[], int elementos, int mesInicial, int mesFinal, GastoDiario registros[]){
    ifstream f;
    for(int i=0; i<elementos;i++){
        string nombreFichero=rutaFicheros[i];
        f.open(nombreFichero);
        if(f.is_open()){
            //hay que cerrar los flujos
            if(leerConsumos(nombreFichero,mesInicial,mesFinal,registros)){
                
            }else{
                cerr << "No se ha podido leer el fichero " <<'"'<<nombreFichero<<'"'<<"."<<endl;
                return false;
            }
            
        }else{
            cerr << "No se ha podido leer el fichero " <<'"'<<nombreFichero<<'"'<<"."<<endl;
            return false;
        }
    }
    
    return true;
}

void crearFichero(string nombreFichero){

    ofstream g;
    g.open(nombreFichero);
}

void escribirCabecera(int mesinicio, int mesfinal){
    cout<<"INFORME DEL CLIENTE "<< '"'<<"A"<<'"'<< " ENTRE LOS MESES "<<mesinicio<<" Y " << mesfinal << " DE 2021" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
}

bool leerFichTafs(int mesInicial, int mesFinal, GastoDiario registros[]){
    ifstream f;
    string nombreFichero = "datos/tarifas-2021-ene-nov.csv";
    f.open(nombreFichero);
    if(f.is_open()){
        if(leerPrecios(nombreFichero, mesInicial, mesFinal, registros)){

        }else{
            cerr << "No se ha podido leer el fichero " <<'"'<<nombreFichero<<'"'<<"."<<endl;
            return false;
        }

    }else{
        cerr << "No se ha podido leer el fichero " <<'"'<<"tarifas-2021-ene-nov.csv"<<'"'<<"."<<endl;
        return false;
    }
    return true;
}

int diasTotales(int mesinicio, int mesfinal){
    int dias = 0;
    for (int i=mesinicio;i<=mesfinal;i++){

        dias+=diasDelMes(i,AGNO_ACTUAL);
    }
    return dias;

}

/*Fecha masBarato (int mesinicio, int mesfinal, GastoDiario registros[]){
    double costes[diasTotales(mesinicio, mesfinal)];
    for(int i=0; i<diasTotales(mesinicio, mesfinal); i++){
        costes[i]=costeDiario(registros[i]);
    }
    double costeaux = costes[0];
    unsigned diamasbarato=0;
    for(int i=1; i<diasTotales(mesinicio, mesfinal); i++){
        if(costeaux>costes[i]){
            costeaux=costes[i];
            diamasbarato=i;
        }
    }
    Fecha masBarato;
    for(int n=mesinicio; n<=mesfinal; n++){
        while(diamasbarato>diasDelMes(n, 2021)){
            diamasbarato = diamasbarato - diasDelMes(n, 2021);
            masBarato.mes=n;
        }
    }
    
    masBarato.dia = diamasbarato;
    
    masBarato.agno = 2021;
    return masBarato;
}

void mostrarPrimerRes(Fecha barato){

    cout << "El día completo más barato fue el " << barato.dia << "-" << barato.mes << "-" << barato.agno << "." << endl;
}*/




/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {
    int mesinicio;
    int mesfinal;
    string usuario;

    pedirDatos(usuario,mesinicio,mesfinal);
    int elementos = mesfinal - mesinicio + 1;

    string rutaFicheros[elementos];
    fichBucle(usuario,mesinicio,mesfinal,rutaFicheros);
    string nombreEscritura;
    //unsigned numero = diasTotales(mesinicio,mesfinal);
    GastoDiario registros[diasTotales(mesinicio,mesfinal)];
    if(leerFichero(rutaFicheros, elementos,mesinicio,mesfinal,registros)){
        if(pedirNombreFichero(nombreEscritura)){
            escribirCabecera(mesinicio,mesfinal);
            if(leerFichTafs(mesinicio, mesfinal, registros)){
                //mostrarPrimerRes
            }

            
        }else{
            //Escribir en fichero ficheros
            //crearFichero(nombreEscritura);
        }
    }else{
        return 1;
    }

    return 0;
}