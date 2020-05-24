//Using SDL and standard IO
//#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm> // For erase-remove idiom
#include <cmath>
//#include <string>

#include "SDL_FontCache.h"

#include "SDLMgmt.h"
#include "Actor.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int DEBUG_FONT_PT = 16;

int main(int argc, char** argv)
{
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized. SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create SDL Window
		SDL_Window* window = SDL_CreateWindow("SDL Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("Window could not be created. SDL_ERROR: %s\n", SDL_GetError());
		}
		else
		{
			//Create SDL Renderer
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
			if(renderer == NULL)
			{
				printf("Could not create renderer. SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				//Get renderer dimensions
				int iRendererW;
				int iRendererH;
				SDL_GetRendererOutputSize(renderer, &iRendererW, &iRendererH);

				std::vector<SDL_Surface*> vSurfaces;
				std::vector<SDL_Texture*> vTextures;

				//Initialize font cache
				TTF_Init();
				FC_Font* fontConsolas = FC_CreateFont();
				FC_LoadFont(fontConsolas, renderer, R"(C:\Windows\Fonts\consola.ttf)", DEBUG_FONT_PT, FC_MakeColor(255, 255, 0, 255), TTF_STYLE_NORMAL);
				
				SDL_Event e;
				
				//Initialize frame timing
				Uint64 iTimingLast = SDL_GetPerformanceCounter();
				Uint64 iTimingNow = iTimingLast;

				Actor actImg(renderer, R"(C:\Users\Sterculius\Downloads\Img2.bmp)");

				int iImgMovX = 0;
				int iImgMovY = 0;
				const float fImgMovSpeed = 128.0f; // px/s

				bool bQuit = false;

				//Enter main loop
				while(!bQuit)
				{
					//Calculate frame timing
					iTimingLast = iTimingNow;
					iTimingNow = SDL_GetPerformanceCounter();
					float fTimingElapsed = (iTimingNow - iTimingLast) / (float)SDL_GetPerformanceFrequency();

					//Process Events
					while(SDL_PollEvent(&e))
					{
						if(e.type == SDL_KEYDOWN)
						{
							switch(e.key.keysym.sym)
							{
								case SDLK_d:
									iImgMovX++;
									break;
								case SDLK_a:
									iImgMovX--;
									break;
								case SDLK_w:
									iImgMovY--;
									break;
								case SDLK_s:
									iImgMovY++;
									break;
							}
						}
						else if(e.type == SDL_KEYUP)
						{
							switch(e.key.keysym.sym)
							{
								case SDLK_d:
									iImgMovX--;
									break;
								case SDLK_a:
									iImgMovX++;
									break;
								case SDLK_w:
									iImgMovY++;
									break;
								case SDLK_s:
									iImgMovY--;
									break;
								case SDLK_ESCAPE:
									bQuit = true;
									break;
							}
						}
						else if(e.type == SDL_QUIT)
						{
							bQuit = true;
						}
					}

					//Clamp actor inputs
					iImgMovX = std::clamp(iImgMovX, -1, 1);
					iImgMovY = std::clamp(iImgMovY, -1, 1);

					//Velocitate actor
					actImg.Move((float)iImgMovX * fImgMovSpeed * fTimingElapsed, (float)iImgMovY * fImgMovSpeed * fTimingElapsed);
						
					//Clamp actor within bounds of renderer/window
					actImg.SetPosX(std::clamp(actImg.GetPosX(), 0.0f, (float)(iRendererW - actImg.GetWidth())));
					actImg.SetPosY(std::clamp(actImg.GetPosY(), 0.0f, (float)(iRendererH - actImg.GetHeight())));

					//Start Rendering

					//Clear renderer with background colour
					SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
					SDL_RenderClear(renderer);

					//Render actor
					actImg.Render();

					//Debug text - FPS
					SDLFillRect(renderer, 0, 0 * DEBUG_FONT_PT, FC_GetWidth(fontConsolas, "FPS: %.1f", 1 / fTimingElapsed), DEBUG_FONT_PT, { 0, 0, 0, 255 });
					FC_Draw(fontConsolas, renderer, 0, 0 * DEBUG_FONT_PT, "FPS: %.1f", 1 / fTimingElapsed);

					//Debug text - Seconds elapsed
					SDLFillRect(renderer, 0, 1 * DEBUG_FONT_PT, FC_GetWidth(fontConsolas, "fTimingElapsed: %f", fTimingElapsed), DEBUG_FONT_PT, { 0, 0, 0, 255 });
					FC_Draw(fontConsolas, renderer, 0, 1 * DEBUG_FONT_PT, "fTimingElapsed: %f", fTimingElapsed);

					//Debug text - Actor position
					SDLFillRect(renderer, 0, 2 * DEBUG_FONT_PT, FC_GetWidth(fontConsolas, "actImg Pos: (%.1f,%.1f)", actImg.GetPosX(), actImg.GetPosY()), DEBUG_FONT_PT, { 0, 0, 0, 255 });
					FC_Draw(fontConsolas, renderer, 0, 2 * DEBUG_FONT_PT, "actImg Pos: (%.1f,%.1f)", actImg.GetPosX(), actImg.GetPosY());

					//Debug text - Actor inputs
					SDLFillRect(renderer, 0, 3 * DEBUG_FONT_PT, FC_GetWidth(fontConsolas, "iImgMov: (%d,%d)", iImgMovX, iImgMovY), DEBUG_FONT_PT, { 0, 0, 0, 255 });
					FC_Draw(fontConsolas, renderer, 0, 3 * DEBUG_FONT_PT, "iImgMov: (%d,%d)", iImgMovX, iImgMovY);

					//Present frame
					SDL_RenderPresent(renderer);

					//Wait two seconds
					//SDL_Delay(500);
				}

				//Clean your room
				FC_FreeFont(fontConsolas);
				fontConsolas = NULL;
				TTF_Quit();

				SDLFreeAssetVector(&vTextures);
				SDLFreeAssetVector(&vSurfaces);

				SDL_DestroyRenderer(renderer);
				renderer = NULL;
			}

			SDL_DestroyWindow(window);
			window = NULL;
		}

		SDL_Quit();
	}

	//Smell ya later
	return 0;
}