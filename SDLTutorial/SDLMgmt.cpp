#include <stdio.h>
#include <SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "SDL_FontCache.h"

#include "SDLMgmt.h"

void SDLFreeAssetVector(std::vector<SDL_Surface*>* vSurfaces)
{
	for(std::vector<SDL_Surface*>::iterator it = vSurfaces->begin();it != vSurfaces->end();++it)
	{
		SDL_FreeSurface(*it);
		*it = NULL;
	}

	vSurfaces->erase(std::remove(vSurfaces->begin(), vSurfaces->end(), (SDL_Surface*)NULL), vSurfaces->end());
}

void SDLFreeAssetVector(std::vector<SDL_Texture*>* vTextures)
{
	for(std::vector<SDL_Texture*>::iterator it = vTextures->begin();it != vTextures->end();++it)
	{
		SDL_DestroyTexture(*it);
		*it = NULL;
	}

	vTextures->erase(std::remove(vTextures->begin(), vTextures->end(), (SDL_Texture*)NULL), vTextures->end());
}

SDL_Surface* SDLLoadBMPtoOptimizedSurface(SDL_Surface* surfScreen, const char* path)
{
	SDL_Surface* surfLoaded = SDL_LoadBMP(path);
	SDL_Surface* surfOptimized = NULL;

	if(surfLoaded == NULL)
	{
		printf("Could not load image \"%s\". SDL_ERROR: %s\n", path, SDL_GetError());
	}
	else
	{
		surfOptimized = SDL_ConvertSurface(surfLoaded, surfScreen->format, 0);
		if(surfOptimized == NULL)
		{
			printf("Could not optimize surface for \"%s\". SDL_ERROR: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(surfLoaded);
	}

	return surfOptimized;
}

SDL_Texture* SDLLoadBMPtoTexture(SDL_Renderer* renderer, const char* path)
{
	SDL_Surface* surfLoaded = SDL_LoadBMP(path);
	SDL_Texture* texLoaded = NULL;

	if(surfLoaded == NULL)
	{
		printf("Could not load image \"%s\". SDL_ERROR: %s\n", path, SDL_GetError());
	}
	else
	{
		texLoaded = SDL_CreateTextureFromSurface(renderer, surfLoaded);
		if(texLoaded == NULL)
		{
			printf("Could not create texture for \"%s\". SDL_ERROR: %s\n", path, SDL_GetError());
		}

		SDL_FreeSurface(surfLoaded);
	}

	return texLoaded;
}

HSV RGBtoHSV(SDL_Color rgb)
{
	float R = (float)rgb.r / 255;
	float G = (float)rgb.g / 255;
	float B = (float)rgb.b / 255;
	float M = std::max({ R, G, B });
	float m = std::min({ R, G, B });
	float C = M - m;
	float Hp;
	float H;
	float S;

	if(C == 0)
	{
		Hp = NULL;
	}
	else if(R >= G && R >= B)
	{
		Hp = (float)std::fmod((G - B) / C, 6);
	}
	else if(G >= R && G >= B)
	{
		Hp = (B - R) / C + 2;
	}
	else if(B >= R && B >= G)
	{
		Hp = (R - G) / C + 4;
	}
	else
	{
		throw 1;
	}

	H = Hp / 6;

	if(M == 0)
	{
		S = 0;
	}
	else
	{
		S = C / M;
	}

	HSV hsv = { (Uint8)(H * 255), (Uint8)(S * 255), (Uint8)(M * 255), rgb.a };

	/*hsv.h = (Uint8)(H * 255);
	hsv.s = (Uint8)(S * 255);
	hsv.v = (Uint8)(M * 255);
	hsv.a = rgb.a;*/

	return hsv;
}

SDL_Rect SDLFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color fillColor)
{
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);

	return rect;
}