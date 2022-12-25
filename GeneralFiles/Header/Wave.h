#ifndef _WAVE_H
#define _WAVE_H

#include <vector>
#include "../../BaseClasses/Header/Enemy.h"
#include "globalParameters.h"

    // Funções que determinam: 
    
    //      1. tipos de inimigos chamados na wave
    //      2. posição inicial de cada inimigo
    //      3. quanidade de inimigos de cada wave
    std::vector<Enemy> waveKamikaseAcelerado18();
    std::vector<Enemy> waveTemplateGeneral(const char* path);

#endif