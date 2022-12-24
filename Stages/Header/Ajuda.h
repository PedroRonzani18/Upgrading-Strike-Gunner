#ifndef _AJUDA_H
#define _AJUDA_H

#include "Stage.h"
#include "../../GeneralFiles/Header/globalParameters.h"


class Ajuda: public Stage
{
    private:
        void drawBackgroundAjuda();

    public:
        Ajuda();
        
        void drawAndMove() override; 
        int stageKeyboard() override;  
        void colider()override{} 
        void callWaves() override {} 
        void initBackgrounds() override{} 
        void initBackgrounds(const int& typeBackground) override{} 
        void timeCounter()override{}
};

#endif