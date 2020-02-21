#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

/*#define WIDTH 1081
#define HEIGHT 720
#define BPP 32
#define FLAGS (SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SWSURFACE)*/
//#include "menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL, *imageDeFond=NULL,*menu=NULL,*start=NULL,*exit=NULL,*settings=NULL;
    SDL_Event event;
    int mx,my,bn=0;
    SDL_Rect positionFond,pstart,pexit,psettings;
    int continuer=1,compteur=0;
    positionFond.x = 0;
    positionFond.y = 0;
    pstart.x=60;
    pstart.y=30;
    pexit.x=265;
    pexit.y=18;
    psettings.x=12;
    psettings.y=150;

    SDL_Init(SDL_INIT_EVERYTHING);
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{
printf("%s",Mix_GetError());
}
    Mix_Music *music = Mix_LoadMUS("airport_sound.mp3");
    Mix_PlayMusic(music,1);
/*Mix_AllocateChannels(2);
Mix_Music *musique;
Mix_Chunk *son=NULL;
musique=Mix_LoadMUS("airport_sound.mp3");
Mix_Volume(2, MIX_MAX_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME/6);
Mix_PlayMusic(musique, -1);*/
//sounds(screen,musique);
    /* Chargement de l'icône AVANT SDL_SetVideoMode */
    //SDL_WM_SetIcon(SDL_LoadBMP("sdl_icone.bmp"), NULL);

    imageDeFond = IMG_Load("menu_background.png");
    screen = SDL_SetVideoMode(imageDeFond->w,imageDeFond->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("OussMan", NULL);
    settings= IMG_Load("settings_button.png");
    exit= IMG_Load("exit_button.png");
    start= IMG_Load("start_button.png");
    SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
    SDL_BlitSurface(settings, NULL, screen, &psettings);
    SDL_BlitSurface(start, NULL, screen, &pstart);
    SDL_BlitSurface(exit, NULL, screen, &pexit);
    SDL_Flip(screen);
    //pause();
while (continuer)
{   
    SDL_WaitEvent(&event);
    if(event.type!=SDL_KEYDOWN && event.type!=SDL_KEYUP) SDL_GetMouseState(&mx,&my);
    if(event.type==SDL_QUIT)
        continuer=0;
    if(event.type==SDL_KEYDOWN)
        if (event.key.keysym.sym==SDLK_f) {
           screen=SDL_SetVideoMode(imageDeFond->w,imageDeFond->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
            SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
           }
    else if(event.type==SDL_KEYDOWN){
       if (event.key.keysym.sym==SDLK_w) {  
             screen=SDL_SetVideoMode(imageDeFond->w,imageDeFond->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
             SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
            }
       else if(event.key.keysym.sym==SDLK_DOWN)
               switch(bn){
                 case 0 : /*no button selected*/
                          mx=start->w; 
                          my=start->h;
                          bn=1;
                          break;
                 case 1 : /*start selected*/ 
                          mx=settings->w; 
                          my=settings->h+100;
                          bn=2;
                          free(start);
                          start= IMG_Load("start_button.png");
                          break;
               }
       else if(event.key.keysym.sym==SDLK_UP)
               switch(bn){
                 case 0 : /*no button selected*/
                          mx=settings->w; 
                          my=settings->h+100;
                          bn=2;
                          break;
                 case 2 : /*settings selected*/ 
                          mx=start->w; 
                          my=start->h;
                          bn=1;
                          free(settings);
                          settings= IMG_Load("settings_button.png");
                          break;
               }
       else if(event.key.keysym.sym==SDLK_RIGHT)
               switch(bn){
                 case 0 : /*no button selected*/
                          mx=start->w; 
                          my=start->h;
                          bn=1;
                          break;
                 case 1 : /*start selected*/ 
                          mx=exit->w+230; 
                          my=exit->h;
                          bn=3;
                          free(start);
                          start= IMG_Load("start_button.png");
                          break;
               }
      else if(event.key.keysym.sym==SDLK_LEFT)
               switch(bn){
                 case 0 : /*no button selected*/
                          mx=exit->w+230; 
                          my=exit->h;
                          bn=3;
                          break;
                 case 3 : /*exit selected*/ 
                          mx=start->w; 
                          my=start->h;
                          bn=1;
                          free(exit);
                          exit= IMG_Load("exit_button.png");
                          break;
               }
    }
    //if(event.type==SDL_MOUSEMOTION){
    if(mx>=60 && mx<=start->w+60 && my>=30 && my<=start->h+30){
        free(start);
        start= IMG_Load("start_button_pressed.png");
        SDL_BlitSurface(start, NULL, screen, &pstart);
        //pause();
        }
    else if(mx>=12 && mx<=settings->w+12 && my>=150 && my<=settings->h+150){
        settings= IMG_Load("settings_button_pressed.png");
        SDL_BlitSurface(settings, NULL, screen, &psettings);
        //SDL_Flip(screen);
        //pause();
        }
    else if(mx>=265 && mx<=exit->w+265 && my>=18 && my<=exit->h+18){
        free(exit);
        exit= IMG_Load("exit_button_pressed.png");
        SDL_BlitSurface(exit, NULL, screen, &pexit);
        //SDL_Flip(screen);
        //pause();
        }
      //}
    else {
          free(start);
          start= IMG_Load("start_button.png");
          free(settings);
          settings= IMG_Load("settings_button.png");
          free(exit);
          exit=IMG_Load("exit_button.png");
    }
          SDL_BlitSurface(start, NULL, screen, &pstart); 
          SDL_BlitSurface(settings, NULL, screen, &psettings); 
          SDL_BlitSurface(exit, NULL, screen, &pexit);   
//if (event.type=SDL_KEYDOWN)
       // if(event.key.keysym.sym=SDLK_ESCAPE) continuer=0;
 SDL_Flip(screen);
}
          free(start);
          start= IMG_Load("start_button.png");
          SDL_BlitSurface(start, NULL, screen, &pstart); 

    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(settings);
    SDL_FreeSurface(start);
    SDL_FreeSurface(exit);
    SDL_FreeSurface(menu);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return EXIT_SUCCESS;
}



