#include "Action.h"

Action::Action() = default;

Action::Action(const std::string& name, const std::string& type)
    : name_(name), type_(type)
{
}