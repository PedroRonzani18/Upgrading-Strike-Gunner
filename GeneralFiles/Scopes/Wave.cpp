#include "../Header/Wave.h"
#include "../../BaseClasses/Header/Parser.h"
#include "../../GeneralFiles/Header/drawings.h"
#include <stdio.h>
#include <iostream>
#include <utility>

std::vector<std::pair<std::string,std::vector<const char*>>> wavesSource;

// retorna classe
std::string findName(std::string str)
{
    if (str.find("BaseWaves")       != std::string::npos) return "BaseWaves";
    else if (str.find("ChadWaves")  != std::string::npos) return "ChadWaves";
    else if (str.find("TitleWaves") != std::string::npos) return "TitleWaves";

    return "erro";
}

void addWavesScripts()
{
    for(const char* enemyPath: Parser::parsePath("Assets/Scripts/Waves/allWaves.txt"))
    {
        bool found = false;
        std::string grupo = findName((std::string)enemyPath);
        //std::cout << "Caminho: " << enemyPath << "  Grupo: " << grupo << std::endl;

        if(wavesSource.empty()){
            std::vector<const char*> aux;
            aux.push_back(enemyPath);
            wavesSource.push_back(std::make_pair(grupo,aux));
        }
        
        else
        {
            for(size_t i=0; i<wavesSource.size(); i++)
            {
                //std::cout << "First: " << wavesSource[i].first <<" Grupo: " << grupo << std::endl; 

                if(wavesSource[i].first == grupo)
                {
                    wavesSource[i].second.push_back(enemyPath);
                    found = true;
                }
            }
            if(!found)
                wavesSource.push_back(std::make_pair(grupo,std::vector<const char*>()));
        }
    }
}

std::vector<Enemy> waveCallerNew(const char* waveCaminho)
{
    for(std::pair<std::string, std::vector<const char *>> par: wavesSource)
    {
        for(const char* path: par.second)
        {
            if(!strcmp(waveCaminho,path))
            {
                     if (par.first == "BaseWaves")  return waveTemplate(path);
                else if (par.first == "TitleWaves") return waveTemplateTitle(path);
                else if (par.first == "ChadWaves")  return waveTemplateChad(path);
            }
        }
    }

    return std::vector<Enemy>();
}

/*
std::vector<Enemy> waveCaller(int waveType)
{
    srand(time(0));
    if(waveType == 18) return waveKamikaseAcelerado18();
    
    //else if(waveType < 25) return waveTemplate(wavesPaths[waveType-1]);

    else if(waveType < 50)
    {
        switch (waveType)
        {
                
            case 25: return waveLevel1();
                
            case 26: return waveLevel2();
                
            case 27: return waveMissaoConcluida();
                
            case 28: return waveGameOver();
                
            case 49: return waveCreditos();
        }
    }

    else 
    {
        switch (waveType)
        {
               
            case 50: return waveChad();
                
            case 99: return waveBossEntrada();
                
            case 100: return waveBoss();
        }
    }
     // retorna vazio para função não reclamar >_<
    return std::vector<Enemy>();
}
*/
std::vector<Enemy> waveTemplateChad(const char* path)
{
    std::cout << "Entrou" << std::endl;
    std::vector<Enemy> aux;
    Parser aP = Parser::parseGeneral(path);

    for(int i=0; i<aP.linhas; i++)
    {
        for (int j = 0; j < aP.numberOfEnemies[i]; j++)
        {
            Enemy e1 = Enemy(aP.type[i],aP.typeMove[i],aP.numberOfShots[i],aP.typeTiroManager[i],aP.vx[i],aP.vy[i]);
            e1.setMidPoint(aP.midpointConstantX[i] + aP.iXSignal[i]* j * aP.multiplyerX[i],
                           aP.midpointConstantY[i] + aP.iYSignal[i]* j * aP.multiplyerY[i]);
            e1.setDisplayListModel(textures[aP.textureId[i]]);
            e1.setResize(aP.resize[i]);
            aux.push_back(e1);
        }
    }
    return aux;
}

std::vector<Enemy> waveTemplateTitle(const char* path)
{
    std::vector<Enemy> aux;
    Parser aP = Parser::parseGeneral(path);

    for(size_t i=0; i<aP.numberOfEnemies.size(); i++)
    {
        for (int j = 0; j < aP.numberOfEnemies[i]; j++)
        {
            Enemy e1 = Enemy(aP.type[i],aP.typeMove[i],aP.numberOfShots[i],aP.typeTiroManager[i],aP.vx[i],aP.vy[i]);
            e1.setMidPoint(aP.midpointConstantX[i] + aP.iXSignal[i]* j * aP.multiplyerX[i],
                           aP.midpointConstantY[i] + aP.iYSignal[i]* j * aP.multiplyerY[i]);
            e1.setDisplayListModel(textures[aP.textureId[i]]);
            aux.push_back(e1);
        }
    }
    return aux;
}

std::vector<Enemy> waveTemplate(const char* path)
{
    std::vector<Enemy> aux;
    Parser aP = Parser::parseGeneral(path);

    for(int i=0; i<aP.linhas; i++)
    {
        for (int j = 0; j < aP.numberOfEnemies[i]; j++)
        {
            Enemy e1 = Enemy(aP.type[i],aP.typeMove[i],aP.numberOfShots[i],aP.typeTiroManager[i],aP.vx[i],aP.vy[i]);
            e1.setMidPoint(aP.midpointConstantX[i] + aP.iXSignal[i]* j * aP.multiplyerX[i],
                           aP.midpointConstantY[i] + aP.iYSignal[i]* j * aP.multiplyerY[i]);
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

std::vector<Enemy> waveBossEntrada()
{
    std::vector<Enemy> aux;

    Enemy e1 = Enemy(7, 24, 0, 0, 2, 2); // boss
    e1.setMidPoint(-150, -50);
    aux.push_back(e1);

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