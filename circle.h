#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void draw_circle(SDL_Renderer *_rndr, float ox, float oy, float angle_r,float radius);

void draw_circle_pbp(SDL_FPoint *center, float angle_r, float radius);
