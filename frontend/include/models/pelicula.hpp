// include/Pelicula.h
#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Pelicula
{
    std::string id;
    std::string titulo;
    std::string sinopsis;
    std::vector<std::string> tags;

    // Deserialización desde JSON
    friend void from_json(const nlohmann::json &j, Pelicula &p)
    {
        j.at("id").get_to(p.id);
        j.at("titulo").get_to(p.titulo);
        j.at("sinopsis").get_to(p.sinopsis);
        j.at("tags").get_to(p.tags);
    }
};
