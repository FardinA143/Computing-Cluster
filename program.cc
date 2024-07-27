/**
 * @mainpage Práctica PRO2: Simulación del rendimiento de procesadores interconectados
* En esta práctica se diseña un programa capaz de simular el rendimiento de un sistema 
 * de procesadores interconectados. El sistema está compuesto por un clúster de procesadores, 
 * los cuales pueden tener subprocesadores. Cada uno de los procesadores tiene una memoria asignada 
 * al principio, con la cual pueden ejecutar procesos. Cada proceso tiene un tiempo de ejecución estimado, 
 * ocupación de memoria estimada y una prioridad. 
 *
 * @author Fardin Arafat
 * 
*/

/** @file program.cc
    @brief Archivo del programa principal encargado de recibir instrucciones y activar las funciones correspondientes.
*/
#include "Espera_procesos.hh"
#include "Cluster.hh"
#include "Procesador.hh"
#include "Proceso.hh"

/**
 * @brief Programa principal encargado de recibir instrucciones y activar las funciones correspondientes.
 * El programa lee las instrucciones de la entrada estándar y las interpreta, para posteriormente ejecutar la acción correspondiente.
 * 
 */
int main() {
    Cluster c_principal;
    Espera_procesos espera;

    c_principal.leer_estructura_cluster();
    espera.leer_id_prioridades();

    string command;
    cin >> command;
    while (command != "fin") {

        if (command == "configurar_cluster"                 or command == "cc"  ){
            cout << '#' << command << endl;
            c_principal.leer_estructura_cluster();
        }

        else if (command == "modificar_cluster"             or command == "mc"  ){
            
            string ID_Procesador;
            cin >> ID_Procesador;

            Cluster c_aux;
            c_aux.leer_estructura_cluster();
            cout << '#' << command << ' ' << ID_Procesador << endl;
            c_principal.modificar_cluster(ID_Procesador, c_aux);

        }

        else if (command == "alta_prioridad"                or command == "ap"  ){
           
            string priority_ID;
            cin >> priority_ID;
            cout << '#' << command << ' ' << priority_ID << endl;                
            espera.add_prioridad(priority_ID);
        }

        else if (command == "baja_prioridad"                or command == "bp"  ){
            
            string priority_ID;
            cin >> priority_ID;
            cout << '#' << command << ' ' << priority_ID << endl;
            espera.del_prioridad(priority_ID);
        }

        else if (command == "alta_proceso_espera"           or command == "ape" ){
            
            string priority_ID;
            cin >> priority_ID;
            Proceso p_to_add;
            p_to_add.leer_proceso();
            cout << '#' << command <<  ' ' << priority_ID << ' ' << p_to_add.consultar_PID() << endl;
            espera.add_proceso(p_to_add, priority_ID);
        }
        
        else if (command == "alta_proceso_procesador"       or command == "app" ){
            
            string ID_Procesador;
            cin >> ID_Procesador;
            Proceso p_to_add;
            p_to_add.leer_proceso();
            cout << '#' << command << ' ' << ID_Procesador << ' ' << p_to_add.consultar_PID() << endl;
            c_principal.add_proc_cpu(p_to_add, ID_Procesador);
        }
        
        else if (command == "baja_proceso_procesador"       or command == "bpp" ){

            string ID_Procesador;
            int PID;
            cin >>  ID_Procesador >> PID;
            cout << '#' << command << ' ' << ID_Procesador << ' ' << PID << endl;
            c_principal.eliminar_proceso(ID_Procesador, PID);
        }

        else if (command == "enviar_procesos_cluster"       or command == "epc" ){ 
            int n;
            cin >> n;
            cout << '#' << command << ' ' << n << endl;
            espera.proceso_cluster(n, c_principal);
        }
    
        else if (command == "avanzar_tiempo"                or command == "at"  ){
            
            int seconds;
            cin >> seconds;
            cout << '#' << command << ' ' << seconds << endl;
            c_principal.avanzar_tiempo(seconds);

        }

        else if (command == "imprimir_prioridad"            or command == "ipri"){
            
            string priority_ID;
            cin >> priority_ID;
            cout << '#' << command << ' ' << priority_ID << endl;
            espera.procesos_prioridad(priority_ID);

        }

        else if (command == "imprimir_area_espera"          or command == "iae" ){
            cout << '#' << command << endl;
            espera.imprimir_area_espera();
          
        }

        else if (command == "imprimir_procesador"           or command == "ipro"){
            string ID_Procesador;
            cin >> ID_Procesador;
            cout << '#' << command << ' ' << ID_Procesador << endl;
            map <string, Procesador>::const_iterator null_iterator;
            c_principal.imprimir_procesador(ID_Procesador, null_iterator);
        }

        else if (command == "imprimir_procesadores_cluster" or command == "ipc" ){
            cout << '#' << command << endl;
            c_principal.imprimir_procesadores_cluster();
           
        }

        else if (command == "imprimir_estructura_cluster"   or command == "iec" ){
            cout << '#' << command << endl;
            c_principal.imprimir_estructura_cluster();
        }

        else if (command == "compactar_memoria_procesador"  or command == "cmp" ){
            string ID_Procesador;
            cin >> ID_Procesador;
            cout << '#' << command << ' ' << ID_Procesador << endl;
            c_principal.compactar_mem_proc(ID_Procesador);
        }

        else if (command == "compactar_memoria_cluster"     or command == "cmc" ){
            cout << '#' << command << endl;
            c_principal.compactar_memoria_cluster();
        }
        cin >> command;
    }
    
}