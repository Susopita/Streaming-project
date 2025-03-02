#pragma once

#include <string>
#include <core/data/repository.hpp>
#include <core/utils/singleton.hpp>
#include <core/pelicula/domain/pelicula.hpp>
#include <utils/configs.hpp>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class PeliculaRepository : public Repository<string, Pelicula>, public makeSingleton<PeliculaRepository>
{
    friend class makeSingleton<PeliculaRepository>;
    void loadData(const string &dataRoute) override;
    PeliculaRepository() { loadData(fs::path(Configs::getInstance()["data"].get<string>()).string()); }

public:
    virtual ~PeliculaRepository() = default;
};