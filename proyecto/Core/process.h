#ifndef PROCESS_H
#define PROCESS_H

#include <string>

enum Estado {
    NUEVO,
    LISTO,
    EJECUTANDO,
    TERMINADO
};

struct Proceso {
    std::string id;
    int llegada;
    int rafaga;
    int prioridad;
    Estado estado;

    // Métricas
    int inicio_ejecucion = -1;
    int finalizacion = -1;
    int tiempo_espera = 0;
    int tiempo_respuesta = -1;
    int tiempo_retorno = 0;
};

#endif
