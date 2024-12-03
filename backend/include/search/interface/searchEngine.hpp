#pragma once

#include <core/data/repository.hpp>
#include <string>
#include <type_traits>
#include <concepts>
#include <vector>

using namespace std;

template <class Repo>
    requires requires { typename Repo::IndexType; typename Repo::ModelType; }
class SearchEngine
{
public:
    using Index = typename Repo::IndexType;
    using Model = typename Repo::ModelType;

    virtual ~SearchEngine() = default;
    virtual vector<Model> search(const Repo &repository, const string &query) = 0;
};