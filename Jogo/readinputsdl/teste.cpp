#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>
//Dimenssões da tela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//cria as variaves de controle dos frames
const int fps = 100;
Uint32 start;
float frame = 0;

//cria as variaveis do fim do jogo
int gameover = 0;

//cria as variaveis do zeramento
int winner = 0;

//cria as variaveis do score
int Pontuacao = 0, Aux_P = 0, indice = 0, aux_indice = -1, aux_indice2 = -1;
char CharPontuacao[100], CharHighPt[100];

//loop principal
int main( int argc, char* args[] )
{
    //cria a saida
    int quit = 1;

    //cria as variaveis do arquivo
    FILE *HighArq;
    int MaiorPont1, MaiorPont2, MaiorPont3, NovoRecorde = 1;
    char CharMaiorPont1[100], CharMaiorPont2[100], CharMaiorPont3[100];
    char Nome1[6], Nome2[6], Nome3[6], Nome[6] = {     };

    //cria os objetos a serem usados
    SDL_Surface *tela = NULL;
    SDL_Surface *fundo = NULL;
    SDL_Surface *NovoNome = NULL;
    SDL_Surface *TelaNN = NULL;


    //cria os ponteiros da musica
    Mix_Music *musica = NULL;

    //cria os ponteiros da fonte
    TTF_Font *fonte = NULL;

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
    //Inicializa o SDL_TTF
    if( TTF_Init() == -1 )
    {
        printf("TTF ruim!!!, SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        //Cria a tela
        tela = SDL_SetVideoMode( SCREEN_WIDTH , SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );
        SDL_WM_SetCaption( "Elsa's Rescue", NULL );

        if( tela != NULL )
        {

            //Le a imagem
            TelaNN = SDL_LoadBMP("novorecorde.bmp");

            //Le a fonte
            fonte = TTF_OpenFont("fonte.ttf", 26);

            //cria os rects da tela de novo recorde
            SDL_Rect TNNRect;
            TNNRect.w = TelaNN->w;
            TNNRect.h = TelaNN->h;
            TNNRect.x = 0;
            TNNRect.y = 0;

            //cria os rects do novo nome
            SDL_Rect NNRect;
            NNRect.x = 300;
            NNRect.y = 300;

            //Gera eventos
            SDL_Event e;
            while( quit != 0)
            {
                //inicia a contagem de tempo do jogo e coloca ela dentro da variavel start
                start = SDL_GetTicks();
                while( SDL_PollEvent( &e ) != 0)
                {
                    //Usuario pede para sair
                    if( e.type == SDL_QUIT )
                    {
                        quit = 0;
                    }
                }

                SDL_BlitSurface(TelaNN, NULL, tela, &TNNRect);
                if(indice < 6)
                {
                    if ( e.type == SDL_KEYDOWN )
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_a:
                            Nome[indice] = 'a';
                            aux_indice2 = 1;
                            break;

                            case SDLK_b:
                            Nome[indice] = 'b';
                            aux_indice2 = 1;
                            break;

                            case SDLK_c:
                            Nome[indice] = 'c';
                            aux_indice2 = 1;
                            break;

                            case SDLK_d:
                            Nome[indice] = 'd';
                            aux_indice2 = 1;
                            break;

                            case SDLK_e:
                            Nome[indice] = 'e';
                            aux_indice2 = 1;
                            break;

                            case SDLK_f:
                            Nome[indice] = 'f';
                            aux_indice2 = 1;
                            break;

                            case SDLK_g:
                            Nome[indice] = 'g';
                            aux_indice2 = 1;
                            break;

                            case SDLK_h:
                            Nome[indice] = 'h';
                            aux_indice2 = 1;
                            break;

                            case SDLK_i:
                            Nome[indice] = 'i';
                            aux_indice2 = 1;
                            break;

                            case SDLK_j:
                            Nome[indice] = 'j';
                            aux_indice2 = 1;
                            break;

                            case SDLK_k:
                            Nome[indice] = 'k';
                            aux_indice2 = 1;
                            break;

                            case SDLK_l:
                            Nome[indice] = 'l';
                            aux_indice2 = 1;
                            break;

                            case SDLK_m:
                            Nome[indice] = 'm';
                            aux_indice2 = 1;
                            break;

                            case SDLK_n:
                            Nome[indice] = 'n';
                            aux_indice2 = 1;
                            break;

                            case SDLK_o:
                            Nome[indice] = 'o';
                            aux_indice2 = 1;
                            break;

                            case SDLK_p:
                            Nome[indice] = 'p';
                            aux_indice2 = 1;
                            break;

                            case SDLK_q:
                            Nome[indice] = 'q';
                            aux_indice2 = 1;
                            break;

                            case SDLK_r:
                            Nome[indice] = 'r';
                            aux_indice2 = 1;
                            break;

                            case SDLK_s:
                            Nome[indice] = 's';
                            aux_indice2 = 1;
                            break;

                            case SDLK_t:
                            Nome[indice] = 't';
                            aux_indice2 = 1;
                            break;

                            case SDLK_u:
                            Nome[indice] = 'u';
                            aux_indice2 = 1;
                            break;

                            case SDLK_v:
                            Nome[indice] = 'v';
                            aux_indice2 = 1;
                            break;

                            case SDLK_w:
                            Nome[indice] = 'w';
                            aux_indice2 = 1;
                            break;

                            case SDLK_x:
                            Nome[indice] = 'x';
                            aux_indice2 = 1;
                            break;

                            case SDLK_y:
                            Nome[indice] = 'y';
                            aux_indice2 = 1;
                            break;

                            case SDLK_z:
                            Nome[indice] = 'z';
                            aux_indice2 = 1;
                            break;

                            case SDLK_RETURN:
                            Nome[indice] = '\0';
                            indice = 6;
                            break;

                            case SDLK_BACKSPACE:
                            Nome[indice - 1] = ' ';
                            aux_indice2 = 1;
                            break;

                            default:
                            break;
                        }
                    if(aux_indice2 == 1)
                    {
                        if ( e.type == SDL_KEYUP )
                            switch( e.key.keysym.sym )
                            {
                                case SDLK_a:
                                aux_indice = 1;
                                break;

                                case SDLK_b:
                                aux_indice = 1;
                                break;

                                case SDLK_c:
                                aux_indice = 1;
                                break;

                                case SDLK_d:
                                aux_indice = 1;
                                break;

                                case SDLK_e:
                                aux_indice = 1;
                                break;

                                case SDLK_f:
                                aux_indice = 1;
                                break;

                                case SDLK_g:
                                aux_indice = 1;
                                break;

                                case SDLK_h:
                                aux_indice = 1;
                                break;

                                case SDLK_i:
                                aux_indice = 1;
                                break;

                                case SDLK_j:
                                aux_indice = 1;
                                break;

                                case SDLK_k:
                                aux_indice = 1;
                                break;

                                case SDLK_l:
                                aux_indice = 1;
                                break;

                                case SDLK_m:
                                aux_indice = 1;
                                break;

                                case SDLK_n:
                                aux_indice = 1;
                                break;

                                case SDLK_o:
                                aux_indice = 1;
                                break;

                                case SDLK_p:
                                aux_indice = 1;
                                break;

                                case SDLK_q:
                                aux_indice = 1;
                                break;

                                case SDLK_r:
                                aux_indice = 1;
                                break;

                                case SDLK_s:
                                aux_indice = 1;
                                break;

                                case SDLK_t:
                                aux_indice = 1;
                                break;

                                case SDLK_u:
                                aux_indice = 1;
                                break;

                                case SDLK_v:
                                aux_indice = 1;
                                break;

                                case SDLK_w:
                                aux_indice = 1;
                                break;

                                case SDLK_x:
                                aux_indice = 1;
                                break;

                                case SDLK_y:
                                aux_indice = 1;
                                break;

                                case SDLK_z:
                                aux_indice = 1;
                                break;

                                case SDLK_BACKSPACE:
                                aux_indice = 2;
                                break;

                                default:
                                break;
                            }
                    }
                if(aux_indice == 1)
                {
                    indice += 1;
                    aux_indice = 0;
                    aux_indice2 = 0;
                }
                if(aux_indice == 2)
                {
                    indice -= 1;
                    aux_indice = 0;
                    aux_indice2 = 0;
                }
                NovoNome = TTF_RenderText_Solid( fonte, Nome , { 150, 188, 224 } );
                SDL_BlitSurface( NovoNome, NULL, tela, &NNRect);
                }
                else
                {
                    if(NovoRecorde == 1)
                        quit = 0;
                    if(NovoRecorde == 2)
                        quit = 0;
                    if(NovoRecorde == 3)
                        quit = 0;
                }

                //Atualiza a tela
                SDL_Flip(tela);

                //controla os frames
                frame = frame + 0.5;
                if (frame > 7)  //numero de frames que o procedimento conta
                    frame = 0;  //se 1 seg / frames for maior que o total menos o inicio
                                // diminuir esse numero para adequar o programa aos frames
                if(1000 / fps > SDL_GetTicks() - start)
                    SDL_Delay(1000 / fps - (SDL_GetTicks() - start));
            }

        //Destroi janela
        SDL_FreeSurface(tela) ;
        SDL_FreeSurface( fundo );
        fundo = NULL;

        //Sai do SDL
        TTF_CloseFont(fonte); //fecha a fonte que foi usada
        TTF_Quit();
        Mix_CloseAudio();
        SDL_Quit();
        }
    }
    return 0;
}


