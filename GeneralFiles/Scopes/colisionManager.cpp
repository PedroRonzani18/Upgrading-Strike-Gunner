#include "../Header/colisionManager.h"
#include "../Header/globalParameters.h"

int colided(Entity& e1, Entity& e2)
{
         if(e1.getMidPoint().getY() + e1.getMax().getY() < e2.getMidPoint().getY() + e2.getMin().getY()) return 0;
    else if(e1.getMidPoint().getY() + e1.getMin().getY() > e2.getMidPoint().getY() + e2.getMax().getY()) return 0;
    else if(e1.getMidPoint().getX() + e1.getMax().getX() < e2.getMidPoint().getX() + e2.getMin().getX()) return 0;
    else if(e1.getMidPoint().getX() + e1.getMin().getX() > e2.getMidPoint().getX() + e2.getMax().getX()) return 0;
    
    return 1;
}

int mantainInsideScreen(Entity& e)
{
    // Se um dos extremos de cima, baixo, esqueda, direita ultrapassar seu respectivo limite da
    // caixa de visualização, sua coordenada X e/ou Y é programada para voltar para o limite,
    // fazendo que ele nunca saia da caixa de visualização.
    int aux = 0; 

    if(e.getMidPoint().getY() + e.getMax().getY() > top){
        e.getMidPoint().setY(top - e.getMax().getY());
        aux = 1;
    }

    if(e.getMidPoint().getY() + e.getMin().getY() < bottom){
        e.getMidPoint().setY(bottom - e.getMin().getY());
        aux = 1;
    }

    if(e.getMidPoint().getX() + e.getMax().getX() > direita){
        e.getMidPoint().setX(direita - e.getMax().getX());
        aux = 2;
    }

    if(e.getMidPoint().getX() + e.getMin().getX() < esquerda){
        e.getMidPoint().setX(esquerda - e.getMin().getX());
        aux = 2;
    }

    return aux;
}


void verifyVisibility(Entity& e)
{
    if(e.getMidPoint().getX() + e.getMin().getX() > direita ||
       e.getMidPoint().getX() + e.getMax().getX() < esquerda  ||
       e.getMidPoint().getY() + e.getMin().getY() > top   ||
       e.getMidPoint().getY() + e.getMax().getY() < bottom)
       e.setOnScreen(GL_FALSE);
    else
        e.setOnScreen(GL_TRUE);
}
