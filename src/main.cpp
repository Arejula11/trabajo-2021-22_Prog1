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

using namespace std;


/*
 * Pre:  ---
 * Post: Asigna a las variables mesinicio y mesfinal los valores introducidos por el usuario.
 */
void pedirmes(int& mesinicio, int& mesfinal){
    
    cout << "Escriba el mes inicial y el final: ";   
    cin >> mesinicio >> mesfinal;

}

/*
 * Pre:  ---
 * Post: Solicita al usuario que introduzca el nombre del cliente y los valores
 *       del primer mes y del último mes. El programa asigna a las variables los valores
 *       introducidos por el usuario.
 */
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

/*
 * Pre:  ---
 * Post: El programa utiliza la información solicitada al usuario(mes y nombre) 
 *       y devuelve una ruta para poder acceder al fichero correspondiente.
 */
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
/*
 * Pre:  ---
 * Post: El programa crea la ruta de los ficheros que pertenecen a los
 *       meses que se encuentran dentro del intervalo determinado por el usuario.
 */
void fichBucle(string usuario, int mesinicio, int mesfinal, string rutaFicheros[]){
    int n=0;
    for(int i=mesinicio; i<=mesfinal; i++){
        rutaFicheros[n]=convRuta(usuario, i);
        n++;
    }
}

/*
 * Pre:  ---
 * Post: El programa solicta al usuario el nombre del fichero 
 *       en el cual se escribirá el informe. El programa devuelve
 *       true si el usuario a escrito, en el caso que presione entrar se devuelve false.
 */
bool pedirNombreFichero(string& nombreEscritura){

    cout << "Escribe el nombre del fichero del informe"<<endl; 
    cout << "(presione solo ENTRAR para escribirlo en la pantalla: ";
    string ignorar;
    getline(cin, ignorar);
    getline(cin,nombreEscritura);
    if(nombreEscritura== ""){
        return true;
    }else{
        return false;
    }
            
/*
 * Pre:  
 * Post: El programa lee los ficheros que siguen la estructura
 *       <fichero-consumo> y en caso de que no sea posible leer 
 *       el fichero el programa muestra en pantalla un mensaje de error. 
 */
}
bool leerFichero(string rutaFicheros[], int elementos, int mesInicial, int mesFinal, GastoDiario registros[]){
    ifstream f;
    for(int i=0; i<elementos;i++){
        string nombreFichero=rutaFicheros[i];
        f.open(nombreFichero);
        if(f.is_open()){
            
            if(leerConsumos(nombreFichero,mesInicial,mesFinal,registros)){
                
            }else{
                cerr << "No se ha podido leer el fichero " <<'"'<<nombreFichero<<'"'<<"."<<endl;
                return false;
            }
            f.close();
        }else{
            cerr << "No se ha podido leer el fichero " <<'"'<<nombreFichero<<'"'<<"."<<endl;
            return false;
        }
    }
    
    return true;
}



/*
 * Pre:  
 * Post: El programa devuelve "false" si no ha podido abrir el fichero
 *       de las tarifas ni ha podido leer 
 *       el fichero e imprime en pantalla un mensaje del error correspondiente. 
 *       En caso contrariodevuelve "true"  y lee los ficheros correspondientes. 
 */
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
        f.close();
    }else{
        cerr << "No se ha podido leer el fichero " <<'"'<<"tarifas-2021-ene-nov.csv"<<'"'<<"."<<endl;
        return false;
    }
    return true;
}

/*
 * Pre:  ---
 * Post: El programa devuelve un numero entero que indica el numero de dias 
 *       que hay entre el primer dia del primer mes hasta el último dí del último mes
 */
int diasTotales(int mesinicio, int mesfinal){
    int dias = 0;
    for (int i=mesinicio;i<=mesfinal;i++){

        dias+=diasDelMes(i,AGNO_ACTUAL);
    }
    return dias;

}



/*
 * Pre:  Las  primeras componentes
 *       del vector «registros» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: El programa busca y escribe en el flujo «f» la hora más cara del periodo 
 *       introducido por el usuario previamente, en que día ocurrió y cual fue su precio.
 */
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


/*
 * Pre:  Las  primeras componentes
 *       del vector «registros» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: El programa busca y escribe en el flujo «f» el dia mas barato del periodo 
 *       introducido por el usuario y cual fue el coste medio del dia
 */
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
    << masBarato.agno << ". Precio medio: "<< fixed << setprecision(5) << costeMedio(registros[diaB])/1000 <<" €/kWh"<<endl;
}


/*
 * Pre:  Las  primeras componentes
 *       del vector «registros» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: El programa calcula el gasto total del consumidor en el  periodo solicitado 
 *       por el usuario y lo escribe en el flujo «f» asociado.
 */
double gastoTotalEF(const GastoDiario registros[],unsigned mesinicial, unsigned mesfinal, ostream& f){
    double gasto = 0;
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gasto+=costeDiario(registros[n]);
        

    }
    f<<"El importe del consumo eléctrico en el periodo considerado ha sido de "<< fixed << setprecision(2)<< gasto <<" €"<<endl;
    return gasto;
}



/*
 * Pre:  Las  primeras componentes
 *       del vector «registros» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: El programa calcula el importe que hubiera supuesto si el precio de la
 *       luz hubiera sido siempre el precio más barato del periodo introducido 
 *       por el usuario y la diferencia entre el precio real y el hipotético.
 *       Además el programa escribe estos resultados en el flujo «f» asociado.
 */
void gastoMinimoEF(const GastoDiario registros[], unsigned mesinicial, unsigned mesfinal,double gasto, ostream& f){
    double gastom = 0;
    for(int n=0;n<diasTotales(mesinicial,mesfinal);n++){
        gastom+=costeDiarioMinimo(registros[n]);
    }
    f<< "El importe mínimo concentrando todo el consumo diario en la hora más barata habría sido de "
    << fixed << setprecision(2)<<gastom<<" €"<<"(un "<<100-(gastom/gasto)*100<<" % menor)."<< endl;
}


/*
 * Pre:  Las  primeras componentes
 *       del vector «registros» contienen datos diarios de precios y consumo
 *       eléctricos de un determinado cliente de nombre «nombreCliente» entre
 *       los meses «mesInicial» y «mesFinal».
 * Post: El programa calcula y escribe en el flujo «f» el coste correspondiente a cada tarifa.
 */
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
string usuario = nombreCliente;
    for( int i=0;i<=usuario.length();i++){
    usuario[i] = toupper(usuario[i]);
    }  
    f<<"INFORME DEL CLIENTE "<< '"'<<usuario<<'"'<< " ENTRE LOS MESES "<<mesInicial<<" Y " << mesFinal << " DE 2021" << endl;
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


/*
 * Pre:  ---
 * Post: El programa crea un fichero y escribe en él, el informe sobre consumo
 *       eléctrico indicado en el enunciado de este trabajo.
 */
void crearFichero(string nombreFichero, GastoDiario regDiarios[], unsigned numRegs, string nombreCliente, unsigned mesInicial, unsigned mesFinal){
    ofstream f;
    f.open(nombreFichero);
    escribirInforme(f, regDiarios, numRegs, nombreCliente, mesInicial, mesFinal);
    
}

/*
 *       El programa utiliza las funciones previamente descritas para solicitar
 *       al usuario el nombre del usuario y el periodo de tiempo. A partir de esos
 *       datos el programa lee los ficheros correspondientes  y extrae de ellos los
 *       datos necesarios para realizar un informe sobre el gasto del usuario en el periodo 
 *       introducido por el usuario. El programa en funcion del usuario muestra en un pantalla 
 *       este informe o crea un fichero con el nombre que el usuario introduce y escribe en él el informe.
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
    GastoDiario registros[diasTotales(mesinicio,mesfinal)];

    if(leerFichero(rutaFicheros, elementos,mesinicio,mesfinal,registros)){
        if(pedirNombreFichero(nombreEscritura)){
            cout<<endl;
            if(leerFichTafs(mesinicio, mesfinal, registros)){
                escribirInforme(cout,registros,diasTotales(mesinicio,mesfinal),usuario,mesinicio,mesfinal);
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

