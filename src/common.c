//
// Created by Frank on 2024/1/20.
//
#include <common.h>
void Write_words(char *text,SDL_Color color,TTF_Font *font,SDL_Renderer *renderer,SDL_Rect *rect){
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font,text,color);
    SDL_Texture *texture= SDL_CreateTextureFromSurface(renderer,surface);
    rect->h=surface->h;
    rect->w=surface->w;
    SDL_RenderCopy(renderer,texture,NULL,rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


