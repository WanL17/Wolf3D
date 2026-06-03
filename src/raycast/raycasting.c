/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** draw
*/
#include "my.h"

void clear_fb(framebuffer_t *fb)
{
    for (int y = 0; y < fb->height; y++) {
        for (int x = 0; x < fb->width; x++) {
            put_pixel(fb, x, y, &sfTransparent);
        }
    }
}

float get_wall_height(float dist)
{
    float projection_plane = 500.0f;
    float height;

    if (dist < 0.0001f)
        dist = 0.0001f;
    height = (TILE_SIZE / dist) * projection_plane;
    return height;
}

void cast_single_ray(player_t *player, float ray_angle, game_t *game)
{
    float step = 1.0f;

    game->ray.dist = 0;
    game->ray.x = player->x;
    game->ray.y = player->y;
    while (game->ray.dist < 1000) {
        game->ray.x += cosf(ray_angle) * step;
        game->ray.y += sinf(ray_angle) * step;
        game->ray.dist += step;
        if (is_wall((int)game->ray.x, (int)game->ray.y, game)){
            game->ray.dist *= cosf(ray_angle - player->angle);
            return;
        }
    }
    game->ray.dist = 1000;
}

void cast_all_rays(framebuffer_t *fb, player_t *player, game_t *game)
{
    float ray_angle = 0;
    float baseangle = player->angle - FOV / 2;
    float constant = FOV / NUM_RAYS;

    clear_fb(fb);
    for (int r = 0; r != NUM_RAYS; r++) {
        ray_angle = baseangle + r * constant;
        cast_single_ray(player, ray_angle, game);
        game->zbuffer[r * SCREEN_WIDTH / NUM_RAYS] = game->ray.dist;
        render_wall_column(fb, r * fb->width / NUM_RAYS, &game->ray, game);
    }
}

static double dominant_coordinate(float x, float y)
{
    x = fmodf(x, TILE_SIZE);
    y = fmodf(y, TILE_SIZE);
    if (ABS(TILE_SIZE / 2 - y) > ABS(TILE_SIZE / 2 - x)){
        if (x < y)
            return 1 - x / TILE_SIZE;
        return x / TILE_SIZE;
    }
    if (x < y)
        return y / TILE_SIZE;
    return 1 - y / TILE_SIZE;
}

static void darken_colors(sfColor *color, float distance)
{
    float darkness = 1 + distance / 200;

    color->r /= darkness;
    color->g /= darkness;
    color->b /= darkness;
}

void render_wall_column(framebuffer_t *fb, int column, ray_t *ray, game_t *game)
{
    float wall_height = get_wall_height(ray->dist);
    float top = (fb->height / 2) - (wall_height / 2);
    float bottom = (fb->height / 2) + (wall_height / 2);
    sfColor color;
    float height_proportion = 1;
    int x_coord = (int)(dominant_coordinate(ray->x, ray->y) * WALL_WIDTH);
    int y_coord;

    if (top < 0){
        height_proportion = fb->height / (fb->height - (top * 2));
        top = 0;
        bottom = fb->height - 1;
    }
    for (int i = ceil(top); i < bottom; i++){
        y_coord = (int)(((1 - height_proportion) * 0.5 + (i - top) / (bottom -
                    top) * height_proportion) * WALL_HEIGHT);
        color = sfImage_getPixel(game->wall, x_coord, y_coord);
        darken_colors(&color, ray->dist);
        put_pixel(fb, column, i, &color);
    }
}
