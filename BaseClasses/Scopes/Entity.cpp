#include "../Header/Entity.h"

Entity::Entity(const int& displayListModel, const GLboolean& onScreen, const OrderedPair& midPoint, const OrderedPair& max, const OrderedPair& min, const double& resize):
        displayListModel(displayListModel),
        onScreen(onScreen),
        midPoint(midPoint),
        max(max),
        min(min),
        resize(resize)
        {
                this->hitbox.resize(4);
                this->alteredHitbox.resize(4);
        }


Entity::Entity()
{
        this->hitbox.resize(4);
        this->alteredHitbox.resize(4);
}

void Entity::setHitbox()
{
        this->hitbox[0].x = (this->max.x);
        this->hitbox[0].y = (this->max.y);
        this->hitbox[1].x = (this->min.x);
        this->hitbox[1].y = (this->max.y);
        this->hitbox[2].x = (this->min.x); 
        this->hitbox[2].y = (this->min.y);
        this->hitbox[3].x = (this->max.x);
        this->hitbox[3].y = (this->min.y);
}
