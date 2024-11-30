#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <format>

using namespace std;
using json = nlohmann::json;

auto main() -> int
{
    ifstream file("../config/config.json");
    json config = json::parse(file);

    string base_url = format("{}://{}:{}",
                             config["protocol"].get<string>(),
                             config["host"].get<string>(),
                             config["port"].get<int>());

    CURL *curl;
    CURLcode res;

    // Inicializar libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // Establecer la URL
        curl_easy_setopt(curl, CURLOPT_URL, base_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);

        // Realizar la solicitud GET
        res = curl_easy_perform(curl);

        // Comprobar si la solicitud fue exitosa
        if (res != CURLE_OK)
        {
            std::cerr << "Error al hacer la solicitud: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            std::cout << "Solicitud GET exitosa." << std::endl;
        }

        // Limpiar
        curl_easy_cleanup(curl);
    }

    // Finalizar libcurl
    curl_global_cleanup();

    return 0;
}
