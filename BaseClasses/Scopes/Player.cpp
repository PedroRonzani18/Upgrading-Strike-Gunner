#include "../Header/Player.h"
#include "../../GeneralFiles/Header/globalParameters.h"
#include "../../GeneralFiles/Header/drawings.h"
#include "../../GeneralFiles/Header/colisionManager.h"
#include <iostream>

std::map<std::string,std::vector<float>> Player::playerDataMap;


Player::Player():
    MovableEntity
    (
        OrderedPair(playerDataMap["velocity"][0], playerDataMap["velocity"][1]),   
        playerDataMap["angle"][0],
        playerDataMap["angularSpeed"][0],
        playerDataMap["hp"][0],
        playerDataMap["type"][0],
        playerDataMap["typeMove"][0],
        textures[playerDataMap["displayListModel"][0]],  
        GL_TRUE,  
        OrderedPair(playerDataMap["dimensions"][0], playerDataMap["dimensions"][1]),  
        OrderedPair(playerDataMap["dimensions"][2], playerDataMap["dimensions"][3]),   
        playerDataMap["resize"][0]
    ),
    Ballistic
    (
        Projectile(playerDataMap["currentProjectile"][0]),
        playerDataMap["numberOfShots"][0],
        playerDataMap["typeTiroManager"][0],
        playerDataMap["fireRatePeriod"][0],
        playerDataMap["alteredFireRate"][0]
    ),
    imortality(0),
    scoreHp(Score(1))
    {
        setResize(playerDataMap["resize"][0]);
        setHitbox();
        setMidPoint();
    }


/*
Player::Player():
    MovableEntity
    (
        OrderedPair(playerDataMap["velocity"][0], playerDataMap["velocity"][1]), 
        0, 0, 3, 0, 0,textures[14], GL_TRUE, OrderedPair(20,20), OrderedPair(-20,-20), 0.5
    ),
    Ballistic(Projectile(0), 3, 0, 0, 0.2),
    imortality(0),
    scoreHp(Score(1))
{
    this->setResize(0.5);
    this->setHitbox();
    this->setMidPoint();
}
*/

//Player::Player() : MovableEntity(), Ballistic()
//{
//    this->type = 0;
//    this->alteredFireRate = 0.2;
//    this->angle = 0;
//    this->angularSpeed = 0;
//    this->currentProjectile = Projectile(0);
//    this->typeTiroManager = 0;
//    this->displayListModel = textures[14];
//    this->numberOfShots = 3;
//    this->onScreen = GL_TRUE;
//    this->imortality = 0;
//    this->hp = 3;
//    this->fireRatePeriod = 0;
//    this->scoreHp = Score(1);
//
//    this->setMax(20,20);
//    this->setMin(-20,-20);
//    this->setResize(0.5);
//    this->setHitbox();
//    this->setMidPoint();
//    this->setVelocity(2,2);   
//
//    std::cout << this->typeMove << std::endl;
//}


void Player::move()
{   
    if(this->hp > -1){
        this->setMidPoint(this->midPoint.x + (keys[2] - keys[3]) * (this->velocity.x),
                          this->midPoint.y + (keys[0] - keys[1]) * (this->velocity.y));
        mantainInsideScreen(*this);
        generalHitBoxMovement();
    }
}

void Player::damage()
{
    this->currentProjectile = Projectile(0);
    this->typeTiroManager = 0;
    this->alteredFireRate = 1;
    this->numberOfShots = 1;

    this->currentProjectile.setHp(1);
    this->imortality = 120;
    
}

void Player::setHp(const double& hp)
{
    this->hp = hp;
    this->scoreHp.setScore(hp);
}

void Player::scaleMove(const double& scale){}

void Player::deathMove()
{
    this->angle += 5;
    this->resize -= 0.002;    

    glPushMatrix();
        glTranslatef(this->getMidPoint().x,
                     this->getMidPoint().y,
                    0);
        glRotatef(this->getAngle(), 0, 0, 1);
        glScalef(this->getResize(), this->getResize(), 1);
        glCallList(this->getDisplayListModel());
    glPopMatrix();   
}

Projectile Player::createProject(Projectile& auxP, const double& angle)
{
    auxP.setMidPoint(this->max.x * cos(this->angle +  angle) + this->midPoint.x,
                     this->max.y * sin(this->angle +  angle) + this->midPoint.y);
    return auxP;
}

std::vector<Projectile> Player::fire()
{
    Projectile projectile1 = this->currentProjectile;

    projectile1.setOwner(1);

    std::vector<Projectile> vec;

    switch (this->typeTiroManager)
    {
        case 0: // tiro reto
            switch(numberOfShots)
            {
                case 3:
                    vec.push_back(createProject(projectile1, M_PI/2));
                    
                case 2:
                    vec.push_back(createProject(projectile1, M_PI/4));
                    vec.push_back(createProject(projectile1, 3*M_PI/4));
                    break;

                case 1:
                    vec.push_back(createProject(projectile1, M_PI/2));
                    break;
            }
            break;
        
        case 1: // tiro que bate nas paredes
            switch(numberOfShots)
            {
                case 1:
                    projectile1.setHp(2);
                    break;
                case 2:
                    projectile1.setHp(3);
                    break;
                case 3:
                    projectile1.setHp(4);
                    break;
            }
            vec.push_back(createProject(projectile1, M_PI/4));

            projectile1.getVelocity().x = -projectile1.getVelocity().x;
            vec.push_back(createProject(projectile1, 3*M_PI/4));

            break;
        
        case 2: // tiro que segue
            switch (numberOfShots)
            {
            case 1:
                vec.push_back(createProject(projectile1,   M_PI/2));
                break;
            case 2:
                vec.push_back(createProject(projectile1,   M_PI/4));
                vec.push_back(createProject(projectile1, 3*M_PI/4));
                break;
            case 3:
                vec.push_back(createProject(projectile1, 0));
                vec.push_back(createProject(projectile1,   M_PI/2));
                vec.push_back(createProject(projectile1,   M_PI));
                break;
            }
            break;
    }

    this->fireRatePeriod = this->currentProjectile.getDefaultFireRate() * this->alteredFireRate;
    return vec;
}

void Player::upgradeManager(const int& upgradeType)
{
    Projectile* u;
    switch (upgradeType)
    {
        case 1: //type 1: aumenta o tanto de tiro 
            if(this->numberOfShots < 3)
                this->numberOfShots += 1;
            break;
        
        case 2: //type 2: aumeta o fireRate
            this->alteredFireRate /= 1.19;
            break;

        case 3: //type 3: troca de projetil
            this->typeTiroManager ++;
            if(this->typeTiroManager == 3)
                this->typeTiroManager = 0;
            u = new Projectile(typeTiroManager);
            this->currentProjectile = *u;
            break;

        case 4: //type 4: aumenta vida
            if(this->hp < 3)
                this->setHp(this->getHp() + 1);
            break;

        case 5:  //type 5: aumenta o dano
            if((currentProjectile.getType() == 0 && currentProjectile.getDamage() < 3) ||
               (currentProjectile.getType() == 1 && currentProjectile.getDamage() < 4) ||
               (currentProjectile.getType() == 2 && currentProjectile.getDamage() < 5))
                this->currentProjectile.setDamage(this->currentProjectile.getDamage() + 0.5);
            break;
    }
}
