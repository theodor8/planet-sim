#pragma once

#include <stdlib.h>

typedef struct
{
    float x, y;
    float vx, vy;
    float r, mass;
    int id;
    float *prev_xs;
    float *prev_ys;
    int prev_i;
    size_t prev_siz;
} planet_t;


planet_t *planet_create(float x, float y, float vx, float vy, float r, int id);
void planet_destroy(planet_t *p);

void planet_update(planet_t *p, float dt);
void planet_apply_force(planet_t *p, float fx, float fy, float dt);
void planet_apply_gravity(planet_t *p1, planet_t *p2, float gravity, float dt);

