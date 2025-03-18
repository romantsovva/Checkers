#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../Models/Project_path.h"

class Config
{
  public:
    Config(const std::string& filename)
    {
        reload(filename);
    }

    void reload(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open()) {
            config = nlohmann::json::parse(file);
        }
    }

    template<typename T>
    T operator()(const std::string& path) const
    {
        return config.value(path, T());
    }

  private:
    json config;
};
