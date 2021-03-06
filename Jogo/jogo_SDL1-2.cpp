#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>
#include <string>

int colisao( SDL_Rect A, SDL_Rect B )
{
    //lados dos retangulos
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //calcula os lados do rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //calcula os lados do rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //Se nao colidir
    if( bottomA <= topB )
    {
        return 0;
    }

    if( topA >= bottomB )
    {
        return 0;
    }

    if( rightA <= leftB )
    {
        return 0;
    }

    if( leftA >= rightB )
    {
        return 0;
    }

    //Se colidir
    return 1;
}

//Dimenssões da tela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//cria as variaves de controle dos frames
const int fps = 100;
Uint32 start;
float frame = 0;

//loop principal
int main( int argc, char* args[] )
{
    //cria a saida
    int quit = 1;

    //cria os objetos a serem usados
    SDL_Surface *tela = NULL;
    SDL_Surface *fundo = NULL;
    SDL_Surface *sprite = NULL;
    SDL_Surface *escada = NULL;
    SDL_Surface *plataforma1 = NULL;
    SDL_Surface *plataforma2 = NULL;
    SDL_Surface *plataforma3 = NULL;

    //Cria o ponteiro da musica
    Mix_Music *musica = NULL;

    //cria o movimento
    int bd = 0; //botao direito
    int be = 0; //botao esquerdo
    int bc = 0; //botao cima
    int bb = 0; //botao baixo

    //Inicializa o SDL
    if( SDL_INIT_EVERYTHING < 0 )
    {
        printf( "SDL nao inicializou!!!, SDL_Error: %s\n", SDL_GetError());
    }
    //Inicializa o SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        printf("SDL_Mixer ruim!!!, SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        //Cria a tela
        tela = SDL_SetVideoMode( SCREEN_WIDTH , SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );
        SDL_WM_SetCaption( "Donkey Frozen", NULL );

        if( tela != NULL )
        {

            //Le a imagem
            fundo = SDL_LoadBMP( "fundo.bmp" );
            sprite = SDL_LoadBMP( "tijolo.bmp" );
            escada = SDL_LoadBMP( "Escada.bmp" );
            plataforma1 = SDL_LoadBMP( "Plataforma1.bmp" );
            plataforma2 = SDL_LoadBMP( "Plataforma2.bmp" );
            plataforma3 = SDL_LoadBMP( "Plataforma41.bmp" );

            //Le a musica
            musica = Mix_LoadMUS("letitgo.wav");

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
            PRect6.x = 405 - PRect6.w;
            PRect6.y = 113 - PRect6.h;

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
            SpriteRect.x = 150 - SpriteRect.w;
            SpriteRect.y = 575 - SpriteRect.h;

            //cria os rects do fundo
            SDL_Rect FRect;
            FRect.w = fundo->w;
            FRect.h = fundo->h;
            FRect.x = 0;
            FRect.y = 0;


            //deixa transparente
            SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 119, 124, 125)) ; //sprite
            SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 108, 222, 86)); //sprite tijolo, excluir depois
            SDL_SetColorKey(escada, SDL_SRCCOLORKEY, SDL_MapRGB(escada->format, 99, 181, 230)); //escada
            SDL_SetColorKey(plataforma1, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma1->format, 119, 124, 145 )) ; //plataforma1
            SDL_SetColorKey(plataforma2, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma2->format, 119, 124, 145 )) ; //plataforma2
            SDL_SetColorKey(plataforma3, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma3->format, 119, 124, 145 )) ; //plataforma3

            //toca a musica
            /*if( Mix_PlayMusic( musica, -1 ) == -1 )
            {
                return 1;
            }*/

            //Gera eventos
            SDL_Event e;
            while( quit != 0)
            {

                //inicia a contagem de tempo do jogo e coloca ela dentro da variavel start
                start = SDL_GetTicks();

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

                            //anda para a direita
                            case SDLK_RIGHT:
                            if(SpriteRect.y < 558 && SpriteRect.y > 458)
                                bd = 0;
                            else
                                bd = 1;
                            break;

                            //anda para a esquerda
                            case SDLK_LEFT:
                            if(SpriteRect.y < 558 && SpriteRect.y > 458)
                                be = 0;
                            else
                                be = -1;
                            break;

                            default:
                            break;
                        }
                    }
                    else if ( e.type == SDL_KEYUP )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_RIGHT:
                            bd = 0;//para de andar para a direita
                            break;

                            case SDLK_LEFT:
                            be = 0; //para de andar para a esquerda
                            break;

                            default:
                            break;
                        }
                    }
                }

                //movimento do sprite pros lados
                if(bd == 1)
                    SpriteRect.x++;
                if(be == -1)
                    SpriteRect.x--;

                //Se o sprite colidiu com o final esquerdo da plataforma ou  o final direito
                if( SpriteRect.x > 700)
                {
                    //Move back
                    SpriteRect.x -= 1;
                }
                if ( SpriteRect.x < 50 )
                {
                    //Move back
                    SpriteRect.x += 1;
                }

                //Se o sprite colidir com a escada
                if (SpriteRect.x >= 426 && SpriteRect.x <= 428 )
                {
                    //permitir que o sprite suba ou desca
                    if ( e.type == SDL_KEYDOWN )
                         switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            bc = -1; //anda pra cima
                            break;

                            case SDLK_DOWN:
                            bb = 1; //anda pra baixo
                            break;

                            default:
                            break;
                        }
                    if ( e.type == SDL_KEYUP )
                         switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            bc = 0; //para de andar pra cima
                            break;

                            case SDLK_DOWN:
                            bb = 0; //para de andar pra baixo
                            break;

                            default:
                            break;
                        }
                }
                else
                {
                    bc = 0;
                    bb = 0;
                }


                //movimento do sprite pra cima ou baixo
                if(bb == 1)
                    SpriteRect.y++;
                if(bc == -1)
                    SpriteRect.y--;

                //limita o movimento para baixo e cima
                if(SpriteRect.y > 558)
                {
                    SpriteRect.y -= 1;
                }
                if(SpriteRect.y < 458)
                {
                    SpriteRect.y += 1;
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
                SDL_Flip(tela);

                //controla os frames
                frame = frame + 0.5;
                if (frame > 7) //numero de frames que o procedimento conta
                    frame = 0;
                //se 1 seg / frames for maior que o total menos o inicio
                // diminuir esse numero para adequar o programa aos frames
                if(1000 / fps > SDL_GetTicks() - start)
                    SDL_Delay(1000 / fps - (SDL_GetTicks() - start));
            }
        }
    }
    //Destroi janela
    SDL_FreeSurface(tela) ;
    SDL_FreeSurface( fundo );
    fundo = NULL;

    //Sai do SDL
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

