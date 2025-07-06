#include "file_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

vector<Proceso> FileHandler::cargarProcesosDesdeArchivo(const string& nombreArchivo) {
    vector<Proceso> procesos;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "❌ Error: No se pudo abrir el archivo " << nombreArchivo << "\n";
        return procesos;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Proceso p;
        ss >> p.id >> p.llegada >> p.rafaga >> p.prioridad;
        p.estado = NUEVO;
        procesos.push_back(p);
    }

    archivo.close();
    return procesos;
}

void FileHandler::guardarResultados(const string& nombreArchivo, const vector<Proceso>& procesos) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "❌ No se pudo escribir en el archivo " << nombreArchivo << "\n";
        return;
    }

    archivo << left << setw(8) << "ID"
            << setw(10) << "Llegada"
            << setw(8) << "Ráfaga"
            << setw(10) << "Prioridad"
            << setw(10) << "Inicio"
            << setw(10) << "Fin"
            << setw(10) << "Retorno"
            << setw(10) << "Espera"
            << setw(10) << "Respuesta" << "\n";

    archivo << string(76, '-') << "\n";

    for (const auto& p : procesos) {
        archivo << left << setw(8) << p.id
                << setw(10) << p.llegada
                << setw(8) << p.rafaga
                << setw(10) << p.prioridad
                << setw(10) << p.inicio_ejecucion
                << setw(10) << p.finalizacion
                << setw(10) << p.tiempo_retorno
                << setw(10) << p.tiempo_espera
                << setw(10) << p.tiempo_respuesta << "\n";
    }

    archivo.close();
    cout << "✅ Resultados guardados en " << nombreArchivo << "\n";
}

