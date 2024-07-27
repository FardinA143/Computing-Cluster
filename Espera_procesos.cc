#include "Espera_procesos.hh"
using namespace std;
// Constructoras
Espera_procesos::Espera_procesos() {}

// Modificadoras
void Espera_procesos::add_prioridad(const string& priority_ID) {
    auto it = prioridades.find(priority_ID);
    if (it != prioridades.end()) cout << "error: ya existe prioridad" << endl;
    else {
        Prioridad p;
        prioridades.emplace(priority_ID, p);
    }
} 

void Espera_procesos::add_proceso(const Proceso& p, const string& priority_ID) {
    auto it = prioridades.find(priority_ID);
    if (it == prioridades.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (it->second.existe_proceso(p.consultar_PID())) cout << "error: ya existe proceso" << endl;
        else it->second.add_proceso(p);
            
    }
}

void Espera_procesos::del_prioridad(const string& priority_ID) {
    auto it = prioridades.find(priority_ID);
    if (it == prioridades.end()) cout << "error: no existe prioridad" << endl;
    else if (not it->second.empty()) cout << "error: prioridad con procesos" << endl;
    else prioridades.erase(it);
} 


void Espera_procesos::proceso_cluster(int num, Cluster& c) {
    auto it = prioridades.begin();
    while (num > 0 and it != prioridades.end()) {
        it->second.send_proceso(num, c);
        ++it;
    }
}

// Lectura y escritura
void Espera_procesos::leer_id_prioridades() {
    int N;
    cin >> N;
    string priority_ID; 
    for (int i = 0; i < N; ++i) {
        cin >> priority_ID;
        Prioridad p;
        prioridades.emplace(priority_ID, p);
    }
} 

void Espera_procesos::imprimir_area_espera() const {
    for (const auto& par : prioridades) {
        cout << par.first << endl;
        par.second.print_procesos();
        par.second.enviados_rechazados();
    }
} 

void Espera_procesos::procesos_prioridad(const string& priority_ID) const {
    const auto& it = prioridades.find(priority_ID);
    if (it == prioridades.end()) cout << "error: no existe prioridad" << endl;
    else {
        it->second.print_procesos();
        it->second.enviados_rechazados();
    }
} 

