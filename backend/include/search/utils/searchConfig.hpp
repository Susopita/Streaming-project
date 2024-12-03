#pragma once

#include <string>
#include <utils/configs.hpp>
#include <search/interface/searchEngine.hpp>
#include <core/pelicula/infrastructure/peliculaRepository.hpp>
#include <memory>

using namespace std;
using json = nlohmann::json;

struct SearchConfig
{
    static unique_ptr<SearchEngine<PeliculaRepository>> getSearchEngine();
};