#include "../Header/Colectible.h"

Colectible::Colectible(double midX, double midY) : MovableEntity()
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
    this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
    this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());

    int i = mantainInsideScreen(*this);

    if(i == 1){
        this->velocity.setY(-this->velocity.getY());
        this->hp--;
    }else if(i == 2){
        this->velocity.setX(-this->velocity.getX());
        this->hp--;
    }
    this->generalHitBoxMovement();

}
void Colectible::scaleMove(const double& scale){}