#include "funciones.h"

bool is_number(std::string s) {

    for(unsigned long long k = 0; k<s.length(); k++){

        if(isdigit(s[k]) == false) return false;

    }
    return true;
}

int obtener_costo(bool puede_ser_negativo) {

    int costo;

    if(puede_ser_negativo == false){
        while(true){
            std::cout<<"Ingresa el costo del enlace (0 - 100): ";
            std::cin>>costo;

            while(std::cin.fail()) { //validacion de entrada
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                system("CLS");
                std::cout << "Opcion no valida"<<std::endl;
                std::cout<<"Ingresa el costo del enlace (0 - 100): "; std::cin>>costo;
            }

            if(costo>0 && costo <=100) break;

            else {
                system("CLS");
                std::cout<<"Costo fuera de rango"<<std::endl;
            }
        }
    }

    else{
        while(true){
            std::cout<<"Ingresa el costo del enlace (0 - 100, o -1 para desenlazar): ";
            std::cin>>costo;

            while(std::cin.fail()) { //validacion de entrada
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                system("CLS");
                std::cout << "Opcion no valida"<<std::endl;
                std::cout<<"Ingresa el costo del enlace (0 - 100, o -1 para desenlazar): "; std::cin>>costo;
            }

            if(costo == -1) break;

            else if(costo>0 && costo <=100) break;

            else {
                system("CLS");
                std::cout<<"Costo fuera de rango"<<std::endl;
            }
        }
    }
    return costo;
}

short menu_creacion_red() {

    std::string menu =
            "|  Menu de creacion de red  |\n"
            "|                           |\n"
            "| 1. Importar red           |\n"
            "| 2. Crear red manualmente  |\n"
            "| 3. Generar red random     |\n"
            "|    (solo hasta 7)         |\n"
            "| 4. Salir                  |";

    short selec;

    system("CLS");

    std::cout<<char(218);
    for(int k = 0; k<27; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;
    std::cout<<menu<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<27; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;

    std::cout<<"-> ";std::cin>>selec;

    while(std::cin.fail()) { //validacion de entrada
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        system("CLS");

        std::cout<<char(218);
        for(int k = 0; k<27; k++) std::cout<<char(196);
        std::cout<<char(191)<<std::endl;
        std::cout<<menu<<std::endl;
        std::cout<<char(192);
        for(int k = 0; k<27; k++) std::cout<<char(196);
        std::cout<<char(217)<<std::endl;

        std::cout << "   Opcion no valida"<<std::endl;
        std::cout<<"-> "; std::cin>>selec;
    }
    system("CLS");

    return selec;
}

short menu_edicion_red(Red& N) {
    std:: string menu =
            "|     Menu de edicion de red    |\n"
            "|                               |\n"
            "| 1. Agregar router             |\n"
            "| 2. Eliminar router            |\n"
            "| 3. Visualizar router          |\n"
            "| 4. Agregar enlace             |\n"
            "| 5. Eliminar enlace            |\n"
            "| 6. Editar enlace              |\n"
            "| 7. Exportar red               |\n"
            "| 8. Ver tabla de enrutamiento  |\n"
            "| 9. Encontrar camino corto     |\n"
            "| 10. Crear nueva red           |\n"
            "| 11. Salir                     |";

    short selec;

    std::cout<<char(218);
    for(int k = 0; k<31; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;
    std::cout<<menu<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<31; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;

    std::cout<<"-> ";std::cin>>selec;

    while(std::cin.fail()) { //validacion de entrada
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        system("CLS");

        N.mostrar_detalles();
        std::cout<<char(218);
        for(int k = 0; k<31; k++) std::cout<<char(196);
        std::cout<<char(191)<<std::endl;
        std::cout<<menu<<std::endl;
        std::cout<<char(192);
        for(int k = 0; k<31; k++) std::cout<<char(196);
        std::cout<<char(217)<<std::endl;

        std::cout << "   Opcion no valida"<<std::endl;
        std::cout<<"-> "; std::cin>>selec;
    }
    system("CLS");

    return selec;
}

bool file_vacio(std::string file_name){

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

    if(file.is_open()){

        std::string temp;

        if (file >> temp){

            file.close();
            return false;

        }
         else return true;
     }
     else return false;
}

bool file_existente(std::string file_name) {

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

    if(file.is_open()){
        file.close();
        return true;
    }
    else return false;
}

void crear_file(std::string file_name){

    std::fstream file (file_name, std:: fstream::out | std::fstream::binary);

    if(file.is_open()){
        file.close();
    }
}
