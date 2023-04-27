#ifndef ENGINE_H
#define ENGINE_H
#include "texture.h"

class Engine {
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;
        
        //Font
        TTF_Font* gFont;

        //Init Engine
        bool init();

    //Init Texture
    bool initTexture();

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

        //Font texture;
        Texture font;

        void render();

        void renderClear();
};

#endif