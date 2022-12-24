#ifndef _BUTTON_H
#define _BUTTON_H

#include "Entity.h"

class Button: public Entity
{
    private:
        int currentPosition;

    public:

        Button();
        
        int getCurrentPosition() {return this->currentPosition;}
        void setCurrentPosition(const int& currentPosition) {this->currentPosition = currentPosition;}
};

#endif