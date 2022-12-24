#include "../Header/Entity.h"

Entity::Entity()
{
        this->hitbox.resize(4);
        this->alteredHitbox.resize(4);
}

void Entity::setHitbox(){
        this->hitbox[0].setX(this->max.getX());
        this->hitbox[0].setY(this->max.getY());
        this->hitbox[1].setX(this->min.getX());
        this->hitbox[1].setY(this->max.getY());
        this->hitbox[2].setX(this->min.getX()); 
        this->hitbox[2].setY(this->min.getY());
        this->hitbox[3].setX(this->max.getX());
        this->hitbox[3].setY(this->min.getY());
}
