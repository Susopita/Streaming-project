#include <search/utils/searchConfig.hpp>

#include <search/engines/pelicula/PeliculaBasicSearchEngine.hpp>

unique_ptr<SearchEngine<PeliculaRepository>> SearchConfig::getSearchEngine()
{
    // Variables de configuracion del servidor
    Configs &configs = Configs::getInstance();

    // Selecciona el motor de búsqueda
    if (configs["searchEngines"]["Peliculas"] == "basic")
    {
        return make_unique<PeliculaBasicSearchEngine>();
    }
    else
    {
        throw runtime_error("Motor de búsqueda no soportado");
    }
}