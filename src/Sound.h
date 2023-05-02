#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>
#include "common.h"

class Sound {
    private:
        Mix_Music* music;
        Mix_Chunk* sfx;

        //Deallocates sound 
        void free();

    public:
        Sound();
        ~Sound();

        //Load sound
        bool loadMusic(const std::string &path);
        bool loadSFX(const std::string &path);

        //Sound control
        void playMusic();
        void stopMusic();
        void playSFX();

};

#endif