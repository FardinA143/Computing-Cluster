/**
 * @file Cluster.hh
 * 
 * @brief Especificación de la clase Cluster.
 * 
 */

#ifndef _CLUSTER_
#define _CLUSTER_

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include<map>
#include "BinTree.hh" 
#include<vector> 
#include<iostream>
#include<queue>
#endif



/**
 * @class Cluster
 * @brief Representa a un cluster de procesadores.
 * 
 * Se proporciona un cluster donde los procesadores se encuentran distribuidos en forma de arbol binario, teniendo cada uno entre 0 y 2 subprocesadores. Todo cluster tiene que tener por lo menos un procesador
 */
class Cluster
{
private:
    /**@brief Mapa de procesadores, con el identificador como clave y el Procesador como valor*/
    map<string, Procesador> procesadores_mapa;    
    /**@brief Arbol de procesadores*/
    BinTree<string> procesadores_arbol;     

    /**
     * @brief Lee la estructura del cluster
     * \pre El cluster esta vacio
     * \post Se leen los procesadores y se almacenan en las variables.
     * \coste Lineal en el numero de procesadores 
     */
    static void leer_cluster(BinTree<string>& arbol_procesadores, map <string, Procesador>& procesadores);
    /**
     * @brief Modifica el cluster copiando los procesadores del cluster c en el cluster actual, manteniendo la jerarquia de procesadores 
     * \pre El procesador ID existe y no contiene procesos en marcha
     * \post Se copian los procesadores del cluster c en el cluster actual, manteniendo la jerarquia de procesadores. En caso de que el procesador ID tenga subprocesadores, se lanza un error.
     * \coste Lineal en el numero de procesadores del cluster c_temp
     */
    bool juntar_arboles(const string& procID, Cluster& c, BinTree<string>& arbol);

    /**
     * @brief Busca un procesador en el cluster que cumpla las condiciones necesarias para añadir un proceso
     * La busqueda se realiza siguiendo el metodo breadth-first search
     * \pre El cluster no esta vacio
     * \post Se devuelve un iterador al procesador que cumple las condiciones necesarias para añadir un proceso
     * \coste Lineal en el numero de procesadores del cluster
     */
    void search_valid_proc(map<string, Procesador>::iterator& cpu_iterator, const BinTree<string>& proc_tree, int pid, int req_mem);
    
    /**
     * @brief Devuelve el mapa de procesadores del cluster
     * \pre *Cierto*
     * \post Se devuelve el mapa de procesadores del cluster
     * \coste Lineal 
     */
    map<string, Procesador> get_cpu_map() const;

    /**
     * @brief Devuelve el arbol de procesadores del cluster
     * \pre *Cierto*
     * \post Se devuelve el arbol de procesadores del cluster
     * \coste Lineal 
     */
    BinTree<string> get_cpu_tree() const;
    /**
     * @brief Imprime la estructura del cluster
     * \pre *Cierto*
     * \post Se imprime la estructura del cluster
     * \coste Lineal en el numero de procesadores
    */
    static void print_cluster(const BinTree<string>& arbol_procesadores);

public:

    // Constructoras
    /**
     * @brief Constructora Cluster 
     * 
     * \pre *Cierto*
     * \post Genera un objeto "Cluster" pero sin inicializarlo.
     * 
     */
    Cluster();
    // Modificadoras
    /**
     * @brief Añade un proceso al procesador especificado
     * \pre El Proceso proceso no existe en el cluster y el procesador ID existe
     * \post Se añade el proceso al procesador especificado. Si ya existe el proceso o no existe el procesador, o no hay suficiente espacio en el procesador, se lanza un error.
     * \coste Logaritmico (llamada a add_proceso de Procesador)
     * 
     */
    void add_proc_cpu(const Proceso& proceso, const string& ID);
    /**
     * @brief Busca un procesador apto para el Proceso p_to_add proporcionado por el area de espera y devuelve un booleano indicando si se ha encontrado un procesador apto
     * \pre El Proceso p_to_add no existe en el cluster
     * \post Se devuelve un booleano indicando si se ha encontrado un procesador apto para el Proceso p_to_add proporcionado por el area de espera. Si no se ha encontrado un procesador apto, se devuelve false.
     * \coste lineal al buscar y logaritmico al añadir (llamada a add_proceso de Procesador) 
     * 
     */
    bool add_proc_ep(const Proceso& p_to_add);

    /**
     * @brief Actualiza los tiempos de los procesos en el cluster
     * \pre *Cierto*
     * \post Se avanza el tiempo de ejecucion de los procesos en el cluster
     * \coste Lineal en el numero de procesos del cluster
     * 
     */
    void avanzar_tiempo(int segundos);
    /**
     * @brief Elimina el proceso con identificador PID del procesador especificado
     * \pre El procesador cpuID existe y contiene el proceso con identificador PID
     * \post Se elimina el proceso con identificador PID del procesador especificado. Si no existe el procesador o no contiene el proceso, se lanza un error.
     * \coste Logaritmico (llamada a del_proceso de Procesador)
     * 
     */
    void eliminar_proceso(const string& cpuID, int PID);

    /**
     * @brief Modifica el cluster copiando los procesadores del cluster c en el cluster actual, manteniendo la jerarquia de procesadores 
     * \pre El procesador ID existe y no contiene procesos en marcha
     * \post Se copian los procesadores del cluster c en el cluster actual, manteniendo la jerarquia de procesadores. En caso de que el procesador ID tenga subprocesadores, se lanza un error.
     * \coste Logaritmico (busquedas en mapas) y lineal (funcion juntar_arboles)
     */
    void modificar_cluster(const string& cpuID, Cluster& cluster);

    /**
     * @brief Compacta la memoria del cluster
     * \pre *Cierto*
     * \post Se compacta la memoria de cada procesador del cluster
     * \coste Lineal
     * 
     */
    void compactar_memoria_cluster();

    /**
     * @brief Compacta la memoria del procesador especificado
     * \pre El procesador ID existe
     * \post Se compacta la memoria del procesador especificado. Si no existe el procesador, se lanza un error.
     * \coste Logaritmico
     */
    void compactar_mem_proc(const string& ID);

    // Lectura y escritura
    /**
     * @brief Lee la estructura del cluster
     * \pre *Cierto*
     * \post Se leen los procesadores y se almacenan en las variables.
     * \coste Lineal 
     */
    void leer_estructura_cluster();

    /**
     * @brief Imprime la estructura del cluster
     * \pre *Cierto*
     * \post Se imprime la estructura del cluster
     * \coste Lineal en el numero de procesadores 
     */
    void imprimir_estructura_cluster() const;
    /**
     * @brief Imprime los procesadores del cluster, junto a sus detalles
     * \pre *Cierto*
     * \post Se imprime los procesadores del cluster, junto a sus detalles
     * \coste Lineal en el numero de procesadores
     */
    void imprimir_procesadores_cluster() const;
    /**
     * @brief Imprime los detalles del procesador especificado
     * \pre El procesador ID existe, o el iterador it apunta a un procesador del cluster
     * \post Se imprime los detalles del procesador especificado. Si no existe el procesador, se lanza un error.
     * \coste Logaritmico (busqueda en mapas) / Lineal si ya se tiene el iterador
     */
    void imprimir_procesador(const string& procID, map<string, Procesador>::const_iterator& it) const;
    
};
#endif