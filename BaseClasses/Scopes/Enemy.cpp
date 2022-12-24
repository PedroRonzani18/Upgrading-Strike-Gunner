#include "../Header/Enemy.h"
#include "../../GeneralFiles/Header/globalParameters.h"

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)

Enemy::Enemy(int type, int typeMove, int numberOfShots, int typeTiroManager, double vx, double vy): Enemy(type) // função com template de enemy
{
    setTypeMove(typeMove);
    setNumberOfShots(numberOfShots);
    setTypeTiroManager(typeTiroManager);
    setVelocity(vx, vy);
}

Enemy::Enemy(int type) : MovableEntity()
{
    srand(time(0));
    this->type = type;
    this->onScreen = GL_TRUE;
    contador = 0;

    switch (this->type)
    {
    case 0: // kamikaze
        this->dropPercentage = 15;
        this->killValue = 55;
        this->angle = 180;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeMove = 0;
        this->typeTiroManager = 0; // determina tipo do tiro
        this->numberOfShots = 0;
        this->hp = 4;
        this->onscreenTestable = GL_FALSE;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->alteredFireRate = 0;
        this->setDisplayListModel(textures[11]);
        this->setMax(20, 20);
        this->setMin(-20, -20);
        this->setVelocity(1, 1);
        this->setResize(0.5);
        break;

    case 1: // sniper
        this->dropPercentage = 90;
        this->killValue = 222;
        this->angle = 180;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(6);
        this->typeTiroManager = 1;
        this->typeMove = 0;
        this->numberOfShots = 0;
        this->hp = 55;
        this->onscreenTestable = GL_FALSE;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->alteredFireRate = 0.4;
        this->setDisplayListModel(textures[13]);
        this->setMax(20, 20);
        this->setMin(-20, -20);
        this->setVelocity(0, 0);
        this->setResize(0.5);
        break;

    case 2: // nave que atira missel que segue
        this->dropPercentage = 8;
        this->killValue = 33;
        this->angle = 180;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(5);
        this->typeMove = 4;
        this->typeTiroManager = 1;
        this->numberOfShots = 0;
        this->hp = 1;
        this->onscreenTestable = GL_FALSE;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->alteredFireRate = 1.20;
        this->setDisplayListModel(textures[27]);
        this->setMax(15, 15);
        this->setMin(-15, -15);
        this->setVelocity(0.5, 1);
        this->setResize(0.5);
        break;

    case 3: // nave raio laser vermelho pequena 1/2
        this->dropPercentage = 6;
        this->killValue = 22;
        this->angle = 180;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 1;
        this->numberOfShots = 0;
        this->hp = 1;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->alteredFireRate = 1.20;
        this->setDisplayListModel(textures[28]);
        this->setMax(20, 20);
        this->setMin(-20, -20);
        this->setVelocity(0.5, 1);
        this->setResize(0.36);
        break;

    case 4: // tank
        this->dropPercentage = 90;
        this->killValue = 444;
        this->angle = 180;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(4);
        this->typeTiroManager = 1;
        this->numberOfShots = 0;
        this->hp = 70;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->alteredFireRate = 1;
        this->setDisplayListModel(textures[29]);
        this->setMax(20, 20);
        this->setMin(-20, -20);
        this->setVelocity(0.5, 1);
        this->setResize(0.9);
        break;

    case 5: // torreta que estará sobre o png de asteroide
        this->dropPercentage = 50;
        this->killValue = 111;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 1; /**/
        this->numberOfShots = 0;   // inutilizzadp
        this->hp = 45;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4; /**/
        this->continueMove = 0;
        this->fireRatePeriod = 0; // tem que ser 0
        this->alteredFireRate = 0.3;
        this->setDisplayListModel(textures[33]);
        this->setMax(24, 24);
        this->setMin(-24, -24);
        this->setVelocity(1, 1); // deixar padrao no cosntrutor e talvez mmudar na wave
        this->setResize(0.5);
        break;

    case 6: // asteroide
        this->dropPercentage = 25;
        this->killValue = 88;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 3;
        this->numberOfShots = 0;
        this->hp = 20;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->setDisplayListModel(textures[32]);
        this->setMax(17, 17);
        this->setMin(-17, -17);
        this->setVelocity(0.5, 1);
        this->setResize(0.5);
        break;

    case 7: // boss
        this->dropPercentage = 100;
        this->killValue = 10000;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 0;
        this->numberOfShots = 0;
        this->hp = 1000;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 0;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->setDisplayListModel(textures[41]);
        this->setMax(50, 50);
        this->setMin(-50, -50); // só será ilustrativo
        this->setVelocity(0, 0);
        this->setResize(0.1);
        break;

    case 8: // barra de vida
        this->dropPercentage = 5;
        this->killValue = 10;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 3;
        this->numberOfShots = 0;
        this->hp = 15;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4;
        this->continueMove = 0;
        this->fireRatePeriod = 0;
        this->setDisplayListModel(textures[32]);
        this->setMax(0, 0);
        this->setMin(0, 0); // só será ilustrativo
        this->setVelocity(0.5, 1);
        this->setResize(0.5);
        break;

    case 9: // torreta boss grossa
        this->dropPercentage = 100;
        this->killValue = 777;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(5);
        this->typeTiroManager = 2;
        this->numberOfShots = 1;
        this->hp = 100;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = -1;
        this->continueMove = 0;
        this->fireRatePeriod = 0; // tem que ser 0
        this->alteredFireRate = 0.7;
        this->setDisplayListModel(textures[50]);
        this->setMax(40, 15);
        this->setMin(-20, -18);
        this->setVelocity(1, 1); // deixar padrao no cosntrutor e talvez mmudar na wave
        this->setResize(0.5);
        break;

    case 11: // torreta tripla
        this->dropPercentage = 100;
        this->killValue = 666;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(3);
        this->typeTiroManager = 0;
        this->numberOfShots = 3;
        this->hp = 150;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = -1;
        this->continueMove = 0;
        this->fireRatePeriod = 0; // tem que ser 0
        this->alteredFireRate = 0.6;
        this->setDisplayListModel(textures[43]);
        this->setMax(23, 13);
        this->setMin(-23, -13);
        this->setVelocity(1, 1); // deixar padrao no cosntrutor e talvez mmudar na wave
        this->setResize(0.5);
        break;

    case 12: // torreta tripla grande
        this->dropPercentage = 100;
        this->killValue = 999;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(4);
        this->typeTiroManager = 4;
        this->numberOfShots = 3;
        this->hp = 250;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = -1;
        this->continueMove = 0;
        this->fireRatePeriod = 0; // tem que ser 0
        this->alteredFireRate = 1;
        this->setDisplayListModel(textures[53]);
        this->setMax(29, 17);
        this->setMin(-29, -17);
        this->setVelocity(1, 1); // deixar padrao no cosntrutor e talvez mmudar na wave
        this->setResize(0.5);
        break;

    case 10: // mensagem
        this->dropPercentage = 15;
        this->killValue = 10;
        this->angle = 0;
        this->angularSpeed = 0;
        this->currentProjectile = Projectile(5);
        this->typeTiroManager = 1; /**/
        this->numberOfShots = 0;   // inutilizzadp
        this->hp = 22;
        this->onscreenTestable = GL_FALSE;
        this->typeMove = 4; /**/
        this->continueMove = 0;
        this->fireRatePeriod = 0; // tem que ser 0
        this->alteredFireRate = 0.3;
        this->setDisplayListModel(textures[45]);
        this->setMax(24, 24);
        this->setMin(-24, -24);
        this->setVelocity(1, 1); // deixar padrao no cosntrutor e talvez mmudar na wave
        this->setResize(0.5);
        break;
    }
    this->setHitbox();
    this->setMidPoint();
}

Projectile Enemy::createProject(Projectile *auxP, double angle)
{
    auxP->setMidPoint(this->max.getX() * cos(grausParaRadianos(this->angle) + angle) + this->midPoint.getX(),
                      this->max.getY() * sin(grausParaRadianos(this->angle) + angle) + this->midPoint.getY());
    return *auxP;
}

void Enemy::parabolicMoveTemplateFy(double a, double b, double c)
{
    this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
    this->midPoint.setX(a * pow(this->midPoint.getY(), 2) + b * this->midPoint.getY() + c);
}

void Enemy::parabolicMoveTemplateFx(double a, double b, double c)
{
    this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
    this->midPoint.setY(a * pow(this->midPoint.getX(), 2) + b * this->midPoint.getX() + c);
}

void Enemy::senoidMoveTemplateFy(double a, double b, double c, double d)
{
    this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
    this->midPoint.setX(a + b * sin(c * this->midPoint.getY() + d));
}

void Enemy::senoidMoveTemplateFx(double a, double b, double c, double d)
{
    this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
    this->midPoint.setY(a + b * sin(c * this->midPoint.getX() + d));
}

void Enemy::kamikazeMove()
{
    if (continueMove < 190)
    {
        aim(90);

        this->midPoint.setX(this->midPoint.getX() + cos(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.getX());
        this->midPoint.setY(this->midPoint.getY() + sin(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.getY());

        this->continueMove++;
    }
    else
    {
        this->midPoint.setX(this->midPoint.getX() + cos(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.getX() * 3);
        this->midPoint.setY(this->midPoint.getY() + sin(grausParaRadianos(this->angle) + M_PI / 2) * this->velocity.getY() * 3);
    }
}

void Enemy::aim(double auxAngle) // mira  a frente do inimigo na direção do player
{
    double angle = atan2(this->followPoint.getY() - this->midPoint.getY(),
                         this->followPoint.getX() - this->midPoint.getX());

    this->angle = radianoParaGraus(angle) - auxAngle;
}

void Enemy::elipsoidMoveNoEntrance(double a, double b, double yo)
{
    if ((-a <= this->midPoint.getX()) && (this->midPoint.getX() <= a))
    {
        if (this->midPoint.getY() > yo)
            this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());

        if (this->midPoint.getY() < yo)
            this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());

        if (this->midPoint.getY() == yo)
        {
            if (this->midPoint.getX() < 0)
            {
                this->midPoint.setY(this->midPoint.getY() - this->velocity.getY());
                this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
            }
            if (this->midPoint.getX() > 0)
            {
                this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
                this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());
            }
        }

        if (this->midPoint.getY() > yo)
            this->midPoint.setY((sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.getX(), 2) / pow(a, 2))) + yo);
        if (this->midPoint.getY() < yo)
            // this->midPoint.setY(-(sqrt(pow(b,2) - pow(b,2) *pow(this->midPoint.getX(), 2)/pow(a,2))));
            this->midPoint.setY(-(sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.getX(), 2) / pow(a, 2))) + yo);
    }
}

void Enemy::elipsoidMove(double a, double b, double yo)
{
    if (this->midPoint.getX() > a)
        this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());

    if ((-a <= this->midPoint.getX()) && (this->midPoint.getX() <= a))
    {
        if (this->midPoint.getY() > yo)
            this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());

        if (this->midPoint.getY() < yo)
            this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());

        if (this->midPoint.getY() == yo)
        {
            if (this->midPoint.getX() < 0)
            {
                this->midPoint.setY(this->midPoint.getY() - this->velocity.getY());
                this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
            }
            if (this->midPoint.getX() > 0)
            {
                this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
                this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());
            }
        }

        if (this->midPoint.getY() > yo)
            this->midPoint.setY((sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.getX(), 2) / pow(a, 2))) + yo);
        if (this->midPoint.getY() < yo)
            // this->midPoint.setY(-(sqrt(pow(b,2) - pow(b,2) *pow(this->midPoint.getX(), 2)/pow(a,2))));
            this->midPoint.setY(-(sqrt(pow(b, 2) - pow(b, 2) * pow(this->midPoint.getX(), 2) / pow(a, 2))) + yo);
    }
}

void Enemy::bateVolta(const int &posY)
{
    if (this->midPoint.getY() > posY)
    {
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
    }
    else
    {
        if (this->onscreenTestable)
            if (this->midPoint.getX() + this->min.getX() < -90 || this->midPoint.getX() + this->max.getX() > 90)
                this->velocity.setX(this->velocity.getX() * (-1));

        this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
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
            if (this->midPoint.getX() + this->min.getX() < -90 || this->midPoint.getX() + this->max.getX() > 90)
                this->velocity.setX(this->velocity.getX() * (-1));

        this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
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
        if (this->midPoint.getX() > 80)
            this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());
        else
        {
            elipsoidMoveNoEntrance(80 - contador, 80 - contador, 0);
            contador += 0.0001;
        }
        break;

    case 8: // funcao de terceiro com 2 de segundo
        aim(90);
        if (this->midPoint.getY() >= 60)
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
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        if (this->onscreenTestable)
            this->velocity.setY(this->velocity.getY() - 0.06);
        break;

    case 13:
        kamikazeMove();
        break;

    case 14:
        if (this->midPoint.getX() < this->followPoint.getX() + this->velocity.getX() && this->midPoint.getX() > this->followPoint.getX() - this->velocity.getX())
            this->midPoint.setX(this->followPoint.getX());

        if (this->midPoint.getX() > this->followPoint.getX())
            this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());

        else if (this->midPoint.getX() < this->followPoint.getX())
            this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());

        if (this->midPoint.getY() + this->max.getY() > 90)
            this->velocity.setY(-abs(this->velocity.getY()));

        else if (this->midPoint.getY() + this->min.getY() < 22)
            this->velocity.setY(abs(this->velocity.getY()));

        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        break;

    case 15:
        bateVolta(0);
        break;

    case 16:
        aim(0);
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        break;

    case 17:
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
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
            this->midPoint.setX(this->midPoint.getX() + this->velocity.getX());
            if (this->midPoint.getX() >= 150)
            {
                this->midPoint.setY(50);
                continueMove = 1;
            }
        }
        if(continueMove == 1)
        {
            this->midPoint.setX(this->midPoint.getX() - this->velocity.getX());
            if (this->midPoint.getX() <= -150)
            {
                this->midPoint.setY(-200);
                this->midPoint.setX(0);
                continueMove = 2;
            }
        }
        if(continueMove == 2)
        {
            this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        }
        
        if (this->resize < 1)
            this->resize = this->resize + 0.001;
        if (this->midPoint.getY() > 200)
        {
            this->onScreen = false;
        }
        break;

    case 25:
        this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        break;

    case 26:
        if (this->midPoint.getY() < -50)
            this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());
        
        continueMove++;
        if(continueMove >= 550)
            this->hp = 0;
        break;

    case 27:
        if (this->midPoint.getY() < 25)
            this->midPoint.setY(this->midPoint.getY() + this->velocity.getY());

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