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


    this->midPoint.x = 0;
    this->midPoint.y = 350;


    this->followPoint.x = 0;
    this->followPoint.y = 0;

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
    double angle = atan2(this->followPoint.y - this->midPoint.y,
                         this->followPoint.x - this->midPoint.x);

    this->midPoint.x = (this->midPoint.x + cos(angle) * this->velocity.x);
    this->midPoint.y = (this->midPoint.y + sin(angle) * this->velocity.y);

    if(this->midPoint.x > this->followPoint.x - 1 && this->midPoint.x < this->followPoint.x + 1 && 
        this->midPoint.y > this->followPoint.y - 1 && this->midPoint.y < this->followPoint.y + 1)
    {
        int rX = rand()%181 - 90;
        int rY = rand()%81  + 20;

        this->setFollowPoint(rX, rY);
    }
}