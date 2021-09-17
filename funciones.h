#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include "red.h"

bool is_number(std::string s);

int obtener_costo(bool puede_ser_negativo);

short menu_creacion_red();

short menu_edicion_red(Red& N);

bool file_vacio(std::string file_name);

bool file_existente(std::string file_name);

void crear_file(std::string file_name);

#endif // FUNCIONES_H
