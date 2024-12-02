#include <core/pelicula/domain/peliculaService.hpp>

#include <string>
#include <vector>
#include <core/pelicula/domain/pelicula.hpp>
#include <optional>

using namespace std;

vector<Pelicula> PeliculaService::buscarPeliculasConMotorBusqueda(const string &busqueda)
{
    return vector<Pelicula>{Pelicula{"1", "Pelicula 1", "Sinopsis de la pelicula 1", {"tag1", "tag2"}}};
}

optional<Pelicula> PeliculaService::buscarPeliculaPorId(string id)
{
    return peliculaRepository.getById(id);
}