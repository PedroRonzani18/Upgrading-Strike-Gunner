#ifndef _BACKGOUND_H
#define _BACKGOUND_H

#include <GL/freeglut.h>
#include "MovableEntity.h"
#include "../../GeneralFiles/Header/drawings.h"

class Background : public MovableEntity
{
    private:
        GLuint id;

    public:
        Background();
    
        GLuint getId(){return this->id;}
        void setId(const GLuint& id){this->id = id;}

        void move() override;
        void scaleMove(const double& scale) override{}
};

#endif