//
// Created by Frank on 2024/1/19.
//
#include <guide.h>
void Guide_logic(){
    app.keyboard[SDL_SCANCODE_BACKSPACE]=false;
    Event_guide();
    Quit_guide();
}
void Draw_guide(){
    Draw_background_guide();
    Draw_back();
    SDL_RenderPresent(app.renderer);
}
void Draw_background_guide(){
    guide.surface_background= IMG_Load("res/img/background/background_guide.png");
    guide.texture_background= SDL_CreateTextureFromSurface(app.renderer,guide.surface_background);
    SDL_RenderCopy(app.renderer,guide.texture_background,NULL,NULL);
    SDL_FreeSurface(guide.surface_background);
    SDL_DestroyTexture(guide.texture_background);
}
void Draw_back(){
    guide.surface_back= IMG_Load("res/img/widget/back.png");
    guide.texture_back= SDL_CreateTextureFromSurface(app.renderer,guide.surface_back);
    SDL_Rect rect_back={BACK_X_GUIDE,BACK_Y_GUIDE,guide.surface_back->w,guide.surface_back->h};
    SDL_RenderCopy(app.renderer,guide.texture_back,NULL,&rect_back);
    SDL_FreeSurface(guide.surface_back);
    SDL_DestroyTexture(guide.texture_back);
}
void Do_Back_guide(){
    if((guide.guide_event.button.x>=DO_BACK_X1_GUIDE&&
    guide.guide_event.button.x<=DO_BACK_X2_GUIDE&&
    guide.guide_event.button.y>=DO_BACK_Y1_GUIDE&&
    guide.guide_event.button.y<=DO_BACK_Y2_GUIDE)&&
    app.keyboard[guide.guide_event.button.button]){
        app.keyboard[SDL_SCANCODE_BACKSPACE]=true;
    }
}
void Event_guide(){
    while((!app.keyboard[SDL_SCANCODE_ESCAPE])&&(!app.keyboard[SDL_SCANCODE_BACKSPACE])&&SDL_WaitEvent(&guide.guide_event)){
        Do_Event_guide(&guide.guide_event);
        Draw_guide();
        Do_Back_guide();
    }
}
void Do_Event_guide(SDL_Event *event){
    switch(event->type){
        case SDL_KEYDOWN:
            app.keyboard[event->key.keysym.scancode]=true;
            break;
        case SDL_KEYUP:
            app.keyboard[event->key.keysym.scancode]=false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            app.keyboard[event->button.button]= true;
            break;
        case SDL_MOUSEBUTTONUP:
            app.keyboard[event->button.button]=false;
            break;
        default:
            break;
    }
}

void Quit_guide(){
    SDL_RenderClear(app.renderer);
    Menu_logic();
}