#include "../Header/StageManager.h"
#include "../../GeneralFiles/Header/drawings.h"

StageManager::StageManager()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->currentLevel = 0;
    this->endLevels = 2;

    srand(time(0));

    initializeTextures();    //carrega texturas a usar

    Player::playerDataMap = Parser::parseEnemyData("Assets/Scripts/EntitiesData/playerData.txt");
    Enemy::enemyDataMap =   Parser::parseEnemyData("Assets/Scripts/EntitiesData/enemiesData.txt");

    initializeStages();

    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096); // Cria um canal de música
}

void StageManager::turnOffMusic()
{
    Mix_FadeOutMusic(1);
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

void StageManager::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    currentStage->drawAndMove();
    glutSwapBuffers();
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

    glutPostRedisplay();
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
            turnOffMusic();
            break;
        case 1:
            this->currentStage = ajuda;
            break;
        case 2:
            initLevel();
            break;
    }
}