#include "planet.h"

#include <math.h>
#include <stdlib.h>




planet_t *planet_create(float x, float y, float vx, float vy, float r, int id)
{
    planet_t *p = calloc(1, sizeof(planet_t));
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    p->r = r;
    p->mass = M_PI * r * r;
    p->id = id;
    p->prev_siz = 1000;
    p->prev_xs = calloc(p->prev_siz, sizeof(float));
    p->prev_ys = calloc(p->prev_siz, sizeof(float));
    for (int i = 0; i < p->prev_siz; ++i)
    {
        p->prev_xs[i] = x;
        p->prev_ys[i] = y;
    }
    return p;
}

void planet_destroy(planet_t *p)
{
    free(p->prev_xs);
    free(p->prev_ys);
    free(p);
}



void planet_update(planet_t *p, float dt)
{
    // save prev pos
    p->prev_i--;
    if (p->prev_i < 0) p->prev_i = p->prev_siz - 1;
    p->prev_xs[p->prev_i] = p->x;
    p->prev_ys[p->prev_i] = p->y;

    p->x += p->vx * dt;
    p->y += p->vy * dt;
}


void planet_apply_force(planet_t *p, float fx, float fy, float dt)
{
    p->vx += fx / p->mass * dt;
    p->vy += fy / p->mass * dt;
}

void planet_apply_gravity(planet_t *p1, planet_t *p2, float gravity, float dt)
{
    float dx = p2->x - p1->x;
    float dy = p2->y - p1->y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist == 0) return;
    float f = gravity * p1->mass * p2->mass / dist / dist;
    float dirx = dx / dist;
    float diry = dy / dist;
    float fx = f * dirx;
    float fy = f * diry;
    planet_apply_force(p1, fx, fy, dt);
    planet_apply_force(p2, -fx, -fy, dt);
}



