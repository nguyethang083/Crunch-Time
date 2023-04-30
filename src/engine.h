#ifndef ENGINE_H
#define ENGINE_H
#include "texture.h"

class Engine {
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;
        
        bool success;

        //Init Engine
        bool init();

        //Init Texture
        bool initTexture();

        //Init font
        bool initFont();

        void exit();

    public:
        Engine();
        ~Engine();

        //Board texture
        Texture boardTexture;

        //Canides textures
        Texture candyTexture[Total];

        //Selector texture
        Texture selectorTexture;

        //Score texture
        Texture scoreTexture;

        //Font texture;
        Texture numberFont;
        Texture letterFont;

        void render();

        void renderClear();
};

#endif