#include "enrutador.h"

Enrutador::Enrutador(){

}

void Enrutador::agregar_enlace(std::string destino, int costo) {
    if(enlaces.find(destino) == enlaces.end()) // Si el enlace no existe
        enlaces.insert(std::pair<std::string, int>(destino, costo));
    else if (enlaces[destino] == -1)
        enlaces[destino] = costo;
}

void Enrutador::modificar_enlace(std::string destino, int costo) {
    if(enlaces.find(destino) != enlaces.end())
        enlaces[destino] = costo;
}

void Enrutador::eliminar_enlace(std::string destino) {
    if(enlaces.find(destino) != enlaces.end())
        enlaces.erase(destino);
}

bool Enrutador::is_linked(std::string destino) {
    if(enlaces[destino] != -1) return true;

    else return false;
}

bool Enrutador::is_linked() {
        for(iterador_enlaces = enlaces.begin(); iterador_enlaces != enlaces.end(); iterador_enlaces++)
            if(iterador_enlaces->second != -1 && iterador_enlaces->second != 0)
                return true;

        return false;
}

void Enrutador::ver_enlances(bool grupo) {
    if(grupo){
        for(iterador_enlaces = enlaces.begin(); iterador_enlaces != enlaces.end(); iterador_enlaces++)

            if(iterador_enlaces->second != -1)
                std::cout<<iterador_enlaces->second<<'\t';
            else
                std::cout<<'-'<<'\t';
        std::cout<<std::endl;
    }
    else{
        for(iterador_enlaces = enlaces.begin(); iterador_enlaces != enlaces.end(); iterador_enlaces++)

            if(iterador_enlaces->second != 0){

                if(iterador_enlaces->second != -1)
                    std::cout<<iterador_enlaces->first<<": "<<iterador_enlaces->second<<'\t';
                else
                    std::cout<<iterador_enlaces->first<<": "<<'-'<<'\t';
            }
        std::cout<<std::endl;
    }
}
