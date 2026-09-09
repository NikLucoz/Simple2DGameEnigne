#pragma once
#include <SFML/System/String.hpp>

class Action
{
    sf::String name_ = "NONE";
    sf::String type_ = "NONE";
public:
    Action();
    Action(const std::string& name, const std::string& type);

    const std::string& name() const
    {
        return name_;
    }

    const std::string& type() const
    {
        return type_;
    }

    std::string toString() const
    {
        return name_ + ": " + type_;
    }
};
