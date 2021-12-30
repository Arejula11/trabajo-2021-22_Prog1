/******************************************************************************\
 *Curso de Programación 1. Tema 11 (Registros) y trabajo obligatorio 2021-22
 * Autores: Javier Martínez y Miguel Ángel Latre
 * Última revisión: 5 de diciembre de 2021
 * Resumen: Fichero de interfaz «fecha.hpp» del módulo «fecha».
\******************************************************************************/
#pragma once
#include <ostream>
using namespace std;

/*
 * Definición del tipo de dato Fecha
 */
struct Fecha {
    unsigned dia, mes, agno;
};


/*
 * Pre:  ---
 * Post: Ha escrito la fecha «dia» en el flujo «f».
 */
void mostrar(ostream& f, const Fecha dia);

/*
 * Pre:  1 ≤ mes ≤ 12 y agno > 1582.
 * Post: Ha devuelto el número de días del mes correspondiente al parámetro «mes»
 *       del año correspondiente al parámetro «agno».
 *       Por ejemplo: diasDelMes(10, 2018) devuelve 31,
 *                    diasDelMes(2, 2018) devuelve 28 y
 *                    diasDelMes(2, 2020) devuelve 29.
 */
unsigned diasDelMes(unsigned mes, unsigned agno);


/*
 * Pre:  agno > 1582.
 * Post: Ha devuelto el número de días que tiene el año «agno».
 *       Por ejemplo: diasDelAgno(2018) devuelve 365 y
 *                    diasDelAgno(2020) devuelve 366.
 */
unsigned diasDelAgno(unsigned agno);

/*
 * Pre:  «inicial» es igual o anterior cronológicamente a «final».
 * Post: Ha devuelto el número de días transcurridos entre las fechas «inicial»
 *       y «final».
 */
unsigned diasTranscurridos(const Fecha inicial, const Fecha final);


