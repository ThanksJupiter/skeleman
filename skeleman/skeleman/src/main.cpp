#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

struct Vec2
{
	float x;
	float y;
};

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* surface;
SDL_Texture* texture;

bool isRunning = true;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Vec2 rectPosition = { 300.0f, 300.0f };

SDL_Rect dstRect =
{
	0.0f, 0.0f,
	100.0f, 100.0f
};

void Init()
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

int main()
{
	Init();

	while (isRunning)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_w:
						rectPosition.y -= 10.0f;
						break;
					case SDLK_s:
						rectPosition.y += 10.0f;
						break;
					case SDLK_d:
						rectPosition.x += 10.0f;
						break;
					case SDLK_a:
						rectPosition.x -= 10.0f;
						break;
				}
			}
		}

		dstRect.x = rectPosition.x;
		dstRect.y = rectPosition.y;

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
