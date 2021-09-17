#include "red.h"

int Red::Distancia_min(int *dist, bool *sptSet){
    int min = INT_MAX, min_index;

    for (int v = 0; v < numero_enrutadores; v++)
        if (sptSet[v] == false && dist[v] <= min && dist[v] != -1)
            min = dist[v], min_index = v;

    return min_index;
}

void Red::printcamino(int *parent, int j) {
      //if (parent[j] == - 1 || j == 0)
      if (parent[j] == - 1)
        return;

    printcamino(parent, parent[j]);

    std::cout<<enrutadores[j]<<' ';
}

void Red::printSolucion(int *dist,  int *parent, int origen, int destino){

    if(dist[destino] < INT_MAX && dist[destino] > 0){

        printf("Conexion\tCosto\tCamino");

        std::cout<<'\n'<<enrutadores[origen]<<" -> "<<enrutadores[destino]<<"\t\t"<<dist[destino]<<"\t"<<enrutadores[origen]<<' ';

        printcamino(parent, destino);
    }
    else std::cout<<"No existe ningun camino entre "<<enrutadores[origen]<<" y "<<enrutadores[destino]<<std::endl;
}

void Red::llenar_grafico(int **grafico){

    std::string key1, key2;

    for(int i = 0; i < numero_enrutadores; i++){

        key1 = enrutadores[i];

        for(int j = 0; j < numero_enrutadores; j++){

            key2 = enrutadores[j];

            grafico[i][j] = tabla_enrutador[key1].enlaces[key2];

        }
    }
}

void Red::eliminar_grafico(int **grafico){

    for(int i = 0; i < numero_enrutadores; ++i) {
        delete[] grafico[i];
    }
    delete[] grafico;
}

Red::Red(){

}

bool Red::is_empty(){
    if(tabla_enrutador.empty()) return true;
    else return false;
}

bool Red::is_present(std::string r){
    if(tabla_enrutador.find(r) != tabla_enrutador.end()) return true;
    else return false;
}

bool Red::is_present(std::string r1, std::string r2){

    if(tabla_enrutador.find(r1) != tabla_enrutador.end()){

        if(tabla_enrutador.find(r2) != tabla_enrutador.end()){

            if(tabla_enrutador[r1].is_linked(r2) && tabla_enrutador[r2].is_linked(r1))
                return true;

            else return false;
        }
        else return false;
    }
    else return false;
}

void Red::agregar_enrutador(std::string name){

    if(tabla_enrutador.find(name) == tabla_enrutador.end()){

        Enrutador r;

        enrutadores.insert(std::pair<int, std::string>(numero_enrutadores, name)); //se agrega a la lista de enrutadores
        numero_enrutadores++;

        for(int i = 0; i<numero_enrutadores; i++){ //crear enlaces con todos los enrutadores

            if(name == enrutadores[i])
                r.agregar_enlace(enrutadores[i], 0);
            else
                r.agregar_enlace(enrutadores[i]);
        }

        tabla_enrutador.insert(std::pair<std::string, Enrutador>(name, r)); //agregar un nuevo enrutador a la tabla de enrutamiento

        for(iterador_table_enrutador=tabla_enrutador.begin(); iterador_table_enrutador != tabla_enrutador.end(); iterador_table_enrutador++) //agregando un enlace con "nombre" a todos los enrutadores existentes
            iterador_table_enrutador->second.agregar_enlace(name);
    }
}

void Red::eliminar_enrutador(std::string name){

        tabla_enrutador.erase(name); //elimina el enrutador de la tabla

        for(iterador_table_enrutador = tabla_enrutador.begin(); iterador_table_enrutador != tabla_enrutador.end(); iterador_table_enrutador++) //eliminar todos los enlaces con 'nombre' de todos los enrutadores existentes
            iterador_table_enrutador->second.eliminar_enlace(name);

        if(tabla_enrutador.size()>1){ // Crea un nuevo "number_of_routers" que no incluye "nombre"
            std::map<int, std::string>temp;
            int temp_index = 0;

            for(int i = 0; i<numero_enrutadores; i++)
                if(enrutadores[i] != name){
                    temp.insert(std::pair<int, std::string>(temp_index, enrutadores[i]));
                    temp_index++;
                }
            enrutadores = temp;
            numero_enrutadores = temp_index;
        }
        else this->red_vacia();
}

void Red::mostrar_enrutador(std::string name){

    std::cout<<name<<'\t';
    tabla_enrutador[name].ver_enlances(false);
}

void Red::mostrar_todo(){

    std::cout<<"\t";

    for(iterador_table_enrutador=tabla_enrutador.begin();iterador_table_enrutador != tabla_enrutador.end(); iterador_table_enrutador++)
        std::cout<<iterador_table_enrutador->first<<'\t';

    std::cout<<std::endl;

    for(iterador_table_enrutador=tabla_enrutador.begin();iterador_table_enrutador != tabla_enrutador.end(); iterador_table_enrutador++){
        std::cout<<iterador_table_enrutador->first<<'\t';
        iterador_table_enrutador->second.ver_enlances(true);
        std::cout<<std::endl;
    }
}

void Red::mostrar_detalles() {

    std::string r, temp = "| ";

    std::cout<<char(218);
    for(int k = 0; k<21; k++) std::cout<<char(196);
    std::cout<<char(191)<<std::endl;

    std::cout<<"| Detalles de la red: |"<<std::endl;
    std::cout<<"|                     |"<<std::endl;

    if(numero_enrutadores >= 10)
        std::cout<<"| Enrutadores activos: "<<numero_enrutadores<<" |"<<std::endl;
    else
        std::cout<<"| Enrutadores activos: "<<numero_enrutadores<<"  |"<<std::endl;

    std::cout<<"|                     |"<<std::endl;

    for(int k = 0; k< numero_enrutadores; k++){

        if(temp.length() < 20){

            temp += enrutadores[k];
            temp += ", ";
        }

        if(temp.length() == 20){

            temp += "  |\n";
            r+=temp;
            temp.clear();
            temp = "| ";
        }
    }

    if(temp != "| "){

        temp += "\b\b";

        while(temp.length() < 24)
            temp += " ";

        temp += "  |\n";
        r += temp;
    }
    else{

        int index = r.rfind(",");
        std::string res;

        for(int k = 0; k< index; k++)
            res += r[k];
        res += "    |\n";
        r = res;
    }

    std::cout<< r ;

    std::cout<<"|                     |"<<std::endl;
    std::cout<<char(192);
    for(int k = 0; k<21; k++) std::cout<<char(196);
    std::cout<<char(217)<<std::endl;
}

void Red::camino_corto(std::string r1, std::string r2){

    int origen = this->obtener_codigo_enrutador(r1);
    int destino = this->obtener_codigo_enrutador(r2);

    int** grafico = new int*[numero_enrutadores]; //crea array 2d

    for (int i = 0; i < numero_enrutadores; ++i)
        grafico[i] = new int[numero_enrutadores];

    llenar_grafico(grafico);

    int dist[numero_enrutadores];
    bool sptSet[numero_enrutadores];
    int parent[numero_enrutadores];

    for (int i = 0; i < numero_enrutadores; i++) {

        parent[origen] = -1;

        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[origen] = 0;

    for (int count = 0; count < numero_enrutadores - 1; count++) {

        int u = Distancia_min(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < numero_enrutadores; v++)

            if (!sptSet[v] && grafico[u][v] && dist[u] + grafico[u][v] < dist[v] && grafico[u][v] != -1) {

                parent[v] = u;
                dist[v] = dist[u] + grafico[u][v];
            }
    }

    printSolucion(dist, parent, origen, destino);

    eliminar_grafico(grafico);
}

int Red::obtener_codigo_enrutador(std::string enrutador){

    for(int k = 0; k < numero_enrutadores; k++)
        if(enrutadores[k] == enrutador)
            return k;

   return -1;
}

void Red::agregar_enlace(std::string r1, std::string r2, int costo){

    tabla_enrutador[r1].agregar_enlace(r2, costo);
    tabla_enrutador[r2].agregar_enlace(r1, costo);
}

void Red::eliminar_enlace(std::string r1, std::string r2){

    tabla_enrutador[r1].eliminar_enlace(r2);
    tabla_enrutador[r2].eliminar_enlace(r1);
}

void Red::modificar_enlace(std::string r1, std::string r2, int costo){

    tabla_enrutador[r1].modificar_enlace(r2, costo);
    tabla_enrutador[r2].modificar_enlace(r1, costo);
}

bool Red::estan_enlazados(std::string r1, std::string r2) {

    if(tabla_enrutador[r1].is_linked(r2) && tabla_enrutador[r2].is_linked(r1)) return true;

    return false;
}

void Red::generar_red(){

    srand(time(NULL));

    short name_code, gen_enrutadores = 2 + (rand() % (7 - 2 + 1));
    std::string name;
    int number_of_links, r1, r2, c, prev_links = 0;

    while(gen_enrutadores > numero_enrutadores){ // genera enrutadores randoms

        name_code = 65 + (rand() % (90 - 65 + 1));
        name = char(name_code);

        if(is_present(name) == false)
            agregar_enrutador(name);
    }

    for(int i = 0; i < numero_enrutadores; i++){ // se asegura de que cada enrutador tenga al menos 1 enlace

        if(tabla_enrutador[enrutadores[i]].is_linked() == false){

            while(true){

                name_code = rand() % numero_enrutadores;

                if(name_code != i){

                    c = 1 + (rand() % (100));

                    agregar_enlace(enrutadores[i], enrutadores[name_code], c);
                    prev_links++;

                    break;
                }
            }
        }
    }

    number_of_links = (((numero_enrutadores-1) * (numero_enrutadores))/2) - prev_links;

    if(number_of_links > 0)
        number_of_links = 1 + (rand() % (number_of_links)); //min + (rand() % static_cast<int>(max - min + 1))

    while(number_of_links > 0){ // crea numero random de enlaces hasta 7

        r1 = rand() % (numero_enrutadores);
        r2 = rand() % (numero_enrutadores);

        if(r1 != r2){

            if(is_present(enrutadores[r1], enrutadores[r2]) == false){

                c = 1 + (rand() % (100));

                modificar_enlace(enrutadores[r1], enrutadores[r2], c);

                number_of_links--;
            }
        }
    }
}

void Red::importar_red(std::string file_name){

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

     if(file.is_open()){

         std::string temp, r1, r2;
         int costo;
         short counter = 1;

         while (file >> temp){

             if(counter == 1){ //enrutador 1
                 r1 = temp;
                 agregar_enrutador(r1);
             }
             else if (counter == 2){ //enrutador 2
                 r2 = temp;
                 agregar_enrutador(r2);
             }
             else if (counter == 3){ //costo
                 costo = stoi(temp);

                 tabla_enrutador[r1].modificar_enlace(r2, costo);
                 tabla_enrutador[r2].modificar_enlace(r1, costo);

                 counter = 0;
             }

             counter++;
         }
         file.close();
         std::cout<<"*| Red importada correctamente |*"<<std::endl;
         Sleep(1000);
     }
     else {
         std::cout<<"!! Error importando la red !!"<<std::endl;
         Sleep(1000);
     }
}

void Red::exportar_red(std::string file_name){

    std::fstream file (file_name, std:: fstream::out | std::fstream::binary);

     if(file.is_open()){

         std::string data;

         std::string key1, key2;
         int costo;

         for(int i = 0; i < numero_enrutadores; i++){

             key1 = enrutadores[i];

             for(int j = 0; j < numero_enrutadores; j++){

                 key2 = enrutadores[j];

                 costo = tabla_enrutador[key1].enlaces[key2];

                 if(costo>0){
                     data += key1;
                     data += ' ';
                     data += key2;
                     data += ' ';
                     data += std::to_string(costo);
                     data += "\r\n";
                 }
             }
         }

         file.write(data.c_str(), data.length());

         file.close();
         std::cout<<"Red exportada correctamente"<<std::endl;
         Sleep(1000);
     }
     else {
         std::cout<<"Error exportando la red"<<std::endl;
         Sleep(1000);
     }
}

void Red::red_vacia(){
    enrutadores.clear();
    tabla_enrutador.clear();
    numero_enrutadores = 0;
}

void Red::verificar_integ(){

    std::map<int, std::string> temp;
    int temp_index = 0;

    for(iterador_table_enrutador = tabla_enrutador.begin(); iterador_table_enrutador != tabla_enrutador.end(); iterador_table_enrutador++){

        if(iterador_table_enrutador->second.is_linked() == false){

            temp[temp_index] = iterador_table_enrutador->first;
            temp_index++;
        }
    }

    for(int k = 0; k<temp_index; k++)
        this->eliminar_enrutador(temp[k]);
}
