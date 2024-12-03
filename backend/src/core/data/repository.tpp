#include <core/data/repository.hpp>

#include <concepts>
#include <optional>
#include <iostream>

using namespace std;

template <class Index, class Model>
    requires ModelClass<Model, Index>
Index Repository<Index, Model>::save(const Model &model)
{
    models[model.getId()] = model;
    return model.getId();
}

template <class Index, class Model>
    requires ModelClass<Model, Index>
optional<Model> Repository<Index, Model>::getById(const Index
                                                      &index) const
{
    auto it = models.find(index); // Busca la clave
    if (it != models.end())
    {
        return it->second; // Retorna el valor si se encuentra
    }
    return std::nullopt; // Retorna 'nullopt' si no se encuentra
}

template <class Index, class Model>
    requires ModelClass<Model, Index>
vector<Model> Repository<Index, Model>::getAll() const
{
    vector<Model> all;
    for (auto &model : models)
    {
        all.push_back(model.second);
    }
    cout << "cantidad: " << all.size() << endl;
    return all;
}

template <class Index, class Model>
    requires ModelClass<Model, Index>
void Repository<Index, Model>::update(const Model &model)
{
    models[model.getId()] = model;
}

template <class Index, class Model>
    requires ModelClass<Model, Index>
void Repository<Index, Model>::remove(const Index &index)
{
    models.erase(index);
}