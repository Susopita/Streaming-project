#pragma once

#include <core/crow_all.h>
#include <concepts>
#include <string>
#include <type_traits>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

template <class T>
concept Serializable = requires(T a) {
    { a.dump() } -> same_as<string>;
};

class ResponseEntity
{
    template <Serializable T>
    static string serializeCollection(const vector<T> &collection)
    {
        json jsonArray;
        for (const auto &item : collection)
        {
            jsonArray.push_back(json::parse(item.dump())); // Serializamos cada objeto y lo agregamos al array
        }
        return jsonArray.dump(); // Retorna como un string serializado
    }

public:
    static crow::response ok()
    {
        return crow::response{200};
    }

    template <Serializable T>
    static crow::response ok(const T &data)
    {
        return crow::response{
            200,
            data.dump()};
    }

    template <Serializable T>
    static crow::response ok(const vector<T> &data)
    {
        crow::response res{
            200,
            serializeCollection(data)};
        res.add_header("Content-Type", "application/json");
        return res;
    }

    static crow::response noContent()
    {
        return crow::response{
            204};
    }

    static crow::response created(string uri)
    {
        crow::response res{201};
        res.add_header("Location", uri);
        return res;
    }

    static crow::response notFound(string message = "Not Found")
    {
        return crow::response{
            404,
            message};
    }

    static crow::response badRequest(string message = "Bad Request")
    {
        return crow::response{
            400,
            message};
    }
};