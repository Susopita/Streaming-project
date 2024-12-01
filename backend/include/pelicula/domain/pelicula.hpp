#pragma once

#include <string>
#include <vector>

using namespace std;

class Pelicula
{
    string id;
    string titulo;
    string sinopsis;
    vector<string> tags;

public:
    Pelicula() = default;
    Pelicula(string id, string titulo, string sinopsis, vector<string> tags) : id(id), titulo(titulo), sinopsis(sinopsis), tags(tags) {}

    string getId() const { return id; }
    string getTitulo() const { return titulo; }
    string getSinopsis() const { return sinopsis; }
    vector<string> getTags() const { return tags; }

    void setId(string id) { this->id = id; }
    void setTitulo(string titulo) { this->titulo = titulo; }
    void setSinopsis(string sinopsis) { this->sinopsis = sinopsis; }
    void setTags(vector<string> tags) { this->tags = tags; }
};