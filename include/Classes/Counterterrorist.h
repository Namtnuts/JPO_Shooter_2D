#pragma once

#include "Classes/Enemy.h"

class Counterterrorist : public Enemy{
protected: 
    void initVariables();
    void initShape();
    void initRays();
    void initPath(int type);
public:
    Counterterrorist(int type);
    virtual ~Counterterrorist();
};