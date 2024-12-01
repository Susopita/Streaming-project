#pragma once

#include <string>
#include <memory>
#include <map>
#include <optional>
#include "../utils/singleton.hpp"

using namespace std;

template <class index, class model>
class Repository : public makeSingleton<Repository<index, model>>
{
    map<index, model> models;
    Repository() = default;

public:
    virtual ~Repository();
    index save(const model &model);
    optional<model> getById(const index &index);
    void update(const model &model);
    void remove(const index &index);

protected:
    virtual void loadData(const string &dataRoute) = 0;
};