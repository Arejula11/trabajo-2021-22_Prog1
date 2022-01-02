#include "fichs-electricos.hpp"
#include "fecha.hpp"
/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-precios> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <precio-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «precio»,
 *       respectivamente, los datos sobre la fecha, hora y precio horario
 *       correspondientes a la línea que se ha extraído del flujo «f».
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerPrecioHorario(istream& f, Fecha& fecha, unsigned& hora, double& precio){
    string ignorar;
    unsigned diffhora;
    getline(f,ignorar,';');
    getline(f,ignorar,';');
    getline(f,ignorar,';');
    getline(f,ignorar,';');
    f >> precio;
    f.get();
    f >> fecha.agno;
    f.get();
    f >> fecha.mes;
    f.get();
    f >> fecha.dia;
    f.get();
    f >> hora;
    getline(f,ignorar,'+');
    f >> diffhora;
    //hora = hora + diffhora;
    getline(f,ignorar);

    if(!f.eof()){
        return true;
    }else{
        return false;
        
    }

}


/*
 * Pre:  «nombreFichero» es el nombre de un fichero externo que cumple con la
 *       sintaxis de la regla <fichero-precios> establecida en el enunciado; 
 *       «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en «nombreFichero» en las 
 *       componentes correspondientes a la hora del precio del campo «precios»
 *       en las primeras componentes del vector «registros», cuyos campos
 *       «fecha» se han actualizado y han quedado en orden cronológico (tal y
 *       como aparecían en el fichero). LOS DATOS DEL VECTOR CORRESPONDIENTE AL
 *       CAMPO «CONSUMO» NO SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer del fichero de nombre 
 *       «nombreFichero» correctamente, y «false» en caso contrario.
 */
bool leerPrecios(const string nombreFichero,
                 const unsigned mesInicial, const unsigned mesFinal,
                 GastoDiario registros[]){

    ifstream f;
    Fecha fecha;
    Fecha fechaInicial;
    fechaInicial.agno=2021;
    fechaInicial.mes=mesInicial;
    fechaInicial.dia=1;
    string ignorar;
    unsigned hora;
    double precio;
    f.open(nombreFichero);
    if(f.is_open()){

        getline(f,ignorar);
        while(leerPrecioHorario(f,fecha,hora, precio)){
            if(fecha.mes>=mesInicial && fecha.mes<=mesFinal){
                    registros[diasTranscurridos(fechaInicial, fecha)].precioE[hora]=precio;
                
            }
        
        }
        return true;

    }else{
        return false;
    }
}


/*
 * Pre:  «f» está asociado con un fichero externo que cumple con la sintaxis de
 *       la regla <fichero-consumos> establecida en el enunciado y está en
 *       disposición de leer desde el principio de una línea que cumple con la
 *       regla <consumo-horario>.
 * Post: Ha extraido de «f» la línea a la que hacía referencia la precondición
 *       y ha asignado a los parámetros «fecha», «hora» y «consumo»,
 *       respectivamente, los datos sobre la fecha, hora y consumo horario
 *       correspondientes a la línea que se ha extraído del flujo «f». 
 *       El flujo «f» continua asociado con el fichero externo y en disposición
 *       de extraer datos a partir de la siguiente línea.
 *       La función ha devuelto «true» si no se han terminado los datos del
 *       fichero en el intento de lectura y «false» en caso contrario.
 */
bool leerConsumoHorario(istream& f,
                        Fecha& fecha, unsigned& hora, double& consumo){
        string ignorar;
        getline(f,ignorar, ';');
        
        f >> fecha.dia;
        f.get();
        f >> fecha.mes;
        f.get();
        f >> fecha.agno;
        f.get();
        f >> hora;
        f.get();
        f >> consumo;
        getline(f,ignorar);
        if(!f.eof()){
            return true;
        }else{
            return false;
        }
    }
            


/*
 * Pre:  «mesInicial» y «mesFinal» están ambos entre «PRIMER_MES» y «ULTIMO_MES»
 *       y mesInicial < mesFinal; si para cada mes entre «mesInicial» y
 *       «mesFinal» existe un fichero con nombre de la forma
 *       "datos/" + nombreCliente + "-2021-" + mes-con-dos-cifras + ".csv", este
 *       cumple con la sintaxis de la regla <fichero-consumos> establecida en el
 *       enunciado.
 * Post: Ha copiado los datos de precios horarios correspondientes a fechas 
 *       entre «mesInicial» y «mesFinal» presentes en los ficheros mencionados
 *       en la precondición en las componentes correspondientes a la hora del
 *       consumo del campo «consumo» en las primeras componentes del vector
 *       «registros». LOS DATOS DEL VECTOR CORRESPONDIENTE AL CAMPO «PRECIOS» NO
 *       SE HAN MODIFICADO.
 *       La función ha devuelto «true» si ha podido leer de todos los ficheros 
 *       referidos en la precondición correctamente, y «false» en caso contrario.
 */
bool leerConsumos(const string nombreCliente,
                  const unsigned mesInicial, const unsigned mesFinal,
                  GastoDiario registros[]){
    ifstream f;
    Fecha fecha;
    Fecha fechaInicial;
    fechaInicial.agno=2021;
    fechaInicial.mes=mesInicial;
    fechaInicial.dia=1;
    unsigned hora;
    double consumo;
    string ignorar;
    unsigned diastrans;
        f.open(nombreCliente);
        if(f.is_open()){
            getline(f,ignorar);
            while(leerConsumoHorario(f,fecha,hora,consumo)){
                diastrans=diasTranscurridos(fechaInicial, fecha);
                registros[diastrans].consumoE[hora]=consumo;
            }
            return true;
            }else{
                return false;
            }
            


}
