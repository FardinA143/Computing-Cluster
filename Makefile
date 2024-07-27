OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cluster.o Espera_procesos.o Prioridad.o Proceso.o Procesador.o
	g++ -o program.exe *.o
Cluster.o: Procesador.hh Proceso.hh
	g++ -c Cluster.cc $(OPCIONS) 
Espera_procesos.o: Prioridad.hh Proceso.hh Cluster.hh
	g++ -c Espera_procesos.cc $(OPCIONS) 
Prioridad.o: Proceso.hh Cluster.hh
	g++ -c Prioridad.cc $(OPCIONS)
Proceso.o: 
	g++ -c Proceso.cc $(OPCIONS)
Procesador.o: Proceso.hh 
	g++ -c Procesador.cc $(OPCIONS)
program.o: program.cc Procesador.hh Proceso.hh Prioridad.hh Cluster.hh Espera_procesos.hh
	g++ -c program.cc $(OPCIONS) 


clean:
	rm *.o *.exe *.tar

practica.tar:
	tar -cvf practica.tar *.cc *.hh Makefile html.zip

cmp:
	./program.exe < sample.inp > out.txt
	kompare sample.cor out.txt
 
