#ifndef _STAGEMANAGER_H
#define _STAGEMANAGER_H

#include "Stage.h"
#include "Menu.h"
#include "Ajuda.h"
#include "Level.h"
#include "../../GeneralFiles/Header/Wave.h"
#include "../../GeneralFiles/Header/colisionManager.h"
#include "../../GeneralFiles/Header/drawings.h"

class StageManager {

    private:
        Stage* currentStage;
        Menu* menu;
        Ajuda* ajuda;
        Level* level;

        int endLevels; // sinaliza que todos os levels foram jogados
        int currentLevel;
        void turnOffMusic();
    public:
        StageManager();

        Stage* getCurrentStage(){return this->currentStage;}
        void setCurrentStage(Stage* currentStage){this->currentStage = currentStage;}

        void keyboardOfStage();
        void display();
        void initializeStages();
        void callWave();
        void timer();
        void initLevel();


        void colision();
};

#endif