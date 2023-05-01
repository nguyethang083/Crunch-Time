#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_image.h>
#include "common.h"

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

		/* Renders texture to an existing SDL_Rect
		   rect = NULL if render to entire screen */
		void renderRect(SDL_Rect* rect);

		//Renders to a new SDL_Rect from image's dimensions
		void renderNewRect(int x, int y);

};

#endif