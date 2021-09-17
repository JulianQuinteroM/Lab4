#ifndef ENRUTADOR_H
#define ENRUTADOR_H
#include <iostream>
#include <string>
#include <map>

class Enrutador {
private: // variables privadas

public: // varibles publicas
    std::map<std::string, int> enlaces; // Contiene todos los enlaces que tiene el nodo. la cadena es el nodo al que está vinculado y el int representa el costo de dicho enlace
    std::map<std::string, int>::iterator iterador_enlaces;

private: // metodos privados

public: // metodos publicos
    Enrutador();
    void agregar_enlace(std::string destino, int costo = -1);
    void modificar_enlace(std::string destino, int costo);
    void eliminar_enlace(std::string destino);
    void unlink(std::string destino);
    bool is_linked(std::string destino); //comprueba si existe un enlace específico
    bool is_linked(); // comprueba si el nodo está vinculado
    void ver_enlances(bool grupo); // El parámetro de grupo determina si el enrutador se muestra o no
};

#endif // ROUTER_H
