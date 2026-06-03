/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** framebuffer.h
*/

#ifndef FRAMEBUFFER_H
    #define FRAMEBUFFER_H

    #include "my.h"

typedef struct framebuffer
{
    int width;
    int height;
    sfUint8 *pixels;
} framebuffer_t;

framebuffer_t *create_fb(unsigned int width, unsigned int height);
void destroy_fb(framebuffer_t *fb);
void put_pixel(framebuffer_t *fb, unsigned int x, unsigned int y, sfColor *clr);
#endif
