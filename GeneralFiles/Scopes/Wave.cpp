#include "../Header/Wave.h"
#include "../../BaseClasses/Header/Parser.h"
#include "../../GeneralFiles/Header/drawings.h"
#include <stdio.h>
#include <iostream>
#include <utility>
#include <time.h>

std::vector<Enemy> waveTemplateGeneral(const char* path)
{
    std::vector<Enemy> aux;
    Parser aP = Parser::parseGeneral(path);


    std::vector<int> rands;

    for(int i=0; i<aP.linhas; i++)
    {       
        if(!aP.randMinus.empty())
            for(int j = 0; j < aP.numberOfEnemies[i]; j++)
                rands.push_back(rand()%aP.randResto[i] - aP.randMinus[i]);
            
        for(int j = 0; j < aP.numberOfEnemies[i]; j++)
        {
            Enemy e1 = Enemy(aP.type[i],aP.typeMove[i],aP.numberOfShots[i],aP.typeTiroManager[i],aP.vx[i],aP.vy[i]);

            if(!aP.randMinus.empty()){
            e1.setMidPoint(aP.midConstX[i] * rands[j] + j * aP.multiplyerX[i], 
                           aP.midConstY[i]            + j * aP.multiplyerY[i]);
            }
            else{
               e1.setMidPoint(aP.midConstX[i] + j * aP.multiplyerX[i],
                              aP.midConstY[i] + j * aP.multiplyerY[i]); 
            }
            if(!aP.textureId.empty()) e1.setDisplayListModel(textures[aP.textureId[i]]);
            if(!aP.resize.empty())    e1.setResize(aP.resize[i]);
            if(!aP.maxX.empty())      e1.setMax(aP.maxX[i],aP.maxY[i]);
            if(!aP.maxY.empty())      e1.setMin(aP.minX[i],aP.minY[i]);
            if(aP.bossTime == 1)      bossTime = 1;

            aux.push_back(e1);
        }
    }
    return aux;
}

std::vector<Enemy> waveKamikaseAcelerado18()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(0, 12, 0, 0, -2, -2);

    int r;
    for(int i = 0; i < 40; i++){
        r = rand()%17 - 8;
        e1.setMidPoint(10*r, 150 + i*40);
        aux.push_back(e1);
    }
    return aux;  
}
