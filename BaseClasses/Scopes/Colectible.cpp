#include "../Header/Colectible.h"

Colectible::Colectible(const double& midX, const double& midY) : MovableEntity()
{ 
    this->upgradeType = 1 + rand()%5; // gera um tipo entre 1 e 4

    /*
        type 1: aumenta o tanto de tiro 
        type 2: aumeta o fireRate
        type 3: troca de projetil
        type 4: aumenta vida
        type 5: aumenta o dano
    */

    switch (this->upgradeType)
    {
        case 1:
            this->displayListModel = textures[37];
            break;
        case 2:
            this->displayListModel = textures[35];
            break;
        case 3:
            this->displayListModel = textures[38];
            break;
        case 4:
            this->displayListModel = textures[34];
            break;
        case 5:
            this->displayListModel = textures[36];
            break;
    }

    this->type = 0;
    this->angle = 0;
    this->angularSpeed = 0;
    this->onScreen = GL_TRUE;
    this->hp = 7;

    this->setMax(10,10);
    this->setMin(-10,-10);
    this->setResize(0.5);
    this->setHitbox();
    this->setMidPoint(midX,midY);
    this->setVelocity(1,1);
}

void Colectible::move()
{
    this->midPoint.y = (this->midPoint.y + this->velocity.y);
    this->midPoint.x = (this->midPoint.x + this->velocity.x);

    int i = mantainInsideScreen(*this);

    if(i == 1){
        this->velocity.y = (-this->velocity.y);
        this->hp--;
    }else if(i == 2){
        this->velocity.x = (-this->velocity.x);
        this->hp--;
    }
    this->generalHitBoxMovement();

}
void Colectible::scaleMove(const double& scale){}