#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <core/utils/singleton.hpp>

using namespace std;
using json = nlohmann::json;

class Configs final : public makeSingleton<Configs>, public json
{
    friend class makeSingleton<Configs>;

    Configs() { ifstream("../config/config.json") >> *this; }
};