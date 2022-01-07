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
#include <iomanip>
#include <fstream>
#include <string>
#include "gasto-diario.hpp"
#include "fichs-electricos.hpp"
#include "vector-gastos.hpp"
#include "tarifas-comerciales.hpp"
//#include "fecha.hpp"
using namespace std;



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

string convRuta(string usuario, int mesinicio){
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
        rutaFicheros[n]=convRuta(usuario, i);
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

void mostrarPrimerResA(Fecha barato, GastoDiario registro[], unsigned& diamasbarato){
    cout << "El día completo más barato fue el " << barato.dia+1 << "-" << barato.mes << "-" << barato.agno << ". Precio medio: "<< costeMedio(registro[diamasbarato])/1000 <<" €/kWh"<<endl; 
    
    
}

void mostrarPrimerResB(GastoDiario registro[],Fecha caro, unsigned& diamascaro){
    cout << "La hora más cara tuvo lugar el " <<caro.dia+1<< "-" << caro.mes << "-" << caro.agno<<" a las "<< horaMasCara(registro[diamascaro]) << " . Precio: "<< registro[diamascaro].precioE[horaMasCara(registro[diamascaro])]/1000 << " €/kWh"<<endl;
    
}
void masCaro( int mesinicio, int mesfinal, GastoDiario registros[]){
    double costeshoras[diasTotales(mesinicio, mesfinal)];
    unsigned diamascaro=0;
    for(int i=0;  i<diasTotales(mesinicio, mesfinal); i++){
        costeshoras[i]=registros[i].precioE[horaMasCara(registros[i])];
    }
    double costeaux = costeshoras[0];
    for(int i=1; i<diasTotales(mesinicio, mesfinal); i++){
        if(costeaux<costeshoras[i]){
            costeaux=costeshoras[i];
            diamascaro=i;
        }
    }
    
    unsigned diaC=diamascaro;
    Fecha masCaro;
    for(int n=mesinicio; n<=mesfinal; n++){
        
        if (diamascaro>diasDelMes(n,2021)){
            diamascaro -=diasDelMes(n,2021);

        }else{
            masCaro.mes=n;
            n=mesfinal+1;
        }
    }
    
    masCaro.dia = diamascaro;
    
    masCaro.agno = 2021;
     cout << "La hora más cara tuvo lugar el " <<masCaro.dia+1<< "-" << masCaro.mes << "-" << masCaro.agno<<" a las "<< horaMasCara(registros[diaC]) 
     << ":00"<< ". Precio: "<< costeshoras[diaC]/1000 << " €/kWh"<<endl;
}

void masCaroF( int mesinicio, int mesfinal, const GastoDiario registros[], ostream& f){
    double costeshoras[diasTotales(mesinicio, mesfinal)];
    unsigned diamascaro=0;
    for(int i=0;  i<diasTotales(mesinicio, mesfinal); i++){
        costeshoras[i]=registros[i].precioE[horaMasCara(registros[i])];
    }
    double costeaux = costeshoras[0];
    for(int i=1; i<diasTotales(mesinicio, mesfinal); i++){
        if(costeaux<costeshoras[i]){
            costeaux=costeshoras[i];
            diamascaro=i;
        }
    }
    
    unsigned diaC=diamascaro;
    Fecha masCaro;
    for(int n=mesinicio; n<=mesfinal; n++){
        
        if (diamascaro>diasDelMes(n,2021)){
            diamascaro -=diasDelMes(n,2021);

        }else{
            masCaro.mes=n;
            n=mesfinal+1;
        }
    }
    
    masCaro.dia = diamascaro;
    
    masCaro.agno = 2021;
     f << "La hora más cara tuvo lugar el " <<masCaro.dia+1<< "-" << masCaro.mes << "-" << masCaro.agno<<" a las "<< horaMasCara(registros[diaC]) 
     << ":00"<< ". Precio: "<< costeshoras[diaC]/1000 << " €/kWh"<<endl;
}

void masBarato (int mesinicio, int mesfinal, GastoDiario registros[]){
    double costes[diasTotales(mesinicio, mesfinal)];
    unsigned diamasbarato=0;
    for(int i=0; i<diasTotales(mesinicio, mesfinal); i++){
        costes[i]=costeMedio(registros[i]);
        
    }

    double costeaux = costes[0];
    for(int i=1; i<diasTotales(mesinicio, mesfinal); i++){
        if(costeaux>costes[i]){
            costeaux=costes[i];
            diamasbarato=i;
        }
    }
    
    unsigned diaB = diamasbarato;
    Fecha masBarato;
    for(int n=mesinicio; n<=mesfinal; n++){
        
        if (diamasbarato>diasDelMes(n,2021)){
            diamasbarato -=diasDelMes(n,2021);

        }else{
            masBarato.mes=n;
            n=mesfinal+1;
        }
    }
    
    masBarato.dia = diamasbarato;
    
    masBarato.agno = 2021;
    cout << "El día completo más barato fue el " << masBarato.dia+1 << "-" << masBarato.mes << "-" 
    << masBarato.agno << ". Precio medio: "<< costeMedio(registros[diaB])/1000 <<" €/kWh"<<endl;
}


void masBaratoF (int mesinicio, int mesfinal, const GastoDiario registros[], ostream& f){
    double costes[diasTotales(mesinicio, mesfinal)];
    unsigned diamasbarato=0;
    for(int i=0; i<diasTotales(mesinicio, mesfinal); i++){
        costes[i]=costeMedio(registros[i]);
        
    }

    double costeaux = costes[0];
    for(int i=1; i<diasTotales(mesinicio, mesfinal); i++){
        if(costeaux>costes[i]){
            costeaux=costes[i];
            diamasbarato=i;
        }
    }
    
    
    unsigned diaB = diamasbarato;
    Fecha masBarato;
    for(int n=mesinicio; n<=mesfinal; n++){
        
        if (diamasbarato>diasDelMes(n,2021)){
            diamasbarato -=diasDelMes(n,2021);

        }else{
            masBarato.mes=n;
            n=mesfinal+1;
        }
    }
    
    masBarato.dia = diamasbarato;
    
    masBarato.agno = 2021;
    f << "El día completo más barato fue el " << masBarato.dia+1 << "-" << masBarato.mes << "-" 
    << masBarato.agno << ". Precio medio: "<< costeMedio(registros[diaB])/1000 <<" €/kWh"<<endl;
}

double gastoTotalE(const GastoDiario registros[],unsigned mesinicial, unsigned mesfinal){
    double gasto = 0;
    
    
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gasto+=costeDiario(registros[n]);
        

    }
    
    cout<<"El importe del consumo eléctrico en el periodo considerado ha sido de "<< fixed << setprecision(2)<< gasto <<" €"<<endl;
    return gasto;
}
double gastoTotalEF(const GastoDiario registros[],unsigned mesinicial, unsigned mesfinal, ostream& f){
    double gasto = 0;
    
    
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gasto+=costeDiario(registros[n]);
        

    }
    
    f<<"El importe del consumo eléctrico en el periodo considerado ha sido de "<< fixed << setprecision(2)<< gasto <<" €"<<endl;
    return gasto;
}

void gastoMinimoE(GastoDiario registros[], unsigned mesinicial, unsigned mesfinal,double gasto){
    double gastom = 0;
    
    
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gastom+=costeDiarioMinimo(registros[n]);
        

    }
    cout<< "El importe mínimo concentrando todo el consumo diario en la hora más barata habría sido de "
    << fixed << setprecision(2)<<gastom<<" €"<<"(un "<<100-(gastom/gasto)*100<<" % menor)."<< endl;
    cout<<endl;
}

void gastoMinimoEF(const GastoDiario registros[], unsigned mesinicial, unsigned mesfinal,double gasto, ostream& f){
    double gastom = 0;
    
    
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gastom+=costeDiarioMinimo(registros[n]);
        

    }
    f<< "El importe mínimo concentrando todo el consumo diario en la hora más barata habría sido de "
    << fixed << setprecision(2)<<gastom<<" €"<<"(un "<<100-(gastom/gasto)*100<<" % menor)."<< endl;
}

void tarifaCabecera(){
    cout<<"COSTE CON TARIFAS COMERCIALES"<<endl;
    cout<<"Coste        Nombre de la tarifa"<<endl;
    cout<<"--------------------------------------------"<<endl;
}

void tarifaPrecios( GastoDiario registros[], TarifaPlanaTramos tarifas[], unsigned mesinicio, unsigned mesfinal){
    double preciostf[NUM_TARIFAS_COMERCIALES];
    for(int i=0;i<NUM_TARIFAS_COMERCIALES; i++){
            preciostf[i] = costeTarifaPlanaTramos(registros, diasTotales(mesinicio, mesfinal), tarifas[i]);
            cout<<preciostf[i]<<"     "<<TARIFAS_COMERCIALES[i].nombre<<endl;

    }
    
}

void tarifaPreciosF(const GastoDiario registros[], TarifaPlanaTramos tarifas[], unsigned mesinicio, unsigned mesfinal, ostream& f){
    double preciostf[NUM_TARIFAS_COMERCIALES];
    for(int i=0;i<NUM_TARIFAS_COMERCIALES; i++){
            preciostf[i] = costeTarifaPlanaTramos(registros, diasTotales(mesinicio, mesfinal), tarifas[i]);
            f<<preciostf[i]<<"     "<<TARIFAS_COMERCIALES[i].nombre<<endl;

    }
    
}

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
                     const unsigned mesInicial, const unsigned mesFinal){
    f<<"INFORME DEL CLIENTE "<< '"'<<"A"<<'"'<< " ENTRE LOS MESES "<<mesInicial<<" Y " << mesFinal << " DE 2021" << endl;
    f << "-------------------------------------------------------------------------------------" << endl;
    masBaratoF(mesInicial, mesFinal, regDiarios, f);
    masCaroF(mesInicial, mesFinal, regDiarios, f);
    f<<endl;
    
    double gastomax = gastoTotalEF(regDiarios,mesInicial,mesFinal, f);
    gastoMinimoEF(regDiarios, mesInicial, mesFinal, gastomax, f);
    f<<endl;
    
    TarifaPlanaTramos tarifas[NUM_TARIFAS_COMERCIALES];
    for(int i=0; i<NUM_TARIFAS_COMERCIALES;i++){
        tarifas[i]=TARIFAS_COMERCIALES[i];
    }
    tarifaPreciosF(regDiarios,tarifas,mesInicial,mesFinal, f);
}

void crearFichero(string nombreFichero, GastoDiario regDiarios[], unsigned numRegs, string nombreCliente, unsigned mesInicial, unsigned mesFinal){

    ofstream f;
    f.open(nombreFichero);
    escribirInforme(f, regDiarios, numRegs, nombreCliente, mesInicial, mesFinal);
    
}

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
            cout<<endl;
            escribirCabecera(mesinicio,mesfinal);
            if(leerFichTafs(mesinicio, mesfinal, registros)){
                
                masBarato( mesinicio, mesfinal, registros);
                masCaro( mesinicio, mesfinal, registros);    
                cout<<endl;
                double gastomax = gastoTotalE(registros,mesinicio,mesfinal);
                gastoMinimoE(registros, mesinicio, mesfinal, gastomax);
                tarifaCabecera();
                TarifaPlanaTramos tarifas[NUM_TARIFAS_COMERCIALES];
                for(int i=0; i<NUM_TARIFAS_COMERCIALES;i++){
                    tarifas[i]=TARIFAS_COMERCIALES[i];
                }
                tarifaPrecios(registros,tarifas,mesinicio,mesfinal);
            }

            
        }else{
            if(leerFichTafs(mesinicio, mesfinal, registros)){
            crearFichero(nombreEscritura, registros, diasTotales(mesinicio,mesfinal), usuario, mesinicio, mesfinal);
            }
        }
    }else{
        return 1;
    }

    return 0;
}