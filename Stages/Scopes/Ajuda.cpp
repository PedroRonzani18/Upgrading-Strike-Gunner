#include "../Header/Ajuda.h"

Ajuda::Ajuda()
{
    getBackgrounds().resize(0);

    Background b1;
    b1.setDisplayListModel(textures[15]);
    b1.setMidPoint(0,0);
    backgrounds.push_back(b1);
}

int Ajuda::stageKeyboard()
{
    if(keys[4] && auxKeys[2] == 1) // volta para o menu
    {
        auxKeys[2] = 0;
        return 0;
    }else{
        return -1;
    }
}

void Ajuda::drawBackgroundAjuda()
{
    for(Background b : getBackgrounds())
    {
        glPushMatrix();
            glTranslatef(b.getMidPoint().getX(),
                         b.getMidPoint().getY(),
                         0);
            glCallList(b.getDisplayListModel());
        glPopMatrix();
    }
}

void Ajuda::drawAndMove()
{
    drawBackgroundAjuda();
}