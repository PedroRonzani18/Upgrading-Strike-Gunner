#ifndef _BOSS_H
#define _BOSS_H

#include "Enemy.h"
#include "Score.h"
#include <vector>
#include <time.h>

class Boss: public Enemy{
    private:
        std::vector<Enemy> enemies;
        Score healthBar;
        double vidaTotal;

    public:
        Boss();
        
        Enemy getEnemy(const int& i){return enemies[i];}
        std::vector<Enemy> getEnemies(){return this->enemies;}
        void addEnemie(const Enemy& enemy) {enemies.push_back(enemy);}

        void setHealthBar(const Score& entity){this->healthBar = entity;}
        Score& getHealthBar(){return this->healthBar;}

        void setVidaTotal(const double& vidaTotal){this->vidaTotal = vidaTotal;}
        double getVidaTotal(){return this->vidaTotal;}

        void setHpBoss();

        void move() override;
};

#endif