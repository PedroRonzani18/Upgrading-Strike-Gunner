#include "../Header/Boss.h"

Boss::Boss()
{
    this->dropPercentage = 100;
    this->killValue = 1000;
    this->angle = 0;
    this->angularSpeed = 0;
    this->hp = 0;
    this->onscreenTestable = GL_FALSE;
    this->continueMove = 0;
    this->setDisplayListModel(textures[41]);
    this->setMax(24, 24);
    this->setMin(-24, -24);
    this->setVelocity(0.5, 0.5); 
    this->setResize(1);

    this->healthBar = Score(2);
    this->healthBar.setScore(0);
    this->vidaTotal = 750;


    this->midPoint.setX(0);
    this->midPoint.setY(350);


    this->followPoint.setX(0);
    this->followPoint.setY(0);

    srand(time(0));
}

void Boss::setHpBoss(){
    double hp = 0;
    for(Enemy e : enemies){
        hp += e.getHp();
    }
    this->setHp(hp);
}

void Boss::move()
{
    double angle = atan2(this->followPoint.getY() - this->midPoint.getY(),
                         this->followPoint.getX() - this->midPoint.getX());

    this->midPoint.setX(this->midPoint.getX() + cos(angle) * this->velocity.getX());
    this->midPoint.setY(this->midPoint.getY() + sin(angle) * this->velocity.getY());

    if(this->midPoint.getX() > this->followPoint.getX() - 1 && this->midPoint.getX() < this->followPoint.getX() + 1 && 
        this->midPoint.getY() > this->followPoint.getY() - 1 && this->midPoint.getY() < this->followPoint.getY() + 1)
    {
        int rX = rand()%181 - 90;
        int rY = rand()%81  + 20;

        this->setFollowPoint(rX, rY);
    }
}