#include "../Header/Level.h"

        #include <iostream>

Level::Level(const int &level)
{
    srand(time(0));
    std::vector<int> auxWaves;
    switch (level)
    {
        case 0:
            addWavesScripts();
            auxWaves = {25, 5, 6, 18, 23, 4, 8, 16, 20, 3, 24, 21, 0}; // executa todas as waves e para na wave 0
            initBackgrounds(0);
            break;

        case 1:
            auxWaves = {26, 11, 18, 13, 14, 17, 19, 19, 19, 15, 22, 12, 99, 100, 27, 49, 50, 0};
            initBackgrounds(1);
            break;
    }

    player.setMidPoint(0, -80);
    this->addWaves(auxWaves);
    this->scorePontis = Score(0);
    startMusic(level);
}

void Level::startMusic(int level)
{
    Mix_FadeOutMusic(1);
    std::string fullPath = "Assets/Scripts/Audios/level" + std::to_string(level+1) + "Musics.txt";

    for(const char* path: Parser::parsePath(Parser::stringToArray(fullPath)))
        musicalizer->addMusic(Mix_LoadMUS(path));

    // Inicia a reproducao da musica
    if(musicalizer->getMusics().size() > 0){
        if(!Mix_PausedMusic())
            Mix_PlayMusic(musicalizer->getMusic(0),-1);
        Mix_VolumeMusic(70);
    }
}

void Level::initBackgrounds(const int &typeBackground)
{
    Background b1;
    Background b2;
    backgrounds.resize(0);

    switch (typeBackground)
    {
        case 0:

            b1.setDisplayListModel(textures[9]);
            b1.setMidPoint(0, 0);
            backgrounds.push_back(b1);

            b2.setDisplayListModel(textures[10]);
            b2.setMidPoint(0, 200);
            backgrounds.push_back(b2);
            break;

        case 1:

            b1.setDisplayListModel(textures[39]);
            b1.setMidPoint(0, 0);
            backgrounds.push_back(b1);

            b2.setDisplayListModel(textures[40]);
            b2.setMidPoint(0, 200);
            backgrounds.push_back(b2);
            break;
    }
}

void Level::callWaves()
{
    std::vector<Enemy> auxiliar;
    if ((waves.size() > 0) && (enemies.size() == 0))
    {
        bossTime = 0;
        auxiliar = waveCaller(waves[0]);

        for (Enemy e : auxiliar)
        {
            addEnemy(e);
        }

        waves.erase(waves.begin());
    }
}

Enemy* Level::smallestDistanceEnemyPlayer(MovableEntity *m1)
{
    Enemy *auxEnemy = new Enemy();
    auxEnemy->setMidPoint(0, 200);

    double smallesDist = 10000;

    double auxD;

    for (size_t i = 0; i < enemies.size(); i++)
    {
        if(enemies[i].getType() != 10 && enemies[i].getType() != 7){
            auxD = sqrt(pow((m1->getMidPoint().getX() - enemies[i].getMidPoint().getX()), 2) +
                        pow((m1->getMidPoint().getY() - enemies[i].getMidPoint().getY()), 2));

            if (auxD < smallesDist && &enemies[i] != nullptr)
            {
                auxEnemy = &enemies[i];
                smallesDist = auxD;
            }
        } 
    }

    return auxEnemy;
}

int Level::stageKeyboard()
{
    if (keys[4] && player.getFireRatePeriod() <= 0 && player.getHp() >= 0) // space
    {
        std::vector<Projectile> p = player.fire();
        projectiles.insert(projectiles.end(), p.begin(), p.end());
    }

    if (player.getHp() < 0)
    {
        if(player.getResize() == 0.5){
            enemies.clear();
            waves.clear();
            
            waves.push_back(28);
            waves.push_back(0);
        }

        player.deathMove();

        if (player.getResize() <= 0) // significa que player morreu e desapareceu da tela
        {
            return 0; // volta para o menu
        }
    }

    if (waves.size() == 0 && player.getHp() >= 0) // se acabaram as waves e o player está vivo, muda de level
    {
        return 2;
    }

    return -1; // chama o level
}

void Level::drawAndMove()
{
    for (size_t i = 0; i < backgrounds.size(); i++)
    {
        if(bossTime) backgrounds[i].setVelocity(0, 1.8);
        else backgrounds[i].setVelocity(0, 0.3);
        backgrounds[i].move();
        drawModel(&backgrounds[i]);
    }

    this->player.move(); // movimentação geral do player
    drawModel(&this->player);
    //drawHitbox(&this->player);

    if(bossTime && player.getHp() >= 0){
        boss.move();
        drawModel(&boss);
    }


    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].move();
        drawModel(&projectiles[i]);
        //drawHitbox(&projectiles[i]);
    }

    double hp = 0;
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if(bossTime)
        {
            enemies[i].setMidPoint(boss.getMidPoint().getX() + enemies[i].getVelocity().getX(), 
                                   boss.getMidPoint().getY() + enemies[i].getVelocity().getY());
            hp += enemies[i].getHp();
        }
        
        enemies[i].move(); // movimentação gerall de cada inimigo
        if (enemies[i].getType() == 5)
            drawModel(&enemies[i], 3.734, 0);
        else if (enemies[i].getType() == 9)
            drawModel(&enemies[i], 6, 0);
        else
            drawModel(&enemies[i]);

        //drawHitbox(&enemies[i]);

        if (enemies[i].getFireRatePeriod() <= 0)
        {
            std::vector<Projectile> p = enemies[i].fire();
            projectiles.insert(projectiles.end(), p.begin(), p.end());
        }
    }
    boss.setHp(hp);

    for (size_t i = 0; i < colectibles.size(); i++)
    {
        colectibles[i].move();
        drawModel(&colectibles[i]);
        //drawHitbox(&colectibles[i]);
    }

    boss.getHealthBar().setScore(1 - boss.getHp()/boss.getVidaTotal());
    if(bossTime) boss.getHealthBar().draw();

    player.getScoreHp().draw();
    scorePontis.draw();
}

void Level::timeCounter()
{
    if (player.getFireRatePeriod() >= 0)
        player.setFireRatePeriod(player.getFireRatePeriod() - 1);

    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].getFireRatePeriod() >= 0)
            enemies[i].setFireRatePeriod(enemies[i].getFireRatePeriod() - 1);
        enemies[i].setFollowPoint(player.getMidPoint().getX(), player.getMidPoint().getY());
    }

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        if (projectiles[i].getType() == 2)
        {
            Enemy *e = smallestDistanceEnemyPlayer(&projectiles[i]);
            projectiles[i].setFollowedEnemy(e);
        }
        else if (projectiles[i].getType() == 5)
        {
            projectiles[i].setFollowedEnemy(&player);
        }
    }

    if (player.getImortality() >= 0)
        player.setImortality(player.getImortality() - 1);
}

void Level::colider() // proibido.
{
    for (size_t j = 0; j < enemies.size(); j++)
    {
        for (size_t i = 0; i < projectiles.size(); i++)
        {
            if (projectiles[i].getOwner() == 1)
            {
                if (colided(projectiles[i], enemies[j]) && enemies[j].getType() != 10 && enemies[j].getType() != 7) // colisao dos tiros do player com o inimido
                {
                    projectiles[i].setHp(0);
                    enemies[j].setHp(enemies[j].getHp() - projectiles[i].getDamage());
                }
            }
            else if (projectiles[i].getOwner() == 2)
            {
                if (colided(projectiles[i], player)) // colisao dos tiros dos inimigos com o player
                {
                    if (player.getImortality() <= 0 && player.getHp() >= 0)
                    {
                        projectiles[i].setHp(0);
                        /*
                        if(player.getHp() > 0)
                        {
                            player.setMidPoint(0, -80);
                        }
                        
                        player.setHp(player.getHp() - projectiles[i].getDamage());
                        player.damage();
                        */
                    }
                }
            }
        }

        if (colided(enemies[j], player) && enemies[j].getType() != 10 && enemies[j].getType() != 7)
        {                                                           // colisao dos inimigos com o player
            if (player.getImortality() <= 0 && player.getHp() >= 0) // quando ele nao ta imortal
            {
                enemies[j].setHp(enemies[j].getHp() - player.getCurrentProjectile().getDamage() * 7);
                /*
                if(player.getHp() > 0)
                {
                    player.setMidPoint(0, -80);
                }
                player.setHp(player.getHp() - 1);
                player.damage();
                */
            }
        }
    }

    for (size_t i = 0; i < colectibles.size(); i++)
    {
        if (colided(colectibles[i], player) && player.getHp() >= 0)
        { // colidiu coletavel com player
            player.upgradeManager(colectibles[i].getUpgradeType());
            colectibles[i].setHp(0);
        }
    }

    remover(); // nao aguento mais corrigir erro de colisao haaaaaaaaaaaaaaaaaa
}

void Level::remover()
{
    for (size_t i = 0; i < enemies.size(); i++)
    {
        int aux = 0;
        if (enemies[i].getHp() <= 0)
        {
            scorePontis.setScore(scorePontis.getScore() + enemies[i].getKillValue());

            int r = rand() % 100;

            if (r <= enemies[i].getDropPercentage())
            {
                Colectible c(enemies[i].getMidPoint().getX(),
                             enemies[i].getMidPoint().getY());
                mantainInsideScreen(c);
                colectibles.push_back(c);
            }

            aux = 1;
        }

        if (!enemies[i].getOnScreen() && enemies[i].getOnscreenTestable()) // se está fora da tela, e é para ser testado, remove ele
            aux = 1;

        if (aux)
            enemies.erase(enemies.begin() + i);
    }

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        if (projectiles[i].getHp() <= 0 || !projectiles[i].getOnScreen())
            projectiles.erase(projectiles.begin() + i);
    }

    for (size_t i = 0; i < colectibles.size(); i++)
    {
        if (colectibles[i].getHp() <= 0 || !colectibles[i].getOnScreen())
            colectibles.erase(colectibles.begin() + i);
    }
}