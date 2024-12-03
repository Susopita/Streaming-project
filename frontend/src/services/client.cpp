// src/services/client.cpp
#include <services/client.hpp>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <models/pelicula.hpp>

using json = nlohmann::json;
using namespace std;

// Implementación de search_peliculas
vector<Pelicula> Client::search_peliculas(const string &query)
{
    vector<Pelicula> peliculas;

    // Crear un cliente apuntando a localhost:8080
    httplib::Client cli("localhost", 8080);

    cli.set_connection_timeout(5); // segundos
    cli.set_read_timeout(5);       // segundos

    // Definir los parámetros de consulta
    httplib::Params params = {{"buscar", query}};

    // Realizar la solicitud GET con parámetros y encabezados adicionales
    auto res = cli.Get("/pelicula/search", params, {{"Accept", "application/json"}});

    if (res && res->status == 200)
    {
        try
        {
            // Parsear la respuesta JSON
            json j = json::parse(res->body);

            // Verificar que la respuesta sea un arreglo
            if (j.is_array())
            {
                for (const auto &item : j)
                {
                    Pelicula p = item.get<Pelicula>();
                    peliculas.push_back(p);
                }
            }
            else
            {
                cerr << "La respuesta no es un arreglo JSON.\n";
            }
        }
        catch (const json::parse_error &e)
        {
            cerr << "Error al parsear el JSON: " << e.what() << "\n";
        }
        catch (const json::type_error &e)
        {
            cerr << "Error de tipo en JSON: " << e.what() << "\n";
        }
    }
    else
    {
        cerr << "Error en la solicitud: " << (res ? to_string(res->status) : "No response") << "\n";
    }

    return peliculas;
}

// Implementación de test_server
string Client::test_server()
{
    string response_body = "";

    // Crear un cliente apuntando a localhost:8080
    httplib::Client cli("localhost", 8080);

    // Realizar la solicitud GET al endpoint raíz
    auto res = cli.Get("/");

    if (res && res->status == 200)
    {
        response_body = res->body;
    }
    else
    {
        response_body = "Error al llamar al endpoint de prueba.";
        cerr << "Error en la solicitud: " << (res ? to_string(res->status) : "No response") << "\n";
    }

    return response_body;
}
