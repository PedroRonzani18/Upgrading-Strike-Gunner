#include "../Header/drawings.h"
#include "../Header/globalParameters.h"

std::vector<GLuint> textures;

void textureModule(void templateSquare(double, double, GLuint),double x, double y, GLuint z)
{
    GLuint aux = glGenLists(1);
    
    glNewList(aux, GL_COMPILE);
        templateSquare(x,y,z);
    glEndList();
    textures.push_back(aux);
}

void textureModule(void templateSquare(double  , double  , GLuint  , double   , double   , double   , double ),
                                       double x, double y, GLuint z, double wo, double uo, double dw, double du)
{
    GLuint aux = glGenLists(1);
    
    glNewList(aux, GL_COMPILE);
        templateSquare(x, y, z, wo, uo, dw, du);
    glEndList();
    textures.push_back(aux);
}

void templateSquare(double x, double y, GLuint id)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0,0); 
        glVertex2f (-x,-y);

        glTexCoord2f(1,0);
        glVertex2f (x,-y);

        glTexCoord2f(1,1);
        glVertex2f (x,y);

        glTexCoord2f(0,1);
        glVertex2f(-x,y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void templateSquare(double x, double y, GLuint id, double wo, double uo, double dw, double du)
{
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, id);
        glColor3f(1,1,1);
        glBegin(GL_TRIANGLE_FAN);

        glBegin(GL_TRIANGLE_FAN);
            glTexCoord2f(wo,uo); 
            glVertex2f (-x,-y);

            glTexCoord2f(wo + dw,uo);
            glVertex2f (x,-y);

            glTexCoord2f(wo + dw,uo + du);
            glVertex2f (x,y);

            glTexCoord2f(wo,uo + du);
            glVertex2f(-x,y);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

GLuint loadTexture(const char* arquivo)
{
    GLuint idTextura = SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    return idTextura;
}

void initializeTextures()
{
    // Cria um quadrado com dimensoes x y, carrega a textura em questão e armazena os IDs gerados no vector "textures"

     /*[0]*/textureModule(templateSquare,50, 15,loadTexture("Assets/Images/ajudaNew.png"));
     /*[1]*/textureModule(templateSquare, 5,  5,loadTexture("Assets/Images/blueBall.png"));
     /*[2]*/textureModule(templateSquare, 7,  2,loadTexture("Assets/Images/blueLaser.png"));
     /*[3]*/textureModule(templateSquare, 7,  7,loadTexture("Assets/Images/fireBall.png"));
     /*[4]*/textureModule(templateSquare, 2, 20,loadTexture("Assets/Images/greenLaser.png"));
     /*[5]*/textureModule(templateSquare,50, 15,loadTexture("Assets/Images/iniciarNew.png"));
     /*[6]*/textureModule(templateSquare, 5,  5,loadTexture("Assets/Images/orangeBall.png"));
     /*[7]*/textureModule(templateSquare, 1, 12,loadTexture("Assets/Images/redLaser.png"));
     /*[8]*/textureModule(templateSquare, 7,  7,loadTexture("Assets/Images/setaNew.png"));
     /*[9]*/textureModule(templateSquare,90,100,loadTexture("Assets/Images/space1.png"));
    /*[10]*/textureModule(templateSquare,90,100,loadTexture("Assets/Images/space2.png"));
    /*[11]*/textureModule(templateSquare,25, 25,loadTexture("Assets/Images/spaceship1.png"));
    /*[12]*/textureModule(templateSquare,20, 25,loadTexture("Assets/Images/spaceship2.png"));
    /*[13]*/textureModule(templateSquare,20, 20,loadTexture("Assets/Images/spaceship3.png"));
    /*[14]*/textureModule(templateSquare,20, 20,loadTexture("Assets/Images/spaceship4.png"));
    /*[15]*/textureModule(templateSquare,90,100,loadTexture("Assets/Images/ajudaBackgoundNew.png"));
    /*[16]*/textureModule(templateSquare, 1, 4, loadTexture("Assets/Images/letrinhasDemasiadamenteMuitoCria.png"), 0, 0, 53.0/1242, 1);
    /*[17 - 25]*/

    float soma=60.0/1242, propX = 131.0/1242;
    for(int i=0; i<9; i++)
    {
        textureModule(templateSquare, 3, 4, loadTexture("Assets/Images/letrinhasDemasiadamenteMuitoCria.png"), soma, 0, propX, 1);
        soma += propX;
    }
    /*[26]*/textureModule(templateSquare,  7,  7,loadTexture("Assets/Images/heart.png"));
    /*[27]*/textureModule(templateSquare, 15, 15,loadTexture("Assets/Images/spaceship5.png"));
    /*[28]*/textureModule(templateSquare, 20, 20,loadTexture("Assets/Images/spaceship6.png"));
    /*[29]*/textureModule(templateSquare, 20, 20,loadTexture("Assets/Images/spaceship7.png"));
    /*[30]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/backGroundMenu.png"));
    /*[31]*/textureModule(templateSquare, 20, 20,loadTexture("Assets/Images/asteroidShip.png"));
    /*[32]*/textureModule(templateSquare, 30, 30,loadTexture("Assets/Images/asteroid.png"));
    /*[33]*/textureModule(templateSquare, 20, 20,loadTexture("Assets/Images/rotationSpecaship.png"));
    /*[34]*/textureModule(templateSquare, 10, 10,loadTexture("Assets/Images/coletavelVida.png"));
    /*[35]*/textureModule(templateSquare, 10, 10,loadTexture("Assets/Images/coletavelFireRate.png"));
    /*[36]*/textureModule(templateSquare, 10, 10,loadTexture("Assets/Images/coletavelDamage.png"));
    /*[37]*/textureModule(templateSquare, 10, 10,loadTexture("Assets/Images/coletavelAumentaNumTiro.png"));
    /*[38]*/textureModule(templateSquare, 10, 10,loadTexture("Assets/Images/coletavelTrocaTipoTiro.png"));
    /*[39]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/redSpace1.png"));
    /*[40]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/redSpace2.png"));
    /*[41]*/textureModule(templateSquare, 50, 50,loadTexture("Assets/Images/boss.png"));
    /*[42]*/textureModule(templateSquare, 17, 15,loadTexture("Assets/Images/rotationSpecaship.png"));
    /*[43]*/textureModule(templateSquare, 30, 20,loadTexture("Assets/Images/trippleTurret.png"));
    /*[44]*/textureModule(templateSquare,140,140,loadTexture("Assets/Images/chadMaster.png"));
    /*[45]*/textureModule(templateSquare, 80, 40,loadTexture("Assets/Images/level1.png"));
    /*[46]*/textureModule(templateSquare, 80, 40,loadTexture("Assets/Images/level2.png"));
    /*[47]*/textureModule(templateSquare, 80, 40,loadTexture("Assets/Images/gameOver.png"));
    /*[48]*/textureModule(templateSquare, 80, 40,loadTexture("Assets/Images/missaoConcluida.png"));
    /*[49]*/textureModule(templateSquare, 40, 40,loadTexture("Assets/Images/balao.png"));
    /*[50]*/textureModule(templateSquare, 30, 25,loadTexture("Assets/Images/torretaGrossa.png"));
    /*[51]*/textureModule(templateSquare, 40, 10,loadTexture("Assets/Images/barraHp.png"));
    /*[52]*/textureModule(templateSquare, 40, 10,loadTexture("Assets/Images/molduraBarraHp.png"));
    /*[53]*/textureModule(templateSquare, 30, 20,loadTexture("Assets/Images/trippleTurretGG.png"));
    /*[54]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/creditos1.png"));
    /*[55]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/creditos2.png"));
    /*[56]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/creditos3.png"));
    /*[57]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/creditos4.png"));
    /*[58]*/textureModule(templateSquare, 90,100,loadTexture("Assets/Images/creditos5.png"));

}

void drawModel(MovableEntity *m)
{
    glPushMatrix();
        glTranslatef(m->getMidPoint().x,
                    m->getMidPoint().y,
                    0);
        glRotatef(m->getAngle(), 0, 0, 1);
        glScalef(m->getResize(), m->getResize(), 1);
        glCallList(m->getDisplayListModel());
    glPopMatrix();
}

void drawModel(MovableEntity *m, const int& dx, const int& dy)
{
    glPushMatrix();
        glTranslatef(m->getMidPoint().x,
                    m->getMidPoint().y,
                    0);
        glRotatef(m->getAngle(), 0, 0, 1);
        glTranslatef(dx, dy, 0);
        glScalef(m->getResize(), m->getResize(), 1);
        glCallList(m->getDisplayListModel());
    glPopMatrix();
}

void drawHitbox(MovableEntity* m)
{
    glColor3f(0, 1, 0);
    glLineWidth(2);


    for (int i = 0, j = 1; i < 4; i++, j = (i + 1) % 4)
    {
        glBegin(GL_LINES);
            glVertex2f(m->getAlteredHitbox()[i].x, m->getAlteredHitbox()[i].y);
            glVertex2f(m->getAlteredHitbox()[j].x, m->getAlteredHitbox()[j].y);
        glEnd();
    }
}