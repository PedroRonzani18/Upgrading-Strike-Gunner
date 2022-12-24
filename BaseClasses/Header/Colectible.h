#ifndef _COLECTIBLE_H
#define _COLECTIBLE_H

#include "../../GeneralFiles/Header/drawings.h"
#include "../../GeneralFiles/Header/colisionManager.h"
#include "MovableEntity.h"
#include <stdlib.h>

class Colectible: public MovableEntity{
    private:
        int upgradeType;

    public:
        Colectible(double midX, double midY);

        int getUpgradeType(){return this->upgradeType;}
        void setUpgradeType(const int& upgradeType){this->upgradeType = upgradeType;}

        void move() override;
        void scaleMove(const double& scale) override;
};

#endif