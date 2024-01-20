#pragma once

#include "Classes/Enemy.h"

class Specialforce : public Enemy{
protected:
    void initVariables();
    void initShape();
    void initRays();
    void initPath(int type);
public:
    Specialforce(int type);
    virtual ~Specialforce();
};