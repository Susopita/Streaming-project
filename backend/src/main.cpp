#include <iostream>
#include "crow_all.h"

using namespace std;

int main()
{
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
    app.port(8080).run(); // El servidor estará escuchando en http://localhost:8080
    return 0;
}
