#include "../Header/colisionManager.h"
#include "../Header/globalParameters.h"

int colided(Entity& e1, Entity& e2)
{
         if(e1.getMidPoint().y + e1.getMax().y < e2.getMidPoint().y + e2.getMin().y) return 0;
    else if(e1.getMidPoint().y + e1.getMin().y > e2.getMidPoint().y + e2.getMax().y) return 0;
    else if(e1.getMidPoint().x + e1.getMax().x < e2.getMidPoint().x + e2.getMin().x) return 0;
    else if(e1.getMidPoint().x + e1.getMin().x > e2.getMidPoint().x + e2.getMax().x) return 0;
    
    return 1;
}

int mantainInsideScreen(Entity& e)
{
    // Se um dos extremos de cima, baixo, esqueda, direita ultrapassar seu respectivo limite da
    // caixa de visualização, sua coordenada X e/ou Y é programada para voltar para o limite,
    // fazendo que ele nunca saia da caixa de visualização.
    int aux = 0; 

    if(e.getMidPoint().y + e.getMax().y > top){
        e.getMidPoint().y = (top - e.getMax().y);
        aux = 1;
    }

    if(e.getMidPoint().y + e.getMin().y < bottom){
        e.getMidPoint().y = (bottom - e.getMin().y);
        aux = 1;
    }

    if(e.getMidPoint().x + e.getMax().x > direita){
        e.getMidPoint().x = (direita - e.getMax().x);
        aux = 2;
    }

    if(e.getMidPoint().x + e.getMin().x < esquerda){
        e.getMidPoint().x = (esquerda - e.getMin().x);
        aux = 2;
    }

    return aux;
}


void verifyVisibility(Entity& e)
{
    if(e.getMidPoint().x + e.getMin().x > direita ||
       e.getMidPoint().x + e.getMax().x < esquerda  ||
       e.getMidPoint().y + e.getMin().y > top   ||
       e.getMidPoint().y + e.getMax().y < bottom)
       e.setOnScreen(GL_FALSE);
    else
        e.setOnScreen(GL_TRUE);
}
