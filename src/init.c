/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** init
*/
#include "my.h"

ray_t *init_ray(float dist, float x, float y)
{
    ray_t *ray = malloc(sizeof(ray_t));

    if (!ray)
        return NULL;
    ray->dist = dist;
    ray->x = x;
    ray->y = y;
    return ray;
}

void free_particule(particule_t *part)
{
    if (part->pixel)
        sfRectangleShape_destroy(part->pixel);
    if (part->clock)
        sfClock_destroy(part->clock);
    if (part)
        free(part);
}

particule_t *create_particule(void)
{
    particule_t *part = malloc(sizeof(particule_t));
    sfVector2f null = {0, 0};

    if (!part)
        return NULL;
    part->clock = sfClock_create();
    part->start = false;
    part->pixel = sfRectangleShape_create();
    part->first_iteration = false;
    for (int i = 0; i < PARTICULE_NB; i++)
        part->pos[i] = null;
    return part;
}

static void init_inputs(game_t *game)
{
    game->inputs[0] = sfKeyZ;
    game->inputs[1] = sfKeyQ;
    game->inputs[2] = sfKeyS;
    game->inputs[3] = sfKeyD;
}

static bool init_game_struct(game_t *game)
{
    game->menu = create_menu();
    game->volume = sfListener_getGlobalVolume();
    game->minimap_visible = true;
    game->menu_index = INTRO_MENU;
    game->enemy_txtr = sfTexture_createFromFile(
        ENTITY_SPRITE_SHEET, NULL);
    game->difficulty = sfClock_create();
    game->ent_spawn = 4;
    if (!game->menu)
        return false;
    return true;
}

game_t *init_game(void)
{
    game_t *game = calloc(1, sizeof(game_t));
    sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};

    if (!game)
        return NULL;
    game->window = sfRenderWindow_create(mode, "Wolf3D", sfResize | sfClose,
        NULL);
    game->zbuffer = malloc(sizeof(float) * SCREEN_WIDTH);
    game->map = init_map();
    game->particule = create_particule();
    if (!game->zbuffer || !game->window || !init_game_struct(game) ||
        !init_assets(game) || !game->map || !game->enemy_txtr){
        destroy_game(game);
        return NULL;
    }
    init_inputs(game);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    return game;
}
