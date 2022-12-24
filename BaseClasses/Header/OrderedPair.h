#ifndef _ORDEREDPAIR_H
#define _ORDEREDPAIR_H

class OrderedPair{
    protected:
        double x;
        double y;

    public:
        OrderedPair();

        double getX(){return x;}
        void setX(const double& x){this->x = x;}

        double getY(){return y;}
        void setY(const double& y){this->y = y;}
};

#endif