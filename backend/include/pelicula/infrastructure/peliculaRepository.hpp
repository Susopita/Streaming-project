#pragma once

#include <data/repository.hpp>
#include <utils/singleton.hpp>
#include <pelicula/domain/pelicula.hpp>

class PeliculaRepository : public Repository<int, Pelicula>, public makeSingleton<PeliculaRepository>
{
};