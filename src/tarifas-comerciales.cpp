#include "tarifas-comerciales.hpp"
#include <iostream>
using namespace std;

/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos del registro «gasto» suponiendo que se han
 *       aplicado los costes especificados por la tarifa del parámetro «tarifa».
 */
double costeDiarioTarifaPlanaTramos(const GastoDiario& gasto,
                                    const TarifaPlanaTramos tarifa){
    double costetotal=0;
    for(int i=0;i<8;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.valle;
    }
    for(int i=8;i<10;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.llano;
    }
    for(int i=10;i<14;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.punta;
    }
    for(int i=14;i<18;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.llano;
    }
    for(int i=18;i<22;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.punta;
    }
    for(int i=22;i<24;i++){
        costetotal +=  gasto.consumoE[i] * tarifa.llano;
    }
    
    return costetotal;

}


/*
 * Pre:  ---
 * Post: Devuelve el importe en euros del coste de la energía eléctrica
 *       reflejados por los datos de las «numRegs» primeras componentes del
 *       vector «regDiario» suponiendo que se han aplicado en cada uno de los
 *       días de dichas componentes los costes especificados por la tarifa del
 *       parámetro «tarifa».
 */
double costeTarifaPlanaTramos(const GastoDiario regDiario[],
                        const unsigned numRegs, const TarifaPlanaTramos tarifa){
    double costetotal=0;
    for(unsigned i=0; i<numRegs; i++){
        costetotal +=  costeDiarioTarifaPlanaTramos(regDiario[i], tarifa);
    }
    return costetotal;
                        
                        
}