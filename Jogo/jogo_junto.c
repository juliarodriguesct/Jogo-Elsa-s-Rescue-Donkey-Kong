#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>
#include <string.h>

int colisao(SDL_Rect *A, SDL_Rect *B)
{
    //lados dos retangulos
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //calcula os lados do rect A
    leftA = A->x;
    rightA = A->x + A->w;
    topA = A->y;
    bottomA = A->y + A->h;

    //calcula os lados do rect B
    leftB = B->x;
    rightB = B->x + B->w;
    topB = B->y;
    bottomB = B->y + B->h;

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
//calula a potuacao do pulo
int calc_pont(int bd, int be, SDL_Rect *SpriteRect, SDL_Rect *BRect, int jump , int Aux_P)
{
    if(bd == 1 && SpriteRect->y >= 550 && SpriteRect->y <= 600 && BRect->y >= 550 && BRect->y <= 600)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w > BRect->x + BRect->w)
            Aux_P+= 10;
    if(bd == 1 && SpriteRect->y >= 450 && SpriteRect->y <= 500 && BRect->y >= 450 && BRect->y <= 500)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w > BRect->x + BRect->w)
            Aux_P+= 10;
    if(bd == 1 && SpriteRect->y >= 350 && SpriteRect->y <= 400 && BRect->y >= 350 && BRect->y <= 400)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w > BRect->x + BRect->w)
            Aux_P+= 10;
    if(bd == 1 && SpriteRect->y >= 250 && SpriteRect->y <= 300 && BRect->y >= 250 && BRect->y <= 300)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w > BRect->x + BRect->w)
            Aux_P+= 10;
    if(bd == 1 && SpriteRect->y >= 150 && SpriteRect->y <= 200 && BRect->y >= 150 && BRect->y <= 200)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w > BRect->x + BRect->w)
            Aux_P+= 10;

    if(be == -1 && SpriteRect->y >= 550 && SpriteRect->y <= 600 && BRect->y >= 550 && BRect->y <= 600)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w < BRect->x + BRect->w)
            Aux_P+= 10;
    if(be == -1 && SpriteRect->y >= 450 && SpriteRect->y <= 500 && BRect->y >= 450 && BRect->y <= 500)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w < BRect->x + BRect->w)
            Aux_P+= 10;
    if(be == -1 && SpriteRect->y >= 350 && SpriteRect->y <= 400 && BRect->y >= 350 && BRect->y <= 400)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w < BRect->x + BRect->w)
            Aux_P+= 10;
    if(be == -1 && SpriteRect->y >= 250 && SpriteRect->y <= 300 && BRect->y >= 250 && BRect->y <= 300)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w < BRect->x + BRect->w)
            Aux_P+= 10;
    if(be == -1 && SpriteRect->y >= 150 && SpriteRect->y <= 200 && BRect->y >= 150 && BRect->y <= 200)
        if(colisao(SpriteRect, BRect) == 0 && jump != 0 && SpriteRect->x + SpriteRect->w < BRect->x + BRect->w)
            Aux_P+= 10;

    return Aux_P;
}
//faz a primeira rota do movimento do barril
int mov_barril(SDL_Rect BarrilRect)
{
    int mb; //direita = 1, esquerda = 2, baixo = 3, voltar = 4
    if(BarrilRect.x >= 50 && BarrilRect.y == 150)
        mb = 1;
    if (BarrilRect.x == 700)
        mb = 3;
    if(BarrilRect.y == 250)
        mb = 2;
    if(BarrilRect.y >= 250 && BarrilRect.x == 10)
        mb = 3;
    if(BarrilRect.y == 350 && BarrilRect.x >= 10)
        mb = 1;
    if(BarrilRect.y == 350 && BarrilRect.x == 700)
        mb = 3;
    if(BarrilRect.y == 450 && BarrilRect.x <= 700)
        mb = 2;
    if(BarrilRect.y == 450 && BarrilRect.x == 10)
        mb = 3;
    if(BarrilRect.y == 550 && BarrilRect.x >= 10)
        mb = 1;
    if(BarrilRect.y == 550 && BarrilRect.x == 650)
        mb = 4;

    return mb;
}
//faz a segunda rota do movimento do barril
int mov_barril2(SDL_Rect BarrilRect)
{
    int mb; //direita = 1, esquerda = 2, baixo = 3, voltar = 4
    if(BarrilRect.x >= 50 && BarrilRect.y == 150)
        mb = 1;
    if (BarrilRect.x == 536)
        mb = 3;
    if(BarrilRect.y == 250)
        mb = 2;
    if(BarrilRect.y >= 250 && BarrilRect.x == 350)
        mb = 3;
    if(BarrilRect.y == 350 && BarrilRect.x >= 10)
        mb = 1;
    if(BarrilRect.y >= 350 && BarrilRect.x == 500)
        mb = 3;
    if(BarrilRect.y == 450 && BarrilRect.x <= 700)
        mb = 1;
    if(BarrilRect.y >= 450 && BarrilRect.x == 600)
        mb = 3;
    if(BarrilRect.y == 550 && BarrilRect.x >= 10)
        mb = 1;
    if(BarrilRect.y == 550 && BarrilRect.x == 650)
        mb = 4;

    return mb;
}
//faz a terceira rota do movimento do barril
int mov_barril3(SDL_Rect BarrilRect)
{
    int mb; //direita = 1, esquerda = 2, baixo = 3, voltar = 4
    if(BarrilRect.x >= 50 && BarrilRect.y == 150)
        mb = 1;
    if (BarrilRect.x == 180)
        mb = 3;
    if(BarrilRect.y == 250)
        mb = 1;
    if(BarrilRect.y >= 250 && BarrilRect.x == 350)
        mb = 3;
    if(BarrilRect.y == 350 && BarrilRect.x >= 10)
        mb = 2;
    if(BarrilRect.y >= 350 && BarrilRect.x == 250)
        mb = 3;
    if(BarrilRect.y == 450 && BarrilRect.x <= 700)
        mb = 1;
    if(BarrilRect.y >= 450 && BarrilRect.x == 600)
        mb = 3;
    if(BarrilRect.y == 550 && BarrilRect.x >= 10)
        mb = 1;
    if(BarrilRect.y == 550 && BarrilRect.x == 650)
        mb = 4;

    return mb;
}
//aplica o movimento do barril
void aplica_mov_barril(SDL_Rect *BarrilRect, int vel_barril, int mov_barril)
{
    if(mov_barril == 1)
        BarrilRect->x += vel_barril;
    if(mov_barril == 2)
        BarrilRect->x -= vel_barril;
    if(mov_barril == 3)
        BarrilRect->y += vel_barril;
    if(mov_barril == 4)
    {
        BarrilRect->x = 150;
        BarrilRect->y = 150;
    }
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
int c = 8;

//cria as variaveis do movimento do barril
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0, tempo = 0;
int mb1 = 0, mb2 = 0, mb3 = 0, mb4 = 0, mb5 =0, mb6 = 0, mb7 = 0;
int bspeed = 0, rotas1 = 0, rotas2 = 0;

//cria as variaveis do pulo
int pulo = 0, pulocima, pulobaixo, jump  = 0, notescada = 1;

//cria a variavel das vidas
int vida = 3, menosvida = 0;
char CharVida[2];

//cria as variaveis do fim do jogo
int gameover = 0;

//cria as variaveis do zeramento
int winner = 0;

//olaf
int p1=1, p2=1, p3=1, p4=1, p5=1;

//cria as variaveis do score
int Pontuacao = 0, Aux_P = 0, Aux_P1 = 0, indice = 0, aux_indice = -1, aux_indice2 = -1, aux_indice3 = -1, byebye = 0;
char CharPontuacao[100], CharHighPt[100];

//faz as variaveis do poder
int pd_disp = 1, tempo_pd1 = 0, tempo_pd2 = 0, invencibilidade = 0;
int aux_poder = 0, aux_poder2 = 0, aux_poder3 = 0, aux_poder4 = 0, aux_poder5 = 0, aux_poder6 = 0, aux_poder7 = 0;

//cria as variaveis da musica
int e_botao = 0, e_run1 = 0, e_run2 = 0, e_pulo = 0, e_venceu = 0, e_perdeu = 0, e_esc1 = 0, e_esc2 = 0;
int e_nrec = 0, e_hammer = 0, e_poder1 = 0, e_poder2 = 0, e_poder3 = 0, e_poder4 = 0, e_poder5 = 0, e_poder6 = 0, e_poder7 = 0;
int e_atingiu = 0, e_jumpoint = 0;

//função principal
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
    SDL_Surface *vilao = NULL;
    SDL_Surface *elsa = NULL;
    SDL_Surface *bola_de_neve = NULL;
    SDL_Surface *neve = NULL;
    SDL_Surface *olafp1 = NULL;
    SDL_Surface *olafp2 = NULL;
    SDL_Surface *olafp3 = NULL;
    SDL_Surface *olafp4 = NULL;
    SDL_Surface *olafp5 = NULL;
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
    SDL_Surface *life = NULL;
    SDL_Surface *martelo = NULL;

    //cria os ponteiros da musica
    Mix_Music *musica = NULL;
    Mix_Chunk *m_botao = NULL;
    Mix_Chunk *m_run = NULL;
    Mix_Chunk *m_escada = NULL;
    Mix_Chunk *m_hammer = NULL;
    Mix_Music *m_novorec = NULL;
    Mix_Music *m_perdeu = NULL;
    Mix_Chunk *m_pulo = NULL;
    Mix_Music *m_venceu = NULL;
    Mix_Chunk *m_poder = NULL;
    Mix_Music *m_fundo = NULL;
    Mix_Chunk *m_atingiu = NULL;
    Mix_Music *m_ptheme = NULL;
    Mix_Chunk *m_jpoint = NULL;

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
            telainicial = IMG_Load("Menu.png");
            fundo = SDL_LoadBMP("fundo.bmp");
            nj = IMG_Load("NovoJogo1.png");
            nje = IMG_Load("NovoJogo2.png");
            sair = IMG_Load("Sair1.png");
            saire = IMG_Load("Sair2.png");
            creditos = IMG_Load("Creditos1.png");
            creditose = IMG_Load("Creditos2.png");
            instrucoes =  IMG_Load("ComoJogar1.png");
            instrucoese = IMG_Load("ComoJogar2.png");
            fcreditos = IMG_Load("Creditos.png");
            voltar = IMG_Load("Voltar1.png");
            voltare = IMG_Load("Voltar2.png");
            instrucao = IMG_Load("ComoJogar.png");
            sprite = IMG_Load("tijolo.bmp" );
            vilao = IMG_Load( "marshmallow.png" );
            elsa = IMG_Load("elsa.png");
            bola_de_neve = IMG_Load("boladeneve.png");
            olafp1 = IMG_Load ("olafp3.png");
            olafp2 = IMG_Load ("olafp1.png");
            olafp3 = IMG_Load ("olafp2.png");
            olafp4 = IMG_Load ("olafp4.png");
            olafp5 = IMG_Load ("olafp5.png");
            neve = IMG_Load("EfeitoDeGelo.png");
            fim = IMG_Load("GameOver.png");
            recordes = IMG_Load("Recordes.png");
            record = IMG_Load("Recordes1.png");
            recorde = IMG_Load("Recordes2.png");
            TelaNN = IMG_Load("NovoRecorde.png");
            life = IMG_Load("vida.png");
            martelo = IMG_Load("tocha.png");
            zerar = IMG_Load("VoceConseguiu.png");



            //Le a musica
            musica = Mix_LoadMUS("letitgo.wav");
            m_fundo = Mix_LoadMUS("letitgo_cut.wav");
            m_botao = Mix_LoadWAV("Botao.wav");
            m_run = Mix_LoadWAV("Correndo.wav");
            m_escada = Mix_LoadWAV("Escada.wav");
            m_hammer = Mix_LoadWAV("Martelo.wav");
            m_novorec = Mix_LoadMUS("NovoRecorde.wav");
            m_perdeu = Mix_LoadMUS("Perdeu.wav");
            m_pulo = Mix_LoadWAV("Pulo.wav");
            m_venceu = Mix_LoadMUS("Venceu.wav");
            m_poder = Mix_LoadWAV("QuebrandoBola.wav");
            m_atingiu = Mix_LoadWAV("BolaAtingiu.wav");
            m_ptheme = Mix_LoadMUS("P_Theme.wav");
            m_jpoint = Mix_LoadWAV("JumpEf.wav");

            //Le a fonte
            fonte = TTF_OpenFont("fonte.ttf", 26);

            //diminui o volume do som
            Mix_Volume(0, 20); //botoes
            Mix_Volume(1, 80); //pulo
            Mix_Volume(2, 50); //corrida
            Mix_Volume(3, 100); //escada

            //cria os rects do martelo
            SDL_Rect HammerRect;
            HammerRect.w = 25;
            HammerRect.h = martelo->h;
            HammerRect.x = 550;
            HammerRect.y = 525;

            SDL_Rect HammerRect2;
            HammerRect2.w = 25;
            HammerRect2.h = martelo->h;
            HammerRect2.x = 300;
            HammerRect2.y = 227;

            SDL_Rect tocha;
            tocha.w=25;
            tocha.h=57;
            tocha.x=0;
            tocha.y=0;

            //cria os rects da vida
            SDL_Rect LRect;
            LRect.w = life->w;
            LRect.h = life->h;
            LRect.x = 0;
            LRect.y = 0;

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
            NJRect.x = 150;
            NJRect.y = 110;

            //cria os rects do efeito do botao do novo jogo
            SDL_Rect NJeRect;
            NJeRect.w = nje->w;
            NJeRect.h = nje->h;
            NJeRect.x = 150;
            NJeRect.y = 110;

            //cria os rects do botao das instruções
            SDL_Rect IRect;
            IRect.w = instrucoes->w;
            IRect.h = instrucoes->h;
            IRect.x = 150;
            IRect.y = 175;

            //cria os rects do efeito do botao das instruções
            SDL_Rect IeRect;
            IeRect.w = instrucoese->w;
            IeRect.h = instrucoese->h;
            IeRect.x = 150;
            IeRect.y = 175;

            //cria os rects do botao dos recordes
            SDL_Rect RERect;
            RERect.w = record->w;
            RERect.h = record->h;
            RERect.x = 230;
            RERect.y = 280;

            //cria os rects do efeito do botao dos recordes
            SDL_Rect REeRect;
            REeRect.w = recorde->w;
            REeRect.h = recorde->h;
            REeRect.x = 230;
            REeRect.y = 280;

            //cria os rects do botao dos creditos
            SDL_Rect CRect;
            CRect.w = creditos->w;
            CRect.h = creditos->h;
            CRect.x = 240;
            CRect.y = 350;

            //cria os rects do efeito do botao dos creditos
            SDL_Rect CeRect;
            CeRect.w = creditose->w;
            CeRect.h = creditose->h;
            CeRect.x = 240;
            CeRect.y = 350;

            //cria os rects do botao da saida
            SDL_Rect SRect;
            SRect.w = sair->w;
            SRect.h = sair->h;
            SRect.x = 150;
            SRect.y = 500;

            //cria os rects do efeito do botao da saida
            SDL_Rect SeRect;
            SeRect.w = saire->w;
            SeRect.h = saire->h;
            SeRect.x = 150;
            SeRect.y = 500;

            //cria os rects do botao de voltar
            SDL_Rect VRect;
            VRect.w = voltar->w;
            VRect.h = voltar->h;
            VRect.x = 550;
            VRect.y = 510;

            //cria os rects do efeito do botao de voltar
            SDL_Rect VeRect;
            VeRect.w = voltare->w;
            VeRect.h = voltare->h;
            VeRect.x = 550;
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

           //cria os rects do sprite
            SDL_Rect SpriteRect;
            SpriteRect.w = 58;
            SpriteRect.h = 70;
            SpriteRect.x = 80;
            SpriteRect.y = 520;

            // rects da anna
            SDL_Rect annaRect;
            annaRect.x = 754;
            annaRect.y = 0;
            annaRect.w = 58;
            annaRect.h = 70;

            // vilão
            SDL_Rect vilaoRect;
            vilaoRect.x = 40;
            vilaoRect.y = 90;
            vilaoRect.w = 145;
            vilaoRect.h = 95;

            // marshmallow
            SDL_Rect marshmallow;
            marshmallow.x = 0;
            marshmallow.y = 0;
            marshmallow.w = 145;
            marshmallow.h = 95;

            // princesa
            SDL_Rect princesaRect;
            princesaRect.x=190;
            princesaRect.y=30;
            princesaRect.w=30;
            princesaRect.h=55;

            // elsa
            SDL_Rect elsaRect;
            elsaRect.x=0;
            elsaRect.y=0;
            elsaRect.w=30;
            elsaRect.h=55;

            //cria os rects do fundo
            SDL_Rect FRect;
            FRect.w = fundo->w;
            FRect.h = fundo->h;
            FRect.x = 0;
            FRect.y = 0;

           // imagem da bola de neve
            SDL_Rect bnimg;
            bnimg.w =32;
            bnimg.h =32;
            bnimg.x = 0;
            bnimg.y =0;

            //cria os rects das bolas de neve
            SDL_Rect BRect;
            BRect.w = bola_de_neve->w;
            BRect.h = bola_de_neve->h;
            BRect.x = 150;
            BRect.y = 150;

            SDL_Rect BRect2;
            BRect2.w = bola_de_neve->w;
            BRect2.h = bola_de_neve->h;
            BRect2.x = 150;
            BRect2.y = 150;

            SDL_Rect BRect3;
            BRect3.w = bola_de_neve->w;
            BRect3.h = bola_de_neve->h;
            BRect3.x = 150;
            BRect3.y = 150;

            SDL_Rect BRect4;
            BRect4.w = bola_de_neve->w;
            BRect4.h = bola_de_neve->h;
            BRect4.x = 150;
            BRect4.y = 150;

            SDL_Rect BRect5;
            BRect5.w = bola_de_neve->w;
            BRect5.h = bola_de_neve->h;
            BRect5.x = 150;
            BRect5.y = 150;

            SDL_Rect BRect6;
            BRect6.w = bola_de_neve->w;
            BRect6.h = bola_de_neve->h;
            BRect6.x = 150;
            BRect6.y = 150;

            SDL_Rect BRect7;
            BRect7.w = bola_de_neve->w;
            BRect7.h = bola_de_neve->h;
            BRect7.x = 150;
            BRect7.y = 150;

            //cria os rects da neve
            SDL_Rect NRect;
            NRect.w = neve->w;
            NRect.h = neve->h;
            NRect.x = 630;
            NRect.y = 510;

            // rects do olaf
            SDL_Rect olafimg;
            olafimg.h=70;
            olafimg.w=40;
            olafimg.x=0;
            olafimg.y=0;

            SDL_Rect olaf1Rect;
            olaf1Rect.h=70;
            olaf1Rect.w=40;
            olaf1Rect.x=250;
            olaf1Rect.y=517;

            SDL_Rect olaf2Rect;
            olaf2Rect.h=70;
            olaf2Rect.w=40;
            olaf2Rect.x=350;
            olaf2Rect.y=417;

            SDL_Rect olaf3Rect;
            olaf3Rect.h=70;
            olaf3Rect.w=40;
            olaf3Rect.x=700;
            olaf3Rect.y=417;

            SDL_Rect olaf4Rect;
            olaf4Rect.h=70;
            olaf4Rect.w=40;
            olaf4Rect.x=270;
            olaf4Rect.y=314;

            SDL_Rect olaf5Rect;
            olaf5Rect.h=70;
            olaf5Rect.w=40;
            olaf5Rect.x=700;
            olaf5Rect.y=217;

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

            //cria os rects dos recordes
            SDL_Rect CP1Rect;
            CP1Rect.x = 200;
            CP1Rect.y = 100;

            SDL_Rect CP2Rect;
            CP2Rect.x = 200;
            CP2Rect.y = 150;

            SDL_Rect CP3Rect;
            CP3Rect.x = 200;
            CP3Rect.y = 200;

            //cria os rects dos nomes dos recordistas
            SDL_Rect N1Rect;
            N1Rect.x = 100;
            N1Rect.y = 100;

            SDL_Rect N2Rect;
            N2Rect.x = 100;
            N2Rect.y = 150;

            SDL_Rect N3Rect;
            N3Rect.x = 100;
            N3Rect.y = 200;

            //cria os rects da tela de novo recorde
            SDL_Rect TNNRect;
            TNNRect.w = TelaNN->w;
            TNNRect.h = TelaNN->h;
            TNNRect.x = 0;
            TNNRect.y = 0;

            //cria os rects do novo nome
            SDL_Rect NNRect;
            NNRect.x = 550;
            NNRect.y = 220;

                        //cria os rects da mensagem do score
            SDL_Rect MSRect;
            MSRect.x = 110;
            MSRect.y = 0;

            SDL_Rect MSRect2;
            MSRect2.x = 210;
            MSRect2.y = 300;

            //cria os rects da mensagem do score (nº)
            SDL_Rect MPSRect;
            MPSRect.x = 190;
            MPSRect.y = 0;

            SDL_Rect MPSRect2;
            MPSRect2.x = 365;
            MPSRect2.y = 300;

            //cria os rects da mensagem do score mais alto
            SDL_Rect MHSRect;
            MHSRect.x = 350;
            MHSRect.y = 0;

            SDL_Rect MHSRect2;
            MHSRect2.x = 450;
            MHSRect2.y = 300;

            //cria os rects da mensagem do score mais alto (nº)
            SDL_Rect MHPSRect;
            MHPSRect.x = 490;
            MHPSRect.y = 0;

            SDL_Rect MHPSRect2;
            MHPSRect2.x = 590;
            MHPSRect2.y = 300;

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
            SDL_SetColorKey(bola_de_neve, SDL_SRCCOLORKEY, SDL_MapRGB(bola_de_neve->format, 119, 124, 145 )) ; //bola de neve
            SDL_SetColorKey(neve, SDL_SRCCOLORKEY, SDL_MapRGB(neve->format, 119, 124, 145 )) ; //neve

            //abre o arquivo e le os recordes
            HighArq = fopen("HighScores.txt", "r");

            fscanf(HighArq, "%s", &Nome3);
            fscanf(HighArq, "%s", &Nome2);
            fscanf(HighArq, "%s", &Nome1);

            N1 = TTF_RenderText_Solid( fonte, Nome1, { 0, 0, 0 } );
            N2 = TTF_RenderText_Solid( fonte, Nome2, { 0, 0, 0 } );
            N3 = TTF_RenderText_Solid( fonte, Nome3, { 0, 0, 0 } );

            fscanf(HighArq, "%d", &MaiorPont3);
            sprintf(CharMaiorPont3, "%d", MaiorPont3);
            CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 0, 0, 0 } );

            fscanf(HighArq, "%d", &MaiorPont2);
            sprintf(CharMaiorPont2, "%d", MaiorPont2);
            CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 0, 0, 0 } );

            fscanf(HighArq, "%d", &MaiorPont1);
            sprintf(CharMaiorPont1, "%d", MaiorPont1);
            CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 0, 0, 0 } );

            fclose(HighArq);

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
                                e_botao++;
                            }
                            else if( ( x > CRect.x ) && ( x < CRect.x + CRect.w ) && ( y > CRect.y ) && ( y < CRect.y + CRect.h ) )
                            {
                                SDL_BlitSurface ( creditose, NULL, tela, &CeRect );
                                e_botao++;
                            }
                            else if( ( x > SRect.x ) && ( x < SRect.x + SRect.w ) && ( y > SRect.y ) && ( y < SRect.y + SRect.h ) )
                            {
                                SDL_BlitSurface ( saire, NULL, tela, &SeRect );
                                e_botao++;
                            }
                            else if( ( x > IRect.x ) && ( x < IRect.x + IRect.w ) && ( y > IRect.y ) && ( y < IRect.y + IRect.h ) )
                            {
                                SDL_BlitSurface ( instrucoese, NULL, tela, &IeRect );
                                e_botao++;
                            }
                            else if( ( x > RERect.x ) && ( x < RERect.x + RERect.w ) && ( y > RERect.y ) && ( y < RERect.y + RERect.h ) )
                            {
                                SDL_BlitSurface ( recorde, NULL, tela, &REeRect );
                                e_botao++;
                            }
                            else
                                e_botao = 0;

                            //Toca a musica do botao
                            if(e_botao == 1)
                                 Mix_PlayChannel( 0, m_botao, 0 );


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
                                    c = 7;
                                    goto begingame;
                                }
                                else if( ( x > CRect.x ) && ( x < CRect.x + CRect.w ) && ( y > CRect.y ) && ( y < CRect.y + CRect.h ) )
                                {
                                    c = 1; //permite entrar nos creditos
                                    goto credits;
                                }
                                else if( ( x > SRect.x ) && ( x < SRect.x + SRect.w ) && ( y > SRect.y ) && ( y < SRect.y + SRect.h ) )
                                {
                                    quit = 0;
                                }
                                else if( ( x > IRect.x ) && ( x < IRect.x + IRect.w ) && ( y > IRect.y ) && ( y < IRect.y + IRect.h ) )
                                {
                                    c = 3;
                                    goto instructions;
                                }
                                else if( ( x > RERect.x ) && ( x < RERect.x + RERect.w ) && ( y > RERect.y ) && ( y < RERect.y + RERect.h ) )
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
                                e_botao++;
                            }
                            else
                                e_botao = 0;
                            //Toca a musica do botao
                            if(e_botao == 1)
                                 Mix_PlayChannel( 0, m_botao, 0 );
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
                                if(SpriteRect.y==520 || SpriteRect.y==420 || SpriteRect.y==317 || SpriteRect.y==220 || SpriteRect.y==117 || SpriteRect.y==20)
                                    bd = 1;
                                else
                                    bd = 0;
                                break;

                                //anda para a esquerda
                                case SDLK_LEFT:
                                //corrije o problema de andar na escada
                                if(SpriteRect.y==520 || SpriteRect.y==420 || SpriteRect.y==317 || SpriteRect.y==220 || SpriteRect.y==117 || SpriteRect.y==20)
                                    be = -1;
                                else
                                    be = 0;
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
                                e_run1 = 0;
                                Mix_Pause(2);
                                break;

                                case SDLK_LEFT:
                                be = 0; //para de andar para a esquerda
                                e_run2 = 0;
                                Mix_Pause(2);
                                break;

                                default:
                                break;
                            }
                        }


                        //movimento do sprite pros lados
                        if(bd == 1)
                        {
                            if(invencibilidade==1)
                                annaRect.y=280;
                            else
                                annaRect.y=0;
                            if ( annaRect.x == 696 || annaRect.x == 754)
                                annaRect.x = 0;
                            else
                                annaRect.x+=58;

                            SpriteRect.x+=5;
                        }
                        if(be == -1)
                        {
                            if(invencibilidade==1)
                                annaRect.y=350;
                            else
                                annaRect.y=70;
                            if ( annaRect.x == 0 || annaRect.x == 754)
                                annaRect.x = 58;
                            else
                                annaRect.x+=58;
                            SpriteRect.x-=5;
                        }

                        if(bd == 1)
                            e_run1++;
                        if(be == -1)
                            e_run2++;

                        //Toca a musica da corrida
                        if(e_run1 == 1 && jump == 0)
                            Mix_PlayChannel(2, m_run, 0 );
                        if(e_run2 == 1 && jump == 0)
                            Mix_PlayChannel(2, m_run, 0 );
                        if(jump == 1)
                        {
                            Mix_Pause(2);
                            e_run1 = 0;
                            e_run2 = 0;
                        }
                        if(jump == 0 && (bd == 1 || be == -1))
                            Mix_Resume(2);

                        // variavel que faz subir
                        int subir, limitador;
                        subir = 0;
                        limitador = 0;

                        //Se o sprite nao colidir com nenhuma escada
                        if(!(SpriteRect.x >= 410 && SpriteRect.x <= 420 && SpriteRect.y <= 520 && SpriteRect.y >= 420))
                            notescada = 1;

                        //Se o sprite colidir com a escada 1
                        if (SpriteRect.x >= 410 && SpriteRect.x <= 420 && SpriteRect.y <= 520 && SpriteRect.y >= 420)
                        {
                            subir = 1;
                            limitador = 1;
                            notescada = 0;
                        }
                        //Se o sprite colidir com a escada 2
                        if (SpriteRect.x >= 610 && SpriteRect.x <= 620 && SpriteRect.y <= 420 && SpriteRect.y >= 317)
                        {
                            subir = 1;
                            limitador = 2;
                            notescada = 0;
                        }
                        //Se o sprite colidir com a escada 3
                        if (SpriteRect.x >= 140 && SpriteRect.x <= 150 && SpriteRect.y <= 317 && SpriteRect.y >= 220)
                        {
                            subir = 1;
                            limitador = 3;
                            notescada = 0;
                        }
                        //Se o sprite colidir com a escada 4
                        if (SpriteRect.x >= 515 && SpriteRect.x <= 530 && SpriteRect.y <= 220 && SpriteRect.y >= 117)
                        {
                            subir = 1;
                            limitador = 4;
                            notescada = 0;
                        }
                        //Se o sprite colidir com a escada 5
                        if (SpriteRect.x >= 270 && SpriteRect.x <= 280 && SpriteRect.y <= 117 && SpriteRect.y >= 20)
                        {
                            subir = 1;
                            limitador = 5;
                            notescada = 0;
                        }

                        // permite que suba
                        if (subir == 1 && invencibilidade == 0)
                        {
                            //permitir que o sprite suba ou desca
                            if ( e.type == SDL_KEYDOWN )
                                 switch( e.key.keysym.sym )
                                {
                                    case SDLK_UP:
                                    annaRect.y=140;
                                    if ( annaRect.x == 754)
                                        annaRect.x = 0;
                                    else
                                        annaRect.x+=58;
                                    bc = -1; //anda pra cima
                                    break;

                                    case SDLK_DOWN:
                                    annaRect.y=140;
                                    if ( annaRect.x == 754)
                                        annaRect.x = 0;
                                    else
                                        annaRect.x+=58;
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
                                    e_esc2 = 0;
                                    Mix_Pause(3);
                                    break;

                                    case SDLK_DOWN:
                                    bb = 0; //para de andar pra baixo
                                    e_esc1 = 0;
                                    Mix_Pause(3);
                                    break;

                                    default:
                                    break;
                                }
                        }
                        else
                        {
                            bc = 0;
                            bb = 0;
                            Mix_Pause(3);
                        }


                        //movimento do sprite pra cima ou baixo
                        if(bb == 1)
                            SpriteRect.y++;
                        if(bc == -1)
                            SpriteRect.y--;

                        if(bb == 1)
                            e_esc1++;
                        if(bc == -1)
                            e_esc2++;
                        //Toca a musica da subida na escada
                        if(e_esc1 == 1)
                            Mix_PlayChannel(3, m_escada, -1);
                        if(e_esc2 == 1)
                            Mix_PlayChannel(3, m_escada, -1);

                        //limita o movimento para baixo e cima
                        if (limitador == 1)
                        {
                            if(SpriteRect.y == 521)
                                SpriteRect.y -= 1;
                            if(SpriteRect.y == 419)
                                SpriteRect.y += 1;
                        }
                        else if (limitador == 2)
                        {
                            if(SpriteRect.y == 421)
                                SpriteRect.y -= 1;
                            if(SpriteRect.y == 316)
                                SpriteRect.y +=1;
                        }
                        else if (limitador == 3)
                        {
                            if(SpriteRect.y == 318)
                                SpriteRect.y -= 1;
                            if(SpriteRect.y == 219)
                                SpriteRect.y +=1;
                        }
                        else if (limitador == 4)
                        {
                            if(SpriteRect.y == 221)
                                SpriteRect.y -= 1;
                            if(SpriteRect.y == 116)
                                SpriteRect.y += 1;
                        }
                        else if (limitador == 5)
                        {
                            if(SpriteRect.y == 118)
                                SpriteRect.y -= 1;
                            if(SpriteRect.y == 19)
                                SpriteRect.y += 1;
                        }

                        //pulo
                        if(notescada != 0)
                        {
                            if ( e.type == SDL_KEYDOWN )
                                switch( e.key.keysym.sym )
                                {
                                    case SDLK_SPACE:
                                    if(invencibilidade == 0)
                                        pulo = 1;
                                    break;

                                    default:
                                    break;
                                }
                        }
                        if(pulo == 1)
                        {
                            e_pulo++;
                            jump++;
                        }
                        if(e_pulo == 1)
                        {
                            Mix_PlayChannel( 1, m_pulo, 0 );
                        }
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
                            e_pulo = 0;
                        }

                       if(pulocima == 1){
                            SpriteRect.y -= 2.5;
                            if (annaRect.y==0 || annaRect.y==280)
                                annaRect.x=0;
                            else if (annaRect.y==70 || annaRect.y==350)
                                annaRect.x=116;
                            annaRect.y=210;
                        }

                        if(pulobaixo == 1){
                            SpriteRect.y += 3;
                            if (annaRect.y==0 || annaRect.y==280 || annaRect.x==0)
                                annaRect.x=58;
                            else if (annaRect.y==70 || annaRect.y==350 || annaRect.x==116)
                                annaRect.x=174;
                            annaRect.y=210;
                        }

                        pulocima = 0;
                        pulobaixo = 0;

                        if (annaRect.y==210 && (SpriteRect.y==520 || SpriteRect.y==420 || SpriteRect.y==317 || SpriteRect.y==220 || SpriteRect.y==117 || SpriteRect.y==20))
                        {
                            if (annaRect.x==58 || annaRect.x==0)
                            {
                                annaRect.y=0;
                                annaRect.x=754;
                            }
                            else if (annaRect.x==174 || annaRect.x==116)
                            {
                                annaRect.y=70;
                                annaRect.x=0;
                            }
                        }

                        //limita as dimensoes da plataforma, impedindo que o sprite ande no nada
                        //extremidade esquerda 2, 4 e 6
                        if (SpriteRect.x<15 && ((SpriteRect.y<=520 && SpriteRect.y>420) || (SpriteRect.y<=317 && SpriteRect.y>220) || (SpriteRect.y<=117 && SpriteRect.y> 20)))
                            SpriteRect.x=15;

                        //extremidade esquerda 3 e 5
                        if(SpriteRect.x<130 && ((SpriteRect.y<=420 && SpriteRect.y>317) || (SpriteRect.y<=220 && SpriteRect.y>117)))
                           SpriteRect.x=130;

                        //extremidade direita 3 e 5
                        if(SpriteRect.x>730 && ((SpriteRect.y<=420 && SpriteRect.y>317) || (SpriteRect.y<=220 && SpriteRect.y>117)))
                           SpriteRect.x=730;

                        //extremidade direita 4 e 6
                        if(SpriteRect.x>630 && ((SpriteRect.y<=520 && SpriteRect.y>420) || (SpriteRect.y<=317 && SpriteRect.y>220)))
                           SpriteRect.x=630;

                        //extremidade direita 2
                        if(SpriteRect.x>590 && (SpriteRect.y<=117 && SpriteRect.y> 20))
                            SpriteRect.x=590;

                        //Aplica a imagem
                        SDL_BlitSurface( fundo, NULL, tela, &FRect );
                        SDL_BlitSurface( sprite, &annaRect, tela, &SpriteRect );
                        SDL_BlitSurface( elsa, &elsaRect, tela, &princesaRect);

                        //animacao da tocha e elsa
                        if (tempo%40==0)
                        {
                            elsaRect.x=30;
                            tocha.x=25;
                        }
                        else if (tempo%20==0)
                        {
                            tocha.x=0;
                            elsaRect.x=0;
                        }


                        if(pd_disp == 1)
                        {
                            SDL_BlitSurface(martelo, &tocha, tela, &HammerRect);
                            SDL_BlitSurface(martelo, &tocha, tela, &HammerRect2);
                        }
                        SDL_BlitSurface(life, NULL, tela, &LRect);

                        //partes do olaf
                        if(p1==1)
                            SDL_BlitSurface( olafp1, &olafimg, tela, &olaf1Rect );

                        if(p2==1)
                            SDL_BlitSurface( olafp2, &olafimg, tela, &olaf2Rect );

                        if(p3==1)
                            SDL_BlitSurface( olafp3, &olafimg, tela, &olaf3Rect );

                        if(p4==1)
                            SDL_BlitSurface( olafp4, &olafimg, tela, &olaf4Rect );

                        if(p5==1)
                            SDL_BlitSurface( olafp5, &olafimg, tela, &olaf5Rect );

                        //pontuacao do olaf
                        if(colisao(&SpriteRect, &olaf1Rect) == 1 && SpriteRect.y==520)
                        {
                            p1=0;
                            Pontuacao += 10;
                        }
                        if(colisao(&SpriteRect, &olaf2Rect) == 1 && SpriteRect.y==420)
                        {
                            p2=0;
                            Pontuacao += 10;
                        }
                        if(colisao(&SpriteRect, &olaf3Rect) == 1 && SpriteRect.y==420)
                        {
                            p3=0;
                            Pontuacao += 10;
                        }
                        if(colisao(&SpriteRect, &olaf4Rect) == 1 && SpriteRect.y==317)
                        {
                            p4=0;
                            Pontuacao += 10;
                        }
                        if(colisao(&SpriteRect, &olaf5Rect) == 1 && SpriteRect.y==220)
                        {
                            p5=0;
                            Pontuacao += 10;
                        }

                        // animacao olaf
                        if (tempo%70==0)
                            olafimg.y=70;

                        else if (tempo%35==0)
                            olafimg.y=0;

                        //cria a contagem dos barris
                        tempo ++;
                        if (tempo == 50)
                            b1 = 1;
                        if (tempo == 350)
                            b2 = 1;
                        if (tempo == 650)
                            b3 = 1;
                        if (tempo == 950)
                            b4 = 1;
                        if (tempo == 1250)
                            b5 = 1;
                        if (tempo == 1550)
                            b6 = 1;
                        if (tempo == 1800)
                            b7 = 1;

                        //aplica os barris na tela
                        if (b1 == 1 && aux_poder != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect );
                        if (b2 == 1 && aux_poder2 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect2 );
                        if (b3 == 1 && aux_poder3 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect3 );
                        if (b4 == 1 && aux_poder4 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect4 );
                        if (b5 == 1 && aux_poder5 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect5 );
                        if (b6 == 1 && aux_poder6 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect6 );
                        if (b7 == 1 && aux_poder7 != 1)
                            SDL_BlitSurface( bola_de_neve, &bnimg, tela, &BRect7 );

                        //camuflagem pro desaparecimento da neve
                        SDL_BlitSurface( neve, NULL, tela, &NRect );

                        //vilao
                        SDL_BlitSurface( vilao, &marshmallow, tela, &vilaoRect);

                    //bola de neve "barril" 1
                    if (b1 == 1)
                    {
                        if(rotas1 == 1)
                            mb1 = mov_barril2(BRect);
                        if(rotas1 == 2)
                            mb1 = mov_barril3(BRect);
                    }
                    if (b2 == 1)
                        mb2 = mov_barril(BRect2);
                    if (b3 == 1)
                        mb3 = mov_barril(BRect3);
                    if (b4 == 1)
                        mb4 = mov_barril(BRect4);
                    if (b5 == 1)
                        mb5 = mov_barril(BRect5);
                    if (b6 == 1)
                        mb6 = mov_barril(BRect6);
                    if (b7 == 1)
                    {
                        if(rotas2 == 1)
                            mb7 = mov_barril3(BRect7);
                        if(rotas2 == 2)
                            mb7 = mov_barril2(BRect7);
                    }

                                        //faz com que o score apareça na tela
                    MensagemScore = TTF_RenderText_Solid( fonte, "Score:", { 150, 188, 224 } );
                    SDL_BlitSurface(MensagemScore , NULL, tela, &MSRect );

                    sprintf(CharPontuacao, "%d" , Pontuacao);
                    MensagemPontScore = TTF_RenderText_Solid( fonte, CharPontuacao, { 150, 188, 224 } );
                    SDL_BlitSurface(MensagemPontScore , NULL, tela, &MPSRect );

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

                     //movimento da bola de neve
                    if (tempo%2==0)
                    {

                           if(bnimg.x==224)
                                bnimg.x=0;
                            else
                                bnimg.x+=32;

                    }

                    //movimentos do vilao
                    if((BRect.y==150 && BRect.x>150 && BRect.x<180) || (BRect2.y==150 && BRect2.x>150 && BRect2.x<180) || (BRect3.y==150 && BRect3.x>150 && BRect3.x<180) ||
                       (BRect4.y==150 && BRect4.x>150 && BRect4.x<180) || (BRect5.y==150 && BRect5.x>150 && BRect5.x<180) || (BRect6.y==150 && BRect6.x>150 && BRect6.x<180) ||
                       (BRect7.y==150 && BRect7.x>150 && BRect7.x<180))
                        marshmallow.x=290;
                    else if(tempo%40==0)
                        marshmallow.x=145;
                    else if(tempo%20==0)
                        marshmallow.x=0;

                    //aplica o movimento do barril
                    bspeed = 2;
                    aplica_mov_barril(&BRect, bspeed, mb1);
                    aplica_mov_barril(&BRect2, bspeed, mb2);
                    aplica_mov_barril(&BRect3, bspeed, mb3);
                    aplica_mov_barril(&BRect4, bspeed, mb4);
                    aplica_mov_barril(&BRect5, bspeed, mb5);
                    aplica_mov_barril(&BRect6, bspeed, mb6);
                    aplica_mov_barril(&BRect7, bspeed, mb7);

                    if(BRect.x == 150 && BRect.y == 150)
                        rotas1++;
                    if(rotas1 == 3)
                        rotas1 = 1;
                    if(BRect7.x == 150 && BRect7.y == 150)
                        rotas2++;
                    if(rotas2 == 3)
                        rotas2 = 1;

                    //faz perder uma vida
                    if(invencibilidade == 0)
                    {
                        if(colisao(&SpriteRect,&BRect) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect2) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect3) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect4) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect5) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect6) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                        if(colisao(&SpriteRect,&BRect7) == 1)
                        {
                            menosvida = 1;
                            e_atingiu++;
                        }
                    }
                    if(e_atingiu == 1)
                        Mix_PlayChannel(6, m_atingiu, 0);
                    if(menosvida == 1)
                    {
                        e_atingiu = 0;
                        vida -= 1; // diminui uma vida
                        menosvida = 0;
                        pulo = 0; //poe as variaveis do pulo em zero
                        jump = 0;
                        pulobaixo = 0;
                        pulocima = 0;
                        SpriteRect.x = 80; //poe as variaveis do sprite em zero
                        SpriteRect.y = 520;
                        tempo = 0; //poe as variaveis da bola de neve em zero
                        BRect.x = 150;
                        BRect.y = 150;
                        BRect2.x = 150;
                        BRect2.y = 150;
                        BRect3.x = 150;
                        BRect3.y = 150;
                        BRect4.x = 150;
                        BRect4.y = 150;
                        BRect5.x = 150;
                        BRect5.y = 150;
                        BRect6.x = 150;
                        BRect6.y = 150;
                        BRect7.x = 150;
                        BRect7.y = 150;
                        mb1 = 0;
                        mb2 = 0;
                        mb3 = 0;
                        mb4 = 0;
                        mb5 = 0;
                        mb6 = 0;
                        mb7 = 0;
                        b1 = 0;
                        b2 = 0;
                        b3 = 0;
                        b4 = 0;
                        b5 = 0;
                        b6 = 0;
                        b7 = 0;
                    }
                    if(vida == 0)
                        gameover = 1;

                    //faz o game over
                    if(gameover == 1)
                    {
                        SDL_BlitSurface( fim, NULL, tela, &GORect );

                        //faz com que o score apareça na tela
                        MensagemScore = TTF_RenderText_Solid( fonte, "Your Score:", { 0, 0, 0 } );
                        SDL_BlitSurface(MensagemScore , NULL, tela, &MSRect2 );

                        sprintf(CharPontuacao, "%d" , Pontuacao);
                        MensagemPontScore = TTF_RenderText_Solid( fonte, CharPontuacao, { 0, 0, 0 } );
                        SDL_BlitSurface(MensagemPontScore , NULL, tela, &MPSRect2 );

                        //faz com que a maior pontuação apareça na tela
                        MgmHighScore = TTF_RenderText_Solid( fonte, "High Score:", { 0, 0, 0 } );
                        SDL_BlitSurface(MgmHighScore , NULL, tela, &MHSRect2 );

                        sprintf(CharHighPt, "%d" , MaiorPont1);
                        MgmHighPtScore = TTF_RenderText_Solid( fonte, CharHighPt, { 0, 0, 0 } );
                        SDL_BlitSurface(MgmHighPtScore , NULL, tela, &MHPSRect2 );

                        e_perdeu++;
                        //Toca a musica do game over do jogo
                        if(e_perdeu == 1)
                            Mix_PlayMusic( m_perdeu, 0 );
                        vida = 0;
                        if ( e.type == SDL_KEYDOWN )
                             switch( e.key.keysym.sym )
                            {
                                case SDLK_s:
                                vida = 3;
                                menosvida = 0;
                                SpriteRect.x = 80;
                                SpriteRect.y = 520;
                                e_atingiu = 0;
                                tempo = 0;
                                pulo = 0; //poe as variaveis do pulo em zero
                                jump = 0;
                                pulobaixo = 0;
                                pulocima = 0;
                                BRect.x = 150;
                                BRect.y = 150;
                                BRect2.x = 150;
                                BRect2.y = 150;
                                BRect3.x = 150;
                                BRect3.y = 150;
                                BRect4.x = 150;
                                BRect4.y = 150;
                                BRect5.x = 150;
                                BRect5.y = 150;
                                BRect6.x = 150;
                                BRect6.y = 150;
                                BRect7.x = 150;
                                BRect7.y = 150;
                                mb1 = 0;
                                mb2 = 0;
                                mb3 = 0;
                                mb4 = 0;
                                mb5 = 0;
                                mb6 = 0;
                                mb7 = 0;
                                b1 = 0;
                                b2 = 0;
                                b3 = 0;
                                b4 = 0;
                                b5 = 0;
                                b6 = 0;
                                b7 = 0;
                                jump = 0;
                                gameover = 0;
                                aux_indice3 = 1;
                                c = 6;
                                NovoRecorde = 0;
                                goto NewHighScores;
                                break;

                                case SDLK_n:
                                gameover = 0;
                                vida = 3;
                                menosvida = 0;
                                SpriteRect.x = 80;
                                SpriteRect.y = 520;
                                tempo = 0;
                                e_atingiu = 0;
                                BRect.x = 150;
                                BRect.y = 150;
                                BRect2.x = 150;
                                BRect2.y = 150;
                                BRect3.x = 150;
                                BRect3.y = 150;
                                BRect4.x = 150;
                                BRect4.y = 150;
                                BRect5.x = 150;
                                BRect5.y = 150;
                                BRect6.x = 150;
                                BRect6.y = 150;
                                BRect7.x = 150;
                                BRect7.y = 150;
                                mb1 = 0;
                                mb2 = 0;
                                mb3 = 0;
                                mb4 = 0;
                                mb5 = 0;
                                mb6 = 0;
                                mb7 = 0;
                                b1 = 0;
                                b2 = 0;
                                b3 = 0;
                                b4 = 0;
                                b5 = 0;
                                b6 = 0;
                                b7 = 0;
                                jump = 0;
                                aux_indice3 = 2;
                                NovoRecorde = 0;
                                c = 6;
                                goto NewHighScores;
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
                            SpriteRect.x = 80;
                            SpriteRect.y = 520;
                            e_atingiu = 0;
                            tempo = 0;
                            BRect.x = 150;
                            BRect.y = 150;
                            BRect2.x = 150;
                            BRect2.y = 150;
                            BRect3.x = 150;
                            BRect3.y = 150;
                            BRect4.x = 150;
                            BRect4.y = 150;
                            BRect5.x = 150;
                            BRect5.y = 150;
                            BRect6.x = 150;
                            BRect6.y = 150;
                            BRect7.x = 150;
                            BRect7.y = 150;
                            mb1 = 0;
                            mb2 = 0;
                            mb3 = 0;
                            mb4 = 0;
                            mb5 = 0;
                            mb6 = 0;
                            mb7 = 0;
                            b1 = 0;
                            b2 = 0;
                            b3 = 0;
                            b4 = 0;
                            b5 = 0;
                            b6 = 0;
                            b7 = 0;
                            jump = 0;
                            c = 4;
                            NovoRecorde = 0;
                            goto youwin;
                        }

                        //faz a pontuação no pulo
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect2,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect3,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect4,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect5,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect6,jump ,Aux_P);
                        Aux_P = calc_pont(bd, be,&SpriteRect, &BRect7,jump ,Aux_P);

                        if((Aux_P == 50 || Aux_P == 70 || Aux_P == 90 || Aux_P == 120 || Aux_P == 130 || Aux_P == 140 || Aux_P == 150) && jump == 0)
                        {
                            Pontuacao += 50;
                            Aux_P = 0;
                            Mix_PlayChannel(5, m_jpoint, 0);
                        }
                        if(jump == 0)
                            Aux_P = 0;

                        //cria os poder da anna
                        if( colisao(&SpriteRect,&HammerRect) == 1 || colisao(&SpriteRect,&HammerRect2) == 1)
                        {
                            e_hammer++;
                            if(e_hammer == 1)
                            {
                                Mix_PlayChannel(4, m_hammer, 0 );
                                Mix_PlayMusic(m_ptheme, -1);
                            }
                            pd_disp = 0;
                            invencibilidade = 1;
                        }
                        if (pd_disp == 0)
                            tempo_pd2++;
                        if(tempo_pd2 == 1000)
                        {
                            pd_disp = 1;
                            tempo_pd2 = 0;
                            e_hammer = 0;
                            Mix_PlayMusic(musica, -1);
                        }
                        if(invencibilidade == 1)
                        {
                            tempo_pd1++;
                            if(colisao(&SpriteRect,&BRect) == 1)
                            {
                                if(aux_poder != 1)
                                    Pontuacao += 25;
                                aux_poder = 1;
                                e_poder1++;
                                if(e_poder1 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect2) == 1)
                            {
                                if(aux_poder2 != 1)
                                    Pontuacao += 25;
                                aux_poder2 = 1;
                                e_poder2++;
                                if(e_poder2 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect3) == 1)
                            {
                                if(aux_poder3 != 1)
                                    Pontuacao += 25;
                                aux_poder3 = 1;
                                e_poder3++;
                                if(e_poder3 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect4) == 1)
                            {
                                if(aux_poder4 != 1)
                                    Pontuacao += 25;
                                aux_poder4 = 1;
                                e_poder4++;
                                if(e_poder4 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect5) == 1)
                            {
                                if(aux_poder5 != 1)
                                    Pontuacao += 25;
                                aux_poder5 = 1;
                                e_poder5++;
                                if(e_poder5 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect6) == 1)
                            {
                                if(aux_poder6 != 1)
                                    Pontuacao += 25;
                                aux_poder6 = 1;
                                e_poder6++;
                                if(e_poder6 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                            if(colisao(&SpriteRect,&BRect7) == 1)
                            {
                                if(aux_poder7 != 1)
                                    Pontuacao += 25;
                                aux_poder7 = 1;
                                e_poder7++;
                                if(e_poder7 == 1)
                                    Mix_PlayChannel(5, m_poder, 0 );
                            }
                        }
                        if(tempo_pd1 == 1000)
                        {
                            tempo_pd1 = 0;
                            invencibilidade = 0;
                        }

                        if(BRect.x == 50 && BRect.y == 150 && aux_poder == 1)
                        {
                            aux_poder = 0;
                            e_poder1 = 0;
                        }
                        if(BRect2.x == 50 && BRect2.y == 150 && aux_poder2 == 1)
                        {
                            aux_poder2 = 0;
                            e_poder2 = 0;
                        }
                        if(BRect3.x == 50 && BRect3.y == 150 && aux_poder3 == 1)
                        {
                            aux_poder3 = 0;
                            e_poder3 = 0;
                        }
                        if(BRect4.x == 50 && BRect4.y == 150 && aux_poder4 == 1)
                        {
                            aux_poder4 = 0;
                            e_poder4 = 0;
                        }
                        if(BRect5.x == 50 && BRect5.y == 150 && aux_poder5 == 1)
                        {
                            aux_poder5 = 0;
                            e_poder5 = 0;
                        }
                        if(BRect6.x == 50 && BRect6.y == 150 && aux_poder6 == 1)
                        {
                            aux_poder6 = 0;
                            e_poder6 = 0;
                        }
                        if(BRect7.x == 50 && BRect7.y == 150 && aux_poder7 == 1)
                        {
                            aux_poder7 = 0;
                            e_poder7 = 0;
                        }

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
                                e_botao++;
                            }
                            else
                                e_botao = 0;
                            //Toca a musica do botao
                            if(e_botao == 1)
                                 Mix_PlayChannel( 0, m_botao, 0 );
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
                        Mix_Pause(3);
                        SDL_BlitSurface (zerar, NULL, tela, &ZRect );

                        //faz com que o score apareça na tela
                        MensagemScore = TTF_RenderText_Solid( fonte, "Your Score:", { 0, 0, 0 } );
                        SDL_BlitSurface(MensagemScore , NULL, tela, &MSRect2 );

                        sprintf(CharPontuacao, "%d" , Pontuacao);
                        MensagemPontScore = TTF_RenderText_Solid( fonte, CharPontuacao, { 0, 0, 0 } );
                        SDL_BlitSurface(MensagemPontScore , NULL, tela, &MPSRect2 );

                        //faz com que a maior pontuação apareça na tela
                        MgmHighScore = TTF_RenderText_Solid( fonte, "High Score:", { 0, 0, 0 } );
                        SDL_BlitSurface(MgmHighScore , NULL, tela, &MHSRect2 );

                        sprintf(CharHighPt, "%d" , MaiorPont1);
                        MgmHighPtScore = TTF_RenderText_Solid( fonte, CharHighPt, { 0, 0, 0 } );
                        SDL_BlitSurface(MgmHighPtScore , NULL, tela, &MHPSRect2 );

                        //Toca a musica de fundo do zeramento
                        e_venceu++;
                        if(e_venceu == 1)
                            Mix_PlayMusic( m_venceu, -1 );
                        winner++;
                        if(winner == 300)
                        {
                            aux_indice3 = 2;
                            e_venceu = 0;
                            c = 6;
                            goto NewHighScores;
                        }
                    }
                    pontuacoesm:
                    if (c == 5)
                    {
                        SDL_BlitSurface (recordes, NULL, tela, &RECRect );
                        SDL_BlitSurface (voltar, NULL, tela, &VRect );

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
                                e_botao++;
                            }
                            else
                                e_botao = 0;
                            //Toca a musica do botao
                            if(e_botao == 1)
                                 Mix_PlayChannel( 0, m_botao, 0 );
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
                        Mix_Pause(3);
                        e_perdeu = 0;
                        if(Pontuacao > MaiorPont3 || Pontuacao > MaiorPont2 || Pontuacao > MaiorPont1)
                        {
                            SDL_BlitSurface(TelaNN, NULL, tela, &TNNRect);
                            e_nrec++;
                            if(e_nrec == 1)
                                Mix_PlayMusic(m_novorec, 0);
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
                            if(NovoRecorde == 0 && indice != 0)
                            {
                                Nome[0] = ' ';
                                indice = 0;
                                NovoRecorde = 1;
                            }
                            NovoNome = TTF_RenderText_Solid( fonte, Nome , { 0, 0, 0 } );
                            if(NovoRecorde != 0)
                                SDL_BlitSurface( NovoNome, NULL, tela, &NNRect);
                            }
                            else
                            {
                                indice = 0;
                                //abre o arquivo para que os dados possam ser alterados
                                HighArq = fopen("HighScores.txt", "w");
                                if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2 && Pontuacao > MaiorPont1)
                                {
                                    strcpy(Nome3, Nome2);
                                    fprintf(HighArq, "%s\n", Nome3);
                                    N3 = TTF_RenderText_Solid( fonte, Nome3, { 0, 0, 0 } );

                                    strcpy(Nome2, Nome1);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    N2 = TTF_RenderText_Solid( fonte, Nome2, { 0, 0, 0 } );

                                    strcpy(Nome1, Nome);
                                    fprintf(HighArq, "%s\n", Nome1);
                                    N1 = TTF_RenderText_Solid( fonte, Nome1, { 0, 0, 0 } );

                                }
                                else if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2)
                                {
                                    strcpy(Nome3, Nome2);
                                    fprintf(HighArq, "%s\n", Nome3);
                                    N3 = TTF_RenderText_Solid( fonte, Nome3, { 0, 0, 0 } );

                                    strcpy(Nome2, Nome);
                                    fprintf(HighArq, "%s\n", Nome2);
                                    N2 = TTF_RenderText_Solid( fonte, Nome2, { 0, 0, 0 } );

                                    fprintf(HighArq, "%s\n", Nome1);
                                    N1 = TTF_RenderText_Solid( fonte, Nome1, { 0, 0, 0 } );
                                }
                                else if(Pontuacao > MaiorPont3)
                                {
                                    strcpy(Nome3, Nome);
                                    fprintf(HighArq, "%s\n", Nome3);
                                    N3 = TTF_RenderText_Solid( fonte, Nome3, { 0, 0, 0 } );

                                    fprintf(HighArq, "%s\n", Nome2);
                                    N2 = TTF_RenderText_Solid( fonte, Nome2, { 0, 0, 0 } );

                                    fprintf(HighArq, "%s\n", Nome1);
                                    N1 = TTF_RenderText_Solid( fonte, Nome1, { 0, 0, 0 } );
                                }
                                else
                                {
                                    byebye = 0;
                                }

                                if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2 && Pontuacao > MaiorPont1)
                                {
                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 0, 0, 0 } );

                                    MaiorPont2 = MaiorPont1;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 0, 0, 0 } );

                                    MaiorPont1 = Pontuacao;
                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 0, 0, 0 } );
                                }
                                else if(Pontuacao > MaiorPont3 && Pontuacao > MaiorPont2)
                                {
                                    MaiorPont3 = MaiorPont2;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 0, 0, 0 } );

                                    MaiorPont2 = Pontuacao;
                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 0, 0, 0 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 0, 0, 0 } );
                                }
                                else if(Pontuacao > MaiorPont3)
                                {
                                    MaiorPont3 = Pontuacao;
                                    sprintf(CharMaiorPont3, "%d", MaiorPont3);
                                    fprintf(HighArq, "%s\n", CharMaiorPont3);
                                    CP3 = TTF_RenderText_Solid( fonte, CharMaiorPont3, { 0, 0, 0 } );

                                    sprintf(CharMaiorPont2, "%d", MaiorPont2);
                                    fprintf(HighArq, "%s\n", CharMaiorPont2);
                                    CP2 = TTF_RenderText_Solid( fonte, CharMaiorPont2, { 0, 0, 0 } );

                                    sprintf(CharMaiorPont1, "%d", MaiorPont1);
                                    fprintf(HighArq, "%s\n", CharMaiorPont1);
                                    CP1 = TTF_RenderText_Solid( fonte, CharMaiorPont1, { 0, 0, 0 } );
                                }
                                byebye = 1;
                                fclose(HighArq);
                            }
                            if(byebye == 1)
                            {
                                Pontuacao = 0;
                                e_nrec = 0;
                                strcpy(Nome, "     ");
                                if(aux_indice3 == 1)
                                {
                                    c = 7;
                                    byebye = 0;
                                    goto begingame;
                                }
                                if(aux_indice3 == 2)
                                {
                                    c = 8;
                                    byebye = 0;
                                    goto inicio;
                                }
                            }
                        }
                        else
                        {
                            Pontuacao = 0;
                            e_nrec = 0;
                            if(aux_indice3 == 1)
                            {
                                c = 7;
                                byebye = 0;
                                goto begingame;
                            }
                            if(aux_indice3 == 2)
                            {
                                c = 8;
                                byebye = 0;
                                goto inicio;
                            }
                        }
                    }

                    if(c == 7)
                    {
                        //Toca a musica de fundo do jogo
                        Mix_PlayMusic( musica, -1 );
                        c = 2;
                    }

                    if(c == 8)
                    {
                        //Toca a musica de fundo do jogo (tela inicial)
                        Mix_PlayMusic( m_fundo, -1 );
                        c = 0;
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

