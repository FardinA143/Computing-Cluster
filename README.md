# Computing Cluster Process Management Simulation

## About
This project consists of simulating a process management system of a computing cluster, as part of the work of the Programming II subject of the Polytechnic University of Catalonia. The wiki and the commands/functionalities are written in Spanish. The project is written in C++.
The system is composed of a master node and worker nodes, which can have subnodes. There's a list of processes to be executed, which are defined by memory usage, time and priority. These are distributed afterwards to all the nodes, taking into account the best way to distribute them.

## How to compile
To compile the project, you need to have the following dependencies installed:
- C++ compiler (g++)
- Make

### Instructions
1. Clone the repository
 ```bash
    $~ git clone https://github.com/FardinA143/Cluster-Compute.git
 ```

2. Navigate to the project directory
 ```bash
    $~ cd Cluster-Compute
 ```

 3. Compile the project
 ```bash
    $~ make
 ```
 4. Run the project
 ```bash
    $~ ./program.exe
 ```

## How to use
When you first execute the program, it'll ask for how the cpu's are distributed in the cluster. To simplify the process, this program it will only take a binary tree as input in a DFS order. Each entry is composed by the name of the processor and it's available memory. An example input is shown below:
```
proc1 10 proc11 100 proc111 500 * * proc112 500 * * proc12 100 proc121
500 * * proc122 500 * *
```
This input will create a binary tree with the following structure:
```
             proc1
          /         \
    proc11          proc12
    /    \          /     \
proc111 proc112  proc121 proc122
```

The asterisks represent an empty leaf node. Inputting two asterisks will mean that the node is a leaf node and has no children, so it will go back to the parent node, according to a DFS order. 

Afterward, the program will ask for the list of priorities. This will help classify the processes according to their priority. The priorities will be ordered alphanumerically, so the first priority will be the one with the lowest value. An example input is shown below:
```
10
11
10C
12A
```
So, a process with priority 10 will have a higher priority than a process with priority 11, and so on.

After this, the program will wait commands. The list of commands is shown below:
| Command |Alias | Description | Usage |
|---------|------|-------------| ------ |
| configurar_cluster | cc | Configures the cluster with a new binary tree | `cc proc1 10 proc11 100 * * proc12 100 * *`` |
| modificar_cluster | mc | Modifies the cluster by replacing a leaf node with another tree| `mc proc11 proc111 500 * * proc112 500 * *`` |
| alta_prioridad | ap | Adds a new priority to the list of priorities | `ap 10` |
| baja_prioridad | bp | Removes a priority from the list of priorities | `bp 10` |
| alta_proceso_espera | ape | Adds a new process to the waiting list, with the following format: priority process_ID memory time ` | `ape 10C 10 98 100` |
| alta_proceso_procesador | Reads a process and tries to allocate it in the specified processor. Format: procID process_ID memory time | `app proc11 10 98 100` |
| baja_proceso_procesador | bpp | Removes a process from the specified processor. Format: procID process_ID | `bpp proc11 10` |
| enviar_procesos_cluster | epc | Sends n possible processes to the cluster, following their priority and age | `epc 10` |
| avanzar_tiempo | at | Advances the time of the processes in the cluster (simulating jobs getting done) | `at 10` |
| imprimir_prioridad | ipri | Reads a priority and prints the processes in the waiting list with that priority | `ipri 10` |
| imprimir_area_espera | iae | Prints the waiting list | `iae` |
| imprimir_procesador | ipro | Prints the processes in the specified processor | `ip proc11` |
| imprimir_procesadores_cluster | ipc | Prints the nodes in the cluster and for each print the processes, if there is any. | `ipc` |
| imprimir_estructura_cluster | iec | Prints the structure of the cluster | `iec` |
| compactar_memoria_procesador | cmp | Compacts the memory of the specified, to have as much free contiguous memory as possible | `cmp proc11` |
| compactar_memoria_cluster | cmc | Compacts the memory of all the processors in the cluster | `cmc` |
| fin | - | Ends the program | `fin` |


## Wiki
You can find a wiki with the classes and methods of the project [here](wiki). 
> [!NOTE]
>  As mentioned previously, the wiki is written in Spanish.

### Contact
You can contact me via email [here](mailto:fardin@tekhmos.com) or via Issues in this repository.

