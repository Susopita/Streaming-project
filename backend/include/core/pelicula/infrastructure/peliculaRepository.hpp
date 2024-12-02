#pragma once

#include <string>
#include <core/data/repository.hpp>
#include <core/utils/singleton.hpp>
#include <core/pelicula/domain/pelicula.hpp>

using namespace std;

class PeliculaRepository : public Repository<string, Pelicula>, public makeSingleton<PeliculaRepository>
{
    friend class makeSingleton<PeliculaRepository>;
    void loadData(const string &dataRoute) override;
    PeliculaRepository() { loadData("../backend/database/limpio.csv"); }

public:
    virtual ~PeliculaRepository() = default;
};