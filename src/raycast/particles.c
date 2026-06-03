/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** particles.c
*/
#include "my.h"

/* sfColor randomize_color(void)
{
    return sfColor_fromRGB(rand() % 255, rand() % 255, rand() % 255);
} */

static void reset_particle_postition(particule_t *particles, int index)
{
    if (particles->pos[index].y > 500) {
        particles->pos[index].y = 10;
        particles->pos[index].x = rand() % 600 + 100;
    }
}

static void draw_a_particle(game_t *game, particule_t *particles, int i)
{
    sfRectangleShape_setFillColor(particles->pixel, sfBlue);
    sfRenderWindow_drawRectangleShape(GAME_WIN, particles->pixel, NULL);
    reset_particle_postition(particles, i);
    sfRectangleShape_setPosition(particles->pixel,
        (sfVector2f){particles->pos[i].x, particles->pos[i].y + 10});
    particles->pos[i].y += 10;
}

void draw_particles(game_t *game, particule_t *particles)
{
    sfTime time = sfClock_getElapsedTime(particles->clock);

    particles->start = true;
    particles->first_iteration = true;
    sfClock_restart(particles->clock);
    if (time.microseconds > 1000000000) {
        particles->start = false;
        return;
    }
    for (int i = 0; i < PARTICULE_NB; i++) {
        if (particles->first_iteration) {
            particles->pos[i] = (sfVector2f){rand() % 800, rand() % 600};
            sfRectangleShape_setSize(particles->pixel, (sfVector2f){3, 10});
            sfRectangleShape_setPosition(particles->pixel, particles->pos[i]);
        }
        if (particles->pos[i].x != 0.0 && particles->pos[i].y != 0.0) {
            draw_a_particle(game, particles, i);
        }
    }
    particles->start = false;
}
