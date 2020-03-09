#include "Renderer.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;

void init_renderer()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't initialize sdl :( %s\n", SDL_GetError());
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("Couldn't initialize img :( %s\n", SDL_GetError());
	}

	window = SDL_CreateWindow("skeleman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (window == NULL)
	{
		printf("Couldn't create window\n", SDL_GetError());
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer == NULL)
	{
		printf("Couldn't create renderer\n", SDL_GetError());
	}

	surface = IMG_Load("skel.png");
	if (surface == NULL)
	{
		printf("Couldn't load image\n", IMG_GetError());
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		printf("Couldn't create texture from surface\n", IMG_GetError());
	}
}

void quit_renderer()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void draw_rect(SDL_Rect& dstRect)
{
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
