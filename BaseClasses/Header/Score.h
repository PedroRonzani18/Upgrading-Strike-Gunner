#ifndef _SCORE_H
#define _SCORE_H

#include "Entity.h"
#include "../../GeneralFiles/Header/drawings.h"

class Score: public Entity
{
    private:
        double score;
        int scoreType; // determina se desenha o score em numeros ou score de vidas do player
        GLuint digitsScoreTextures [10];

    public:
        Score(){}

        Score(const int& scoreType);

        double getScore(){return this->score;}
        void setScore(const double& score){score <= 999999999 ? this->score = score : this->score = 999999999;}

        void draw();

};

#endif