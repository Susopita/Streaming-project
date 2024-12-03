#pragma once

#include <search/interface/searchEngine.hpp>
#include <core/pelicula/infrastructure/peliculaRepository.hpp>
#include <core/pelicula/domain/pelicula.hpp>

using namespace std;

class PeliculaBasicSearchEngine final : public SearchEngine<PeliculaRepository>
{
public:
    vector<Pelicula> search(const PeliculaRepository &repository, const string &query) override;
    ~PeliculaBasicSearchEngine() override = default;
};