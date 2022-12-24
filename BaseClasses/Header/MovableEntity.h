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

        OrderedPair& getVelocity(){return velocity;}
        void setVelocity(const OrderedPair& velocity){this->velocity = velocity;}
        void setVelocity(double x, double y){this->velocity.setX(x); this->velocity.setY(y);}

        double getAngle(){return angle;}
        void setAngle(const double& angle){this->angle = angle;}

        double getAngularSpeed(){return angularSpeed;}
        void setAngularSpeed(const double& angularSpeed){this->angularSpeed = angularSpeed;}

        double getHp(){return hp;}
        void setHp(const double& hp){this->hp = hp;}

        int getType(){return type;}
        void setType(const int& type){this->type = type;}

        void generalHitBoxMovement();

        virtual void move() = 0; // movimentação padrão da entidade
        virtual void scaleMove(const double& scale) = 0; // movimentação usando escala de uma entidade

        int getTypeMove(){return this->typeMove;}
        void setTypeMove(const int& typeMove){this->typeMove = typeMove;}
};

#endif