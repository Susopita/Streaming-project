#include <iostream>
#include "crow_all.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main()
{
    ifstream file("../config/config.json");
    json config = json::parse(file);

    crow::SimpleApp app;
    // Define una ruta (endpoint) para manejar solicitudes GET en la raíz "/"
    CROW_ROUTE(app, "/")([]()
                         {
                             return "¡Hola, mundo!"; // Responde con un mensaje simple
                         });

    // Define otra ruta que acepta parámetros en la URL
    CROW_ROUTE(app, "/saludar/<string>")([](std::string nombre)
                                         {
                                             return "¡Hola, " + nombre + "!"; // Saluda al usuario por nombre
                                         });

    // Inicia el servidor en el puerto 8080
    app.port(config["port"]).run(); // El servidor estará escuchando en http://localhost:8080
    return 0;
}
