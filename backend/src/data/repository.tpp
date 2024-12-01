#include <data/repository.hpp>

#include <concepts>
#include <optional>

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
                                                      &index)
{
    if (models.find(index) != models.end())
    {
        return models[index];
    }
    return nullopt;
}

template <class Index, class Model>
    requires ModelClass<Model, Index>
vector<Model> Repository<Index, Model>::getAll()
{
    vector<Model> all;
    for (auto &model : models)
    {
        all.push_back(model.second);
    }
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