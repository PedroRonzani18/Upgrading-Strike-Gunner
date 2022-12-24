#include "../Header/StageManager.h"
#include "../../GeneralFiles/Header/drawings.h"

StageManager::StageManager()
{
    this->currentLevel = 0;
    this->endLevels = 2;

    gameInit();
}

void StageManager::initLevel()
{
    if(this->currentLevel == endLevels){
        this->currentStage = menu;
        this->currentLevel = 0;
    }else{
        Level *level = new Level(this->currentLevel);
        this->currentStage = level;
        this->currentLevel ++;
    }
}

void StageManager::initializeStages()
{
    this->menu = new Menu();
    this->ajuda = new Ajuda();
    this->level = new Level();

    this->currentStage = menu;
}

int StageManager::gameOverVerify()
{
    return 0;
}

void StageManager::movements()
{
    currentStage->drawAndMove();
}

void StageManager::colision()
{
     currentStage->colider();
}

void StageManager::timer()
{
    keyboardOfStage();
    colision();
    callWave();

    currentStage->timeCounter();
}

void StageManager::callWave()
{
    currentStage->callWaves();
}

void StageManager::keyboardOfStage()
{
    int auxStageIndicator = currentStage->stageKeyboard();

    switch(auxStageIndicator)
    {
        case 0:
            this->currentStage = menu;
            this->currentLevel = 0;
            break;
        case 1:
            this->currentStage = ajuda;
            break;
        case 2:
            initLevel();
            break;
    }
}

void StageManager::gameInit()
{
    srand(time(0));
    
    glClearColor(0, 0, 0, 1); 

    initializeTextures();    //carrega texturas a usar

    initializeStages();

    // Cria um canal de música
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}