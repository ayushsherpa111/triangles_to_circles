#include "./circle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const int WIDTH = 600;
static const int HEIGHT = 600;

#define CENTER_X WIDTH / 2.0
#define CENTER_Y HEIGHT / 2.0

void draw_triangle() {
  SDL_Point *points = malloc(sizeof(SDL_Point) * 3);
  points[0].x = 30;
  points[0].y = 30;
}

double to_radians(double degree) { return degree * (M_PI/ 180.0); }

int main() {
  SDL_Renderer *renderer;
  SDL_Window *window;
  int8_t is_running;
  uint32_t *framebuffer;
  double angle = -1 * to_radians(10.0);
  int radius = 150;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  window =
      SDL_CreateWindow("Triangle", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  is_running = 1;

  draw_circle(renderer, CENTER_X, CENTER_Y, angle, radius);
  while (is_running) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_KEYDOWN) {
        is_running = 0;
      }
    }
    // Clear screen
    // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);

    // create assets to draw
    // SDL_RenderDrawLinesF(renderer, trig, 4);

    // render
    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

/*
  trig = malloc(sizeof(SDL_FPoint) * 4);

  // center
  trig[0].x = CENTER_X;
  trig[0].y = CENTER_Y;

  trig[1].x = trig[0].x;
  trig[1].y = trig[0].y - radius;

  float translateX = trig[1].x - trig[0].x;
  float translateY = (-1 * trig[1].y) - (-1 * trig[0].y);

  float cos_angle = cos(angle);
  float sin_angle = sin(angle);

  trig[2].x = (cos_angle * translateX - sin_angle * translateY) + trig[0].x;
  trig[2].y =
      (-1 * (sin_angle * translateX + cos_angle * translateY)) + trig[0].y;

  trig[3] = trig[0];

  printf("%f %f\n", trig[0].x, trig[0].y);
  printf("%f %f\n", trig[1].x, trig[1].y);
  printf("%f %f\n", trig[2].x, trig[2].y);
*/
