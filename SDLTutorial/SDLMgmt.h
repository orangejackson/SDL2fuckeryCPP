#ifndef SDLMGMT_H
#define SDLMGMT_H

#include <SDL.h>
#include <vector>

struct HSV
{
	Uint8 h;
	Uint8 s;
	Uint8 v;
	Uint8 a;
};

void SDLFreeAssetVector(std::vector<SDL_Surface*>* vSurfaces);
void SDLFreeAssetVector(std::vector<SDL_Texture*>* vTextures);

SDL_Surface* SDLLoadBMPtoOptimizedSurface(SDL_Surface* surfScreen, const char* path);
SDL_Texture* SDLLoadBMPtoTexture(SDL_Renderer* renderer, const char* path);

HSV RGBtoHSV(SDL_Color rgb);

SDL_Rect SDLFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color fillColor);

#endif //SDLMGMT_H