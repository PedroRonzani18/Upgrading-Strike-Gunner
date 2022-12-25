#ifndef _WAVE_H
#define _WAVE_H

#include <vector>
#include "../../BaseClasses/Header/Enemy.h"
#include "globalParameters.h"


    void addWavesScripts();

    std::vector<Enemy> waveCaller(int waveType); // vector com os enemies que serão usados na wave
    std::vector<Enemy> waveCallerNew(const char* waveCaminho);


    // Funções que determinam: 
    
    //      1. tipos de inimigos chamados na wave
    //      2. posição inicial de cada inimigo
    //      3. quanidade de inimigos de cada wave

    std::vector<Enemy> waveTemplate(const char* path);
    std::vector<Enemy> waveTemplateTitle(const char* path);
    std::vector<Enemy> waveKamikaseAcelerado18();
    std::vector<Enemy> waveLevel1();
    std::vector<Enemy> waveLevel2();
    std::vector<Enemy> waveMissaoConcluida();
    std::vector<Enemy> waveGameOver();
    std::vector<Enemy> waveChad();
    std::vector<Enemy> waveBoss();
    std::vector<Enemy> waveBossEntrada();
    std::vector<Enemy> waveCreditos();

#endif