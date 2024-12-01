#include <httplib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <format>
#include <thread>
#include <atomic>

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

    httplib::Client client(base_url);

    auto res = client.Get("/");
    if (res)
    {
        cout << res->status << endl;
        cout << res->body << endl;
    }
    else
    {
        cout << "Error: " << res.error() << endl;
    }
    return 0;
}
