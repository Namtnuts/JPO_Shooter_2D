#pragma once

#include "Classes/Enemy.h"

class Guard : public Enemy{
protected:
    void initVariables();
    void initShape();
    void initRays();
    void initPath(int type);
public:
    Guard(int type);
    virtual ~Guard();
};
