/**
 * @file Proceso.hh
 *
 * @brief Especificacion de la clase Proceso
 * 
 */
#ifndef _PROCESO_
#define _PROCESO_
#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

/**
 * @class Proceso
 * @brief Representa a un proceso con un identificador, su memoria requerida y su tiempo de ejecucion
 * 
 * Ofrece la funcionalidad de leer e imprimir los atributos de un proceso, actualizar su tiempo de ejecucion 
 * y la consulta de sus atributos.
 */
 class Proceso
 {
 private:
   /** @brief Identificador del proceso*/
    int PID;

    /** @brief Tiempo restante del proceso antes de terminar*/
    int tiempo; 

    /** @brief Cantidad de memoria necesaria para el proceso*/
    int memoria; 

 public:
    // Constructoras
    /**
     * @brief Constructora Proceso por defecto
     * \pre *Cierto*
     * \post Un Proceso vacio, con identificador, tiempo requerido y memoria requerida sin inicializar.
	  * \coste Constante
     */
    Proceso();


    // Modificadoras

	/**
	 * @brief Actualiza el tiempo restante de ejecucion del proceso
	 * 
	 * \pre seconds > 0 y seconds menos o igual que el tiempo restante del proceso
    * \post El tiempo restante del proceso se reduce en seconds
    * \coste Constante
	 */
	void actualizar_tiempo(int seconds);
    
    // Consultoras

    /**
     * @brief Consulta el identificador del proceso
     * 
     * \pre *Cierto*
     * \post Devuelve el identificador del proceso
     * \coste Constante
     */
    int consultar_PID() const;

    /**
     * @brief Consulta la cantidad de memoria que ocupa el proceso
     * 
     * 
     * 
     * \pre *Cierto*
     * \post Devuelve el tamaño de memoria que ocupa el proceso
     * \coste Constante
     */
    int consultar_mem_req() const;

    /**
     * @brief Consulta el tiempo en el que finalizara el proceso 
     * 
     * 
     * 
     * \pre *Cierto*
     * \post Devuelve el tiempo de finalizacion del proceso
     * \coste Constante
     */
    int consultar_tiempo_finalizacion() const;



    // Lectura y escritura

    /**
     * @brief Lee los atributos de un proceso
     * 
     * \pre *Cierto*
     * \post El proceso se inicializa con los atributos leidos
     * \coste Constante
     */
    void leer_proceso();

    /**
     * @brief Imprime los atributos de un proceso
     * 
     * \pre *Cierto*
     * \post Se imprimen los atributos del proceso por el canal estandar de salida
     * \coste Constante
     */
    void imprimir_proceso() const;

 };
 #endif
 
 