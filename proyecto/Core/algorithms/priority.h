#ifndef PRIORITY_H
#define PRIORITY_H

#include "../process.h"
#include <vector>

namespace priority {
    void ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal);
}

#endif
