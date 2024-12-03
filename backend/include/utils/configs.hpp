#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <core/utils/singleton.hpp>
#include <filesystem>
#include <iostream>

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

class Configs final : public makeSingleton<Configs>, public json
{
    friend class makeSingleton<Configs>;

    Configs()
    {
        try
        {
            ifstream(fs::path("../config/config.json")) >> *this;
        }
        catch (exception &e)
        {
            cerr << "Error al cargar el archivo de configuración: " << e.what() << endl;
            cerr << "Directorio actual: " << fs::current_path() << endl;
            char x;
            cin >> x;
            exit(1);
        }
    }
};