#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Core/process.h"
#include "../Core/scheduler.h"
#include <vector>

class Interfaz {
public:
    static AlgoritmoPlanificacion seleccionarAlgoritmo();
    static std::vector<Proceso> crearProcesosManualmente();
    static int solicitarQuantum();
};

#endif
