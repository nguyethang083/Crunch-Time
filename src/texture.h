#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_image.h>
#include "common.h"

class Texture {
	private:
		//The actual hardware texture
		SDL_Texture* texture;

		//Deallocates texture
		void free();

	public:
		//Initializes variables
		Texture();

		//Deallocates memory
		~Texture();

		//Loads image at specified path
		bool loadFile(const std::string &path);

		/* Renders texture to an existing SDL_Rect
		   rect = NULL if render to entire screen */
		
		void renderTexture(SDL_Rect* rect = NULL);

};

#endif