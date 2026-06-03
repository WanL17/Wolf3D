/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** blur_shader.c
*/
#include "my.h"

bool create_blur_shader(menu_t *menu)
{
    menu->blur[0] = sfSprite_create();
    menu->blur_txtr[0] = sfTexture_createFromFile(
        "./assets/images/blur.png", NULL);
    if (!menu->blur[0] || !menu->blur_txtr[0])
        return false;
    sfSprite_setTexture(menu->blur[0], menu->blur_txtr[0], sfTrue);
    menu->blur[1] = sfSprite_create();
    menu->blur_txtr[1] = sfTexture_createFromFile(
        "./assets/images/gameoverscreen.png", NULL);
    if (!menu->blur[1] || !menu->blur_txtr[1])
        return false;
    sfSprite_setTexture(menu->blur[1], menu->blur_txtr[1], sfTrue);
    return true;
}
