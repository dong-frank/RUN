//
// Created by Frank on 2024/1/19.
//

#ifndef RUN_GUIDE_H
#define RUN_GUIDE_H
#include <common.h>
#include <menu.h>
#define BACK_X_GUIDE 1100
#define BACK_Y_GUIDE 50
#define DO_BACK_X1_GUIDE 1110
#define DO_BACK_X2_GUIDE 1185
#define DO_BACK_Y1_GUIDE 75
#define DO_BACK_Y2_GUIDE 120
void Guide_logic();
void Event_guide();
void Do_Event_guide(SDL_Event*);
void Draw_guide();
void Draw_background_guide();
void Draw_back();
void Do_Back_guide();
typedef struct guide{
    SDL_Event guide_event;
    SDL_Surface *surface_background;
    SDL_Texture *texture_background;
    SDL_Surface *surface_back;
    SDL_Texture *texture_back;
}Guide;
Guide guide;

void Quit_guide();
#endif //RUN_GUIDE_H
