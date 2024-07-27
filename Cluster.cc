#include "Cluster.hh"

using namespace std;

//CONSTRUCTOR
Cluster::Cluster() {}

//FUNCIONES PRIVADAS


void Cluster::leer_cluster(BinTree<string>& arbol_procesadores, map <string, Procesador>& procesadores){
    BinTree<string> arbol_left, arbol_right;
    string inp;
    cin >> inp;
    
    if (inp != "*") {
        int mem;
        cin >> mem;
        Procesador proc_aux(inp, mem);
        procesadores.insert(make_pair(inp, proc_aux));
        leer_cluster(arbol_left, procesadores);
        leer_cluster(arbol_right, procesadores);
        arbol_procesadores = BinTree<string>(inp, arbol_left, arbol_right);
    }
    else arbol_procesadores = BinTree<string>();
} 
bool Cluster::juntar_arboles(const string& procID, Cluster& c, BinTree<string>& arbol) {
    if (arbol.empty()) return false;
    BinTree<string> left = arbol.left();
    BinTree<string> right = arbol.right();

    if (arbol.value() == procID) { // lleva el arbol a la rama necesaria
        if (left.empty() and right.empty()) {
            arbol = c.get_cpu_tree();
            return true;
        }
        else {
            cout << "error: procesador con auxiliares" << endl;
            return false;

        }
    }
    else {
        bool next = juntar_arboles(procID, c, left);
        if (not next) next = juntar_arboles(procID, c, right);
        arbol = BinTree<string>(arbol.value(), left, right);
        return next;
    } // posiblemente lo podría mejorar usando referencia en vez de copias
}

void Cluster::search_valid_proc(map<string, Procesador>::iterator& it, const BinTree<string>& avail_proc, int ID, int req_mem){
    queue<BinTree<string>> q;
    q.push(avail_proc);
    int space = -1; 
    while (not q.empty()) {
        BinTree<string> aux (q.front());
        auto auxit = procesadores_mapa.find(aux.value());
        int space_left;
        if (not auxit->second.existe_proceso(ID) and auxit->second.get_free_space(req_mem, space_left)) {
            if (it == procesadores_mapa.end() or space_left < space) {
                it = auxit;
                space = space_left;
            }
            else if (space_left == space and auxit->second.get_memoria_disponible() > it->second.get_memoria_disponible()) it = auxit;
        }
        if (not aux.left().empty()) q.push(aux.left());
        if (not aux.right().empty()) q.push(aux.right());
        q.pop();
    } 
}

map<string, Procesador> Cluster::get_cpu_map() const {
    return procesadores_mapa;
}

BinTree<string> Cluster::get_cpu_tree() const {
    return procesadores_arbol;
}

void Cluster::print_cluster(const BinTree<string>& arbol_procesadores) {
    if (not arbol_procesadores.empty()) {
        cout << '(';
        cout << arbol_procesadores.value();
        
        print_cluster(arbol_procesadores.left());
        print_cluster(arbol_procesadores.right());

        cout << ')';
    }
    else cout << ' ';

}


// FUNCIONES PUBLICAS
// Modificadoras
void Cluster::add_proc_cpu(const Proceso& proceso, const string& ID) {

    auto it = procesadores_mapa.find(ID);
    if (it == procesadores_mapa.end()) cout << "error: no existe procesador" << endl;
    else {
        if (it->second.existe_proceso(proceso.consultar_PID())) cout << "error: ya existe proceso" << endl;
        else it->second.add_proceso(proceso);
    }
} 

bool Cluster::add_proc_ep(const Proceso& p) {
    auto it = procesadores_mapa.end();
    search_valid_proc(it, procesadores_arbol, p.consultar_PID(), p.consultar_mem_req());
    if (it == procesadores_mapa.end()) return false;
    it->second.add_proceso(p);
    return true;
}

void Cluster::avanzar_tiempo(int segundos) {
    map <string, Procesador>::iterator it;
    for (it = procesadores_mapa.begin(); it != procesadores_mapa.end(); ++it) {
        it->second.actualizar_tiempo(segundos);
    }
} 

void Cluster::eliminar_proceso(const string& cpuID, int PID) {

    auto it = procesadores_mapa.find(cpuID);
    if (it == procesadores_mapa.end()) cout << "error: no existe procesador" << endl;
    else {
        map <int, Proceso>::iterator null_iterator;
        it->second.del_proceso(null_iterator, PID);
} 
}

void Cluster::modificar_cluster(const string& procID, Cluster& c) {
    auto it = procesadores_mapa.find(procID);
    if (it == procesadores_mapa.end()) cout << "error: no existe procesador" << endl;
    else {
        if (it->second.en_marcha()) cout << "error: procesador con procesos" << endl;
        else if (juntar_arboles(procID, c, procesadores_arbol)) {
            procesadores_mapa.erase(it);
            auto rama = c.get_cpu_map();
            procesadores_mapa.insert(rama.begin(), rama.end());            
        }
            
        }
    }

void Cluster::compactar_memoria_cluster() {
    auto it = procesadores_mapa.begin();
    while (it != procesadores_mapa.end()) {
         if (it->second.en_marcha()) it->second.compactar_memoria();
         ++it;
    }
}

void Cluster::compactar_mem_proc(const string& ID) {
    auto it = procesadores_mapa.find(ID);
    if (it == procesadores_mapa.end()) cout << "error: no existe procesador" << endl;
    else it->second.compactar_memoria();
}
    
void Cluster::leer_estructura_cluster() {
    procesadores_mapa.clear();
    leer_cluster(procesadores_arbol, procesadores_mapa);
} 

// Lectura y escritura
void Cluster::imprimir_estructura_cluster() const {
    print_cluster(procesadores_arbol);
    cout << endl;  
} 

void Cluster::imprimir_procesadores_cluster() const{
    for (auto it = procesadores_mapa.begin(); it != procesadores_mapa.end(); ++it) {
        cout << it->first << endl;
        imprimir_procesador("#", it);
} 
}

void Cluster::imprimir_procesador(const string& procID, map<string, Procesador>::const_iterator& it) const{
    if (procID != "#") {
        it = procesadores_mapa.find(procID);
        if (it == procesadores_mapa.end()) cout << "error: no existe procesador" << endl;
        else if (it->second.en_marcha())  it->second.imprimir_procesador();
    }
    else if (it->second.en_marcha()) it->second.imprimir_procesador();

}