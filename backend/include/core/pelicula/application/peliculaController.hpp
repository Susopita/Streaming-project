#pragma once

#include <core/crow_all.h>
#include <core/pelicula/domain/peliculaService.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <core/utils/responseEntity.hpp>

using json = nlohmann::json;

class PeliculaController
{
    PeliculaService &peliculaService = PeliculaService::getInstance();

public:
    PeliculaController(crow::SimpleApp &app)
    {
        CROW_ROUTE(app, "/pelicula/search")
            .methods("GET"_method)([&](const crow::request &req)
                                   {
                string buscar = req.url_params.get("buscar") ? req.url_params.get("buscar"): "";
                if (buscar.empty())
                {
                    return ResponseEntity::badRequest("Argumento 'buscar' no encontrado");
                }
                auto peliculas = peliculaService.buscarPeliculasConMotorBusqueda(buscar);
                return ResponseEntity::ok(peliculas); });
    }
};