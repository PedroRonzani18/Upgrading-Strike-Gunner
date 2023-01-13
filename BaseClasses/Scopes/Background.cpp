#include "../Header/Background.h"

Background::Background() : MovableEntity()
{
    this->angle = 0;
    this->angularSpeed = 0;
    this->midPoint.x = 0;
    this->setMax( 90, 100);
    this->setMin(-90,-100);
    this->setResize(1);
    this->setMidPoint();
    this->setVelocity(0,0.3);
    this->setOnScreen(GL_TRUE);
}

void Background::move()
{
    midPoint.y -= velocity.y;

    if(this->midPoint.y <= -200)
        this->midPoint.y = 200;
}