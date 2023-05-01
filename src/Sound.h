#ifndef SOUND_H
#define SOUND_H
#include <SDL_mixer.h>
#include "common.h"

class Sound {
    private:
        Mix_Music* music;
        Mix_Chunk* sfx;

    public:
        Sound();
        ~Sound();

        //Load sound
        bool loadMusic(std::string path);
        bool loadSFX(std::string path);

        //Sound control
        void playMusic();
        void stopMusic();
        void playSFX();

        //Deallocates sound 
        void free();
};

#endif