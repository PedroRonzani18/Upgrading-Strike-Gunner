#include "../Header/MovableEntity.h"

#define radianoParaGraus(radianos) (radianos * (180.0 / M_PI))
#define grausParaRadianos(graus) ((graus * M_PI) / 180.0)

MovableEntity::MovableEntity() : Entity(){}

MovableEntity::MovableEntity(const OrderedPair& velocity, const double& angle, const double& angularSpeed, const double& hp, const int& type, const int& typeMove,
                             const int& displayListModel, const GLboolean& onScreen, const OrderedPair& max, const OrderedPair& min, const double& resize) : 
    Entity(displayListModel, onScreen, max, min, resize),
    velocity(velocity), 
    angle(angle),
    angularSpeed(angularSpeed),
    hp(hp),
    type(type),
    typeMove(typeMove)
    {}


void MovableEntity::generalHitBoxMovement()
{
    for(int i=0; i<4; i++)
    {
        double auxAngle = grausParaRadianos(this->getAngle());
        
        // Usadas no calculo dos valores de x' e y' ao rotacionar a entidade
        double x = this->getHitbox()[i].x;
        double y = this->getHitbox()[i].y;

        // Altera o valor das coordenadas x e y da hitbox de acordo com as rotações
        this->setAlteredHitbox(i,x * cos(auxAngle) - y * sin(auxAngle),
                                 x * sin(auxAngle) + y * cos(auxAngle));

        // Altera o valor das coordenadas x e y da hitbox de acordo com as translações
        this->setAlteredHitbox(i, this->getAlteredHitbox()[i].x + this->midPoint.x,
                                  this->getAlteredHitbox()[i].y + this->midPoint.y);
    }
}  
