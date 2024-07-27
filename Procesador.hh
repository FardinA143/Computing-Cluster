/**
 * @file Procesador.hh
 * @brief Especificacion de la clase Procesador
 * 
 */

#ifndef _PROCESADOR_
#define _PROCESADOR_

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <vector>
#include <set>
#endif
using namespace std;
 
/**
 * @class Procesador
 * @brief Representa a un procesador con un identificador, su memoria y los procesos que contiene
 * 
 */
class Procesador
{
private:
    /**@brief Identificador del Procesador en formato string*/
    string ID;
    /**@brief Valor de la memoria en el procesador
     * mem.first = memoria total del procesador
     * mem.second = memoria ocupada del procesador
    */
    pair<int, int> mem;

    /**@brief Mapa de procesos del procesador, con el identificador del proceso como clave y la posición de memoria del proceso como valor*/
    map<int, int> procesos_ID; 

    /**@brief Mapa de procesos del procesador, con la posición de memoria del proceso como clave y el proceso como valor*/
    map<int, Proceso> mem_proc;

    /**@brief Mapa de espacios libres del procesador, con el tamaño del espacio libre como clave y el inicio del espacio libre como valor*/
    map<int, set<int>> free_space;

public:
    //Constructoras
    /**
     * @brief Constructora por defecto de un objeto Procesador
     * 
     * \pre *Cierto*
     * \post Un Procesador vacio, con identificador y memoria sin inicializar.
     * \coste Constante
     */
    Procesador();

    /**
     * @brief Constructora de un objeto Procesador
     * 
     * \pre El procesador procID no existe y mem es mayor que 0
     * \post Un Procesador con identificador y memoria inicializados.
     * \coste Constante
     */
    Procesador(const string& procID, int mem);
    
    //Modificadoras
    /**
     * @brief Añade un proceso al procesador
     * 
     * \pre El procesador tiene espacio suficiente para el proceso
     * \post El proceso se añade al procesador
     * \coste Logaritmico
     */
    void add_proceso(const Proceso& p);

    /**
     * @brief Elimina un proceso con id_proceso del procesador
     * \pre El procesador contiene un proceso con id_proceso
     * \post El proceso con id_proceso se elimina del procesador
     * \coste Logaritmico
     */
    void del_proceso(map <int, Proceso>::iterator& it, int id_proceso);

    /**
     * @brief Actualiza el tiempo restante de ejecucion de cada proceso del procesador
     * \pre seconds mayor que 0
     * \post El tiempo restante de ejecucion de cada proceso del procesador se reduce en seconds
     * \coste Lineal respecto al numero de procesos del procesador. Exponencial si hay procesos que terminan (llamada a del_proceso)
     */
    void actualizar_tiempo(int seconds);
    
    /**
     * @brief Compacta la memoria del procesador
     * \pre Hay procesos en el procesador
     * \post Los procesos del procesador se desplazan al principio del procesador para dejar el espacio libre al final
     * 
     * \coste Logaritmico 
     */
    void compactar_memoria();

    //Consultoras
    /**
     * @brief Get the memoria disponible object
     * 
     * \pre *Cierto*
     * \post Devuelve la memoria disponible del procesador
     * \coste Constante
     * 
     */
    int get_memoria_disponible() const;

    /**
     * @brief Devuelve true o false dependiendo si existe el proceso con id_proceso en el procesador
     * 
     * \pre El procesador esta inicializado
     * \post Devuelve un valor booleano informando de la existencia del proceso con id_proceso en el procesador
     * \coste Logaritmico 
     * 
     */
    bool existe_proceso(int id_proceso) const;

    /**
     * @brief Consulta el identificador del procesador
     * \pre *Cierto*
     * \post Devuelve el identificador del procesador
     * \coste Constante
     */
    const string& get_ID() const;

    /**
     * @brief Indica si hay procesos en el procesador
     * \pre *Cierto*
     * \post Devuelve un valor booleano informando de si hay procesos en el procesador
     * \coste Constante
     */
    bool en_marcha() const;

    /**
     * @brief Indica si hay espacio libre en el procesador de tamaño size
     * 
     * \pre size mayor que 0
     * \post Devuelve un valor booleano informando de si hay espacio libre en el procesador de tamaño size, y si lo hay, devuelve la posicion del espacio libre en la variable pos
     * \coste Logaritmico
     */
    bool get_free_space(int size, int& pos) const;

   // Lectura y escritura
    /**
     * @brief Imprime el procesador
     * 
     * \pre *Cierto*
     * \post Imprime el procesador
     * \coste Lineal respecto al numero de procesos del procesador
     */
    void imprimir_procesador() const;
    
};
#endif



