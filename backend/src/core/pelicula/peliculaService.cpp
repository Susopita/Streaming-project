#include <core/pelicula/domain/peliculaService.hpp>

#include <string>
#include <vector>
#include <core/pelicula/domain/pelicula.hpp>
#include <optional>

using namespace std;

vector<Pelicula> PeliculaService::buscarPeliculasConMotorBusqueda(const string &busqueda)
{
    return searchEngine->search(peliculaRepository, busqueda);
}

optional<Pelicula> PeliculaService::buscarPeliculaPorId(string id)
{
    return peliculaRepository.getById(id);
}