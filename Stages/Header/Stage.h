#ifndef _STAGE_H
#define _STAGE_H

#include "../../BaseClasses/Header/Button.h"
#include "../../BaseClasses/Header/Boss.h"
#include "../../BaseClasses/Header/Projectile.h"
#include "../../BaseClasses/Header/Colectible.h"
#include "../../BaseClasses/Header/Enemy.h"
#include "../../BaseClasses/Header/Player.h"
#include "../../BaseClasses/Header/Background.h"
#include "../../BaseClasses/Header/Score.h"
#include "../../BaseClasses/Header/Musicalizer.h"

#include <vector>

class Stage 
{
    protected:
        Score scorePontis;

        int ammountOfButtons;
        std::vector<int> waves;
        Button focusButton;
        Boss boss;
        Player player;
        std::vector<Background> backgrounds;
        std::vector<Button> buttons;
        std::vector<Enemy> enemies;
        std::vector<Projectile> projectiles;
        std::vector<Colectible> colectibles;
        Musicalizer* musicalizer;

    public:
        Stage();

        virtual int stageKeyboard() = 0; // função que gerencia as açĩoes do teclado
        virtual void drawAndMove() = 0; // chama as funções de desenho e movimento de cada entidade em cada stage (Level, Ajuda, Menu)
        virtual void colider() = 0; // gerencia as colisões de cada stage
        virtual void callWaves() = 0; // chama as waves de inimigos 
        virtual void initBackgrounds() = 0; // inicia os backgrounds de cada stage 
        virtual void initBackgrounds(const int& typeBackground) = 0; // inicia os backgrounds de cada stage
        virtual void timeCounter() = 0;

        Score& getScorePontis(){return this->scorePontis;}
        void setScorePontis(const Score& scorePontis){this->scorePontis = scorePontis;}

        std::vector<int> getWaves(){return this->waves;}
        void addWave(const int& waveId){this->waves.push_back(waveId);}
        void addWaves(std::vector<int>wavesAux){waves.insert(waves.end(),wavesAux.begin(),wavesAux.end());}
        int getWave(const int& pos){return waves[pos];}

        int getAmmountOfButtons(){return ammountOfButtons;}
        void setAmmountOfButtons();

        std::vector<Button> getButtons(){return buttons;}
        void addButton(const Button& b){this->buttons.push_back(b);}
        Entity getButton(const int& pos){return buttons[pos];}

        Button& getFocusButton(){return this->focusButton;}
        void setFocusButton(const Button& focusButton){this->focusButton = focusButton;}

        Player& getPlayer(){return this->player;}
        void setPlayer(const Player& player){this->player = player;}

        std::vector<Enemy> getEnemies(){return this->enemies;}
        Enemy getEnemy(const int& i){return this->enemies[i];}
        void addEnemy(const Enemy& e){enemies.push_back(e);}

        std::vector<Background> getBackgrounds(){return this->backgrounds;}
        Background getBackground(const int& i){return this->backgrounds[i];}
        void addBackground(const Background& b){backgrounds.push_back(b);}

        std::vector<Projectile> getProjectiles(){return this->projectiles;}

        Projectile& getProjectile(const int& i){return  this->projectiles[i];}
        
        void addProjectile(const Projectile& e){projectiles.push_back(e);}
        void removeProjectile(const int& i){this->projectiles.erase(this->projectiles.begin() + i);}

        std::vector<Colectible> getColectibles(){return this->colectibles;}
        Colectible getColectible(const int& i){return this->colectibles[i];}
        void addColectible(const Colectible& e){colectibles.push_back(e);}
};

#endif