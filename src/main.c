//
// Created by Frank on 2024/1/16.
//
#include <main.h>
App app;

int main (int argc ,char *argv[]){
    //Init
    Init_App();
    Create_Renderer();
    Menu_logic();
    Quit_App();
    return 0;
}
static void Init_App(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        HANDLE_ERROR("Init SDL")
    }//init video

    if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)==0){
        HANDLE_ERROR("Init IMG")
    }//init img

    if(TTF_Init()!=0){
        HANDLE_ERROR("Init TTF")
    }//init ttf

    app.keyboard= calloc(SDL_NUM_SCANCODES ,sizeof (bool));


app.window=SDL_CreateWindow("Pal",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH_OF_WINDOW,HEIGHT_OF_WINDOW,SDL_WINDOW_SHOWN);
}
void Create_Renderer() {
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
}
static void Quit_App(){
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    free(app.keyboard);
}