#pragma once

#include <string>
#include <map>
#include <optional>
#include <vector>
#include <concepts>
#include <type_traits>

using namespace std;

template <class T, class Index>
concept ModelClass = requires(T t) {
    { t.getId() }
      -> same_as<Index>;
};

template <class Index, class Model>
    requires ModelClass<Model, Index>
class Repository
{
public:
    virtual ~Repository() = default;
    Index save(const Model &model);
    optional<Model> getById(const Index &index);
    vector<Model> getAll();
    void update(const Model &model);
    void remove(const Index &index);

protected:
    map<Index, Model> models;
    virtual void loadData(const string &dataRoute) = 0;
    Repository() = default;
};

#include "../../../src/core/data/repository.tpp"