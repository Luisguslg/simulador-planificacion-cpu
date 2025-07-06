#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../Core/process.h"
#include <vector>
#include <string>

class FileHandler {
public:
    static std::vector<Proceso> cargarProcesosDesdeArchivo(const std::string& nombreArchivo);
    static void guardarResultados(const std::string& nombreArchivo, const std::vector<Proceso>& procesos);
};

#endif
