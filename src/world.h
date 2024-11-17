#pragma once

#include <stdlib.h>

#include "planet.h"

typedef struct
{
    planet_t **planets;
    size_t planets_i, planets_siz;
    float gravity;
} world_t;

world_t *world_create(float gravity);
void world_destroy(world_t *w);

void world_add_planet(world_t *w, planet_t *p);

void world_update(world_t *w, float dt);

