#include "texture.h"
#include "log.h"

Texture::Texture() {
	//Init
	texture = NULL;
}

Texture::~Texture() {
	free();
}

bool Texture::loadFile(std::string path) {
	//Get rid of preexisting texture
	free();

	SDL_Texture* newTexture = NULL;
	newTexture = IMG_LoadTexture(renderer, path.c_str());
	if(newTexture == NULL) {
		LogIMG("IMG_Load");
	}

	texture = newTexture;
	return texture != NULL;
}

void Texture::renderTexture(SDL_Rect* rect) {
	//Render to screen
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Texture::free() {
	//Free texture if it exists
	if(texture != NULL){
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}