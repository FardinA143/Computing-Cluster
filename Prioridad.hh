/**
 * @file Prioridad.hh
 * @brief Especificacion de la clase Prioridad
 * 
 */
#ifndef _PRIORIDAD_
#define _PRIORIDAD_
#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <list>
#include <map>
#endif
/**
 * @class Prioridad
 * @brief Representa una prioridad con una lista de procesos, el orden en el que ingresaron a la prioridad y el numero de procesos enviados y rechazados por el cluster
 * 
 */
class Prioridad
{
private:
    /**@brief Lista de procesos ordenados por el orden de entrada de los procesos. */
    list<int> proc_age; 
    /**@brief Mapa de procesos con identificador como clave y el Proceso como valor*/
    map<int, Proceso> procesos; 
    /**@brief Envios y rechazos de procesos que se han intentado enviar con send_proceso()*/
    pair<int, int> send_data; 
    

public:
    //Constructora
    /**
     * @brief Constructora Prioridad con identificador
     * 
     * @param priority_ID Identificador de la prioridad
     * \pre *Cierto*
     * \post Genera un objeto Prioridad con send_data a 0 
     * \coste Constante
     */
    Prioridad();

    // Modificadoras
    /**
     * @brief Añade un proceso a la prioridad
     * 
     * @param p Proceso a añadir
     * \pre *Cierto*
     * \post El proceso se añade al final de la lista de procesos, en caso de que no existe
     * \coste Logaritmico
     */
    void add_proceso(const Proceso& p); 



    /**
     * @brief Envia al cluster c num procesos 
     * \pre num es mayor que 0
     * \post Se intentan enviar num procesos al cluster c
     * \coste Lineal 
     */
    void send_proceso(int &num, Cluster &c);


    // Consultoras
    /**
     * @brief Mira si la prioridad esta vacia
     * 
     * 
     * \pre *Cierto*
     * \post Se devuelve el estado de la prioridad
     * \coste Constante 
     */
    bool empty() const; 

    /**
     * @brief Mira si un proceso existe en la prioridad
     *
     * \pre *Cierto*
     * \post Se devuelve la existencia del proceso
     * \coste Logaritmico
     */
    bool existe_proceso(int ID) const; 

    
    // Entrada salida
    /**
     * @brief Imprime los procesos de la prioridad
     * 
     * \pre Hay procesos en la prioridad
     * \post Se imprimen los procesos de la prioridad, con sus detalles por orden de antiguedad
     * \coste Lineal
     */
    void print_procesos() const; 
    /**
     * @brief Imprime las veces que se han enviado y rechazado procesos de la prioridad
     * \pre *Cierto*
     * \post Se imprimen las veces que se han enviado y rechazado procesos de la prioridad por la salida estandar
     * \coste Constante
     */
    void enviados_rechazados() const; 

};
#endif

