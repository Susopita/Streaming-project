#pragma once

#include <string>
#include <utils/singleton.hpp>
#include <vector>
#include <optional>
#include <pelicula/domain/pelicula.hpp>
#include <pelicula/infrastructure/peliculaRepository.hpp>

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