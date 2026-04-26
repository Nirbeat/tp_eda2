#ifndef CIUDAD_H
#define CIUDAD_H

#include "../structs.h"

class Ciudad {
public:
  char nombre[30];
  struct Coordenadas coordenadas;
  int id;
};

#endif