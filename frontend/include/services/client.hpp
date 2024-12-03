// include/services/client.h++
#pragma once
#include <vector>
#include <string>
#include <models/pelicula.hpp>

class Client
{
public:
    // Busca películas basadas en el término de búsqueda proporcionado
    std::vector<Pelicula> search_peliculas(const std::string &query);

    // Llama al endpoint de prueba (Hello World)
    std::string test_server();
};
