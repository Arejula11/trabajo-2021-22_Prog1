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
                     const unsigned mesInicial, const unsigned mesFinal) {
}

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

void leerFichero(string rutaFicheros[], int elementos){
    ifstream f;
    for(int i=0; i<elementos;i++){
        f.open(rutaFicheros[i]);
        if(f.is_open()){
            cout << "corrector"<<endl;
        }
        else{
            cout << "error" <<" "<<i<<endl;
        }
    }
    

}


/*
 * ¡ESCRIBID LA ESPECIFICACIÓN DE ESTA FUNCIÓN!
 */
int main() {
    int mesinicio;
    int mesfinal;
    string usuario;
    int elementos = mesfinal - mesinicio;
    pedirDatos(usuario,mesinicio,mesfinal);
    string rutaFicheros[11];
    fichBucle(usuario,mesinicio,mesfinal,rutaFicheros);
    leerFichero(rutaFicheros, elementos);
    return 0;
}