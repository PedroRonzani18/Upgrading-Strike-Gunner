#include "../Header/Enemy.h"
#include "../../GeneralFiles/Header/globalParameters.h"
#include <time.h>
#include <iostream>

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)

std::map<std::string,std::vector<float>> Enemy::enemyDataMap;

Enemy::Enemy(const int& type, const int& typeMove, const int& numberOfShots, const int& typeTiroManager, const double& vx, const double& vy):

    MovableEntity
        (
        //OrderedPair(enemyDataMap["velocity"][2*type], enemyDataMap["velocity"][2*type+1]),
        OrderedPair(vx, vy), 
        enemyDataMap["angle"][type], 
        enemyDataMap["angularSpeed"][type], 
        enemyDataMap["hp"][type], 
        type, 
        typeMove,
        textures[enemyDataMap["displayListModel"][type]], 
        GL_TRUE, 
        OrderedPair(enemyDataMap["dimensions"][4*type], 
        enemyDataMap["dimensions"][4*type +1]), 
        OrderedPair(enemyDataMap["dimensions"][4*type +2], 
        enemyDataMap["dimensions"][4*type +3]), 
        enemyDataMap["resize"][type]
        ),

    Ballistic
        (
        Projectile(enemyDataMap["currentProjectile"][type]),
        numberOfShots,
        typeTiroManager, 
        0,
        enemyDataMap["alteredFireRate"][type]
        ),
    
    killValue(enemyDataMap["killValue"][type]),
    dropPercentage(enemyDataMap["dropPercentage"][type]),
    onscreenTestable(GL_FALSE),
    followPoint(OrderedPair()),
    continueMove(0)
{
    srand(time(0));
    setResize(enemyDataMap["resize"][type]);    
    this->type = type;
    this->onScreen = GL_TRUE;
    contador = 0;
    this->setHitbox();
    this->setMidPoint();
}

Projectile Enemy::createProject(Projectile *auxP, const double& angle)
{
    auxP->setMidPoint(this->max.x * cos(grausParaRadianos(this->angle) + angle) + this->midPoint.x,
                      this->max.y * sin(grausParaRadianos(this->angle) + angle) + this->midPoint.y);
    return *auxP;
}

void Enemy::parabolicMoveTemplateFy(const double& a, const double& b, const double& c)
{
    this->midPoint.y = (this->midPoint.y + this->velocity.y);
    this->midPoint.x = (a * pow(this->midPoint.y, 2) + b * this->midPoint.y + c);
}

void Enemy::parabolicMoveTemplateFx(const double& a, const double& b, const double& c)
{
    this->midPoint.x = (this->midPoint.x + this->velocity.x);
    this->midPoint.y = (a * pow(this->midPoint.x, 2) + b * this->midPoint.x + c);
}

void Enemy::senoidMoveTemplateFy(const double& a, const double& b, const double& c, const double& d)
{
    this->midPoint.y = (this->midPoint.y + this->velocity.y);
    this->midPoint.x = (a + b * sin(c * this->midPoint.y + d));
}

void Enemy::senoidMoveTemplateFx(const double& a, const double& b, const double& c, const double& d)
{
    this->midPoint.x = (this->midPoint.x + this->velocity.x);
    this->midPoint.y = (a + b * sin(c * this->midPoint.x + d));
}

void Enemy::kamikazeMove()
{
    if (continueMove < 190)
    {
        aim(90);

        this->midPoint.x = (this->midPoint.x + cos(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.x);
        this->midPoint.y = (this->midPoint.y + sin(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.y);

        this->continueMove++;
    }
    else
    {
        this->midPoint.x = (this->midPoint.x + cos(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.x * 3);
        this->midPoint.y = (this->midPoint.y + sin(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.y * 3);
    }
}

void Enemy::aim(const double& auxAngle) // mira  a frente do inimigo na direção do player
{
    const double& angle = atan2(this->followPoint.y - this->midPoint.y,
                         this->followPoint.x - this->midPoint.x);

    this->angle = radianoParaGraus(angle) - auxAngle;
}

void Enemy::elipsoidMoveNoEntrance(const double& a, const double& b, const double& yo)
{
    if ((-a <= this->midPoint.x) && (this->midPoint.x <= a))
    {
        if (this->midPoint.y > yo)
            this->midPoint.x = (this->midPoint.x - this->velocity.x);

        if (this->midPoint.y < yo)
            this->midPoint.x = (this->midPoint.x + this->velocity.x);

        if (this->midPoint.y == yo)
        {
            if (this->midPoint.x < 0)
            {
                this->midPoint.y = (this->midPoint.y - this->velocity.y);
                this->midPoint.x = (this->midPoint.x + this->velocity.x);
            }
            if (this->midPoint.x > 0)
            {
                this->midPoint.y = (this->midPoint.y + this->velocity.y);
                this->midPoint.x = (this->midPoint.x - this->velocity.x);
            }
        }

        if (this->midPoint.y > yo)
            this->midPoint.y = ((sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.x, 2) / pow(a, 2))) + yo);
        if (this->midPoint.y < yo)
            // this->midPoint.y = (-(sqrt(pow(b,2) - pow(b,2) *pow(this->midPoint.x, 2)/pow(a,2))));
            this->midPoint.y = (-(sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.x, 2) / pow(a, 2))) + yo);
    }
}

void Enemy::elipsoidMove(const double& a, const double& b, const double& yo)
{
    if (this->midPoint.x > a)
        this->midPoint.x = (this->midPoint.x - this->velocity.x);

    if ((-a <= this->midPoint.x) && (this->midPoint.x <= a))
    {
        if (this->midPoint.y > yo)
            this->midPoint.x = (this->midPoint.x - this->velocity.x);

        if (this->midPoint.y < yo)
            this->midPoint.x = (this->midPoint.x + this->velocity.x);

        if (this->midPoint.y == yo)
        {
            if (this->midPoint.x < 0)
            {
                this->midPoint.y = (this->midPoint.y - this->velocity.y);
                this->midPoint.x = (this->midPoint.x + this->velocity.x);
            }
            if (this->midPoint.x > 0)
            {
                this->midPoint.y = (this->midPoint.y + this->velocity.y);
                this->midPoint.x = (this->midPoint.x - this->velocity.x);
            }
        }

        if (this->midPoint.y > yo)
            this->midPoint.y = ((sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.x, 2) / pow(a, 2))) + yo);
        if (this->midPoint.y < yo)
            // this->midPoint.y = (-(sqrt(pow(b,2) - pow(b,2) *pow(this->midPoint.x, 2)/pow(a,2))));
            this->midPoint.y = (-(sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.x, 2) / pow(a, 2))) + yo);
    }
}

void Enemy::bateVolta(const int &posY)
{
    if (this->midPoint.y > posY)
    {
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
    }
    else
    {
        if (this->onscreenTestable)
            if (this->midPoint.x + this->min.x < -90 || this->midPoint.x + this->max.x > 90)
                this->velocity.x = (this->velocity.x * (-1));

        this->midPoint.x = (this->midPoint.x + this->velocity.x);
    }
}

void Enemy::move()
{
    switch (this->typeMove)
    {
    case -2:
        aim(-90);
        break;

    case -1:
        aim(0);
        break;

    case 0: // nao anda
        break;

    case 1: // Parabola (direita: Vx > 0 | esquerda: Vx < 0)
        aim(90);
        parabolicMoveTemplateFx(-1.0 / 81, 0, 0);
        break;

    case 2: // rebate nas paredes
        aim(90);

        if (this->onscreenTestable)
            if (this->midPoint.x + this->min.x < -90 || this->midPoint.x + this->max.x > 90)
                this->velocity.x = (this->velocity.x * (-1));

        this->midPoint.x = (this->midPoint.x + this->velocity.x);
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        break;

    case 3: // parabola  y = x²
        aim(90);
        parabolicMoveTemplateFy(-9.0 / 160, 9.0 / 2, -90);
        break;

    case 4: // parabola  y = x²
        aim(90);
        parabolicMoveTemplateFy(9.0 / 160, -9, 360);
        break;

    case 5: // parabola  y = x²
        aim(90);
        parabolicMoveTemplateFy(9.0 / 160, 0, 0);
        break;

    case 6: // parabola alta
        aim(90);
        parabolicMoveTemplateFx(-17.0 / 810, 0, 70);
        break;

    case 7:
        aim(90);
        if (this->midPoint.x > 80)
            this->midPoint.x = (this->midPoint.x - this->velocity.x);
        else
        {
            elipsoidMoveNoEntrance(80 - contador, 80 - contador, 0);
            contador += 0.0001;
        }
        break;

    case 8: // funcao de terceiro com 2 de segundo
        aim(90);
        if (this->midPoint.y >= 60)
            parabolicMoveTemplateFy(9.0 / 160, -27.0 / 4, 405.0 / 2);
        else
            parabolicMoveTemplateFy(-9.0 / 160, 27.0 / 4, -405.0 / 2);
        break;

    case 9: // tank eleptico
        elipsoidMove(80, 15, 0);
        break;

    case 10: // tank bate e volta na horizontal
        bateVolta(50);
        break;

    case 11:
        elipsoidMove(80, 40, 45);
        break;

    case 12:
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        if (this->onscreenTestable)
            this->velocity.y = (this->velocity.y - 0.06);
        break;

    case 13:
        kamikazeMove();
        break;

    case 14:
        if (this->midPoint.x < this->followPoint.x + this->velocity.x && this->midPoint.x > this->followPoint.x - this->velocity.x)
            this->midPoint.x = (this->followPoint.x);

        if (this->midPoint.x > this->followPoint.x)
            this->midPoint.x = (this->midPoint.x - this->velocity.x);

        else if (this->midPoint.x < this->followPoint.x)
            this->midPoint.x = (this->midPoint.x + this->velocity.x);

        if (this->midPoint.y + this->max.y > 90)
            this->velocity.y = (-abs(this->velocity.y));

        else if (this->midPoint.y + this->min.y < 22)
            this->velocity.y = (abs(this->velocity.y));

        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        break;

    case 15:
        bateVolta(0);
        break;

    case 16:
        aim(0);
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        break;

    case 17:
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        break;

    case 18:
        aim(0);
        elipsoidMove(80, 40, 45);
        break;

    case 19:
        aim(90);
        elipsoidMove(80, 50, 20);
        break;

    case 24: // boss
        if (continueMove == 0)
        {
            this->midPoint.x = (this->midPoint.x + this->velocity.x);
            if (this->midPoint.x >= 150)
            {
                this->midPoint.y = (50);
                continueMove = 1;
            }
        }
        if(continueMove == 1)
        {
            this->midPoint.x = (this->midPoint.x - this->velocity.x);
            if (this->midPoint.x <= -150)
            {
                this->midPoint.y = (-200);
                this->midPoint.x = (0);
                continueMove = 2;
            }
        }
        if(continueMove == 2)
        {
            this->midPoint.y = (this->midPoint.y + this->velocity.y);
        }
        
        if (this->resize < 1)
            this->resize = this->resize + 0.001;
        if (this->midPoint.y > 200)
        {
            this->onScreen = false;
        }
        break;

    case 25:
        this->midPoint.y = (this->midPoint.y + this->velocity.y);
        break;

    case 26:
        if (this->midPoint.y < -50)
            this->midPoint.y = (this->midPoint.y + this->velocity.y);
        
        continueMove++;
        if(continueMove >= 550)
            this->hp = 0;
        break;

    case 27:
        if (this->midPoint.y < 25)
            this->midPoint.y = (this->midPoint.y + this->velocity.y);

        continueMove++;
        if(continueMove >= 550)
            this->hp = 0;
        break;
    }

    if (this->type != 9 && this->type != 11 && this->type != 12 && this->type != 7)
        verifyVisibility(*this);

    if (this->onScreen)
        this->onscreenTestable = 1;

    generalHitBoxMovement();
}

void Enemy::scaleMove(const double &scale) {}

std::vector<Projectile> Enemy::fire()
{
    Projectile projectile1 = this->currentProjectile;

    projectile1.setAngle(angle);

    projectile1.setOwner(2);

    std::vector<Projectile> vec;

    switch (this->typeTiroManager)
    {
    case 0: // tiro que sai na direcao do player
        switch (numberOfShots)
        {
        case 1: // tiro da torreta
            projectile1.setAngle(angle - 90);
            vec.push_back(createProject(&projectile1, 0));
            break;

        case 2: // tiro da nave simples
            vec.push_back(createProject(&projectile1, M_PI/2));
            break;

        case 3: // tiro da nave simples
            projectile1.setAngle(angle + 180);
            vec.push_back(createProject(&projectile1, -M_PI / 4));
            vec.push_back(createProject(&projectile1, -M_PI / 2));
            vec.push_back(createProject(&projectile1, -3 * M_PI / 4));
            break;
        }
        break;
    case 1: // tiro simples que espalha (tank)
        switch (numberOfShots)
        {
        case 3:
            projectile1.setAngle(angle - 32);
            vec.push_back(createProject(&projectile1, 0));

            projectile1.setAngle(angle);
            vec.push_back(createProject(&projectile1, M_PI / 2));

            projectile1.setAngle(angle + 32);
            vec.push_back(createProject(&projectile1, M_PI));
            break;

        case 5:
            projectile1.setAngle(angle - 50);
            vec.push_back(createProject(&projectile1, 0));

            projectile1.setAngle(angle - 25);
            vec.push_back(createProject(&projectile1, M_PI / 4));

            projectile1.setAngle(angle);
            vec.push_back(createProject(&projectile1, M_PI / 2));

            projectile1.setAngle(angle + 25);
            vec.push_back(createProject(&projectile1, 3 * M_PI / 4));

            projectile1.setAngle(angle + 50);
            vec.push_back(createProject(&projectile1, M_PI));
            break;
        }
        break;

    case 2: // tiro que segue
        switch (numberOfShots)
        {
        case 1:
            vec.push_back(createProject(&projectile1, M_PI / 2));
            break;

        case 2:
            vec.push_back(createProject(&projectile1, 0));
            break;
        }
        break;

    case 3: // tiro do sniper
        switch (numberOfShots)
        {
        case 1:
            projectile1.setAngle(this->angle);
            vec.push_back(createProject(&projectile1, M_PI / 2));
            break;
        }
        break;

    case 4: // tiro que espalha do boss
        switch (numberOfShots)
        {
        case 3:
            projectile1.setAngle(angle + 212);
            vec.push_back(createProject(&projectile1, -M_PI / 4));

            projectile1.setAngle(angle + 180);
            vec.push_back(createProject(&projectile1, -M_PI / 2));

            projectile1.setAngle(angle + 148);
            vec.push_back(createProject(&projectile1, -3 * M_PI / 4));
            break;
        }
        break;
    }

    double r = 1 + rand() % 20;

    this->fireRatePeriod = (this->currentProjectile.getDefaultFireRate() * this->alteredFireRate) * (1 + 2 * r / 20);

    return vec;
}