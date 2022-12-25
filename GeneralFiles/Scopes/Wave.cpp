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
    else if (str.find("BossWaves")  != std::string::npos) return "BossWaves";
    else if (str.find("CreditosWaves") !=std::string::npos) return "CreditosWaves";

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
                     if (par.first == "BaseWaves")  return waveTemplateGeneral(path);
                else if (par.first == "TitleWaves") return waveTemplateGeneral(path);
                else if (par.first == "ChadWaves")  return waveTemplateGeneral(path);
                else if (par.first == "BossWaves") return waveTemplateGeneral(path);
                else if(par.first == "CreditosWaves") return waveTemplateGeneral(path);
            }
        }
    }

    return std::vector<Enemy>();
}

std::vector<Enemy> waveTemplateGeneral(const char* path)
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

std::vector<Enemy> waveTemplateCreditos(const char* path)
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
            e1.setDisplayListModel(textures[aP.textureId[i]]);
            e1.setResize(aP.resize[i]);
            e1.setMax(aP.maxX[i],aP.maxY[i]);
            e1.setMin(aP.minX[i],aP.minY[i]);
            aux.push_back(e1);
        }
    }
    return aux;
}

std::vector<Enemy> waveTemplateChad(const char* path)
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
            e1.setDisplayListModel(textures[aP.textureId[i]]);
            e1.setResize(aP.resize[i]);
            aux.push_back(e1);
        }
    }
    return aux;
}

std::vector<Enemy> waveTemplateBoss(const char* path)
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
                           e1.getCurrentProjectile().setDamage(aP.currentProjectileDamage[i]);
            bossTime = aP.bossTime;
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
