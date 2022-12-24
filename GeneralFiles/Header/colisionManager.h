#ifndef _COLISIONMANAGER_H
#define _COLISIONMANAGER_H

#include "../../BaseClasses/Header/Entity.h"
#include "../../BaseClasses/Header/OrderedPair.h"
#include <stdbool.h>

int colided(Entity& e1, Entity& e2); // confere se duas entidades colidiram (return 1) ou não (return 0)

int mantainInsideScreen(Entity& e); // garante que uma entidade não saia da tela

void verifyVisibility(Entity& e); // verifica se uma entidade está dentro da tela

#endif