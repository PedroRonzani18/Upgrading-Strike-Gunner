#ifndef _PARSER_H
#define _PARSER_H

// STL
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

// OpenGL
#include <GL/freeglut.h>
#include <SDL2/SDL_mixer.h>
#include <cstring>
#include <cstdio>

class Parser
{
    public:
        Parser();
        std::vector<float> numberOfEnemies;
        std::vector<float> type;
        std::vector<float> typeMove;
        std::vector<float> numberOfShots;
        std::vector<float> typeTiroManager;
        std::vector<float> vx;
        std::vector<float> vy;
        std::vector<float> midpointConstantX;
        std::vector<float> iXSignal;
        std::vector<float> multiplyerX;
        std::vector<float> midpointConstantY;
        std::vector<float> iYSignal;
        std::vector<float> multiplyerY;
        std::vector<GLuint> textureId;
        std::vector<float> resize;
        float linhas;

        // Funcoes que leem arquivos script.txt e retornam um parser 
        // carregado com informacoes especificas para cada tipo de construtor
        static std::vector<const char*> parsePath(const char* fileName);
        static char* stringToArray(std::string str);
        static std::string arrayToString(const char* arr);
        static Parser parseGeneral(const char* fileName);
};

#endif