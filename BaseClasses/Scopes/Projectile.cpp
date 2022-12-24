#include "../Header/Projectile.h"

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)

Projectile::Projectile(const int& type) : MovableEntity()
{
    this->type = type;
    
/*
    type 0: tiro padrão
    type 1: bate nas paredes
    type 2: tiro que segue inimigos
*/

    switch (this->type)
    {
        case 0: // tiro padrão (bola azul) e anda para baixo
            this->typeMove = 0;
            this->displayListModel = textures[1];
            this->owner = 0; 
            this->hp = 1;
            this->damage = 1;
            this->defaultFireRate = 15;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(4, 4);
            this->setMin(-4, -4);
            this->setResize(0.5);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(3,3);
            break;

        case 1: // tiro que rebate (bola vermelha)
            this->typeMove = 1;
            this->displayListModel = textures[6];
            this->owner = 0; 
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->hp = 1;
            this->damage = 2;
            this->defaultFireRate = 50;
            this->setMax(4, 4);
            this->setMin(-4, -4);
            this->setResize(0.5);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(2,2);
            break;

        case 2: // tiro que segue (fireBall)
            this->typeMove = 2;
            this->displayListModel = textures[3];
            this->owner = 0;
            this->hp = 1;
            this->damage = 3;
            this->defaultFireRate = 76;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(4, 4);
            this->setMin(-4, -4);
            this->setResize(0.5);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(3,3);
            break;

        case 3: // INIMIGO: laser vermelho que segue reto
            this->typeMove = 3;
            this->displayListModel = textures[7];
            this->owner = 0; 
            this->hp = 1;
            this->damage = 1;
            this->defaultFireRate = 160;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(1, 6.5);
            this->setMin(-1, -6.5);
            this->setResize(1);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(1.7, 1.7);
            break;

        case 4: // INIMIGO: tiro do tanque que espalha bolinhas
            this->typeMove = 3;
            this->displayListModel = textures[6];
            this->owner = 0; 
            this->hp = 1;
            this->damage = 1;
            this->defaultFireRate = 120;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(4, 4);
            this->setMin(-4, -4);
            this->setResize(0.5);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(1, 1);
            break;

        case 5: // tiro que segue (fireBall)
            this->typeMove = 4;
            this->displayListModel = textures[3];
            this->owner = 0;
            this->hp = 1;
            this->damage = 1;
            this->defaultFireRate = 230;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(4, 4);
            this->setMin(-4, -4);
            this->setResize(0.5);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(1.1,1.1);
            this->continueMove = 0;
            break;

        case 6: //tiro sniper
            this->typeMove = 3;
            this->displayListModel = textures[4];
            this->owner = 0; 
            this->hp = 1;
            this->damage = 1;
            this->defaultFireRate = 140;
            this->onScreen = GL_TRUE;
            this->angle = 0;
            this->angularSpeed = 0;
            this->setMax(1, 10);
            this->setMin(-1, -10);
            this->setResize(1);
            this->setHitbox();
            this->setMidPoint();
            this->setVelocity(3.7, 3.7);
            break;
    }    
}

void Projectile::straightMove()
{
    this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
}

void Projectile::bouncyMove()
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
}

void Projectile::folllowMove()
{
    double angle = atan2(followedEnemy->getMidPoint().getY() - this->midPoint.getY(),
                         followedEnemy->getMidPoint().getX() - this->midPoint.getX());

    this->angle = radianoParaGraus(angle)-90;

    this->midPoint.setX(this->midPoint.getX() + cos(angle) * this->velocity.getX());
    this->midPoint.setY(this->midPoint.getY() + sin(angle) * this->velocity.getY());
}

void Projectile::followPlayerMove()
{
    if(continueMove < 70)
    {
        double angle = atan2(followedEnemy->getMidPoint().getY() - this->midPoint.getY(),
                         followedEnemy->getMidPoint().getX() - this->midPoint.getX());

        this->angle = radianoParaGraus(angle)-90;

        this->midPoint.setX(this->midPoint.getX() + cos(angle) * this->velocity.getX());
        this->midPoint.setY(this->midPoint.getY() + sin(angle) * this->velocity.getY());
        continueMove++;
    }
    else
    {
        this->midPoint.setX(this->midPoint.getX() + cos(grausParaRadianos(this->angle) + M_PI/2) * this->velocity.getX() * 1.7);
        this->midPoint.setY(this->midPoint.getY() + sin(grausParaRadianos(this->angle) + M_PI/2) * this->velocity.getY() * 1.7);
    }
}

void Projectile::angularShooting()
{
    this->midPoint.setX(this->midPoint.getX() + cos(grausParaRadianos(this->angle) + M_PI/2) * this->velocity.getX());
    this->midPoint.setY(this->midPoint.getY() + sin(grausParaRadianos(this->angle) + M_PI/2) * this->velocity.getY());
}

void Projectile::move() //movimentação geral do projectile
{
    switch (this->typeMove)
    {
    case 0:
        straightMove();
        break;
    
    case 1:
        bouncyMove();
        break;

    case 2:
        folllowMove();     
        break;

    case 3:
        angularShooting();
        break;

    case 4:
        followPlayerMove();
        break;

    case 5:
        this->midPoint.setY(this->midPoint.getY() - this->velocity.getY());
        break;
    }
    verifyVisibility(*this);
    this->generalHitBoxMovement();
}
void Projectile::scaleMove(const double& scale){}
