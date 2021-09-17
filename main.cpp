#include "red.h"
#include "funciones.h"
#include <limits>
#include <windows.h>

int main()
{
    //variable declaracion

    Red red_local;

    bool loop = true, sub_loop, gen = false;
    short selec;
    int costo;

    std::string name1, name2, aux;

    //Menu inicio

    while(loop){

        if(gen == false){ // gen determina si hay una red generada válida o no

            selec = menu_creacion_red();

            switch (selec){
            case 1:{ //Importar red

                std::cout<<"Ingrese el nombre del archivo (incluyendo la extension) o -1 para cancelar: ";
                std::cin>>name1;

                if(name1 != "-1"){
                    system("CLS");
                    red_local.importar_red(name1);

                    if(red_local.is_empty() == false)
                        gen = true;
                }
                break;
            }

            case 2:{ //Crear red manualmente

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Para crear una red debes agregar 2 enrutadores y un enlace entre ellos. Podras modificar la red despues de crearla."<<std::endl;
                        std::cout<<"Ingrese el primer enrutador (-1 para cancelar): ";
                        std::cin>>name1;

                        if(name1 == "-1") sub_loop = false;

                        else break;
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el segundo enrutador (-1 para cancelar): ";
                        std::cin>>name2;

                        if(name2 == "-1") sub_loop = false;

                        else break;
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los enrutadores deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop){

                    red_local.agregar_enrutador(name1);
                    red_local.agregar_enrutador(name2);

                    costo = obtener_costo(false);

                    red_local.modificar_enlace(name1, name2, costo);

                    gen = true;
                    std::cout<<"*| Red creada correctamente |*"<<std::endl;
                    Sleep(1000);
                }
                break;
            }
            case 3:{ //Generar red
                red_local.generar_red();
                gen = true;
                std::cout<<"*| Red generada correctamente |*"<<std::endl;
                Sleep(1000);
                break;
            }
            case 4:{ //Salir
                loop = false;
                break;
            }
            }
        }

        red_local.verificar_integ();               // comprueba la integridad de la red y de cada enrutador
        if(red_local.is_empty()) gen = false; // Elimina los enrutadores que se quedan solos y lleva al usuario al menú de creación de red cuando la red ya no es válida
        else if(gen == true){ // si hay una red existente
            system("CLS");

            red_local.mostrar_detalles();
            selec = menu_edicion_red(red_local);

            switch (selec){
            case 1:{ //Agregar enrutador

                sub_loop = true;
                while(sub_loop){

                    std::cout<<"Ingrese el nombre del nuevo enrutador (-1 para cancelar): ";
                    std::cin>>name1;

                    if(red_local.is_present(name1) == false && name1 != "-1") break;

                    else if (name1 == "-1") sub_loop = false;

                    else {
                        system("CLS");
                        std::cout<<"El enrutador ya existe, por favor elige un nombre distinto"<<std::endl;
                    }
                }

                if(sub_loop == true){

                    red_local.agregar_enrutador(name1);

                    while(true){
                        std::cout<<"El enrutador debe tener minimo un enlace. Ingrese el nombre del enrutador con que desea enlazarlo: ";
                        std::cin>>name2;

                        if(red_local.is_present(name2) == true && name2 != name1) break;

                        else if ( name2 == name1){
                            system("CLS");
                            std::cout<<"Los enrutador deben ser distintos"<<std::endl;
                        }

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    costo = obtener_costo(false);

                    red_local.agregar_enlace(name1, name2, costo);
                }
                break;
            }
            case 2:{ //Eliminar enrutador

                sub_loop = true;
                while(sub_loop){
                    std::cout<<"Ingrese el nombre del enrutador que desea eliminar (-1 para cancelar): ";
                    std::cin>>name1;

                    if(red_local.is_present(name1) == true) break;

                    else if (name1 == "-1") sub_loop = false;

                    else {
                        system("CLS");
                        std::cout<<"El enrutador no existe"<<std::endl;
                    }
                }

                while(sub_loop){ //confirmacion

                    std::cout<<"Esta a punto de borrar el enrutador "<<name1<<" y todos sus enlaces (Esto puede afectar la existencia de otros enrutadores). Desea continuar? (Y/N): "; std::cin>>name2;

                    if(name2 == "Y" || name2 == "y"){

                        red_local.eliminar_enrutador(name1);

                        std::cout<<"Enrutador borrado correctamente";
                        Sleep(1000);

                        break;
                    }

                    else if(name2 == "N" || name2 == "n") break;

                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }

                break;
            }
            case 3:{ //Visualizar enrutador

                sub_loop = true;
                while(sub_loop){
                    std::cout<<"Ingrese el nombre del enrutador que desea visualizar (-1 para cancelar): ";
                    std::cin>>name1;

                    if(red_local.is_present(name1) == true) break;

                    else if (name1 == "-1") sub_loop = false;

                    else {
                        system("CLS");
                        std::cout<<"El enrutador no existe"<<std::endl;
                    }
                }
                system("CLS");

                if(sub_loop){
                    red_local.mostrar_enrutador(name1);

                    std::cout<<"\nPresiona ESC para volver"<<std::endl;

                    while(true)
                        if (GetAsyncKeyState(VK_ESCAPE))
                            break;
                }
                break;
            }
            case 4:{ //Agregar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(red_local.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(red_local.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los enrutadores deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop == true){

                    costo = obtener_costo(false);

                   red_local.agregar_enlace(name1, name2, costo);
                }
                break;
            }
            case 5:{ //Eliminar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(red_local.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(red_local.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2 && red_local.estan_enlazados(name1, name2)) break;

                    else if(!red_local.estan_enlazados(name1, name2)){
                        system("CLS");
                        std::cout<<"Los routers no estan enlazados"<<std::endl;
                    }

                    else{
                        system("CLS");
                        std::cout<<"Los enrutadores deben ser distintos"<<std::endl;
                    }
                }

                while(sub_loop){ //confirmacion

                    std::cout<<"Esta a punto de desenlazar "<<name1<<" y "<<name2<<" (Esto puede afectar su existencia en la red). Desea continuar? (Y/N): "; std::cin>>aux;

                    if(aux == "Y" || aux == "y"){

                        red_local.modificar_enlace(name1, name2, -1);

                        std::cout<<"Enlace borrado correctamente";
                        Sleep(1000);

                        break;
                    }
                    else if(aux == "N" || aux == "n") break;
                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }
                break;
            }
            case 6:{ //Editar enlace

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(red_local.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el enrutador destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(red_local.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los enrutadores deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop) {

                    costo = obtener_costo(true);

                    if(costo == -1){
                        while(sub_loop){

                            std::cout<<"Esta a punto de desenlazar "<<name1<<" y "<<name2<<" (Esto puede afectar su existencia en la red). Desea continuar? (Y/N): "; std::cin>>aux;

                            if(aux == "Y" || aux == "y"){

                                red_local.modificar_enlace(name1, name2, costo);

                                std::cout<<"Enlace modificado correctamente";
                                Sleep(1000);

                                break;
                            }

                            else if(aux == "N" || aux == "n") break;

                            else {
                                system("CLS");
                                std::cout<<"Opcion no valida"<<std::endl;
                            }
                        }
                    }
                    else{
                        red_local.modificar_enlace(name1, name2, costo);

                        std::cout<<"Enlace modificado correctamente";
                        Sleep(1000);
                    }
                }

                break;
            }
            case 7:{ //Exportar red

                std::cout<<"Ingrese el nombre del archivo (incluyendo la extension) o -1 para cancelar: ";
                std::cin>>name1;

                if(name1 != "-1"){
                    system("CLS");

                    if(!file_existente(name1))
                        crear_file(name1);

                    if(file_vacio(name1) == true) {
                        red_local.exportar_red(name1);
                    }

                    else
                        while(true){

                            std::cout<<"El archivo "<<name1<<" contiene datos y estos seran sobreescritos. Desea continuar? (Y/N): "; std::cin>>name2;

                            if(name2 == "Y" || name2 == "y"){

                                red_local.exportar_red(name1);

                                break;
                            }

                            else if(name2 == "N" || name2 == "n") break;

                            else {
                                system("CLS");
                                std::cout<<"Opcion no valida"<<std::endl;
                            }
                        }
                }
                break;
            }
            case 8:{ //Ver tabla de enrutamiento

                red_local.mostrar_todo();

                std::cout<<"Presiona ESC para volver"<<std::endl;

                while(true)
                    if (GetAsyncKeyState(VK_ESCAPE))
                        break;

                break;
            }
            case 9:{ //Encontrar camino mas eficiente entre 2 routers

                sub_loop = true;
                while(sub_loop){
                    while(sub_loop){
                        std::cout<<"Ingrese el router origen (-1 para cancelar): ";
                        std::cin>>name1;

                        if(red_local.is_present(name1) == true) break;

                        else if(name1 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    while(sub_loop){
                        std::cout<<"Ingrese el router destino(-1 para cancelar): ";
                        std::cin>>name2;

                        if(red_local.is_present(name2) == true) break;

                        else if(name2 == "-1") sub_loop = false;

                        else {
                            system("CLS");
                            std::cout<<"El enrutador no existe"<<std::endl;
                        }
                    }

                    if(name1 != name2) break;

                    else{
                        system("CLS");
                        std::cout<<"Los enrutadores deben ser distintos"<<std::endl;
                    }
                }

                if(sub_loop == true){

                    system("CLS");

                    red_local.camino_corto(name1, name2);

                    std::cout<<"\n\n"<<"Presiona ESC para volver"<<std::endl;

                    while(true)
                        if (GetAsyncKeyState(VK_ESCAPE))
                            break;
                }
                break;
            }
            case 10:{ //Crear nueva red
                while(true){

                    std::cout<<"Esta a punto de borrar toda la red actual. Desea continuar? (Y/N): "; std::cin>>name1;

                    if(name1 == "Y" || name1 == "y"){

                        red_local.red_vacia();
                        gen = false;

                        std::cout<<"Red borrada correctamente";
                        Sleep(1000);

                        break;
                    }

                    else if(name1 == "N" || name1 == "n") break;

                    else {
                        system("CLS");
                        std::cout<<"Opcion no valida"<<std::endl;
                    }
                }
                break;
            }
            case 11:{ //Salir
                loop = false;
                break;
            }
            }
        }
    }
    return 0;
}
