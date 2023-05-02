#ifndef TEXT_H
#define TEXT_H
#include <SDL_ttf.h>
#include "common.h"

class Text {
    private:
        TTF_Font* font;

        //The actual hardware texture
		SDL_Texture* texture;

		//Text dimensions
		int width;
		int height;

        //Deallocates texture
        void free();

    public:
        Text();

        //Open font
		bool openFont(int size);

		//Creates image from font string
		bool loadText(std::string textureText);

		/* Render text in center horizontally if x = -1, vertically if y = -1
		   rect = NULL if render to entire screen	*/
		void renderText(int x, int y, SDL_Rect* rect = NULL);
};

#endif