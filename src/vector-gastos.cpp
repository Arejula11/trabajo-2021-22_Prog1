#include "vector-gastos.hpp"
#include "gasto-diario.hpp"
#include <iostream>
using namespace std;
/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el menor precio
 *       diario promedio de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios» y al parámetro «precioMaximo», el valor de ese precio
 *       promedio diario mínimo.
 */
void diaMasBarato(const GastoDiario regsDiarios[], const unsigned numRegs,
                  Fecha& dia, double& precioMedioMinimo){

        GastoDiario gasto;
        double aux = 0;
        unsigned diaCaro;
        for ( int i=0; i<numRegs;i++){
            gasto = regsDiarios[i];
            if (aux>costeMedio(gasto)){

                diaCaro = i;
                aux = costeMedio(gasto);
            }


        }
        dia.dia = diaCaro ;
        precioMedioMinimo = aux;

}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios horarios de energía eléctrica.
 * Post: Asigna al parámetro «dia» el día en el que se registró el mayor precio
 *       horario de entre las primeras «numRegs» componentes del vector
 *       «regsDiarios»; al parámetro «hora», la hora de ese día en la que se
 *       registró ese mayor precio horario y al parámetro «precioMaximo», el
 *       valor de ese precio máximo.
 */
void horaMasCara( const GastoDiario regsDiarios[], const unsigned numRegs,
                 Fecha& dia, unsigned& hora, double& precioMaximo){
    double preciomayor;
    for(unsigned n=0;n<numRegs;n++){
        preciomayor=regsDiarios[n].precioE[horaMasCara(regsDiarios[n])];
        if(precioMaximo<preciomayor){
            precioMaximo=preciomayor;
            dia.dia=n;
            hora=horaMasCara(regsDiarios[n]);
        }
    }
    

}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros de la energía eléctrica consumida según los
 *       datos de las primeras «numRegs» componentes del vector «regsDiarios».
 */
double costeTerminoVariable(const GastoDiario regsDiarios[],
                            const unsigned numRegs){

    GastoDiario gasto;
    double coste;
    for ( int i=0; i<numRegs;i++){
        gasto = regsDiarios[i];
        coste+=costeDiario(gasto);  
    }

    return coste;      
          



}

/*
 * Pre:  Las primeras «numRegs» componentes del vector «regsDiarios» almacenan
 *       datos de precios y consumo horarios de energía eléctrica.
 * Post: Devuelve el coste en euros del coste de la energía eléctrica consumida 
 *       según los datos de las primeras «numRegs» componentes del vector
 *       «regsDiarios», suponiendo que TODO el consumo de cada uno de los días
 *       almacenados en las componentes de «regsDiarios» se ha producido
 *       precisamente en la hora más barata de ese día.
 */
double costeMinimoPosible(const GastoDiario regsDiarios[], 
                          const unsigned numRegs){
    double gastototal=0;
    for(unsigned i=0; i<numRegs; i++){
        gastototal = gastototal + costeDiarioMinimo(regsDiarios[i]);
    }
    return gastototal;

}