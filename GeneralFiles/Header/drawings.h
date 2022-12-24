#ifndef _DRAWINGS_H
#define _DRAWINGS_H

#include "../../BaseClasses/Header/MovableEntity.h"
#include <SOIL/SOIL.h>

extern std::vector<GLuint> textures;

void initializeTextures(); // armazena o id de todas as texturas dentro do vector de textures

GLuint loadTexture(const char* arquivo); // carrega as texturas

void templateSquare(double x, double y, GLuint id); // função de desenho de um retangulo generalizado

void drawModel(MovableEntity *m, const int& dx, const int& dy); // desenha um modelo com eixo de rotação transladado
void drawModel(MovableEntity* m); // desenha o modelo de uma entidade 
void drawHitbox(MovableEntity* m); // ddesenha a hitbox da entity

#endif