#ifndef _MOVABLEENTITY_H
#define _MOVABLEENTITY_H

#include "Entity.h"
#include "OrderedPair.h"
#include <cmath>

class MovableEntity: public Entity
{
    protected:
        OrderedPair velocity;
        double angle;
        double angularSpeed;
        double hp;
        int type;
        int typeMove;

    public:

        MovableEntity();
        MovableEntity(const OrderedPair& velocity, const double& angle, const double& angularSpeed, const double& hp, const int& type, const int& typeMove,
                      const int& displayListModel, const GLboolean& onScreen, const OrderedPair& max, const OrderedPair& min, const double& resize);

        OrderedPair& getVelocity(){return this->velocity;}
        void setVelocity(const OrderedPair& velocity){this->velocity = velocity;}
        void setVelocity(const double& x, const double& y){this->velocity.x = x; this->velocity.y = y;}

        double getAngle()const {return this->angle;}
        void setAngle(const double& angle){this->angle = angle;}

        double getAngularSpeed()const{return angularSpeed;}
        void setAngularSpeed(const double& angularSpeed){this->angularSpeed = angularSpeed;}

        double getHp()const{return hp;}
        void setHp(const double& hp){this->hp = hp;}

        int getType()const{return type;}
        void setType(const int& type){this->type = type;}

        int getTypeMove()const{return this->typeMove;}
        void setTypeMove(const int& typeMove){this->typeMove = typeMove;}

        void generalHitBoxMovement();

        virtual void move() = 0; // movimentação padrão da entidade
        virtual void scaleMove(const double& scale) = 0; // movimentação usando escala de uma entidade
};

#endif