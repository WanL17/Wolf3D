/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** Functions related to framebuffer;
*/
#include "my.h"

framebuffer_t *create_fb(unsigned int width, unsigned int height)
{
    framebuffer_t *fb = malloc(sizeof(framebuffer_t));

    if (!fb)
        return NULL;
    fb->width = width;
    fb->height = height;
    fb->pixels = calloc(width * height * 4, sizeof(sfUint8));
    if (!fb->pixels) {
        free(fb);
        return NULL;
    }
    return fb;
}

void put_pixel(framebuffer_t *fb, unsigned int x, unsigned int y, sfColor *clr)
{
    int index;

    if (!fb || x >= (unsigned int)fb->width || y >= (unsigned int)fb->height)
        return;
    index = (y * fb->width + x) * 4;
    fb->pixels[index] = clr->r;
    fb->pixels[index + 1] = clr->g;
    fb->pixels[index + 2] = clr->b;
    fb->pixels[index + 3] = clr->a;
}

void destroy_fb(framebuffer_t *fb)
{
    if (fb) {
        free(fb->pixels);
        free(fb);
    }
}
