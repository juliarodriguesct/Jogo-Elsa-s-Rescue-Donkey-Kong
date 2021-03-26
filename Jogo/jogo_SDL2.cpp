//jogo sdl2
#include <SDL.h>
#include <stdio.h>
#include <string>

//Dimenssões da tela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main( int argc, char* args[] )
{
    //cria a saida
    int quit = 1;

    //cria os objetos a serem usados
    SDL_Window *janela = NULL;
    SDL_Surface *tela = NULL;
    SDL_Surface *fundo = NULL;
    SDL_Surface *sprite = NULL;
    SDL_Surface *escada = NULL;
    SDL_Surface *plataforma1 = NULL;
    SDL_Surface *plataforma2 = NULL;
    SDL_Surface *plataforma3 = NULL;

    //Inicializa o SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL nao inicializou!!!, SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Cria a janela
        janela = SDL_CreateWindow( "Donkey Frozen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( janela != NULL )
        {
            //Cria a tela
            tela = SDL_GetWindowSurface( janela );

            //Le a imagem
            fundo = SDL_LoadBMP( "fundo.bmp" );
            sprite = SDL_LoadBMP( "tijolo.bmp" );
            escada = SDL_LoadBMP( "Escada.bmp" );
            plataforma1 = SDL_LoadBMP( "Plataforma1.bmp" );
            plataforma2 = SDL_LoadBMP( "Plataforma2.bmp" );
            plataforma3 = SDL_LoadBMP( "Plataforma4.bmp" );

            //cria os rects da plataforma1
            SDL_Rect PRect1;
            PRect1.w = plataforma1->w;
            PRect1.h = plataforma1->h;
            PRect1.x = 800 - PRect1.w;
            PRect1.y = 680 - PRect1.h;

            //cria os rects da plataforma2
            SDL_Rect PRect2;
            PRect2.w = plataforma2->w;
            PRect2.h = plataforma2->h;
            PRect2.x = 800 - PRect2.w;
            PRect2.y = 580 - PRect2.h;

            //cria os rects da plataforma3
            SDL_Rect PRect3;
            PRect3.w = plataforma1->w;
            PRect3.h = plataforma1->h;
            PRect3.x = 800 - PRect3.w;
            PRect3.y = 480 - PRect3.h;

            //cria os rects da plataforma4
            SDL_Rect PRect4;
            PRect4.w = plataforma2->w;
            PRect4.h = plataforma2->h;
            PRect4.x = 800 - PRect4.w;
            PRect4.y = 380 - PRect4.h;

            //cria os rects da plataforma5
            SDL_Rect PRect5;
            PRect5.w = plataforma1->w;
            PRect5.h = plataforma1->h;
            PRect5.x = 800 - PRect5.w;
            PRect5.y = 280 - PRect5.h;

            //cria os rects da plataforma6
            SDL_Rect PRect6;
            PRect6.w = plataforma3->w;
            PRect6.h = plataforma3->h;
            PRect6.x = 800 - PRect6.w;
            PRect6.y = 180 - PRect6.h;

            //cria os rects da escada1
            SDL_Rect ERect1;
            ERect1.w = escada->w;
            ERect1.h = escada->h;
            ERect1.x = 550 - ERect1.w;
            ERect1.y = 630 - ERect1.h;

            //cria os rects da escada2
            SDL_Rect ERect2;
            ERect2.w = escada->w;
            ERect2.h = escada->h;
            ERect2.x = 800 - ERect2.w;
            ERect2.y = 530 - ERect2.h;

            //cria os rects da escada3
            SDL_Rect ERect3;
            ERect3.w = escada->w;
            ERect3.h = escada->h;
            ERect3.x = 250 - ERect3.w;
            ERect3.y = 430 - ERect3.h;

            //cria os rects da escada4
            SDL_Rect ERect4;
            ERect4.w = escada->w;
            ERect4.h = escada->h;
            ERect4.x = 650 - ERect4.w;
            ERect4.y = 330 - ERect4.h;

            //cria os rects da escada5
            SDL_Rect ERect5;
            ERect5.w = escada->w;
            ERect5.h = escada->h;
            ERect5.x = 400 - ERect5.w;
            ERect5.y = 230 - ERect5.h;

            //cria os rects do sprite
            SDL_Rect SpriteRect;
            SpriteRect.w = sprite->w;
            SpriteRect.h = sprite->h;
            SpriteRect.x = 250 - SpriteRect.w;
            SpriteRect.y = 665 - SpriteRect.h;

            //cria os rects do fundo
            SDL_Rect FRect;
            FRect.w = fundo->w;
            FRect.h = fundo->h;
            FRect.x = 0;
            FRect.y = 0;

            //deixa transparente
            SDL_SetColorKey( sprite, SDL_TRUE, SDL_MapRGB( sprite->format, 119, 124, 125 ) ); //sprite
            SDL_SetColorKey( sprite, SDL_TRUE, SDL_MapRGB( sprite->format, 108, 222, 86 ) ); //sprite tijolo, excluir depois
            SDL_SetColorKey( escada, SDL_TRUE, SDL_MapRGB( escada->format, 99, 181, 230 ) ); //escada
            SDL_SetColorKey( plataforma1, SDL_TRUE, SDL_MapRGB( plataforma1->format, 119, 124, 145 ) ); //plataforma1
            SDL_SetColorKey( plataforma2, SDL_TRUE, SDL_MapRGB( plataforma2->format, 119, 124, 145 ) ); //plataforma2
            SDL_SetColorKey( plataforma3, SDL_TRUE, SDL_MapRGB( plataforma3->format, 119, 124, 145 ) ); //plataforma3

            //Gera eventos
            SDL_Event e;
            while( quit != 0)
            {
                 while( SDL_PollEvent( &e ) != 0 )
                {
                    //Usuario pede para sair
                    if( e.type == SDL_QUIT )
                    {
                        quit = 0;
                    }
                    //Usuario pressiona uma tecla
                    else if ( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {

                            case SDLK_ESCAPE:
                            quit = 0; //fecha o jogo
                            break;

                            case SDLK_RIGHT:
                            SpriteRect.x = SpriteRect.x + 1; //anda para a direita
                            break;

                            case SDLK_LEFT:
                            SpriteRect.x = SpriteRect.x - 1; //anda para a esquerda
                            break;
                        }
                    }
                }

                //Aplica a imagem
                SDL_BlitSurface( fundo, NULL, tela, &FRect );
                SDL_BlitSurface( plataforma1, NULL, tela, &PRect1 );
                SDL_BlitSurface( plataforma2, NULL, tela, &PRect2 );
                SDL_BlitSurface( plataforma1, NULL, tela, &PRect3 );
                SDL_BlitSurface( plataforma2, NULL, tela, &PRect4 );
                SDL_BlitSurface( plataforma1, NULL, tela, &PRect5 );
                SDL_BlitSurface( plataforma3, NULL, tela, &PRect6 );
                SDL_BlitSurface( escada, NULL, tela, &ERect1 );
                SDL_BlitSurface( escada, NULL, tela, &ERect2 );
                SDL_BlitSurface( escada, NULL, tela, &ERect3 );
                SDL_BlitSurface( escada, NULL, tela, &ERect4 );
                SDL_BlitSurface( escada, NULL, tela, &ERect5 );
                SDL_BlitSurface( sprite, NULL, tela, &SpriteRect );

                //Atualiza a tela
                SDL_UpdateWindowSurface(janela);
            }
        }
    }
    //Destroi janela
    SDL_DestroyWindow( janela );
    SDL_FreeSurface( fundo );
    fundo = NULL;
    //Sai do SDL
    SDL_Quit();

    return 0;
}
