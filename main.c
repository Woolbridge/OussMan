#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "menu.h"
/*#define WIDTH 1081
#define HEIGHT 720
#define BPP 32
#define FLAGS (SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SWSURFACE)*/
//#include "menu.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL,*back=NULL,*cb=NULL,*fs=NULL,*wd=NULL,*o=NULL,*o1=NULL,*o2=NULL,*credits=NULL, *background=NULL,*start=NULL,*exit=NULL,*text=NULL,*settings=NULL;
    SDL_Event event;
    SDL_MouseButtonEvent b;
    int i=0,c=0,menu=1,sc=1/*screen number*/,mx,my,bn=0/*button number*/;
    SDL_Rect pfond,pstart,pexit,fcb,psettings,pback,pfs,pwd,pcredits,pperso;
    int continuer=1,compteur=0,j;
    pperso.y=400;
    pfond.x = 0;
    pfond.y = 0;
    pstart.x=60;
    pstart.y=30;
    pexit.x=265;
    pexit.y=18;
    psettings.x=12;
    psettings.y=150;
    pback.x=25;
    pback.y=100;
    pfs.x=170;
    pfs.y=230;
    pwd.x=170;
    pwd.y=300;
    pcredits.x=170;
    pcredits.y=375;
    fcb.x=510;
    fcb.y=120;
    SDL_Init(SDL_INIT_EVERYTHING);
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
{
printf("%s",Mix_GetError());
}
    SDL_Color colorcoor={0,0,0};
    if(TTF_Init()==1){
       printf("TTF_Init %s \n",TTF_GetError());
      }
    TTF_Font *fonttext;
    SDL_Rect postext={50,440};
    fonttext=TTF_OpenFont("fontmenu.otf",22);    
    Mix_Music *music= Mix_LoadMUS("airport_sound.mp3");
    Mix_PlayMusic(music,1);
    SDL_WM_SetIcon(IMG_Load("ouss.png"), NULL);
    background = IMG_Load("menu_background.png");
    screen = SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("OussMan", NULL);
    background = IMG_Load("menu_background.png");
    settings= IMG_Load("settings_button.png");
    exit= IMG_Load("exit_button.png");
    start= IMG_Load("start_button.png");
    o=IMG_Load("phase 1.png");
    o1=IMG_Load("phase 2.png");
    o2=IMG_Load("phase 3.png");
    SDL_BlitSurface(background, NULL, screen, &pfond);
    SDL_BlitSurface(settings, NULL, screen, &psettings);
    SDL_BlitSurface(start, NULL, screen, &pstart);
    SDL_BlitSurface(exit, NULL, screen, &pexit);
    
    SDL_Flip(screen);
    //pause();
while (continuer)
{   
 if(sc==1){
    free(background);
    background=IMG_Load("menu_background.png");
    if(i==1){
    screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
      SDL_BlitSurface(background, NULL, screen, &pfond);
      i=0;    
        }
  /*for(pperso.x=0;pperso.x<=background->w;pperso.x+=5)
    for(j=0;j<=2;j++)
       {
       switch(j){
             case 0:
     	     free(o1);
             free(o2);
             o=IMG_Load("phase 1.png");
             SDL_BlitSurface(o,NULL,screen,&pperso);
             break;
             case 1:
     	     free(o);
             free(o2);
             o1=IMG_Load("phase 2.png");
             SDL_BlitSurface(o1,NULL,screen,&pperso);
             break;
             case 2:
     	     free(o1);
             free(o);
             o2=IMG_Load("phase 3.png");
             SDL_BlitSurface(o2,NULL,screen,&pperso);
             break;
       }
       } 
*/
    SDL_WaitEvent(&event);
    if(event.type!=SDL_KEYDOWN && event.type!=SDL_KEYUP) SDL_GetMouseState(&mx,&my);
    if(event.type==SDL_QUIT)
        continuer=0;
    if(event.type==SDL_KEYDOWN)
        if (event.key.keysym.sym==SDLK_f) {
           screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
            SDL_BlitSurface(background, NULL, screen, &pfond);
           }
    /*else if(event.type==SDL_KEYDOWN){*/
      else if (event.key.keysym.sym==SDLK_w) {  
             screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
             SDL_BlitSurface(background, NULL, screen, &pfond);
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
                          free(text);
                          /*SDL_FillRect(text,NULL,0x000000);*/
                          text=TTF_RenderText_Blended(fonttext,"Press 'BACKSPACE' to begin your quest",colorcoor);
                          SDL_BlitSurface(text,NULL,background,&postext);
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
                          free(text);
                          text=TTF_RenderText_Blended(fonttext,"Press 'BACKSPACE' to access Settings",colorcoor);
                          SDL_BlitSurface(text,NULL,screen,&postext);
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
                          free(text);
                          text=TTF_RenderText_Blended(fonttext,"Press 'BACKSPACE' to begin your quest",colorcoor);
			  SDL_BlitSurface(text,NULL,screen,&postext);
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
                          free(text);
                          text=TTF_RenderText_Blended(fonttext,"Press 'BACKSPACE' or 'ESCAPE' to Exit",colorcoor);
			  SDL_BlitSurface(text,NULL,screen,&postext);
                          break;
                    }
        else if(event.key.keysym.sym==SDLK_ESCAPE) 
                 continuer=0;
 
    /*SDL_WaitEvent(&b);*/

    //if(event.type==SDL_MOUSEMOTION){
    if(mx>=60 && mx<=start->w+60 && my>=30 && my<=start->h+30){
        free(start);
        start= IMG_Load("start_button_pressed.png");
        SDL_BlitSurface(start, NULL, screen, &pstart);
        }
    else if(mx>=12 && mx<=settings->w+12 && my>=150 && my<=settings->h+150){
       /* if(event.type==SDL_KEYDOWN)
            if(event.key.keysym.sym=SDLK_SPACE)
                 sc=2;*/
        free(settings);
        settings= IMG_Load("settings_button_pressed.png");
        SDL_BlitSurface(settings, NULL, screen, &psettings);
        if(event.type==SDL_KEYDOWN){
           if(event.key.keysym.sym==SDLK_SPACE)
              sc=2;
              }
        if(event.type==SDL_MOUSEBUTTONDOWN)
              sc=2; 
        }
    else if(mx>=265 && mx<=exit->w+265 && my>=18 && my<=exit->h+18){
        free(exit);
        exit= IMG_Load("exit_button_pressed.png");
        SDL_BlitSurface(exit, NULL, screen, &pexit);
        if(event.type==SDL_MOUSEBUTTONDOWN)
            /*if(event.button==SDL_BUTTON_LEFT)*/
                 continuer=0;
        if(event.type==SDL_KEYDOWN)
             if(event.key.keysym.sym==SDLK_SPACE)
                 continuer=0;
        }
         
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

       
   }/*end of screen 1*/
 else if(sc==2)
      {
    i=1;
    free(background);
    background=IMG_Load("settings_background.png");
    SDL_BlitSurface(background,NULL,screen,&pfond);
    SDL_WaitEvent(&event);
    if(event.type!=SDL_KEYUP && event.type!=SDL_KEYDOWN)
      SDL_GetMouseState(&mx,&my);
    back=IMG_Load("back_button.png");
    cb=IMG_Load("credits_bar_down.png");
    SDL_BlitSurface(back,NULL,screen,&pback);
    fs=IMG_Load("fullscreen_button.png");
    SDL_BlitSurface(fs,NULL,screen,&pfs);
    wd=IMG_Load("windowed_button.png");
    SDL_BlitSurface(wd,NULL,screen,&pwd);
    credits=IMG_Load("credits_button.png");
    SDL_BlitSurface(credits,NULL,screen,&pcredits);
    SDL_WaitEvent(&event);
    if(event.type==SDL_KEYDOWN ||event.type==SDL_KEYUP)
           if(event.key.keysym.sym==SDLK_BACKSPACE){
            /*if(event.button==SDL_BUTTON_LEFT)*/
                 sc=1;
		 SDL_Flip(screen);
                }
    if(mx>=25 && mx<=back->w+25 && my>=100 && my<=back->h+100){
        free(back);
        back= IMG_Load("back_button_pressed.png");
        SDL_BlitSurface(back, NULL, screen, &pback);
        SDL_WaitEvent(&event);
           if(event.type==SDL_MOUSEBUTTONDOWN)
                sc=1;
        if(event.type==SDL_KEYDOWN)
             if(event.key.keysym.sym==SDLK_SPACE)
                 sc=1;
      }

    if(mx>=170 && mx<=fs->w+170 && my>=230 && my<=fs->h+230){
        free(fs);
        fs= IMG_Load("fullscreen_button_pressed.png");
        SDL_BlitSurface(fs, NULL, screen, &pfs);
        SDL_WaitEvent(&event);
        if(event.type==SDL_MOUSEBUTTONDOWN){
           screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        SDL_BlitSurface(background, NULL, screen, &pfond);
        back=IMG_Load("back_button.png");
        SDL_BlitSurface(back,NULL,screen,&pback);
        fs=IMG_Load("fullscreen_button.png");
        SDL_BlitSurface(fs,NULL,screen,&pfs);
        wd=IMG_Load("windowed_button.png");
        SDL_BlitSurface(wd,NULL,screen,&pwd);
        credits=IMG_Load("credits_button.png");
    	SDL_BlitSurface(credits,NULL,screen,&pcredits);
        }
      if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_f){
   	 screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
        SDL_BlitSurface(background, NULL, screen, &pfond);
        back=IMG_Load("back_button.png");
        SDL_BlitSurface(back,NULL,screen,&pback);
        fs=IMG_Load("fullscreen_button.png");
        SDL_BlitSurface(fs,NULL,screen,&pfs);
        wd=IMG_Load("windowed_button.png");
        SDL_BlitSurface(wd,NULL,screen,&pwd);
        credits=IMG_Load("credits_button.png");
    	SDL_BlitSurface(credits,NULL,screen,&pcredits);
      }
    }
      if(mx>=170 && mx<=wd->w+170 && my>=300 && my<=wd->h+300){
        free(wd);
        wd= IMG_Load("windowed_button_pressed.png");
        SDL_BlitSurface(wd, NULL, screen, &pwd);
          SDL_WaitEvent(&event);
        if(event.type==SDL_MOUSEBUTTONDOWN){
           screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
        SDL_BlitSurface(background, NULL, screen, &pfond);
        back=IMG_Load("back_button.png");
        SDL_BlitSurface(back,NULL,screen,&pback);
        fs=IMG_Load("fullscreen_button.png");
        SDL_BlitSurface(fs,NULL,screen,&pfs);
        wd=IMG_Load("windowed_button.png");
        SDL_BlitSurface(wd,NULL,screen,&pwd);
        credits=IMG_Load("credits_button.png");
    	SDL_BlitSurface(credits,NULL,screen,&pcredits);
        }
      if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w){
   	 screen=SDL_SetVideoMode(background->w,background->h,32, SDL_HWSURFACE|SDL_SWSURFACE|SDL_DOUBLEBUF);
        SDL_BlitSurface(background, NULL, screen, &pfond);
        back=IMG_Load("back_button.png");
        SDL_BlitSurface(back,NULL,screen,&pback);
        fs=IMG_Load("fullscreen_button.png");
        SDL_BlitSurface(fs,NULL,screen,&pfs);
        wd=IMG_Load("windowed_button.png");
        SDL_BlitSurface(wd,NULL,screen,&pwd);
        credits=IMG_Load("credits_button.png");
    	SDL_BlitSurface(credits,NULL,screen,&pcredits);
      }
  }
      if(mx>=170 && mx<=credits->w+170 && my>=375 && my<=credits->h+375){
        free(credits);
        credits= IMG_Load("credits_button_pressed.png");
        SDL_BlitSurface(credits, NULL, screen, &pcredits);
        SDL_WaitEvent(&event);
           if(event.type==SDL_MOUSEBUTTONDOWN)
                { if(c==0){
                  c=1;
                  SDL_BlitSurface(cb,NULL,screen,&fcb);
                       }
                   else{
                        c=0;
                        free(cb);
                       }
                }
        if(event.type==SDL_KEYDOWN)
             if(event.key.keysym.sym==SDLK_c)
                { if(c==0){
                  
                  SDL_BlitSurface(cb,NULL,screen,&fcb);
                  c=1;
                       }
                   else{
                        //c=0;
                        free(cb);
                       }
                }
      }
 if(c==1) SDL_BlitSurface(cb,NULL,screen,&fcb);
}
 SDL_Flip(screen);
}
         /* free(start);
          start= IMG_Load("start_button.png");
          SDL_BlitSurface(start, NULL, screen, &pstart); */

    SDL_FreeSurface(background);
    SDL_FreeSurface(settings);
    SDL_FreeSurface(start);
    SDL_FreeSurface(exit);
    SDL_FreeSurface(text);
    TTF_CloseFont(fonttext);
    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return EXIT_SUCCESS;
}



