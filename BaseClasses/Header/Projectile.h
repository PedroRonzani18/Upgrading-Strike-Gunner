#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "MovableEntity.h"
#include "../../GeneralFiles/Header/drawings.h"
#include "../../GeneralFiles/Header/colisionManager.h"

class Projectile: public MovableEntity{
    private:
        double damage;
        double defaultFireRate;
        int continueMove;
        MovableEntity* followedEnemy;

        //owner == 1 ? owner = player : owner = enemy 
        int owner; // dono do tiro. usado na hora de analizar colisões

    public:
        Projectile(){}

        Projectile(const int& type);

        double getDamage(){return damage;}
        void setDamage(const double& damage){this->damage = damage;}

        double getDefaultFireRate(){return defaultFireRate;}
        void setDefaultFireRate(const double& defaultFireRate){this->defaultFireRate = defaultFireRate;}

        MovableEntity* getFollowedEnemy(){return this->followedEnemy;}
        void setFollowedEnemy(MovableEntity* followedEnemy){this->followedEnemy = followedEnemy;}

        int getOwner(){return owner;}
        void setOwner(const int& owner){this->owner = owner;}

        void move() override;
        void straightMove(); // projecile anda para frente
        void bouncyMove();
        void folllowMove();
        void followPlayerMove();
        void angularShooting();

        void scaleMove(const double& scale) override;
};

#endif