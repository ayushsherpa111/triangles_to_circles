#include "./circle.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdlib.h>

float map_y_origin(float y) { return -1.0 * y; }
const float CIRCLE_ANGLE_RAD = 360 * (M_PI / 180.0);

static float sin_angle;
static float cos_angle;
static const int Point_Count = 3;
float translate_X(float x, float y) { return cos_angle * x - sin_angle * y; }

float translate_Y(float x, float y) { return sin_angle * x + cos_angle * y; }

void draw_circle(SDL_Renderer *_rndr, float ox, float oy, float angle_r,
                 float radius) {
  // initalize center
  SDL_FPoint *trig = malloc(sizeof(SDL_FPoint) * 4);
  trig[0].x = ox;
  trig[0].y = oy;

  // how many triangles is required
  int triangle_count = CIRCLE_ANGLE_RAD / fabsf(angle_r);
  cos_angle = cos(angle_r);
  sin_angle = sin(angle_r);

  for (int i = 0; i < triangle_count; i++) {
    // drawing the first triangle.
    draw_circle_pbp(trig, angle_r, radius);
    SDL_SetRenderDrawColor(_rndr, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPointsF(_rndr, trig, 3);
  }
}

void draw_circle_pbp(SDL_FPoint *center, float angle_r, float radius) {
  cos_angle = cos(angle_r);
  sin_angle = sin(angle_r);

  if (center[1].x == 0 && center[1].y == 0){
    center[1].x = center[0].x;
    center[1].y = center[0].y - radius;
  } else {
    center[1].x = center[2].x;
    center[1].y = center[2].y;
  }

  float offsetX = center[1].x - center[0].x;
  float offsetY = map_y_origin(center[1].y) - map_y_origin(center[0].y);

  center[2].x = translate_X(offsetX, offsetY) + center[0].x;
  center[2].y = map_y_origin(translate_Y(offsetX, offsetY)) + center[0].y;
}
/*
  if (i == 0) {
    // calculate the first point
    trig[1].x = trig[0].x;
    trig[1].y = trig[0].y - radius;
  } else {
    // end of the previous
    trig[1].x = trig[2].x;
    trig[1].y = trig[2].y;
  }
  float offsetX = trig[1].x - trig[0].x;
  float offsetY = map_y_origin(trig[1].y) - map_y_origin(trig[0].y);

  trig[2].x = translate_X(offsetX, offsetY) + trig[0].x;
  trig[2].y = map_y_origin(translate_Y(offsetX, offsetY)) + trig[0].y;
*/
