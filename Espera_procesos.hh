/**
 * @file Espera_procesos.hh
 * @brief Especificacion de la clase Espera_procesos
 * 
 */
#ifndef _ESPERA_PROCESOS_
#define _ESPERA_PROCESOS_

#include "Cluster.hh"
#include "Prioridad.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM

#include <list>
#include <map>
#endif
/**
 * @class Espera_procesos
 * @brief Representa un área de espera de procesos con una lista de prioridades, las cuales tienen una lista de procesos en espera.
 * 
 */
class Espera_procesos
{
private:
    /**@brief  Mapa de prioridades con el identificador de la Prioridad como clave y la Prioridad como valor.
*/
    map<string, Prioridad> prioridades; 
public:
    //Constructoras
    /**
     * @brief Crea un area de espera de procesos vacia
     * \pre *Cierto*
     * \post Genera un objeto Espera_procesos vacio
     * \coste Constante
     */
    Espera_procesos();

    //Modificadoras
    /**
     * @brief Añade una Prioridad al área de espera 
     * 
     * \pre *La prioridad no existe*
     * \post La prioridad se añade al área de espera de procesos en caso de que no exista
     * \coste Logaritmico
     */
     
    void add_prioridad(const string& priority_ID); 

    /**
     * @brief Añade un proceso a la prioridad
     * 
     *
     * \pre *La prioridad existe y el proceso no existe*
     * \post El proceso se añade a la prioridad priority_ID
     * \coste Logaritmico
     */
    void add_proceso(const Proceso& p, const string& priority_ID); 
    
    /**
     * @brief Elimina una prioridad del area de espera de procesos
     * 
     * \pre *La prioridad existe*
     * \post La prioridad se elimina del área de espera de procesos
     * \coste Logaritmico
     */
    void del_prioridad(const string& priority_ID);

    /**
     * @brief Se envia n procesos al cluster
     * 
     * \pre *El área de espera de procesos no esta vacia*
     * \post Los n procesos más antiguos de las prioridades más altas se envian al cluster
     */

    void proceso_cluster(int n, Cluster& c);

    //Entrada y salida
    /**
     * @brief Se leen N identificadores de prioridad
     * 
     * \pre *Cierto*
     * \post El area de espera de procesos se inicializa con N prioridades
     * \coste N * Logaritmico
     */
    void leer_id_prioridades();

    /**
     * @brief Se imprime por la salida estandar el area de espera de procesos
     * 
     * \pre *Cierto*
     * \post Se imprime por la salida estandar todos los procesos de todas las prioridades
     *  \coste Lineal en el numero de procesos
     */
    void imprimir_area_espera() const;

    /**
     * @brief Se imprime por la salida estandar los procesos de la prioridad
     * 
     * @param priority_ID El identificador de la prioridad a imprimir
     * \pre *La prioridad existe*
     * \post Se imprime por la salida estandar todos los procesos de la prioridad
     * \coste Lineal en el numero de procesos de la prioridad
     
     */
    void procesos_prioridad(const string& priority_ID) const;


};

#endif
