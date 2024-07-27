#include "Proceso.hh"

using namespace std;

// Constructoras
Proceso::Proceso(){}

// Modificadoras
void Proceso::actualizar_tiempo(int seconds) {
    tiempo -= seconds;
}

// Consultoras
int Proceso::consultar_PID() const{
    return PID;
}

int Proceso::consultar_mem_req() const{
    return memoria;
}

int Proceso::consultar_tiempo_finalizacion() const{
    return tiempo;
}


// Lectura y escritura
void Proceso::leer_proceso() {
    cin >> PID >> memoria >> tiempo;
}

void Proceso::imprimir_proceso() const{
    cout << PID << ' ' << memoria << ' ' << tiempo << endl;
}