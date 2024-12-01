#include <nlohmann/json.hpp>
#include <crow_all.h>
#include <fstream>
#include <pelicula/application/peliculaController.hpp>

using namespace std;
using json = nlohmann::json;

int main()
{
    // Variables de configuracion del servidor
    ifstream file("../config/config.json");
    json config = json::parse(file);

    // Inicializa la aplicación
    crow::SimpleApp app;

    // Inicializa los controladores
    PeliculaController peliculaController(app);

    // Define una ruta (endpoint) para manejar solicitudes GET en la raíz "/"
    CROW_ROUTE(app, "/")
    ([]()
     {
         return "¡Hola, mundo!"; // Responde con un mensaje simple
     });

    // Inicia el servidor en el puerto 8080
    app.port(config["port"]).multithreaded().run(); // El servidor estará escuchando en http://localhost:8080
    return 0;
}
