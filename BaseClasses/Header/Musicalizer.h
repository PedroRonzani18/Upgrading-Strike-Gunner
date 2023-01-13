#ifndef _Musicalizer_H
#define _Musicalizer_H

#include <SDL2/SDL_mixer.h>
#include <vector>

class Musicalizer
{
    private:
        std::vector<Mix_Music*> musics;
        std::vector<Mix_Chunk*> soundEffects;
    
    public:
        Musicalizer();

        Mix_Music* getMusic(const int& i){return this->musics[i];}
        Mix_Music* getFinalMusic()const{return this->musics.back();}
        std::vector<Mix_Music*> getMusics(){return this->musics;}
        void addMusic(Mix_Music* music){this->musics.push_back(music);}

        Mix_Chunk* getSoundEffect(const int& i){return this->soundEffects[i];}
        std::vector<Mix_Chunk*> getSoundEffects(){return this->soundEffects;}
        void addSoundEffect(Mix_Chunk* soundEffect){this->soundEffects.push_back(soundEffect);}
};

#endif