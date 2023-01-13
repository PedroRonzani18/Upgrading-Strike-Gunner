#ifndef _BALLISTIC_H
#define _BALLISTIC_H

#include "Projectile.h"

class Ballistic{
    protected:
        
        Projectile currentProjectile; //modelo do tiro atual
        int numberOfShots; // numero de tiros lançados por vez (1, 2, 3)
        int typeTiroManager;
        int fireRatePeriod; // contador interno
        double alteredFireRate; // fire rate alterado por coletável
                                // tempo entre cada tiro
                                // porcentagem do defaultFirefrate

    public:
        
        Ballistic();

        Ballistic(const Projectile& currentProjectile, const int& numberOfShots, const int& typeTiroManager, const int& fireRatePeriod, const double& alteredFireRate);

        Projectile& getCurrentProjectile(){return this->currentProjectile;}
        void setCurrentProjectile(const Projectile& currentProjectile){this->currentProjectile = currentProjectile;}

        int getNumberOfShots()const{return this->numberOfShots;}
        void setNumberOfShots(const int& numberOfShots){this->numberOfShots = numberOfShots;}

        int getTypeTiroManager()const{return this->typeTiroManager;}
        void setTypeTiroManager(const int& typeTiroManager){this->typeTiroManager = typeTiroManager;}

        int getFireRatePeriod()const{return this->fireRatePeriod;}
        void setFireRatePeriod(const int& fireRatePeriod){this->fireRatePeriod = fireRatePeriod;}

        double getAlteredFireRate()const{return alteredFireRate;}
        void setAlteredFireRate(const double& alteredFireRate){this->alteredFireRate = alteredFireRate;}
        
        virtual std::vector<Projectile> fire() = 0;
};

#endif