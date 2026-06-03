/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** creation of buttons and text
*/

#include "my.h"

void destroy_button(button_t *button)
{
    if (button->txtr)
        sfTexture_destroy(button->txtr);
    if (button->hover_txtr)
        sfTexture_destroy(button->hover_txtr);
    if (button->sprite)
        sfSprite_destroy(button->sprite);
    free(button);
}

button_t *create_button(char *txtr_path, char *hover_txtr_path, sfVector2f *pos,
    void (*action)(game_t *, player_t *, button_t *))
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->txtr = sfTexture_createFromFile(txtr_path, NULL);
    button->hover_txtr = sfTexture_createFromFile(hover_txtr_path, NULL);
    button->sprite = sfSprite_create();
    if (!button->txtr || !button->hover_txtr || !button->sprite){
        destroy_button(button);
        return NULL;
    }
    sfSprite_setTexture(button->sprite, button->txtr, sfTrue);
    sfSprite_setPosition(button->sprite, *pos);
    button->action = action;
    return button;
}

text_t *create_text(char *str, sfVector2f *pos, int size,
    void (*action)(game_t *, player_t *, text_t *))
{
    text_t *text = malloc(sizeof(text_t));

    if (!text)
        return NULL;
    text->text = sfText_create();
    if (!text->text){
        free(text);
        return NULL;
    }
    sfText_setString(text->text, str);
    sfText_setCharacterSize(text->text, size);
    sfText_setPosition(text->text, *pos);
    text->action = action;
    return text;
}
