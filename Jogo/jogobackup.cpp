#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>

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

//cria as variaveis do mouse
int x = 0, y = 0;

//cria a variavel que altera as telas do jogo
int c = 0;

//cria as variaveis do movimento do barril
int b1 = 0, tempo = 0;
int esq, dir, baix, dir2, esq2, baix2, dir3, esq3, baix3;
int esq4, dir4, baix4, dir5, esq5, baix5;
int bspeed = 0;

//cria as variaveis do pulo
int pulo = 0, pulocima, pulobaixo, jump  = 0, notescada = 1;

//cria a variavel das vidas
int vida = 3, menosvida = 0;
char CharVida[2];

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
    int MaiorPont1, MaiorPont2, MaiorPont3, NovoRecorde = 0;
    char CharMaiorPont1[100], CharMaiorPont2[100], CharMaiorPont3[100];
    char Nome1[6], Nome2[6], Nome3[6], Nome[6] = {     };

    //cria os objetos a serem usados
    SDL_Surface *tela = NULL;
    SDL_Surface *fundo = NULL;
    SDL_Surface *telainicial = NULL;
    SDL_Surface *sprite = NULL;
    SDL_Surface *escada = NULL;
    SDL_Surface *plataforma1 = NULL;
    SDL_Surface *plataforma2 = NULL;
    SDL_Surface *plataforma3 = NULL;
    SDL_Surface *bola_de_neve = NULL;
    SDL_Surface *neve = NULL;
    SDL_Surface *fim = NULL;
    SDL_Surface *nj = NULL; //botao novo jogo
    SDL_Surface *nje = NULL; //efeito do botao novo jogo
    SDL_Surface *sair = NULL;
    SDL_Surface *saire = NULL;
    SDL_Surface *creditos = NULL;
    SDL_Surface *creditose = NULL;
    SDL_Surface *instrucoes = NULL;
    SDL_Surface *instrucoese = NULL;
    SDL_Surface *fcreditos = NULL;
    SDL_Surface *voltar = NULL;
    SDL_Surface *voltare = NULL;
    SDL_Surface *instrucao = NULL;
    SDL_Surface *zerar = NULL;
    SDL_Surface *recordes = NULL; //cria a tela dos recordes
    SDL_Surface *record = NULL; //cria o botao dos recordes
    SDL_Surface *recorde = NULL; //cria o efeito do botao dos recordes
    SDL_Surface *MensagemScore = NULL; //mostra o score na tela
    SDL_Surface *MensagemPontScore = NULL; //mostra o score na tela
    SDL_Surface *MensagemVida = NULL; //mostra as vidas na tela
    SDL_Surface *MensagemValorVida = NULL; //mostra as vidas na tela
    SDL_Surface *MgmHighScore = NULL; //mostra o maior score na tela
    SDL_Surface *MgmHighPtScore = NULL; //mostra o maior score na tela
    SDL_Surface *CP1 = NULL; //surface do charmaiorpont1
    SDL_Surface *CP2 = NULL; //surface do charmaiorpont2
    SDL_Surface *CP3 = NULL; //surface do charmaiorpont3
    SDL_Surface *N1 = NULL; //surface do nome do primeiro recordista
    SDL_Surface *N2 = NULL; //surface do nome do segundo recordista
    SDL_Surface *N3 = NULL; //surface do nome do terceiro recordista
    SDL_Surface *NovoNome = NULL;
    SDL_Surface *TelaNN = NULL;


    //cria os ponteiros da musica
    Mix_Music *musica = NULL;

    //cria os ponteiros da fonte
    TTF_Font *fonte = NULL;

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
            telainicial = SDL_LoadBMP("menu.bmp");
            fundo = SDL_LoadBMP("fundo.bmp");
            nj = SDL_LoadBMP("novojogo.bmp");
            nje = SDL_LoadBMP("novojogo1.bmp");
            sair = SDL_LoadBMP("sair.bmp");
            saire = SDL_LoadBMP("sair1.bmp");
            creditos = SDL_LoadBMP("creditos.bmp");
            creditose = SDL_LoadBMP("creditos1.bmp");
            instrucoes =  SDL_LoadBMP("instrucoes.bmp");
            instrucoese = SDL_LoadBMP("instrucoes1.bmp");
            fcreditos = SDL_LoadBMP("credito.bmp");
            voltar = SDL_LoadBMP("voltar.bmp");
            voltare = SDL_LoadBMP("voltar1.bmp");
            instrucao = SDL_LoadBMP("instrucao.bmp");
            sprite = IMG_Load("tijolo.bmp");
            escada = SDL_LoadBMP( "Escada.bmp" );
            plataforma1 = SDL_LoadBMP( "Plataforma1.bmp" );
            plataforma2 = SDL_LoadBMP( "Plataforma2.bmp" );
            plataforma3 = SDL_LoadBMP( "Plataforma41.bmp" );
            bola_de_neve = SDL_LoadBMP("boladeneve1.bmp");
            neve = SDL_LoadBMP("neve.bmp");
            fim = SDL_LoadBMP("fimdejogo.bmp");
            zerar = SDL_LoadBMP("vcvenceu.bmp");
            recordes = SDL_LoadBMP("recordes.bmp");
            record = SDL_LoadBMP("rec.bmp");
            recorde = SDL_LoadBMP("rece.bmp");
            TelaNN = SDL_LoadBMP("novorecorde.bmp");
            //Le a musica
            musica = Mix_LoadMUS("letitgo.wav");

            //Le a fonte
            fonte = TTF_OpenFont("fonte.ttf", 26);

            //cria os rects do menu
            SDL_Rect TIRect;
            TIRect.w = telainicial->w;
            TIRect.h = telainicial->h;
            TIRect.x = 0;
            TIRect.y = 0;

            //cria os rects do botao do novo jogo
            SDL_Rect NJRect;
            NJRect.w = nj->w;
            NJRect.h = nj->h;
            NJRect.x = 440;
            NJRect.y = 100;

            //cria os rects do efeito do botao do novo jogo
            SDL_Rect NJeRect;
            NJeRect.w = nje->w;
            NJeRect.h = nje->h;
            NJeRect.x = 440;
            NJeRect.y = 100;

            //cria os rects do botao dos creditos
            SDL_Rect CRect;
            CRect.w = creditos->w;
            CRect.h = creditos->h;
            CRect.x = 460;
            CRect.y = 190;

            //cria os rects do efeito do botao dos creditos
            SDL_Rect CeRect;
            CeRect.w = creditose->w;
            CeRect.h = creditose->h;
            CeRect.x = 460;
            CeRect.y = 190;

            //cria os rects do botao da saida
            SDL_Rect SRect;
            SRect.w = sair->w;
            SRect.h = sair->h;
            SRect.x = 512;
            SRect.y = 460;

            //cria os rects do efeito do botao da saida
            SDL_Rect SeRect;
            SeRect.w = saire->w;
            SeRect.h = saire->h;
            SeRect.x = 512;
            SeRect.y = 460;

            //cria os rects do botao das instruções
            SDL_Rect IRect;
            IRect.w = instrucoes->w;
            IRect.h = instrucoes->h;
            IRect.x = 450;
            IRect.y = 275;

            //cria os rects do efeito do botao das instruções
            SDL_Rect IeRect;
            IeRect.w = instrucoese->w;
            IeRect.h = instrucoese->h;
            IeRect.x = 450;
            IeRect.y = 275;

            //cria os rects do botao de voltar
            SDL_Rect VRect;
            VRect.w = voltar->w;
            VRect.h = voltar->h;
            VRect.x = 500;
            VRect.y = 510;

            //cria os rects do efeito do botao de voltar
            SDL_Rect VeRect;
            VeRect.w = voltare->w;
            VeRect.h = voltare->h;
            VeRect.x = 500;
            VeRect.y = 510;

            //cria os rects dos creditos
            SDL_Rect FCRect;
            FCRect.w = fcreditos->w;
            FCRect.h = fcreditos->h;
            FCRect.x = 0;
            FCRect.y = 0;

            //cria os rects das instruções
            SDL_Rect ISRect;
            ISRect.w = instrucao->w;
            ISRect.h = instrucao->h;
            ISRect.x = 0;
            ISRect.y = 0;

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
            //cria os rects da bola de neve 1
            SDL_Rect BRect;
            BRect.w = bola_de_neve->w;
            BRect.h = bola_de_neve->h;
            BRect.x = 50;
            BRect.y = 150;

            //cria os rects da bola de neve 2
            SDL_Rect BRect2;
            BRect2.w = bola_de_neve->w;
            BRect2.h = bola_de_neve->h;
            BRect2.x = 50;
            BRect2.y = 150;

            //cria os rects da bola de neve 3
            SDL_Rect BRect3;
            BRect3.w = bola_de_neve->w;
            BRect3.h = bola_de_neve->h;
            BRect3.x = 50;
            BRect3.y = 150;

            //cria os rects da bola de neve 4
            SDL_Rect BRect4;
            BRect4.w = bola_de_neve->w;
            BRect4.h = bola_de_neve->h;
            BRect4.x = 50;
            BRect4.y = 150;

            //cria os rects da bola de neve 5
            SDL_Rect BRect5;
            BRect5.w = bola_de_neve->w;
            BRect5.h = bola_de_neve->h;
            BRect5.x = 50;
            BRect5.y = 150;

            //cria os rects da neve
            SDL_Rect NRect;
            NRect.w = neve->w;
            NRect.h = neve->h;
            NRect.x = 630;
            NRect.y = 530;

            //cria os rects do fim de jogo
            SDL_Rect GORect;
            GORect.w = fim->w;
            GORect.h = fim->h;
            GORect.x = 0;
            GORect.y = 0;

            //cria os rects do zeramento
            SDL_Rect ZRect;
            ZRect.w = zerar->w;
            ZRect.h = zerar->h;
            ZRect.x = 0;
            ZRect.y = 0;

            //cria os rects dos recordes
            SDL_Rect RECRect;
            RECRect.w = recordes->w;
            RECRect.h = recordes->h;
            RECRect.x = 0;
            RECRect.y = 0;

            //cria os rects do botao dos recordes
            SDL_Rect RERect;
            RERect.w = record->w;
            RERect.h = record->h;
            RERect.x = 0;
            RERect.y = 0;

            //cria os rects do efeito do botao dos recordes
            SDL_Rect REeRect;
            REeRect.w = recorde->w;
            REeRect.h = recorde->h;
            REeRect.x = 0;
            REeRect.y = 0;

            //cria os rects dos recordes
            SDL_Rect CP1Rect;
            CP1Rect.x = 400;
            CP1Rect.y = 200;

            SDL_Rect CP2Rect;
            CP2Rect.x = 400;
            CP2Rect.y = 250;

            SDL_Rect CP3Rect;
            CP3Rect.x = 400;
            CP3Rect.y = 300;

            //cria os rects dos nomes dos recordistas
            SDL_Rect N1Rect;
            N1Rect.x = 300;
            N1Rect.y = 200;

            SDL_Rect N2Rect;
            N2Rect.x = 300;
            N2Rect.y = 250;

            SDL_Rect N3Rect;
            N3Rect.x = 300;
            N3Rect.y = 300;

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

            //cria os rects da mensagem do score
            SDL_Rect MSRect;
            MSRect.x = 110;
            MSRect.y = 0;

            //cria os rects da mensagem do score (nº)
            SDL_Rect MPSRect;
            MPSRect.x = 190;
            MPSRect.y = 0;

            //cria os rects da mensagem do score mais alto
            SDL_Rect MHSRect;
            MHSRect.x = 350;
            MHSRect.y = 0;

            //cria os rects da mensagem do score mais alto (nº)
            SDL_Rect MHPSRect;
            MHPSRect.x = 490;
            MHPSRect.y = 0;

            //cria os rects da mensagem da vida
            SDL_Rect MVRect;
            MVRect.x = 40;
            MVRect.y = 0;

            //cria os rects da mensagem da vida (nº)
            SDL_Rect MVVRect;
            MVVRect.x = 60;
            MVVRect.y = 0;

            //deixa transparente
            SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 119, 124, 125)) ; //sprite
            SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, SDL_MapRGB(sprite->format, 108, 222, 86)); //sprite tijolo, excluir depois
            SDL_SetColorKey(escada, SDL_SRCCOLORKEY, SDL_MapRGB(escada->format, 99, 181, 230)); //escada
            SDL_SetColorKey(plataforma1, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma1->format, 119, 124, 145 )) ; //plataforma1
            SDL_SetColorKey(plataforma2, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma2->format, 119, 124, 145 )) ; //plataforma2
            SDL_SetColorKey(plataforma3, SDL_SRCCOLORKEY, SDL_MapRGB(plataforma3->format, 119, 124, 145 )) ; //plataforma3
            SDL_SetColorKey(bola_de_neve, SDL_SRCCOLORKEY, SDL_MapRGB(bola_de_neve->format, 119, 124, 145 )) ; //bola de neve
            SDL_SetColorKey(neve, SDL_SRCCOLORKEY, SDL_MapRGB(neve->format, 119, 124, 145 )) ; //neve

            //abre o arquivo e le os recordes
            HighArq = fopen("HighScores.txt", "r");

            fscanf(HighArq, "%s", &Nome3);
            fscanf(HighArq, "%s", &Nome2);
            fscanf(HighArq, "%s", &Nome1);

            fscanf(HighArq, "%d", &MaiorPont3);
            sprintf(CharMaiorPont3, "%d", MaiorPont3);
            CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

            fscanf(HighArq, "%d", &MaiorPont2);
            sprintf(CharMaiorPont2, "%d", MaiorPont2);
            CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

            fscanf(HighArq, "%d", &MaiorPont1);
            sprintf(CharMaiorPont1, "%d", MaiorPont1);
            CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

            fclose(HighArq);

            //abre o arquivo para que os dados possam ser alterados
            HighArq = fopen("HighScores.txt", "r+");

            //Gera eventos
            SDL_Event e;
            while( quit != 0)
            {
                //inicia a contagem de tempo do jogo e coloca ela dentro da variavel start
                start = SDL_GetTicks();
                inicio:
                while( SDL_PollEvent( &e ) != 0)
                {
                    //Usuario pede para sair
                    if( e.type == SDL_QUIT )
                    {
                        quit = 0;
                    }
                }
                    //testa se a variavel c é zero para iniciar o jogo
                    if(c == 0)
                    {
                        SDL_BlitSurface( telainicial, NULL, tela, &TIRect );
                        SDL_BlitSurface( nj, NULL, tela, &NJRect );
                        SDL_BlitSurface( sair, NULL, tela, &SRect );
                        SDL_BlitSurface( creditos, NULL, tela, &CRect );
                        SDL_BlitSurface(instrucoes, NULL, tela, &IRect);
                        SDL_BlitSurface(record, NULL, tela, &RERect);
                        //If the mouse moved
                        if( e.type == SDL_MOUSEMOTION )
                        {
                            //Get the mouse offsets
                            x = e.motion.x;
                            y = e.motion.y;

                            //If the mouse is over the button
                            if( ( x > NJRect.x ) && ( x < NJRect.x + NJRect.w ) && ( y > NJRect.y ) && ( y < NJRect.y + NJRect.h ) )
                            {
                                SDL_BlitSurface ( nje, NULL, tela, &NJeRect );
                            }
                            if( ( x > CRect.x ) && ( x < CRect.x + CRect.w ) && ( y > CRect.y ) && ( y < CRect.y + CRect.h ) )
                            {
                                SDL_BlitSurface ( creditose, NULL, tela, &CeRect );
                            }
                            if( ( x > SRect.x ) && ( x < SRect.x + SRect.w ) && ( y > SRect.y ) && ( y < SRect.y + SRect.h ) )
                            {
                                SDL_BlitSurface ( saire, NULL, tela, &SeRect );
                            }
                            if( ( x > IRect.x ) && ( x < IRect.x + IRect.w ) && ( y > IRect.y ) && ( y < IRect.y + IRect.h ) )
                            {
                                SDL_BlitSurface ( instrucoese, NULL, tela, &IeRect );
                            }
                            if( ( x > RERect.x ) && ( x < RERect.x + RERect.w ) && ( y > RERect.y ) && ( y < RERect.y + RERect.h ) )
                            {
                                SDL_BlitSurface ( recorde, NULL, tela, &REeRect );
                            }
                        }
                        //If a mouse button was pressed
                        if( e.type == SDL_MOUSEBUTTONDOWN )
                        {
                            //If the left mouse button was pressed
                            if( e.button.button == SDL_BUTTON_LEFT )
                            {
                                //Get the mouse offsets
                                x = e.button.x;
                                y = e.button.y;
                                //If the mouse is over the button
                                if( ( x > NJRect.x ) && ( x < NJRect.x + NJRect.w ) && ( y > NJRect.y ) && ( y < NJRect.y + NJRect.h ) )
                                {
                                    c = 2;
                                    goto begingame;
                                }
                                if( ( x > CRect.x ) && ( x < CRect.x + CRect.w ) && ( y > CRect.y ) && ( y < CRect.y + CRect.h ) )
                                {
                                    c = 1; //permite entrar nos creditos
                                    goto credits;
                                }
                                if( ( x > SRect.x ) && ( x < SRect.x + SRect.w ) && ( y > SRect.y ) && ( y < SRect.y + SRect.h ) )
                                {
                                    quit = 0;
                                }
                                if( ( x > IRect.x ) && ( x < IRect.x + IRect.w ) && ( y > IRect.y ) && ( y < IRect.y + IRect.h ) )
                                {
                                    c = 3;
                                    goto instructions;
                                }
                                if( ( x > RERect.x ) && ( x < RERect.x + RERect.w ) && ( y > RERect.y ) && ( y < RERect.y + RERect.h ) )
                                {
                                    c = 5;
                                    goto pontuacoesm;
                                }
                            }
                        }
                    }

                    credits:
                    if (c == 1)
                    {
                        SDL_BlitSurface (fcreditos, NULL, tela, &FCRect );
                        SDL_BlitSurface (voltar, NULL, tela, &VRect );
                        //If the mouse moved
                        if( e.type == SDL_MOUSEMOTION )
                        {
                            //Get the mouse offsets
                            x = e.motion.x;
                            y = e.motion.y;

                            //If the mouse is over the button
                            if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                            {
                                SDL_BlitSurface ( voltare, NULL, tela, &VeRect );
                            }
                        }
                        //If a mouse button was pressed
                        if( e.type == SDL_MOUSEBUTTONDOWN )
                        {
                            //If the left mouse button was pressed
                            if( e.button.button == SDL_BUTTON_LEFT )
                            {
                                //Get the mouse offsets
                                x = e.button.x;
                                y = e.button.y;
                                //If the mouse is over the button
                                if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                                {
                                    c = 0;
                                    goto inicio;
                                }
                            }
                        }
                    }

                    begingame:
                    if (c == 2)
                    {
                        //Usuario pressiona uma tecla
                        if ( e.type == SDL_KEYDOWN )
                        {
                            switch( e.key.keysym.sym )
                            {

                                //anda para a direita
                                case SDLK_RIGHT:
                                //corrije o problema de andar na escada
                                if(SpriteRect.y < 558 && SpriteRect.y > 458)
                                    bd = 0;
                                else if (SpriteRect.y < 455 && SpriteRect.y > 358)
                                    bd = 0;
                                else if (SpriteRect.y < 355 && SpriteRect.y > 260)
                                    bd = 0;
                                else if (SpriteRect.y < 255 && SpriteRect.y > 160)
                                    bd = 0;
                                else if (SpriteRect.y < 155 && SpriteRect.y > 60)
                                    bd = 0;
                                else
                                    bd = 1;
                                break;

                                //anda para a esquerda
                                case SDLK_LEFT:
                                //corrije o problema de andar na escada
                                if(SpriteRect.y < 558 && SpriteRect.y > 458)
                                    be = 0;
                                else if (SpriteRect.y < 455 && SpriteRect.y > 358)
                                    be = 0;
                                else if (SpriteRect.y < 355 && SpriteRect.y > 260)
                                    be = 0;
                                else if (SpriteRect.y < 255 && SpriteRect.y > 160)
                                    be = 0;
                               else if (SpriteRect.y < 155 && SpriteRect.y > 60)
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


                    //movimento do sprite pros lados
                    if(bd == 1)
                        SpriteRect.x++;
                    if(be == -1)
                        SpriteRect.x--;

                    //limita as dimensoes da plataforma, impedindo que o sprite saia dela
                    //melhorar essa logica, n funciona para o pulo
                    int moveback = 1;
                    //Se o sprite colidiu com o final esquerdo da plataforma ou o final direito da plataforma 2 ou 4
                    if(SpriteRect.x > 750 && ((SpriteRect.y >= 450 && SpriteRect.y <= 500) || (SpriteRect.y >= 250 && SpriteRect.y <= 300)))
                    {
                        //Move back
                        SpriteRect.x -= moveback;
                        be = 0;
                    }
                    if ( SpriteRect.x < 100 && ((SpriteRect.y >= 450 && SpriteRect.y <= 500) || (SpriteRect.y >= 250 && SpriteRect.y <= 300)))
                    {
                        //Move back
                        SpriteRect.x += moveback;
                        bd = 0;
                    }
                    //Se o sprite colidiu com o final esquerdo da plataforma ou o final direito da plataforma 1, 3 ou 5
                    if(SpriteRect.x > 680 && ((SpriteRect.y >= 550 && SpriteRect.y <= 600) || (SpriteRect.y >= 350 && SpriteRect.y <= 400) || (SpriteRect.y >= 150 && SpriteRect.y <= 200 )))
                    {
                        //Move back
                        SpriteRect.x -= moveback;
                        be = 0;
                    }
                    if ( SpriteRect.x < 10 && ((SpriteRect.y >= 550 && SpriteRect.y <= 600) || (SpriteRect.y >= 350 && SpriteRect.y <= 400) || (SpriteRect.y >= 150 && SpriteRect.y <= 200 )))
                    {
                        //Move back
                        SpriteRect.x += moveback;
                        bd = 0;
                    }

                    // variavel que faz subir
                    int subir, limitador;
                    subir = 0;
                    limitador = 0;

                    //Se o sprite nao colidir com nenhuma escada
                    if(!(SpriteRect.x >= 425 && SpriteRect.x <= 429 && SpriteRect.y <= 560 && SpriteRect.y >= 456))
                        notescada = 1;
                    else if(!(SpriteRect.x >= 670 && SpriteRect.x <= 690 && SpriteRect.y <= 458 && SpriteRect.y >= 356 ))
                        notescada = 1;
                    else if(!(SpriteRect.x >= 120 && SpriteRect.x <= 132 && SpriteRect.y <= 358 && SpriteRect.y >= 256 ))
                        notescada = 1;
                    else if(!(SpriteRect.x >= 520 && SpriteRect.x <= 530 && SpriteRect.y <= 258 && SpriteRect.y >= 156 ))
                        notescada = 1;
                    else if(!(SpriteRect.x >= 270 && SpriteRect.x <= 280 && SpriteRect.y <= 158 && SpriteRect.y >= 56 ))
                        notescada = 1;

                    //Se o sprite colidir com a escada 1
                    if (SpriteRect.x >= 425 && SpriteRect.x <= 429 && SpriteRect.y <= 560 && SpriteRect.y >= 456)
                    {
                        subir = 1;
                        limitador = 1;
                        notescada = 0;
                    }
                    //Se o sprite colidir com a escada 2
                    if (SpriteRect.x >= 670 && SpriteRect.x <= 690 && SpriteRect.y <= 458 && SpriteRect.y >= 356 )
                    {
                        subir = 1;
                        limitador = 2;
                        notescada = 0;
                    }
                    //Se o sprite colidir com a escada 3
                    if (SpriteRect.x >= 120 && SpriteRect.x <= 132 && SpriteRect.y <= 358 && SpriteRect.y >= 256 )
                    {
                        subir = 1;
                        limitador = 3;
                        notescada = 0;
                    }
                    //Se o sprite colidir com a escada 4
                    if (SpriteRect.x >= 520 && SpriteRect.x <= 530 && SpriteRect.y <= 258 && SpriteRect.y >= 156 )
                    {
                        subir = 1;
                        limitador = 4;
                        notescada = 0;
                    }
                    //Se o sprite colidir com a escada 5
                    if (SpriteRect.x >= 270 && SpriteRect.x <= 280 && SpriteRect.y <= 158 && SpriteRect.y >= 56 )
                    {
                        subir = 1;
                        limitador = 5;
                        notescada = 0;
                    }

                    // permite que suba
                    if (subir == 1)
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
                    if (limitador == 1)
                    {
                        if(SpriteRect.y > 559)
                            SpriteRect.y -= 1;
                        if(SpriteRect.y < 458)
                            SpriteRect.y += 1;
                    }
                    else if (limitador == 2)
                    {
                        if(SpriteRect.y > 458)
                            SpriteRect.y -= 1;
                        if(SpriteRect.y < 358)
                            SpriteRect.y += 1;
                    }
                    else if (limitador == 3)
                    {
                        if(SpriteRect.y > 358)
                            SpriteRect.y -= 1;
                        if(SpriteRect.y < 258)
                            SpriteRect.y += 1;
                    }
                    else if (limitador == 4)
                    {
                        if(SpriteRect.y > 258)
                            SpriteRect.y -= 1;
                        if(SpriteRect.y < 158)
                            SpriteRect.y += 1;
                    }
                    else if (limitador == 5)
                    {
                        if(SpriteRect.y > 158)
                            SpriteRect.y -= 1;
                        if(SpriteRect.y < 58)
                            SpriteRect.y += 1;
                    }

                    //pulo
                    if(notescada != 0)
                    {
                        if ( e.type == SDL_KEYDOWN )
                            switch( e.key.keysym.sym )
                            {
                                case SDLK_SPACE:
                                pulo = 1;
                                break;

                                default:
                                break;
                            }
                    }
                    if(pulo == 1)
                        jump++;
                    if (jump > 0)
                    {
                        pulocima = 1;
                        pulobaixo = 0;
                    }
                    if(jump > 25)
                    {
                        pulocima = 0;
                        pulobaixo = 1;
                    }
                    if(jump > 50)
                    {
                        jump = 0;
                        pulo = 0;
                        pulocima = 0;
                        pulobaixo = 0;
                    }

                    if(pulocima == 1)
                        SpriteRect.y -= 2;
                    if(pulobaixo == 1)
                        SpriteRect.y += 2;

                    pulocima = 0;
                    pulobaixo = 0;


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

                    //cria a contagem dos barris
                    tempo ++;
                    if (tempo == 50)
                        b1 = 1;
                    if (tempo == 350)
                        b1 = 2;
                    if (tempo == 650)
                        b1 = 3;
                    if (tempo == 950)
                        b1 = 4;
                    if (tempo == 1250)
                        b1 = 5;

                    //aplica os barris na tela
                    if (b1 >= 1)
                        SDL_BlitSurface( bola_de_neve, NULL, tela, &BRect );
                    if (b1 >= 2)
                        SDL_BlitSurface( bola_de_neve, NULL, tela, &BRect2 );
                    if (b1 >= 3)
                        SDL_BlitSurface( bola_de_neve, NULL, tela, &BRect3 );
                    if (b1 >= 4)
                        SDL_BlitSurface( bola_de_neve, NULL, tela, &BRect4 );
                    if (b1 >= 5)
                        SDL_BlitSurface( bola_de_neve, NULL, tela, &BRect5 );


                    //camuflagem pro desaparecimento da neve
                    SDL_BlitSurface( neve, NULL, tela, &NRect );


                    //bola de neve "barril" 1
                    if (b1 >= 1) {
                        if(BRect.x == 50 && BRect.y == 150)
                        {
                            dir = 1;
                            esq = 0;
                            baix = 0;
                        }
                        if (BRect.x == 700)
                        {
                            dir = 0;
                            baix = 1;
                            esq = 0;
                        }
                        if(BRect.y == 250)
                        {
                            dir = 0;
                            baix = 0;
                            esq = 1;
                        }
                        if(BRect.y >= 250 && BRect.x == 10)
                        {
                            dir = 0;
                            baix = 1;
                            esq = 0;
                        }
                        if(BRect.y == 350 && BRect.x == 10)
                        {
                            dir = 1;
                            baix = 0;
                            esq = 0;
                        }
                        if(BRect.y == 450 && BRect.x == 700)
                        {
                            dir = 0;
                            baix = 0;
                            esq = 1;
                        }
                        if(BRect.y == 550 && BRect.x == 10)
                        {
                            dir = 1;
                            baix = 0;
                            esq = 0;
                        }
                        if(BRect.y == 550 && BRect.x == 700)
                        {
                            BRect.x = 50;
                            BRect.y = 140;
                        }
                    }
                    if (b1 >= 2) {
                        if(BRect2.x == 50 && BRect2.y == 150)
                        {
                            dir2 = 1;
                            esq2 = 0;
                            baix2 = 0;
                        }
                        if (BRect2.x == 700)
                        {
                            dir2 = 0;
                            baix2 = 1;
                            esq2 = 0;
                        }
                        if(BRect2.y == 190 + 60)
                        {
                            dir2 = 0;
                            baix2 = 0;
                            esq2 = 1;
                        }
                        if(BRect2.y >= 190 + 60 && BRect2.x == 10)
                        {
                            dir2 = 0;
                            baix2 = 1;
                            esq2 = 0;
                        }
                        if(BRect2.y == 290 + 60 && BRect2.x == 10)
                        {
                            dir2 = 1;
                            baix2 = 0;
                            esq2 = 0;
                        }
                        if(BRect2.y == 390 + 60 && BRect2.x == 700)
                        {
                            dir2 = 0;
                            baix2 = 0;
                            esq2 = 1;
                        }
                        if(BRect2.y == 490 + 60 && BRect2.x == 10)
                        {
                            dir2 = 1;
                            baix2 = 0;
                            esq2 = 0;
                        }
                        if(BRect2.y == 550 && BRect2.x == 700)
                        {
                            BRect2.x = 50;
                            BRect2.y = 80 + 60 ;
                        }
                    }
                    if (b1 >= 3) {
                        if(BRect3.x == 50 && BRect3.y == 90 + 60)
                        {
                            dir3 = 1;
                            esq3 = 0;
                            baix3 = 0;
                        }
                        if (BRect3.x == 700)
                        {
                            dir3 = 0;
                            baix3 = 1;
                            esq3 = 0;
                        }
                        if(BRect3.y == 190 + 60 )
                        {
                            dir3 = 0;
                            baix3 = 0;
                            esq3 = 1;
                        }
                        if(BRect3.y >= 190 + 60 && BRect3.x == 10)
                        {
                            dir3 = 0;
                            baix3 = 1;
                            esq3 = 0;
                        }
                        if(BRect3.y == 290 + 60 && BRect3.x == 10)
                        {
                            dir3 = 1;
                            baix3 = 0;
                            esq3 = 0;
                        }
                        if(BRect3.y == 390 + 60 && BRect3.x == 700)
                        {
                            dir3 = 0;
                            baix3 = 0;
                            esq3 = 1;
                        }
                        if(BRect3.y == 490 + 60 && BRect3.x == 10)
                        {
                            dir3 = 1;
                            baix3 = 0;
                            esq3 = 0;
                        }
                        if(BRect3.y == 550 && BRect3.x == 700)
                        {
                            BRect3.x = 50;
                            BRect3.y = 80;
                        }
                    }
                    if (b1 >= 4) {
                        if(BRect4.x == 50 && BRect4.y == 90 + 60)
                        {
                            dir4 = 1;
                            esq4 = 0;
                            baix4 = 0;
                        }
                        if (BRect4.x == 700)
                        {
                            dir4 = 0;
                            baix4 = 1;
                            esq4 = 0;
                        }
                        if(BRect4.y == 190 + 60 )
                        {
                            dir4 = 0;
                            baix4 = 0;
                            esq4 = 1;
                        }
                        if(BRect4.y >= 190 + 60 && BRect4.x == 10)
                        {
                            dir4 = 0;
                            baix4 = 1;
                            esq4 = 0;
                        }
                        if(BRect4.y == 290 + 60 && BRect4.x == 10)
                        {
                            dir4 = 1;
                            baix4 = 0;
                            esq4 = 0;
                        }
                        if(BRect4.y == 390 + 60 && BRect4.x == 700)
                        {
                            dir4 = 0;
                            baix4 = 0;
                            esq4 = 1;
                        }
                        if(BRect4.y == 490 + 60 && BRect4.x == 10)
                        {
                            dir4 = 1;
                            baix4 = 0;
                            esq4 = 0;
                        }
                        if(BRect4.y == 550 && BRect4.x == 700)
                        {
                            BRect4.x = 50;
                            BRect4.y = 80;
                        }
                    }
                    if (b1 >= 5) {
                        if(BRect5.x == 50 && BRect5.y == 90 + 60)
                        {
                            dir5 = 1;
                            esq5 = 0;
                            baix5 = 0;
                        }
                        if (BRect5.x == 700)
                        {
                            dir5 = 0;
                            baix5 = 1;
                            esq5 = 0;
                        }
                        if(BRect5.y == 190 + 60)
                        {
                            dir5 = 0;
                            baix5 = 0;
                            esq5 = 1;
                        }
                        if(BRect5.y >= 190 + 60 && BRect5.x == 10)
                        {
                            dir5 = 0;
                            baix5 = 1;
                            esq5 = 0;
                        }
                        if(BRect5.y == 290 + 60 && BRect5.x == 10)
                        {
                            dir5 = 1;
                            baix5 = 0;
                            esq5 = 0;
                        }
                        if(BRect5.y == 390 + 60 && BRect5.x == 700)
                        {
                            dir5 = 0;
                            baix5 = 0;
                            esq5 = 1;
                        }
                        if(BRect5.y == 490 + 60 && BRect5.x == 10)
                        {
                            dir5 = 1;
                            baix5 = 0;
                            esq5 = 0;
                        }
                        if(BRect5.y == 550 && BRect5.x == 700)
                        {
                            BRect5.x = 50;
                            BRect5.y = 80 + 60;
                        }
                    }

                    //aplica o movimento do barril
                    bspeed = 2;
                    if(esq == 1)
                        BRect.x -= bspeed;
                    if(dir == 1)
                        BRect.x += bspeed;
                    if(baix == 1)
                        BRect.y += bspeed;
                    if(esq2 == 1)
                        BRect2.x -= bspeed;
                    if(dir2 == 1)
                        BRect2.x += bspeed;
                    if(baix2 == 1)
                        BRect2.y += bspeed;
                    if(esq3 == 1)
                        BRect3.x -= bspeed;
                    if(dir3 == 1)
                        BRect3.x += bspeed;
                    if(baix3 == 1)
                        BRect3.y += bspeed;
                    if(esq4 == 1)
                        BRect4.x -= bspeed;
                    if(dir4 == 1)
                        BRect4.x += bspeed;
                    if(baix4 == 1)
                        BRect4.y += bspeed;
                    if(esq5 == 1)
                        BRect5.x -= bspeed;
                    if(dir5 == 1)
                        BRect5.x += bspeed;
                    if(baix5 == 1)
                        BRect5.y += bspeed;

                    //faz perder uma vida
                    if(colisao(SpriteRect,BRect) == 1)
                        menosvida = 1;
                    if(colisao(SpriteRect,BRect2) == 1)
                        menosvida = 1;
                    if(colisao(SpriteRect,BRect3) == 1)
                        menosvida = 1;
                    if(colisao(SpriteRect,BRect4) == 1)
                        menosvida = 1;
                    if(colisao(SpriteRect,BRect5) == 1)
                        menosvida = 1;
                    if(menosvida == 1)
                    {
                        vida -= 1; // diminui uma vida
                        menosvida = 0;
                        pulo = 0; //poe as variaveis do pulo em zero
                        jump = 0;
                        pulobaixo = 0;
                        pulocima = 0;
                        SpriteRect.x = 150 - SpriteRect.w; //poe as variaveis do sprite em zero
                        SpriteRect.y = 575 - SpriteRect.h;
                        tempo = 0; //poe as variaveis da bola de neve em zero
                        BRect.x = 50;
                        BRect.y = 90 + 60;
                        BRect2.x = 50;
                        BRect2.y = 90 + 60;
                        BRect3.x = 50;
                        BRect3.y = 90 + 60;
                        BRect4.x = 50;
                        BRect4.y = 90 + 60;
                        BRect5.x = 50;
                        BRect5.y = 90 + 60;
                        dir = 0;
                        esq = 0;
                        baix = 0;
                        dir2 = 0;
                        esq2 = 0;
                        baix2 = 0;
                        dir3 = 0;
                        esq3 = 0;
                        baix3 = 0;
                        dir4 = 0;
                        esq4 = 0;
                        baix4 = 0;
                        dir5 = 0;
                        esq5 = 0;
                        baix5 = 0;
                        b1 = 0;
                    }
                    if(vida == 0)
                        gameover = 1;

                    //faz o game over
                    if(gameover == 1)
                    {
                        SDL_BlitSurface( fim, NULL, tela, &GORect );
                        vida = 0;
                        if ( e.type == SDL_KEYDOWN )
                             switch( e.key.keysym.sym )
                            {
                                case SDLK_s:
                                vida = 3;
                                menosvida = 0;
                                SpriteRect.x = 150 - SpriteRect.w;
                                SpriteRect.y = 575 - SpriteRect.h;
                                tempo = 0;
                                BRect.x = 50;
                                BRect.y = 90 + 60;
                                BRect2.x = 50;
                                BRect2.y = 90 + 60;
                                BRect3.x = 50;
                                BRect3.y = 90 + 60;
                                BRect4.x = 50;
                                BRect4.y = 90 + 60;
                                BRect5.x = 50;
                                BRect5.y = 90 + 60;
                                dir = 0;
                                esq = 0;
                                baix = 0;
                                dir2 = 0;
                                esq2 = 0;
                                baix2 = 0;
                                dir3 = 0;
                                esq3 = 0;
                                baix3 = 0;
                                dir4 = 0;
                                esq4 = 0;
                                baix4 = 0;
                                dir5 = 0;
                                esq5 = 0;
                                baix5 = 0;
                                b1 = 0;
                                jump = 0;
                                c = 2;
                                gameover = 0;
                                if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2 && Pontuacao > MaiorPont1)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    MaiorPont2 = MaiorPont1;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    MaiorPont1 = Pontuacao;
                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 1;
                                }
                                else if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    MaiorPont2 = Pontuacao;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 2;
                                }
                                else if(Pontuacao > MaiorPont3)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = Pontuacao;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 3;
                                }
                                Pontuacao = 0;
                                if(NovoRecorde > 0)
                                {
                                    c = 6;
                                    goto NewHighScores;
                                }
                                else
                                    goto begingame;//continua o jogo
                                break;

                                case SDLK_n:
                                gameover = 0;
                                vida = 3;
                                menosvida = 0;
                                SpriteRect.x = 150 - SpriteRect.w;
                                SpriteRect.y = 575 - SpriteRect.h;
                                tempo = 0;
                                BRect.x = 50;
                                BRect.y = 90 + 60;
                                BRect2.x = 50;
                                BRect2.y = 90 + 60;
                                BRect3.x = 50;
                                BRect3.y = 90 + 60;
                                BRect4.x = 50;
                                BRect4.y = 90 + 60;
                                BRect5.x = 50;
                                BRect5.y = 90 + 60;
                                dir = 0;
                                esq = 0;
                                baix = 0;
                                dir2 = 0;
                                esq2 = 0;
                                baix2 = 0;
                                dir3 = 0;
                                esq3 = 0;
                                baix3 = 0;
                                dir4 = 0;
                                esq4 = 0;
                                baix4 = 0;
                                dir5 = 0;
                                esq5 = 0;
                                baix5 = 0;
                                b1 = 0;
                                jump = 0;
                                c = 0;
                                if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2 && Pontuacao > MaiorPont1)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    MaiorPont2 = MaiorPont1;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    MaiorPont1 = Pontuacao;
                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 1;
                                }
                                else if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    MaiorPont2 = Pontuacao;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 2;
                                }
                                else if(Pontuacao > MaiorPont3)
                                {
                                    fprintf(HighArq, "%s\n", Nome3);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    fprintf(HighArq, "%s\n", Nome1);

                                    MaiorPont3 = Pontuacao;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                    NovoRecorde = 3;
                                }
                                Pontuacao = 0;
                                if(NovoRecorde > 0)
                                {
                                    c = 6;
                                    goto NewHighScores;
                                }
                                else
                                    goto inicio;
                                break;

                                default:
                                break;
                            }
                        }
                        //faz o fim do jogo
                        if (SpriteRect.y == 58)
                        {
                            gameover = 0;
                            vida = 3;
                            menosvida = 0;
                            SpriteRect.x = 150 - SpriteRect.w;
                            SpriteRect.y = 575 - SpriteRect.h;
                            tempo = 0;
                            BRect.x = 50;
                            BRect.y = 90 + 60;
                            BRect2.x = 50;
                            BRect2.y = 90 + 60;
                            BRect3.x = 50;
                            BRect3.y = 90 + 60;
                            BRect4.x = 50;
                            BRect4.y = 90 + 60;
                            BRect5.x = 50;
                            BRect5.y = 90 + 60;
                            dir = 0;
                            esq = 0;
                            baix = 0;
                            dir2 = 0;
                            esq2 = 0;
                            baix2 = 0;
                            dir3 = 0;
                            esq3 = 0;
                            baix3 = 0;
                            dir4 = 0;
                            esq4 = 0;
                            baix4 = 0;
                            dir5 = 0;
                            esq5 = 0;
                            baix5 = 0;
                            b1 = 0;
                            jump = 0;
                            c = 4;
                            if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2 && Pontuacao > MaiorPont1)
                            {
                                fprintf(HighArq, "%s\n", Nome3);
                                fprintf(HighArq, "%s\n", Nome2);
                                fprintf(HighArq, "%s\n", Nome1);

                                MaiorPont3 = MaiorPont2;
                                sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                fprintf(HighArq, "%s\n", CharMaiorPont3);
                                CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                MaiorPont2 = MaiorPont1;
                                sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                fprintf(HighArq, "%s\n", CharMaiorPont2);
                                CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                MaiorPont1 = Pontuacao;
                                sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                fprintf(HighArq, "%s\n", CharMaiorPont1);
                                CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                NovoRecorde = 1;
                            }
                            else if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2)
                            {
                                fprintf(HighArq, "%s\n", Nome3);
                                fprintf(HighArq, "%s\n", Nome2);
                                fprintf(HighArq, "%s\n", Nome1);

                                MaiorPont3 = MaiorPont2;
                                sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                fprintf(HighArq, "%s\n", CharMaiorPont3);
                                CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                MaiorPont2 = Pontuacao;
                                sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                fprintf(HighArq, "%s\n", CharMaiorPont2);
                                CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                fprintf(HighArq, "%s\n", CharMaiorPont1);
                                CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                NovoRecorde = 2;
                            }
                            else if(Pontuacao > MaiorPont3)
                            {
                                fprintf(HighArq, "%s\n", Nome3);
                                fprintf(HighArq, "%s\n", Nome2);
                                fprintf(HighArq, "%s\n", Nome1);

                                MaiorPont3 = Pontuacao;
                                sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                fprintf(HighArq, "%s\n", CharMaiorPont3);
                                CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 150, 188, 224 } );

                                sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                fprintf(HighArq, "%s\n", CharMaiorPont2);
                                CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 150, 188, 224 } );

                                sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                fprintf(HighArq, "%s\n", CharMaiorPont1);
                                CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 150, 188, 224 } );

                                NovoRecorde = 3;
                            }
                            Pontuacao = 0;
                            if(NovoRecorde > 0)
                            {
                                c = 6;
                                goto NewHighScores;
                            }
                            else
                                goto youwin;
                        }

                        //faz com que o score apareça na tela
                        MensagemScore = TTF_RenderText_Solid( fonte, "Score:", { 150, 188, 224 } );
                        SDL_BlitSurface(MensagemScore , NULL, tela, &MSRect );

                        sprintf(CharPontuacao, "%d" , Pontuacao);
                        MensagemPontScore = TTF_RenderText_Solid( fonte, CharPontuacao, { 150, 188, 224 } );
                        SDL_BlitSurface(MensagemPontScore , NULL, tela, &MPSRect );

                        //faz a pontuação no pulo
                        //Bola 1
                        if(bd == 1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect.y >= 550 && BRect.y <= 600)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect.y >= 450 && BRect.y <= 500)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect.y >= 350 && BRect.y <= 400)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect.y >= 250 && BRect.y <= 300)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect.y >= 150 && BRect.y <= 200)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect.x + BRect.w)
                                Aux_P+= 10;

                        if(be == -1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect.y >= 550 && BRect.y <= 600)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect.y >= 450 && BRect.y <= 500)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect.y >= 350 && BRect.y <= 400)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect.y >= 250 && BRect.y <= 300)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect.x + BRect.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect.y >= 150 && BRect.y <= 200)
                            if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect.x + BRect.w)
                                Aux_P+= 10;

                        //Bola 2
                        if(bd == 1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect2.y >= 550 && BRect2.y <= 600)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect2.y >= 450 && BRect2.y <= 500)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect2.y >= 350 && BRect2.y <= 400)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect2.y >= 250 && BRect2.y <= 300)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect2.y >= 150 && BRect2.y <= 200)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect2.x + BRect2.w)
                                Aux_P+= 10;

                        if(be == -1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect2.y >= 550 && BRect2.y <= 600)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect2.y >= 450 && BRect2.y <= 500)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect2.y >= 350 && BRect2.y <= 400)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect2.y >= 250 && BRect2.y <= 300)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect2.x + BRect2.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect2.y >= 150 && BRect2.y <= 200)
                            if(colisao(SpriteRect, BRect2) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect2.x + BRect2.w)
                                Aux_P+= 10;

                        //Bola 3
                        if(bd == 1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect3.y >= 550 && BRect3.y <= 600)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect3.y >= 450 && BRect3.y <= 500)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect3.y >= 350 && BRect3.y <= 400)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect3.y >= 250 && BRect3.y <= 300)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect3.y >= 150 && BRect3.y <= 200)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect3.x + BRect3.w)
                                Aux_P+= 10;

                        if(be == -1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect3.y >= 550 && BRect3.y <= 600)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect3.y >= 450 && BRect3.y <= 500)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect3.y >= 350 && BRect3.y <= 400)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect3.y >= 250 && BRect3.y <= 300)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect3.x + BRect3.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect3.y >= 150 && BRect3.y <= 200)
                            if(colisao(SpriteRect, BRect3) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect3.x + BRect3.w)
                                Aux_P+= 10;

                        //Bola 4
                        if(bd == 1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect4.y >= 550 && BRect4.y <= 600)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect4.y >= 450 && BRect4.y <= 500)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect4.y >= 350 && BRect4.y <= 400)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect4.y >= 250 && BRect4.y <= 300)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect4.y >= 150 && BRect4.y <= 200)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect4.x + BRect4.w)
                                Aux_P+= 10;

                        if(be == -1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect4.y >= 550 && BRect4.y <= 600)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect4.y >= 450 && BRect4.y <= 500)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect4.y >= 350 && BRect4.y <= 400)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect4.y >= 250 && BRect4.y <= 300)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect4.x + BRect4.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect4.y >= 150 && BRect4.y <= 200)
                            if(colisao(SpriteRect, BRect4) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect4.x + BRect4.w)
                                Aux_P+= 10;

                        //Bola 5
                        if(bd == 1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect5.y >= 550 && BRect5.y <= 600)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect5.y >= 450 && BRect5.y <= 500)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect5.y >= 350 && BRect5.y <= 400)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect5.y >= 250 && BRect5.y <= 300)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(bd == 1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect5.y >= 150 && BRect5.y <= 200)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w > BRect5.x + BRect5.w)
                                Aux_P+= 10;

                        if(be == -1 && SpriteRect.y >= 550 && SpriteRect.y <= 600 && BRect5.y >= 550 && BRect5.y <= 600)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 450 && SpriteRect.y <= 500 && BRect5.y >= 450 && BRect5.y <= 500)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 350 && SpriteRect.y <= 400 && BRect5.y >= 350 && BRect5.y <= 400)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 250 && SpriteRect.y <= 300 && BRect5.y >= 250 && BRect5.y <= 300)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect5.x + BRect5.w)
                                Aux_P+= 10;
                        if(be == -1 && SpriteRect.y >= 150 && SpriteRect.y <= 200 && BRect5.y >= 150 && BRect5.y <= 200)
                            if(colisao(SpriteRect, BRect5) == 0 && jump != 0 && SpriteRect.x + SpriteRect.w < BRect5.x + BRect5.w)
                                Aux_P+= 10;

                        if(Aux_P == 50)
                        {
                            Pontuacao += 50;
                            Aux_P = 0;
                        }
                        if(jump == 0)
                            Aux_P = 0;

                        //faz com que as vidas apareçam na tela
                        MensagemVida = TTF_RenderText_Solid( fonte, "x ", { 150, 188, 224 } );
                        SDL_BlitSurface(MensagemVida , NULL, tela, &MVRect );

                        sprintf(CharVida, "%d" , vida);
                        MensagemValorVida = TTF_RenderText_Solid( fonte, CharVida , { 150, 188, 224 } );
                        SDL_BlitSurface(MensagemValorVida , NULL, tela, &MVVRect );

                        //faz com que a maior pontuação apareça na tela
                        MgmHighScore = TTF_RenderText_Solid( fonte, "High Score:", { 150, 188, 224 } );
                        SDL_BlitSurface(MgmHighScore , NULL, tela, &MHSRect );

                        sprintf(CharHighPt, "%d" , MaiorPont1);
                        MgmHighPtScore = TTF_RenderText_Solid( fonte, CharHighPt, { 150, 188, 224 } );
                        SDL_BlitSurface(MgmHighPtScore , NULL, tela, &MHPSRect );

                    }

                    instructions:
                    if (c == 3)
                    {
                        SDL_BlitSurface (instrucao, NULL, tela, &ISRect );
                        SDL_BlitSurface (voltar, NULL, tela, &VRect );
                        //If the mouse moved
                        if( e.type == SDL_MOUSEMOTION )
                        {
                            //Get the mouse offsets
                            x = e.motion.x;
                            y = e.motion.y;

                            //If the mouse is over the button
                            if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                            {
                                SDL_BlitSurface ( voltare, NULL, tela, &VeRect );
                            }
                        }
                        //If a mouse button was pressed
                        if( e.type == SDL_MOUSEBUTTONDOWN )
                        {
                            //If the left mouse button was pressed
                            if( e.button.button == SDL_BUTTON_LEFT )
                            {
                                //Get the mouse offsets
                                x = e.button.x;
                                y = e.button.y;
                                //If the mouse is over the button
                                if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                                {
                                    c = 0;
                                    goto inicio;
                                }
                            }
                        }
                    }
                    youwin:
                    if( c == 4)
                    {
                        SDL_BlitSurface (zerar, NULL, tela, &ZRect );
                        winner++;
                        if(winner == 300)
                        {
                            c = 0;
                            goto inicio;
                        }
                    }
                    pontuacoesm:
                    if (c == 5)
                    {
                        SDL_BlitSurface (recordes, NULL, tela, &RECRect );
                        SDL_BlitSurface (voltar, NULL, tela, &VRect );

                        N1 = TTF_RenderText_Solid( fonte, Nome1, { 150, 188, 224 } );
                        N2 = TTF_RenderText_Solid( fonte, Nome2, { 150, 188, 224 } );
                        N3 = TTF_RenderText_Solid( fonte, Nome3, { 150, 188, 224 } );

                        SDL_BlitSurface(N1 , NULL, tela, &N1Rect );
                        SDL_BlitSurface(N2 , NULL, tela, &N2Rect );
                        SDL_BlitSurface(N3 , NULL, tela, &N3Rect );
                        SDL_BlitSurface(CP1 , NULL, tela, &CP1Rect );
                        SDL_BlitSurface(CP2 , NULL, tela, &CP2Rect );
                        SDL_BlitSurface(CP3 , NULL, tela, &CP3Rect );
                        //If the mouse moved
                        if( e.type == SDL_MOUSEMOTION )
                        {
                            //Get the mouse offsets
                            x = e.motion.x;
                            y = e.motion.y;

                            //If the mouse is over the button
                            if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                            {
                                SDL_BlitSurface ( voltare, NULL, tela, &VeRect );
                            }
                        }
                        //If a mouse button was pressed
                        if( e.type == SDL_MOUSEBUTTONDOWN )
                        {
                            //If the left mouse button was pressed
                            if( e.button.button == SDL_BUTTON_LEFT )
                            {
                                //Get the mouse offsets
                                x = e.button.x;
                                y = e.button.y;
                                //If the mouse is over the button
                                if( ( x > VRect.x ) && ( x < VRect.x + VRect.w ) && ( y > VRect.y ) && ( y < VRect.y + VRect.h ) )
                                {
                                    c = 0;
                                    goto inicio;
                                }
                            }
                        }
                    }
                    //coloca o nome do jogador que superou o recorde antigo
                    NewHighScores:
                    if(c == 6)
                    {
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
                            indice = 0;
                            if(NovoRecorde == 1)
                            {
                                fprintf(HighArq, "%s\n", Nome3);
                                fprintf(HighArq, "%s\n", Nome2);
                                fprintf(HighArq, "%s\n", Nome);
                            }
                            if(NovoRecorde == 2)
                            {
                                fprintf(HighArq, "%s\n", Nome3);
                                fprintf(HighArq, "%s\n", Nome);
                                fprintf(HighArq, "%s\n", Nome1);
                            }
                            if(NovoRecorde == 3)
                            {
                                fprintf(HighArq, "%s\n", Nome);
                                fprintf(HighArq, "%s\n", Nome2);
                                fprintf(HighArq, "%s\n", Nome1);
                            }
                            c = 0;
                            goto inicio;
                        }
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
        }
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

    return 0;
}

