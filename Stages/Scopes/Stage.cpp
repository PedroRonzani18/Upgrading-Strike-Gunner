#include "../Header/Stage.h"
#include "../Header/Menu.h"

Stage::Stage()
{
    musicalizer = new Musicalizer();
}

void Stage::setAmmountOfButtons()
{
    this->ammountOfButtons = this->getButtons().size();
}

