#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Types.h>
#include <SFML/Window/VideoMode.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct booster_particles {
    sfSprite *sprite;
    sfTexture *text;
    sfClock *clock;
    sfVector2f vector_array[50];
    bool start;
    bool first_iteration;
} b_particles_t;

b_particles_t *create_particles(void)
{
    b_particles_t *particles = malloc(sizeof(b_particles_t));

    particles->sprite = sfSprite_create();
    particles->clock = sfClock_create();
    particles->start = false;
    particles->first_iteration = false;
    particles->text = sfTexture_createFromFile("./ammo_high.png", NULL);
    sfSprite_setTexture(particles->sprite, particles->text, sfFalse);
    for (int i = 0; i < 10; i++) {
        particles->vector_array[i].x = 0.0;
        particles->vector_array[i].y = 0.0;
    }
    return particles;
}

void destroy_particles(b_particles_t *particles)
{
    sfSprite_destroy(particles->sprite);
    sfTexture_destroy(particles->text);
    sfClock_destroy(particles->clock);
    free(particles);
}

sfColor randomize_color(void)
{
    return sfColor_fromRGB(rand() % 255, rand() % 255, rand() % 255);
}

static void reset_particle_postition(b_particles_t *particles, int index)
{
    if (particles->vector_array[index].y > 500) {
        particles->vector_array[index].y = 10;
        particles->vector_array[index].x = rand() % 600 + 100;
    }
}

void display_particles(sfRenderWindow *win, b_particles_t *particles)
{
    sfTime time = sfClock_getElapsedTime(particles->clock);

    if (time.microseconds > 10000000) {
        particles->start = false;
        return;
    }
    for (int i = 0; i < 50; i++) {
        if (particles->first_iteration) {
            particles->vector_array[i] = (sfVector2f){rand() % 600 + 100, rand() % 50};
            sfSprite_setScale(particles->sprite, (sfVector2f){0.2, 0.2});
            sfSprite_setPosition(particles->sprite, particles->vector_array[i]);
        }
        if (particles->vector_array[i].x != 0.0 && particles->vector_array[i].y != 0.0) {
            sfSprite_setColor(particles->sprite, randomize_color());
            sfRenderWindow_drawSprite(win, particles->sprite, NULL);
            reset_particle_postition(particles, i);
            sfSprite_setPosition(particles->sprite, (sfVector2f){particles->vector_array[i].x, particles->vector_array[i].y + 0.1});
            particles->vector_array[i].y += 0.1;
        }
    }
    particles->first_iteration = false;
}

int main(void)
{
    sfVideoMode video_mode = {800, 500, 32};
    sfRenderWindow *window = sfRenderWindow_create(video_mode, "Brawl3D", sfClose,
        NULL);
    sfEvent event;
    b_particles_t *particles = create_particles();

    srand(time(NULL));
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtMouseButtonPressed) {
                particles->start = true;
                particles->first_iteration = true;
                sfClock_restart(particles->clock);
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        if (particles->start)
            display_particles(window, particles);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    destroy_particles(particles);
}
