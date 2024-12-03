#pragma once

#include <string>
#include <core/utils/singleton.hpp>
#include <vector>
#include <optional>
#include <memory>
#include <core/pelicula/domain/pelicula.hpp>
#include <core/pelicula/infrastructure/peliculaRepository.hpp>
#include <search/interface/searchEngine.hpp>
#include <search/utils/searchConfig.hpp>

using namespace std;

class PeliculaService : public makeSingleton<PeliculaService>
{
    friend class makeSingleton<PeliculaService>;
    PeliculaRepository &peliculaRepository = PeliculaRepository::getInstance();
    unique_ptr<SearchEngine<PeliculaRepository>> searchEngine = SearchConfig::getSearchEngine();

public:
    vector<Pelicula> buscarPeliculasConMotorBusqueda(const string &busqueda);
    optional<Pelicula> buscarPeliculaPorId(string id);
    virtual ~PeliculaService() = default;
};