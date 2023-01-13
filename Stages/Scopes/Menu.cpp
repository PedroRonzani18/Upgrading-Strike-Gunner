#include "../Header/Menu.h"
#include "../../GeneralFiles/Header/globalParameters.h"
#include "../../GeneralFiles/Header/drawings.h"

Menu::Menu()
{
    getButtons().resize(0);

    Button startButton;
    startButton.setDisplayListModel(textures[5]);
    startButton.setCurrentPosition(1);
    startButton.setMidPoint(0, -40);
    this->addButton(startButton);

    Button helpButton;
    helpButton.setDisplayListModel(textures[0]);
    helpButton.setCurrentPosition(2);
    helpButton.setMidPoint(0, -70);
    this->addButton(helpButton);

    setAmmountOfButtons();

    Button emphasisButton;
    emphasisButton.setDisplayListModel(textures[8]);
    emphasisButton.setCurrentPosition(1);
    emphasisButton.setMidPoint(startButton.getMidPoint().x - 60, startButton.getMidPoint().y);
    this->setFocusButton(emphasisButton);

    getBackgrounds().resize(0);

    Background b1;
    b1.setDisplayListModel(textures[30]);
    b1.setMidPoint(0, 0);
    backgrounds.push_back(b1);
}

int Menu::stageKeyboard()
{
    int auxFocus = this->getFocusButton().getCurrentPosition();

    if (keys[0] && auxKeys[0] == 1)
    {
        auxKeys[0] = 0;
        if (auxFocus > 1)
            this->getFocusButton().setCurrentPosition(auxFocus - 1);
        else
            this->getFocusButton().setCurrentPosition(this->getAmmountOfButtons());

        for (Button b : this->getButtons())
        {
            if (b.getCurrentPosition() == this->getFocusButton().getCurrentPosition())
            {
                getFocusButton().setMidPoint(b.getMidPoint().x - 60, b.getMidPoint().y);
            }
        }
    }

    if (keys[1] && auxKeys[1] == 1)
    {
        auxKeys[1] = 0;
        if (auxFocus < this->getAmmountOfButtons())
        {
            this->getFocusButton().setCurrentPosition(auxFocus + 1);
        }
        else
            this->getFocusButton().setCurrentPosition(1);

        for (Button b : this->getButtons())
        {
            if (b.getCurrentPosition() == this->getFocusButton().getCurrentPosition())
            {
                getFocusButton().setMidPoint(b.getMidPoint().x - 60, b.getMidPoint().y);
            }
        }
    }

    if (keys[4] && auxKeys[2] == 1)
    {
        auxKeys[2] = 0;

        switch (this->getFocusButton().getCurrentPosition())
        {
        case 1: // LEVEL
            return 2;

            break;

        case 2: // AJUDA
            return 1;
            break;
        }
    }
    return -1;
}

void Menu::drawButtons()
{
    for (Button b : getButtons())
    {
        glPushMatrix();
        glTranslatef(b.getMidPoint().x,
                     b.getMidPoint().y,
                     0);
        glCallList(b.getDisplayListModel());
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(getFocusButton().getMidPoint().x,
                 getFocusButton().getMidPoint().y,
                 0);
    glCallList(getFocusButton().getDisplayListModel());
    glPopMatrix();
}

void Menu::drawBackgroundMenu()
{
    for (Background b : getBackgrounds())
    {
        glPushMatrix();
        glTranslatef(b.getMidPoint().x,
                     b.getMidPoint().y,
                     0);
        glCallList(b.getDisplayListModel());
        glPopMatrix();
    }
}

void Menu::drawAndMove()
{
    drawBackgroundMenu();
    drawButtons();
}