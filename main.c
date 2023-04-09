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
#include <time.h>

static const int WIDTH = 600;
static const int HEIGHT = 600;

#define CENTER_X WIDTH / 2.0
#define CENTER_Y HEIGHT / 2.0

void draw_triangle() {
  SDL_Point *points = malloc(sizeof(SDL_Point) * 3);
  points[0].x = 30;
  points[0].y = 30;
}

double to_radians(double degree) { return degree * (M_PI / 180.0); }

int main(int argc, char **argv) {
  SDL_Renderer *renderer;
  SDL_Window *window;
  int8_t is_running;
  uint32_t *framebuffer;
  SDL_FPoint *center;
  double angle = -1 * to_radians(10.0);
  int radius = 150;

  // first argument radius of circle
  if (argc > 1) {
    radius = atoi(argv[1]);
  }

  if (argc > 2) {
    angle = -1 * to_radians(atof(argv[2]));
  }
  printf("Drawing with angle %f and radius %d\n", angle, radius);

  srand(time(NULL));
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  window =
      SDL_CreateWindow("Triangle", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  is_running = 1;
  center = malloc(sizeof(SDL_FPoint) * 3);
  center[0].x = CENTER_X;
  center[0].y = CENTER_Y;

  center[1].x = 0;
  center[1].y = 0;

  while (is_running) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym) {
          case SDLK_q:
          is_running = 0;
          break;
        default: ;
        }
      }
    }
    // Clear screen
    // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);

    // create assets to draw
    uint8_t R = rand() % 0x100;
    uint8_t G = rand() % 0x100;
    uint8_t B = rand() % 0x100;
    SDL_SetRenderDrawColor(renderer, R, G, B, SDL_ALPHA_OPAQUE);
    // SDL_RenderDrawLinesF(renderer, trig, 4);
    draw_circle_pbp(center, angle, radius);
    SDL_RenderDrawLinesF(renderer, center, 3);
    // render
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  free(center);
}
