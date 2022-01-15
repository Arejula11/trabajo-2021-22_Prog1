/******************************************************************************\
 * Programación 1. Trabajo obligatorio curso 2021-22
 * Autores: Pablo Ernesto Angusto Delgado y Miguel Aréjula Aísa
\******************************************************************************/

#include "gasto-diario.hpp"
#include <iostream>
using namespace std;


/*
 * Pre:  ---
 * Post: Devuelve la hora en la que el precio de la electricidad según los datos
 *       de precios horarios del registro «gasto» fue más cara.
 */
unsigned horaMasCara(const GastoDiario& gasto){
    double preciomayor = gasto.precioE[0];
    unsigned hora;
    for(unsigned i=1; i<24; i++){
        if(preciomayor<gasto.precioE[i]){
            preciomayor=gasto.precioE[i];
            hora = i;
        }
    }
    return hora;
}


/*
 * Pre:  ---
 * Post: Devuelve el precio medio de la electricidad según los datos de precios
 *       horarios del registro «gasto».
 */
double costeMedio(const GastoDiario& gasto){
    double suma = 0;
    for(int i=0;i<24;i++){
        suma+=gasto.precioE[i];

    }
    return suma/24;
}


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto».
 */
double costeDiario(const GastoDiario& gasto){
    double gastoTotal = 0;
    for(int i=0;i<24;i++){
        gastoTotal+=(gasto.precioE[i]/1000)*gasto.consumoE[i];

    }
    return gastoTotal;
}


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que todo el 
 *       consumo eléctrico reflejado en el registro «gasto» hubiera tenido lugar
 *       en la hora con el precio más barato del registro «gasto».
 */
double costeDiarioMinimo(const GastoDiario& gasto){
    double preciomenor = gasto.precioE[0];
    double costetotal=0;
    for(unsigned i=1; i<24; i++){
        if(preciomenor>gasto.precioE[i]){
            preciomenor=gasto.precioE[i];
            
        }
    }
    for(int i=0; i<24; i++){
        costetotal+= (preciomenor/1000)*gasto.consumoE[i];
    }
    return costetotal;
}