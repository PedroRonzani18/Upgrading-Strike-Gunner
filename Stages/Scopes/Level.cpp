#include "../Header/Level.h"
#include <iostream>

#define SHOWHITBOX 0
#define GODMODE 1

Level::Level(const int &level)
{
    srand(time(0));
    std::vector<const char*> auxWaves;
    std::string fullPath = "Assets/Scripts/Waves/OrderWaves/orderLevel" + std::to_string(level+1) + ".txt";

    //25, 5, 6, 18, 23, 4, 8, 16, 20, 3, 24, 21, 0
    //26, 11, 18, 13, 14, 17, 19, 19, 19, 15, 22, 12, 99, 100, 27, 49, 50, 0

    for(auto path: Parser::parsePath(Parser::stringToArray(fullPath)))
        auxWaves.push_back(path);

    initBackgrounds(level);

    player.setMidPoint(0, -80);
    this->addWaves(auxWaves);
    this->scorePontis = Score(0);
    addMusic(level);
    startMusic();
}

void Level::addMusic(int level)
{
    std::string fullPath = "Assets/Scripts/Audio/Musics/level" + std::to_string(level+1) + "Musics.txt";

    for(const char* path: Parser::parsePath(Parser::stringToArray(fullPath)))
        musicalizer->addMusic(Mix_LoadMUS(path));

    fullPath = "Assets/Scripts/Audio/SoundEffects/level" + std::to_string(level+1) + "SoundEffects.txt";

    //for(const char* path: Parser::parsePath(Parser::stringToArray(fullPath)))
    //    musicalizer->addSoundEffect(Mix_load(path));
}

// Inicia a reproducao da musica
void Level::startMusic()
{
    Mix_FadeOutMusic(1);

    if(musicalizer->getMusics().size() > 0){
        if(!Mix_PausedMusic())
            Mix_PlayMusic(musicalizer->getFinalMusic(),-1);
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
            b2.setDisplayListModel(textures[10]);
            break;

        case 1:
            b1.setDisplayListModel(textures[39]);
            b2.setDisplayListModel(textures[40]);
            break;
    }
    
    b1.setMidPoint(0, 0);
    backgrounds.push_back(b1);
    b2.setMidPoint(0, 200);
    backgrounds.push_back(b2);
}

void Level::callWaves()
{
    std::vector<Enemy> auxiliar;
    if ((!waves.empty()) && (enemies.empty()))
    {
        bossTime = 0;
        for (Enemy enemy : waveTemplateGeneral(waves.front())) addEnemy(enemy);
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
            auxD = sqrt(pow((m1->getMidPoint().x - enemies[i].getMidPoint().x), 2) +
                        pow((m1->getMidPoint().y - enemies[i].getMidPoint().y), 2));

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
            projectiles.clear();
            enemies.clear();
            waves.clear();
            waves.push_back("Assets/Scripts/Waves/TitleWaves/waveGameOver.txt");
        }

        player.deathMove();

        if (player.getResize() <= 0) // significa que player morreu e desapareceu da tela
            return 0; // volta para o menu
    }
    else if (waves.empty()) // se acabaram as waves e o player está vivo, muda de level
        return 2;
    
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

    if(SHOWHITBOX) drawHitbox(&this->player);

    if(bossTime && player.getHp() >= 0){
        boss.move();
        drawModel(&boss);
    }


    for (size_t i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].move();
        drawModel(&projectiles[i]);
        if(SHOWHITBOX) drawHitbox(&projectiles[i]);
    }

    double hp = 0;
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if(bossTime)
        {
            enemies[i].setMidPoint(boss.getMidPoint().x + enemies[i].getVelocity().x, 
                                   boss.getMidPoint().y + enemies[i].getVelocity().y);
            hp += enemies[i].getHp();
        }
        
        enemies[i].move(); // movimentação gerall de cada inimigo
        if (enemies[i].getType() == 5)
            drawModel(&enemies[i], 3.734, 0);
        else if (enemies[i].getType() == 9)
            drawModel(&enemies[i], 6, 0);
        else
            drawModel(&enemies[i]);

        if(SHOWHITBOX) drawHitbox(&enemies[i]);

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
        if(SHOWHITBOX) drawHitbox(&colectibles[i]);
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
        enemies[i].setFollowPoint(player.getMidPoint().x, player.getMidPoint().y);
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

                        if(!GODMODE) {
                            if(player.getHp() > 0)
                            {
                                player.setMidPoint(0, -80);
                            }
                            
                            player.setHp(player.getHp() - projectiles[i].getDamage());
                            player.damage();
                        }
                    }
                }
            }
        }

        if (colided(enemies[j], player) && enemies[j].getType() != 10 && enemies[j].getType() != 7)
        {                                                           // colisao dos inimigos com o player
            if (player.getImortality() <= 0 && player.getHp() >= 0) // quando ele nao ta imortal
            {
                enemies[j].setHp(enemies[j].getHp() - player.getCurrentProjectile().getDamage() * 7);
                
                if(!GODMODE) {
                    if(player.getHp() > 0)
                    {
                        player.setMidPoint(0, -80);
                    }
                    player.setHp(player.getHp() - 1);
                    player.damage();
                }
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
                Colectible c(enemies[i].getMidPoint().x,
                             enemies[i].getMidPoint().y);
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