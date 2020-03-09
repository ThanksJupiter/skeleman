#pragma once

struct SDL_Rect;

void init_renderer();
void quit_renderer();

void draw_rect(SDL_Rect& dstRect);

void render();
