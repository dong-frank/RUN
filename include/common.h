//
// Created by Frank on 2024/1/16.
//

#ifndef RUN_COMMON_H
#define RUN_COMMON_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define HANDLE_ERROR(msg) printf(msg ": %s\n",SDL_GetError()); \
exit(EXIT_FAILURE);                                            \

typedef struct app{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool *keyboard;
}App;
extern App app;

void Write_words(char *text,SDL_Color color,TTF_Font *font,SDL_Renderer *renderer,SDL_Rect *rect);

#endif //RUN_COMMON_H

