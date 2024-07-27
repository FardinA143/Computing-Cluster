#include "Prioridad.hh"
using namespace std;


// Constructoras
Prioridad::Prioridad() {
    send_data.first = send_data.second = 0;
}
// Modificadoras
void Prioridad::add_proceso(const Proceso& p) {
    proc_age.emplace_back(p.consultar_PID());
    procesos.emplace(p.consultar_PID(), p);

} 

void Prioridad::send_proceso(int &num, Cluster &c) {
    if (not proc_age.empty()) {
        auto it = proc_age.begin();
        int max_size = proc_age.size();
        int index = 0;
        while(not (num == 0 or index == max_size)) {
            if (c.add_proc_ep(procesos.at(*it))) {
                ++send_data.first;
                procesos.erase(*it);
                it = proc_age.erase(it);
                --num;
            }
            else {
                proc_age.emplace_back(*it);
                it = proc_age.erase(it); 
                ++send_data.second;
            }
            ++index;
        }

    }
} 
// Consultoras
bool Prioridad::empty() const {
    return (procesos.size() == 0);
} 



bool Prioridad::existe_proceso(int ID) const {
    return (not procesos.empty() and procesos.count(ID) != 0);

} 

// Lectura y escritura
void Prioridad::print_procesos() const {
    for (int id : proc_age) {
        procesos.at(id).imprimir_proceso();
    }
}

void Prioridad::enviados_rechazados() const{
    cout << send_data.first << " " << send_data.second << endl;
} 



