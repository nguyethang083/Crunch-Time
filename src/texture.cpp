#include "texture.h"

Texture::Texture() {
	//Init
	texture = NULL;
	width = 0;
	height = 0;
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
	SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);

	texture = newTexture;
	return texture != NULL;
}

bool Texture::loadText(std::string textureText) {
	//Get rid of preexisting texture
	free();

	SDL_Color textColor = {255, 255, 255};

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if(textSurface == NULL) {
		LogTTF("TTF_RenderText");
	} else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if(texture == NULL) {
			LogSDL("CreateTextureFromSurface");
		} else {
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	return texture != NULL;
}

void Texture::free() {
	//Free texture if it exists
	if(texture != NULL){
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::render(SDL_Rect* renderRect) {
	//Render to screen
	SDL_RenderCopy(renderer, texture, NULL, renderRect);
}

void Texture::renderNew(int x, int y) {
	//Set rendering space and render to screen
	SDL_Rect renderRect = {x, y, width, height};

	//Render to screen
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);
}