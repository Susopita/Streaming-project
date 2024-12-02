#pragma once

#include <string>
#include <core/utils/singleton.hpp>
#include <vector>
#include <optional>
#include <core/pelicula/domain/pelicula.hpp>
#include <core/pelicula/infrastructure/peliculaRepository.hpp>

using namespace std;

class PeliculaService : public makeSingleton<PeliculaService>
{
    friend class makeSingleton<PeliculaService>;
    PeliculaRepository &peliculaRepository = PeliculaRepository::getInstance();

public:
    vector<Pelicula> buscarPeliculasConMotorBusqueda(const string &busqueda);
    optional<Pelicula> buscarPeliculaPorId(string id);
    virtual ~PeliculaService() = default;
};