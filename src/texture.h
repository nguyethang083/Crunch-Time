#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "common.h"
#include "log.h"

class Texture {
	private:
		//The actual hardware texture
		SDL_Texture* texture;

		//Image dimensions
		int width;
		int height;

		//Deallocates texture
		void free();

	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFile(std::string path);

		//Creates image from font string
		bool loadText(TTF_Font* gFont, std::string textureText, SDL_Color textColor);

		//Renders texture to an existing SDL_Rect
		void render(SDL_Rect* renderRect);

		//Renders to a new SDL_Rect from image's dimensions
		void renderNew(int x, int y);

};

#endif