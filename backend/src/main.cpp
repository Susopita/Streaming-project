#include <nlohmann/json.hpp>
#include <core/crow_all.h>
#include <fstream>
#include <core/pelicula/application/peliculaController.hpp>
#include <utils/configs.hpp>

using namespace std;
using json = nlohmann::json;

int main()
{
    // Variables de configuracion del servidor
    Configs &configs = Configs::getInstance();

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
    app.port(configs["port"]).multithreaded().run(); // El servidor estará escuchando en http://localhost:8080
    return 0;
}
