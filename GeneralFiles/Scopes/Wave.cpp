#include "../Header/Wave.h"
#include "../../BaseClasses/Header/Parser.h"
#include <stdio.h>
#include <iostream>

std::vector<const char*> wavesPaths;

void addWavesScripts()
{
    for(const char* enemyPath: Parser::parsePath("Assets/Scripts/Waves/baseAllWaves.txt"))
        wavesPaths.push_back(enemyPath);
}

std::vector<Enemy> waveCaller(int waveType)
{
    srand(time(0));
    
    if(waveType < 25 && waveType != 18) return waveTemplate(wavesPaths[waveType-1]);

    else 
    {
        switch (waveType)
        {
            case 18: return waveKamikaseAcelerado18();
                
            case 25: return waveLevel1();
                
            case 26: return waveLevel2();
                
            case 27: return waveMissaoConcluida();
                
            case 28: return waveGameOver();
                
            case 49: return waveCreditos();
                
            case 50: return waveChad();
                
            case 99: return waveBossEntrada();
                
            case 100: return waveBoss();
        }
    }
     // retorna vazio para função não reclamar >_<
    return std::vector<Enemy>();
}

std::vector<Enemy> waveTemplate(const char* path)
{
    std::vector<Enemy> aux;
    Parser aP = Parser::parseEnemy(path);

    for(int i=0; i<aP.linhas; i++)
    {
        for (int j = 0; j < aP.numberOfEnemies[i]; j++)
        {
            Enemy e1 = Enemy(aP.type[i],aP.typeMove[i],aP.numberOfShots[i],aP.typeTiroManager[i],aP.vx[i],aP.vy[i]);
            e1.setMidPoint(aP.midpointConstantX[i] + aP.iXSignal[i]* j * aP.multiplyerX[i],
                           aP.midpointConstantY[i] + aP.iYSignal[i]* j * aP.multiplyerY[i]);
            aux.push_back(e1);
            //printf("Midpoint: %f   %f\n",aP.midpointConstantX[i] + aP.iXSignal[i]* j * aP.multiplyerX[i],
             //              aP.midpointConstantY[i] + aP.iYSignal[i]* j * aP.multiplyerY[i]);
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

std::vector<Enemy> waveBoss() // O boss e muito zika 
{
    std::vector<Enemy> aux;

    bossTime = 1;

    Enemy e1 = Enemy(9, -1, 2, 2, 0, 0); // torreta grossa
    e1.getCurrentProjectile().setDamage(0.5);
    e1.setMidPoint(-30,18);
    e1.setVelocity(-30,18);
    aux.push_back(e1);

    e1.setMidPoint(30,18);
    e1.setVelocity(30,18);
    aux.push_back(e1);

    Enemy e2 = Enemy(11, -2, 3, 0, 0, 0); // triple turret
    e2.getCurrentProjectile().setDamage(0.5);
    e2.setMidPoint(40,-15);
    e2.setVelocity(40,-15);
    aux.push_back(e2);

    e2.setMidPoint(-40, -15);
    e2.setVelocity(-40, -15);
    aux.push_back(e2);

    Enemy e3 = Enemy(12, -2, 3, 4, -0.2, -0.8); // triple turret GG
    e3.getCurrentProjectile().setDamage(0.5);
    e3.setMidPoint(0,0);
    e3.setVelocity(0,0);
    aux.push_back(e3);

    return aux; 
}

std::vector<Enemy> waveLevel1()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 25, 0, 0, 0, -1);
    e1.setMidPoint(0,120);
    e1.setDisplayListModel(textures[45]);
    aux.push_back(e1);

    return aux;
}

std::vector<Enemy> waveLevel2()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 25, 0, 0, 0, -1);
    e1.setMidPoint(0,120);
    e1.setDisplayListModel(textures[46]);
    aux.push_back(e1);

    return aux;
}

std::vector<Enemy> waveMissaoConcluida()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 25, 0, 0, 0, -1);
    e1.setMidPoint(0,120);
    e1.setDisplayListModel(textures[48]);
    aux.push_back(e1);

    return aux;
}

std::vector<Enemy> waveGameOver()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 25, 0, 0, 0, -1);
    e1.setMidPoint(0,120);
    e1.setDisplayListModel(textures[47]);
    aux.push_back(e1);

    return aux;
}

std::vector<Enemy> waveBossEntrada()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(7, 24, 0, 0, 2, 2); // boss
    e1.setMidPoint(-150, -50);
    aux.push_back(e1);

    return aux;
}

std::vector<Enemy> waveChad()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 26, 0, 0, 0, 1); // chad
    e1.setMidPoint(0,-180);
    e1.setDisplayListModel(textures[44]);
    e1.setResize(0.6);
    aux.push_back(e1);

    Enemy e2 = Enemy(10, 27, 0, 0, 0, 1); // balão
    e2.setMidPoint(40,-105);
    e2.setDisplayListModel(textures[49]);
    e2.setResize(0.7);
    aux.push_back(e2);

    return aux;
}

std::vector<Enemy> waveCreditos()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(10, 17, 0, 0, 0, 1); 
    e1.setVelocity(0, 0.14);
    e1.setMax(90, 100);
    e1.setMin(-90, -100);
    e1.setResize(1);

    e1.setMidPoint(0, -200);
    e1.setDisplayListModel(textures[54]);
    aux.push_back(e1);

    e1.setMidPoint(0, -400);
    e1.setDisplayListModel(textures[55]);
    aux.push_back(e1);

    e1.setMidPoint(0, -600);
    e1.setDisplayListModel(textures[56]);
    aux.push_back(e1);

    e1.setMidPoint(0, -800);
    e1.setDisplayListModel(textures[57]);
    aux.push_back(e1);

    e1.setMidPoint(0, -1000);
    e1.setDisplayListModel(textures[58]);
    aux.push_back(e1);

    return aux;
}