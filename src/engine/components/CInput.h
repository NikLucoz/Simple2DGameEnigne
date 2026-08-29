#pragma once
#include "Component.h"

class CInput : public Component
{
public:
    bool bUp = false;
    bool bDown = false;
    bool bLeft = false;
    bool bRight = false;
    bool bMouseLeft = false;
    bool bMouseRight = false;
    
    CInput() = default;
};
