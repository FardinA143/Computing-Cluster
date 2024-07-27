#include "Procesador.hh"

using namespace std;

// Constructoras
Procesador::Procesador() {}

Procesador::Procesador(const string& procID, int memory) {
    ID = procID;
    mem.first = memory;
    mem.second = 0;
    free_space[memory].insert(0);
}

// Modificadoras
void Procesador::add_proceso(const Proceso& p) {
    int memory_needed = p.consultar_mem_req();
    auto it = free_space.lower_bound(memory_needed);
    if (it == free_space.end()) cout << "error: no cabe proceso" << endl;
    else {
        auto it_pos = it->second.begin();
        mem.second += memory_needed;
        
        int space = it->first - memory_needed;
        if (space > 0) free_space[space].insert(*it_pos + memory_needed);
        mem_proc.emplace(*it_pos, p);
        procesos_ID.emplace(p.consultar_PID(), *it_pos);

        it->second.erase(*it_pos);
        if (it->second.empty()) it = free_space.erase(it);
}}

void Procesador::del_proceso(map<int, Proceso>::iterator& it, int id_proceso) {
    if (id_proceso != -1) {
        auto it_aux = procesos_ID.find(id_proceso); // Este lado se llama desde baja_proceso_procesador
        if (it_aux == procesos_ID.end()) {
            cout << "error: no existe proceso" << endl;
            return;
        }

        it = mem_proc.find(it_aux->second);
        mem.second -= it->second.consultar_mem_req();
    }

    procesos_ID.erase(it->second.consultar_PID());

    if (procesos_ID.empty()) { // Si no quedan procesos, se resetea los mapas y indices
        free_space.clear();
        free_space[mem.first].insert(0);
    } 
    else { // En otro caso se sigue esto
        int index = it->first;
        int mempos = it->second.consultar_mem_req() + index;
        int old_ind = 0;
        int next_ind = mem.first;

        auto prev_it = it;
        if (it != mem_proc.begin()) {
            --prev_it;
            old_ind = prev_it->first + prev_it->second.consultar_mem_req();
            free_space[index - old_ind].erase(old_ind);

            if (free_space[index - old_ind].empty()) free_space.erase(index - old_ind);
            ++prev_it;
        } else {
            free_space[index].erase(0);
            if (free_space[index].empty()) free_space.erase(index);
        }

        auto next_it = it;
        ++next_it;
        if (next_it != mem_proc.end()) {
            next_ind = next_it->first;
            free_space[next_ind - mempos].erase(mempos);
            if (free_space[next_ind - mempos].empty()) free_space.erase(next_ind - mempos);
        } else {
            free_space[mem.first - mempos].erase(mempos);
            if (free_space[mem.first - mempos].empty()) free_space.erase(mem.first - mempos);
        }

        free_space[next_ind - old_ind].insert(old_ind);
    }

    it = mem_proc.erase(it); // Apunta al elemento siguiente al borrado
}
 
void Procesador::actualizar_tiempo(int seconds) {
    if (not procesos_ID.empty()) {
        auto it = mem_proc.begin();
        while (it != mem_proc.end()) {
            if (it->second.consultar_tiempo_finalizacion() <= seconds) del_proceso(it, -1);
        
            else {
                it->second.actualizar_tiempo(seconds);
                ++it;
            }}}}

void Procesador::compactar_memoria() {
    if (not procesos_ID.empty()) {
        free_space.clear();
        auto it = mem_proc.begin();
        int pos = 0;
        while (it != mem_proc.end()) {
            if (it->first != pos) {
                mem_proc.insert(it, make_pair(pos, it->second));
                
                procesos_ID[it->second.consultar_PID()] = pos;
                pos += it->second.consultar_mem_req();
                it = mem_proc.erase(it);
            }
            else {
                pos += it->second.consultar_mem_req();
                ++it;
            } 
        }
        free_space[mem.first - pos].insert(pos);
    }
}

// Consultoras
int Procesador::get_memoria_disponible() const {
    return mem.first - mem.second;
}

bool Procesador::existe_proceso(int id_proceso) const {
    return procesos_ID.count(id_proceso) != 0;
}

const string& Procesador::get_ID() const {
    return ID;
} 
bool Procesador::en_marcha() const {
    return not procesos_ID.empty();
}


bool Procesador::get_free_space(int size, int& pos) const{
    auto it = free_space.lower_bound(size);
    if (it == free_space.end()) return false;
    pos = it->first;
    return true;
} 

// Lectura y escritura

void Procesador::imprimir_procesador() const {
    for (const auto& par : mem_proc) {
        cout << par.first << ' ';
        par.second.imprimir_proceso();
    }
}