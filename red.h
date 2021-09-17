#ifndef RED_H
#define RED_H
#include "enrutador.h"
//#include "funciones.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <limits.h>
#include <stdio.h>

class Red {
private: // variables privadas
std::map<std::string, Enrutador> tabla_enrutador; // Contiene todos los enlaces. La cadena representa el nombre del nodo y el enrutador contiene los enlaces de dicho nodo.
std::map<std::string, Enrutador>::iterator iterador_table_enrutador;

int numero_enrutadores = 0;
std::map<int, std::string> enrutadores; // Contiene todos los nodos, pero como clave int. Hace que algunas tareas como el algoritmo de dijkstra sean mucho más fáciles

public: //variables publicas

private: // Métodos privados: todos estos son utilizados por el algoritmo de distancia minima
    int Distancia_min(int *dist, bool *sptSet);
    void printcamino(int *parent, int j);
    void printSolucion(int *dist, int *parent, int origen, int destino);

    void llenar_grafico(int **grafico);
    void eliminar_grafico(int **grafico);

    int obtener_codigo_enrutador(std::string enrutador);

public: // metodos publicos
    Red();

    bool is_empty();

    bool is_present(std::string r); // Comprueba si existe un enrutador o no
    bool is_present(std::string r1, std::string r2); // Comprueba si existe o no un camino entre r1 y r2

    void agregar_enrutador(std::string name);
    void eliminar_enrutador(std::string name);

    void mostrar_enrutador(std::string name);
    void mostrar_todo();
    void mostrar_detalles();

    void camino_corto(std::string r1, std::string r2);

    void agregar_enlace(std::string r1, std::string r2, int costo);
    void eliminar_enlace(std::string r1, std::string r2);
    void modificar_enlace(std::string r1, std::string r2, int costo);
    bool estan_enlazados(std::string r1, std::string r2);

    void generar_red();

    void importar_red(std::string file_name);
    void exportar_red(std::string file_name);

    void red_vacia();

    void verificar_integ();
};

#endif // NETWORK_H
