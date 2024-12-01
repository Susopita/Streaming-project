#include "crow_all.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <atomic>

using namespace std;
using json = nlohmann::json;

vector<crow::websocket::connection *> clients;
mutex clients_mutex;
atomic<bool> stop_flag(false);

void broadcast_message(const std::string &message)
{
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (auto client : clients)
    {
        if (client)
        {
            client->send_text(message);
        }
    }
}

int main()
{
    ifstream file("../config/config.json");
    json config = json::parse(file);

    crow::SimpleApp app;
    // Define una ruta (endpoint) para manejar solicitudes GET en la raíz "/"
    CROW_ROUTE(app, "/")
    ([]()
     {
         return "¡Hola, mundo!"; // Responde con un mensaje simple
     });

    // Define otra ruta que acepta parámetros en la URL
    CROW_ROUTE(app, "/buscar/<string>")
        .methods("GET"_method)([](std::string nombre)
                               {
                                   return "¡Hola, " + nombre + "!"; // Saluda al usuario por nombre
                               });

    CROW_ROUTE(app, "")
        .methods("PATCH"_method)([]()
                                 { return "¡Hola, mundo!"; });

    // Inicia el servidor en el puerto 8080
    app.port(config["port"]).run(); // El servidor estará escuchando en http://localhost:8080
    return 0;
}
