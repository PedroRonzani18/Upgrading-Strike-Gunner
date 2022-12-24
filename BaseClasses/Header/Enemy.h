#ifndef _ENEMY_H
#define _ENEMY_H

#include "MovableEntity.h"
#include "Ballistic.h"
#include "Projectile.h"
#include "../../GeneralFiles/Header/colisionManager.h"
#include <time.h>

class Enemy: public MovableEntity, public Ballistic{
    protected:
        int killValue; // valor em pontos de matar o inimigo
        int dropPercentage; //probbilidade do inimigo dropar um coletavel 
        GLboolean onscreenTestable;
        OrderedPair followPoint;
        int continueMove;

    private: 
        double contador;

    public:
        Enemy(){}

        Enemy(int type);
        Enemy(int type, int typeMove, int numberOfShots, int typeTiroManager, double vx, double vy);

        Projectile createProject(Projectile* auxP, double angle);

        int getKillValue(){return this->killValue;}
        void setKillValue(const int& killValue){this->killValue = killValue;}

        int getDropPercentage(){return this->dropPercentage;}
        void setDropPercentage(const int& dropPercentage){this->dropPercentage = dropPercentage;}

        GLboolean getOnscreenTestable(){return this->onscreenTestable;}
        void setOnscreenTestable(const GLboolean& onscreenTestable){this->onscreenTestable = onscreenTestable;}

        OrderedPair getFollowPoint(){return this->followPoint;}
        void setFollowPoint(const double& x, const double& y){this->followPoint.setX(x); this->followPoint.setY(y);}
        void setFollowPoint(const OrderedPair& followPoint){this->followPoint = followPoint;}

        int getContinueMove(){return this->continueMove;}

        void aim(double auxAngle);
        void elipsoidMove(double a, double b, double yo);
        void elipsoidMoveNoEntrance(double a, double b, double yo);

        void parabolicMoveTemplateFx(double a, double b, double c);
        void parabolicMoveTemplateFy(double a, double b, double c);

        void senoidMoveTemplateFx(double a, double b, double c, double d);
        void senoidMoveTemplateFy(double a, double b, double c, double d);

        void bateVolta(const int& posY);

        void kamikazeMove();
        void move() override;
        void scaleMove(const double& scale) override;
        std::vector<Projectile> fire() override;
};  

#endif