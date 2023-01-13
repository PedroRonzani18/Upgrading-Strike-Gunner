#ifndef _ENEMY_H
#define _ENEMY_H

#include "MovableEntity.h"
#include "Ballistic.h"
#include "Projectile.h"
#include "../../GeneralFiles/Header/colisionManager.h"

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

        Enemy(const int& type);
        Enemy(const int& type, const int& typeMove, const int& numberOfShots, const int& typeTiroManager, const double& vx, const double& vy);
        Enemy(int killValue, int dropPercentage, GLboolean onscreenTestable, OrderedPair followPoint, int continueMove, 
              const OrderedPair& velocity, const double& angle, const double& angularSpeed, const double& hp, const int& type, const int& typeMove,
              const int& displayListModel, const GLboolean& onScreen, const OrderedPair& midPoint, const OrderedPair& max, const OrderedPair& min, const double& resize,
              const Projectile& currentProjectile, const int& numberOfShots, const int& typeTiroManager, const int& fireRatePeriod, const double& alteredFireRate
        );

        Enemy enemySelector(const int& type);

        Projectile createProject(Projectile* auxP, const double& angle);

        int getKillValue()const{return this->killValue;}
        void setKillValue(const int& killValue){this->killValue = killValue;}

        int getDropPercentage()const{return this->dropPercentage;}
        void setDropPercentage(const int& dropPercentage){this->dropPercentage = dropPercentage;}

        GLboolean getOnscreenTestable()const{return this->onscreenTestable;}
        void setOnscreenTestable(const GLboolean& onscreenTestable){this->onscreenTestable = onscreenTestable;}

        OrderedPair getFollowPoint()const{return this->followPoint;}
        void setFollowPoint(const double& x, const double& y){this->followPoint.x = x; this->followPoint.y = y;}
        void setFollowPoint(const OrderedPair& followPoint){this->followPoint = followPoint;}

        int getContinueMove()const{return this->continueMove;}

        void aim(const double& auxAngle);
        void elipsoidMove(const double& a, const double& b, const double& yo);
        void elipsoidMoveNoEntrance(const double& a, const double& b, const double& yo);

        void parabolicMoveTemplateFx(const double& a, const double& b, const double& c);
        void parabolicMoveTemplateFy(const double& a, const double& b, const double& c);

        void senoidMoveTemplateFx(const double& a, const double& b, const double& c, const double& d);
        void senoidMoveTemplateFy(const double& a, const double& b, const double& c, const double& d);

        void bateVolta(const int& posY);

        void kamikazeMove();
        void move() override;
        void scaleMove(const double& scale) override;
        std::vector<Projectile> fire() override;
};  

#endif