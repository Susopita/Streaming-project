#pragma once

#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;

class Client
{
    static unique_ptr<Client> instance;

    Client();

    template <class Request, class Response>
    Response request(const string &url, Request &request, const string &method);

public:
    static Client *getInstance();

    template <class Request, class Response>
    Response get(const string &url, Request &request);

    template <class Request, class Response>
    Response post(const string &url, Request &request);

    template <class Request, class Response>
    Response del(const string &url, Request &request);

    template <class Request, class Response>
    Response patch(const string &url, Request &request);
};
