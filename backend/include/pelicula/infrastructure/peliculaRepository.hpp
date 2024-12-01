#pragma once

#include <string>
#include <data/repository.hpp>
#include <utils/singleton.hpp>
#include <pelicula/domain/pelicula.hpp>

using namespace std;

class PeliculaRepository : public Repository<string, Pelicula>, public makeSingleton<PeliculaRepository>
{
    friend class makeSingleton<PeliculaRepository>;
    void loadData(const string &dataRoute) override;
    PeliculaRepository() { loadData("../backend/database/limpio.csv"); }

public:
    virtual ~PeliculaRepository() = default;
};