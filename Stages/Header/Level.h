#ifndef _LEVEL_H
#define _LEVEL_H

#include "../../BaseClasses/Header/Player.h"
#include "../../BaseClasses/Header/Enemy.h"
#include "../../BaseClasses/Header/Colectible.h"
#include "../../BaseClasses/Header/Boss.h"
#include "../../BaseClasses/Header/Score.h"
#include "../../BaseClasses/Header/Parser.h"

#include "../../GeneralFiles/Header/drawings.h"
#include "../../GeneralFiles/Header/colisionManager.h"
#include "../../GeneralFiles/Header/globalParameters.h"
#include "../../GeneralFiles/Header/Wave.h"

#include "Stage.h"
#include <stdbool.h>

class Level: public Stage
{
    private:
        void remover(); // remove o inimigo de acordo com: 1) hp<0 2) fora da tela
                        // além de criar os coletáveis a uma taxa de drop pré-definida no enemy

        Enemy* smallestDistanceEnemyPlayer(MovableEntity* m1); // encontra o enemy mais próximo do player a ser seguido pelo tiro que segue
        void startMusic(int l);


    public:
        Level(){}

        Level(const int& l);

        void drawAndMove() override;
        int stageKeyboard() override;
        void drawScore(); // desenha o score do level

        void timeCounter() override; // gerencia os contradores de tempo específicos
        
        void colider() override;
        void callWaves() override;
        void initBackgrounds() override {}
        void initBackgrounds(const int& typeBackground) override;

};


#endif