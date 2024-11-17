#include "world.h"

#include <stdlib.h>

#include "planet.h"


world_t *world_create(float gravity)
{
    world_t *w = calloc(1, sizeof(world_t));
    w->planets_siz = 10;
    w->planets = calloc(w->planets_siz, sizeof(planet_t *));
    w->gravity = gravity;
    return w;
}

void world_destroy(world_t *w)
{
    for (int i = 0; i < w->planets_i; ++i)
    {
        planet_destroy(w->planets[i]);
    }
    free(w->planets);
    free(w);
}




void world_add_planet(world_t *w, planet_t *p)
{
    if (w->planets_i >= w->planets_siz)
    {
        w->planets_siz *= 2;
        w->planets = realloc(w->planets, sizeof(planet_t *) * w->planets_siz);
    }
    w->planets[w->planets_i] = p;
    w->planets_i++;
}



void world_update(world_t *w, float dt)
{
    for (int i = 0; i < w->planets_i; ++i)
    {
        for (int j = i + 1; j < w->planets_i; ++j)
        {
            planet_apply_gravity(w->planets[i], w->planets[j], w->gravity, dt);
        }
    }
    for (int i = 0; i < w->planets_i; ++i)
    {
        planet_update(w->planets[i], dt);
    }
}

