#ifndef _ENTITY_H
#define _ENTITY_H

#include <GL/freeglut.h>
#include <stdbool.h>
#include <vector>
#include "OrderedPair.h"

class Entity{
    protected:
        int displayListModel;
        GLboolean onScreen;
        OrderedPair midPoint;
        OrderedPair max;
        OrderedPair min;
        std::vector<OrderedPair> hitbox;
        std::vector<OrderedPair> alteredHitbox;
        double resize;

    public:
        Entity();

        int getDisplayListModel()const{return this->displayListModel;}
        void setDisplayListModel(const int& displayListModel){this->displayListModel = displayListModel;}

        GLboolean getOnScreen()const{return this->onScreen;}
        void setOnScreen(const GLboolean& onScreen){this->onScreen = onScreen;}

        OrderedPair& getMidPoint(){return this->midPoint;}
        void setMidPoint(const OrderedPair& midpoint){this->midPoint = midPoint;}
        void setMidPoint(const double& x, const double& y){this->midPoint.x = (x); this->midPoint.y = (y);}

        void setMidPoint(){this->midPoint.x = ((this->max.x + this->min.x)/2); 
                           this->midPoint.y = ((this->max.y + this->min.y)/2);}

        OrderedPair& getMax(){return this->max;}
        void setMax(const OrderedPair& max){this->max = max;}
        void setMax(const double& x, const double& y){this->max.x = (x); this->max.y = (y);}

        OrderedPair& getMin(){return this->min;}
        void setMin(const OrderedPair& min){this->min = min;}
        void setMin(const double& x, const double& y){this->min.x = (x); this->min.y = (y);}
        
        std::vector<OrderedPair> getHitbox()const{return this->hitbox;}
        void setHitbox();
        std::vector<OrderedPair> getAlteredHitbox()const{return this->alteredHitbox;}
        void setAlteredHitbox(const int& i, const int& x, const int& y ){this->alteredHitbox[i].x = (x); this->alteredHitbox[i].y = (y);}
        
        double getResize(){return this->resize;}
        void setResize(const double& resize)
        {
            this->resize = resize;
            this->setMax(this->getMax().x * resize, this->getMax().y * resize);
            this->setMin(this->getMin().x * resize, this->getMin().y * resize);
        }
};

#endif