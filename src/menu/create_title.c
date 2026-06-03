/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** create_title.c
*/
#include "my.h"

bool create_titles(menu_t *menu)
{
    sfColor colors[2] = {sfWhite, sfBlack};
    sfVector2f vectors[2] = {{50, 30}, {60, 40}};

    menu->title_txtr = sfTexture_createFromFile(
        "./assets/images/title.png", NULL);
    menu->title[0] = sfSprite_create();
    menu->title[1] = sfSprite_create();
    if (!menu->title[0] || !menu->title[1] || !menu->title_txtr)
        return false;
    for (int i = 0; i < 2; i++){
        sfSprite_setTexture(menu->title[i], menu->title_txtr, sfTrue);
        sfSprite_setColor(menu->title[i], colors[i]);
        sfSprite_setScale(menu->title[i], (sfVector2f){0.7, 0.7});
        sfSprite_setPosition(menu->title[i], vectors[i]);
    }
    return true;
}
