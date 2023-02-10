#include "../Header/drawings.h"
#include "../Header/globalParameters.h"
#include "../../BaseClasses/Header/Parser.h"

std::vector<GLuint> textures;

char* stringToArray(const std::string& str)
{
    int t = str.length() + 1;
    char* arr = (char *)malloc(t * sizeof(char));

    for(int i=0; i<t; i++)
        arr[i] = str[i];

    return arr;
}

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
    return SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
}

// Cria um quadrado com dimensoes x y, carrega a textura em questão e armazena os IDs gerados no vector "textures"
void initializeTextures()
{
    using namespace std;
    for(auto vec: Parser::parseTextureData("Assets/Scripts/Textures/data.txt"))
    {
        if(vec[4] == "-1")
            textureModule(templateSquare, stof(vec[0]), stof(vec[1]), loadTexture(stringToArray(vec[2])));
        
        else
            textureModule(templateSquare, stof(vec[0]), stof(vec[1]), loadTexture(stringToArray(vec[2])), 
                                          stof(vec[3]), stof(vec[4]), stof(vec[5]), stof(vec[6]));
    }
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