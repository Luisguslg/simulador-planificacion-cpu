#ifndef SJF_H
#define SJF_H

#include "../process.h"
#include <vector>

namespace sjf {
    void ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal);
}

#endif
