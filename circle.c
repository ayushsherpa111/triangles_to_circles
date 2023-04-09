#include "./circle.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>

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

  trig[3] = trig[0];

  // how many triangles is required
  int triangle_count = CIRCLE_ANGLE_RAD / fabsf(angle_r);
  cos_angle = cos(angle_r);
  sin_angle = sin(angle_r);
  printf("%d\n", triangle_count);
  for (int i = 0; i < triangle_count; i++) {
    // drawing the first triangle.
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
    SDL_SetRenderDrawColor(_rndr, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLinesF(_rndr, trig, 4);

  }
}
